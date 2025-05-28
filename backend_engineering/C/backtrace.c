/*
    Here is the complete working code with the missing functions fully defined.
    This is simplified for demonstration, but preserves the core behavior of per-thread
    context tracking and crash diagnostics.

    The key to understanding how the stack trace shows the actual function calls leading
    up to the crash lies in how the backtrace() and backtrace_symbols_fd() functions work in Linux.
    Both backtrace() and backtrace_symbols_fd() are standard GNU extensions to the C library,
    provided by glibc on Linux systems. They are not part of the ISO C standard, but they are
    widely available on Linux and Unix-like systems that use glibc.

    Important Notes:
        These functions are only available on systems with glibc (i.e., Linux).
        They are not available on Windows.
        They may not show function names unless the binary includes debugging symbols.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <execinfo.h>
#include <sys/syscall.h>
#include <time.h>

// ========================
// Backtrace Message Struct
// ========================
typedef struct segv_backtrace_msg {
    const char *msg;
    struct segv_backtrace_msg *prev;
} segv_backtrace_msg_t;

// ==========================
// TLS Key and Init Flag
// ==========================
static pthread_key_t thread_context_key;
static int thread_context_initialized = 0;

// ==========================
// Thread Context Management
// ==========================

void segv_thread_context_sysinit(void)
{
    if (!thread_context_initialized) {
        pthread_key_create(&thread_context_key, NULL);
        thread_context_initialized = 1;
    }
}

void segv_thread_context_push_message(segv_backtrace_msg_t *msg)
{
    if (thread_context_initialized) {
        msg->prev = pthread_getspecific(thread_context_key);
        pthread_setspecific(thread_context_key, msg);
    }
}

void segv_thread_context_pop_message(void)
{
    if (thread_context_initialized) {
        segv_backtrace_msg_t *msg = pthread_getspecific(thread_context_key);
        if (msg) {
            pthread_setspecific(thread_context_key, msg->prev);
        }
    }
}

// ===============
// Signal Handler
// ===============

#define BT_STACK_MAX 32

void segv_backtrace(int sig)
{
    void *array[BT_STACK_MAX];
    int size;
    const char *sigstr = strsignal(sig);

    signal(sig, SIG_DFL);
    alarm(60);

    time_t now = time(NULL);
    struct tm tmnow;
    char strtm[32] = "";

    if (localtime_r(&now, &tmnow) != NULL)
        strftime(strtm, sizeof(strtm), "%Y/%m/%d %H:%M:%S", &tmnow);

    fprintf(stderr, "%s PID %d TID %ld received %s; stacktrace follows:\n",
            strtm, getpid(), syscall(SYS_gettid), sigstr);
    fflush(stderr);

    size = backtrace(array, BT_STACK_MAX);
    backtrace_symbols_fd(array, size, fileno(stderr));

    // Print thread context messages
    if (thread_context_initialized) {
        const segv_backtrace_msg_t *msg = pthread_getspecific(thread_context_key);
        while (msg) {
            fprintf(stderr, "Thread context message: %s\n", msg->msg);
            msg = msg->prev;
        }
    }

    // Raise signal again to terminate with core dump if enabled
    kill(getpid(), sig);
}

// =======================
// Register Signal Handler
// =======================
void segv_backtrace_init(void)
{
    signal(SIGSEGV, segv_backtrace);
    signal(SIGABRT, segv_backtrace);
    signal(SIGFPE,  segv_backtrace);
    signal(SIGBUS,  segv_backtrace);
}

// =======================
// Thread Function
// =======================
void *worker_thread(void *arg)
{
    segv_backtrace_msg_t ctx1 = { .msg = "Starting file indexing..." };
    segv_thread_context_push_message(&ctx1);

    sleep(1); // Simulate work

    segv_backtrace_msg_t ctx2 = { .msg = "Reading file header..." };
    segv_thread_context_push_message(&ctx2);

    // Simulate crash
    int *p = NULL;
    *p = 42;

    segv_thread_context_pop_message(); // ctx2
    segv_thread_context_pop_message(); // ctx1
    return NULL;
}

// =======================
// Main Function
// =======================
int main()
{
    pthread_t thread;

    segv_thread_context_sysinit();
    segv_backtrace_init();

    pthread_create(&thread, NULL, worker_thread, NULL);
    pthread_join(thread, NULL);

    return 0;
}
