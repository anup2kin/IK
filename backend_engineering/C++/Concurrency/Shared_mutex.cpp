#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>

class Shared_mutex
{
public:
    Shared_mutex():readers_count(0), writer_waiting(false), writer_active(false) {}

    void shared_lock()
    {
        // Acquire lock on the mutex
        std::unique_lock<std::mutex> lock(mtx);

        // Release mutex and wait until none of the writers are active or waiting
        cv.wait(lock, [this](){return writer_active == false && writer_waiting == false;});

        // Lock aquired

        // Increase the number of readers
        ++readers_count;
    }

    void shared_unlock()
    {
        // Acquire lock on the mutex
        std::lock_guard<std::mutex> lock(mtx);

        // Decrease the reader count
        --readers_count;

        // If the reader count reaches 0, just notify the writer thread
        if(readers_count == 0) cv.notify_one();
    }

    void lock()
    {
        // Acquire lock on the mutex
        std::unique_lock<std::mutex> lock(mtx);

        // Mark that the writer want to now lock the mutex
        writer_waiting = true;

        // Release the lock and wait until the reader count is 0 and none of the write threads are active
        // who have acquired the lock already
        cv.wait(lock, [this](){ return readers_count == 0 && writer_active == false;});

        // Lock acquired

        // Mark that now no writer is waiting for the lock
        writer_waiting = false;
        // Mark that now no writer is active
        writer_active = true;
    }

    void unlock()
    {
        // Acquire the lock
        std::lock_guard<std::mutex> lock(mtx);

        // Mark that the this writer is no longer active
        writer_active = false;

        // Notify all the reader and writer threads
        cv.notify_all();
    }

protected:
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<int> readers_count; // Number of readers holding the shared lock
    bool writer_waiting = false; // Flag to check if writer is wating for the lock
    bool writer_active = false; // Flag to indicate if writer has the lock

};
