#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <vector>

std::mutex mtx; // Mutex for shared buffer
std::condition_variable cv; // Condition variable for synchronization
std::queue<int> buffer;
const size_t buffer_size = 5; // Maximum buffer size
bool done = false; // Variable to indicated completion from producer

// Producer function
void producer()
{
    for(int i = 0; i <= 20; i++)
    {
        // Aquire the lock
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if buffer is full
        // If the buffer is full, the lock on mutex is released.
        cv.wait(lock, []{return buffer.size() < buffer_size;});

        // Wait condition satisfied and hence lock is aquired on the mutex

        // Add item to the buffer
        buffer.push(i);
        std::cout<<"Produced: "<<i<<std::endl;

        // Unlock the mutex
        lock.unlock();

        // Notify other threads waiting on the condition variable
        cv.notify_all();

        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    // Notify consumers that production is done
    {
        // Aquired lock on the mutex
        std::unique_lock<std::mutex> lock(mtx);

        // Mark the variable to mark the production done
        done = true;

        // Notify all the threads waiting on the condition variable
        cv.notify_all();
    }
}

// Consumer function
void consumer(int id)
{
    while(true)
    {
        // Aquire lock on the mutex
        std::unique_lock<std::mutex> lock(mtx);

        // Wait on the codition
        cv.wait(lock, []{return !buffer.empty() || done;});

        // Lock aquired
        if(!buffer.empty())
        {
            int item = buffer.front();
            buffer.pop();
            std::cout<<"Consuer "<<id<<" consumed: "<<item<<std::endl;
        }
        else if (done == true)
        {
            // Producer is done producing the items and hence break from the loop
            // Destructor of unqiue_lock will take care of releasing the lock
            break; 
        }

        // Release the lock
        lock.unlock();

        // Notify other threads waiting on the codition variable
        cv.notify_all();

        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main()
{
    std::vector<std::thread> threads;

    threads.push_back(std::thread(producer));

    for(int i = 0; i < 2; i++)
        threads.push_back(std::thread(consumer, i));
    
    for(auto &thread : threads)
    {
        if(thread.joinable() == true) thread.join();
    }

    std::cout<<"All task completed.\n";
    return 0;
}