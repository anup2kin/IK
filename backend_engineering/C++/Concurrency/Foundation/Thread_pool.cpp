/*
    The main idea behind the thread pool is to use a queue with synchronization.
    The number of threads:
        1. If the tasks being done are non-blocking, it is better to have number of threads
            equal to the number of logical processor in the system. This kind of thread pool
            is known as performance based thread poo.
        2. If the task being done are blocking, it is better to have number of threads
            much higher then the number of logical processor in the system. This enables
            the system to schedule more tasks when a thread (or threads) blocks due
            to something (like IO).
*/

#include <iostream>
#include <exception>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

// Create a random number generator
std::random_device rd; // Seed for random number generator
std::mt19937 gen(rd()); // Mersenne Twister based random number generator
std::uniform_int_distribution<> dis(100, 1000);

int random_sleep_time(){
    // Generate a random sleep duration
    return dis(gen);
}


/*
    Class to be thrown when thread pool receives quit request.
*/
class Quit_exception : public std::exception {
public:
    const char* what() const noexcept override {
        return "Thread quitting!";
    }
};

/*
    Task is the object which represents a work to be done.
    The run function should not return any type. This is because, user of the thread pool,
    can return any thing and it will complicate the design.
    Instead of that, returning nothing will make the code simple and robost.
*/
class Task{
public:
    virtual ~Task() = default;
    virtual void run() = 0;
};

/*
    To shutdown the thread pool, one way is to create a special task object and add this to the same
    task qeueue.
    The run function in this special class will simply throw an exception, allowing the worker thread
    to identify quit condition and return. In case the run function of the task the worker thread is
    handling returns any exeception, we dont want to bring down the thread.
*/
class Quit_task: public Task{
    void run() override { throw Quit_exception(); }
};

/*
    This queue class provides synchornized access to the queue of tasks.
*/
template <typename Queue_data_type>
class Concurrent_queue{
public:
    void push(Queue_data_type t){
        std::unique_lock<std::mutex> lock(mtx);

        q.push(std::move(t));

        cv.notify_one();
    }

   Queue_data_type pop(){
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [this](){return !q.empty();});

        Queue_data_type t = std::move(q.front());
        q.pop();

        return t;
    }

    bool empty(){
        std::lock_guard<std::mutex> lock(mtx);
        return q.empty(); 
    }

private:
    std::queue<Queue_data_type> q;
    std::mutex mtx;
    std::condition_variable cv;
};


class Thread_pool{
private:
    Concurrent_queue<std::unique_ptr<Task>> q;
    std::vector<std::thread> threads;
    int num_threads;

private:
    void worker_thread(){
        while(true)
        {
            std::unique_ptr<Task> t = q.pop();

            try{
                t->run();
            }
            catch(const Quit_exception& e){
                return;
            }
            catch(const std::exception& e){}
        }
    }
public:
    Thread_pool(int num_threads){
        init(num_threads);
    }

    ~Thread_pool(){
        quit();
    }

    void init(int num_threads){
        this->num_threads = num_threads;

        for(int i = 0; i < this->num_threads; i++){
            threads.emplace_back(&Thread_pool::worker_thread, this);
        }
    }

    void add_work(std::unique_ptr<Task> t){
        q.push(std::move(t));
    }

    void quit()
    {
        for(int i = 0; i < num_threads; i++){
            q.push(std::make_unique<Quit_task>());
        }

        for(auto &thread : threads){
            if(thread.joinable()) thread.join();
        }

        threads.clear();
    }
};


class PrintTask : public Task {
    int id;
public:
    explicit PrintTask(int id) : id(id) {}
    void run() override {
        std::cout << "Task " << id << " is running on thread "
                  << std::this_thread::get_id() << std::endl;
        
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(random_sleep_time()));

    }
};

int main() {
    Thread_pool pool(4); // 4 threads

    for (int i = 0; i < 10; ++i) {
        pool.add_work(std::make_unique<PrintTask>(i));
    }

    pool.quit();
    return 0;
}