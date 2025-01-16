#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

std::mutex mtx;

// NOTE: Potential Issues with Single Condition Variable
// 1. Spurious wake-ups:
//      A single condition variable may cause both threads to wake up unnecessarily,
//      even if their respective conditions (count % 2 == 0 or count % 2 == 1) are not satisfied.
//      Extra context switches and unnecessary CPU usage due to repeated condition checks.
// 2. Loss of Granularity:
//      A single condition variable does not distinguish between the two threads’ specific needs
//      (odd or even turn). Each thread wakes up to recheck the condition, which introduces
//      some inefficiency.
std::condition_variable cv_even;
std::condition_variable cv_odd;

int count = 1;
void print_even()
{
    while(true)
    {
        // Acquire the mutex
        std::unique_lock<std::mutex> lock(mtx);

        // Release the mutex and wait if the count is still less than 100 or count is not even
        cv_even.wait(lock, [](){return (count > 100) || (count % 2 == 0);});

        // Lock acquired

        // Count is greater than 100. Even thread is done
        if(count > 100) break;

        // Print the value of count which is even
        std::cout << "Even: " << count << std::endl;

        // Increase the count value
        ++count;

        // Notify the odd thread waiting on the condition variable
        cv_odd.notify_one();

        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void print_odd()
{
    while(true)
    {
        // Acquire the lock
        std::unique_lock<std::mutex> lock(mtx);

        // Release the mutex lock and wait untill the count is > 100 or count is odd
        cv_odd.wait(lock, [](){return (count > 100) || (count % 2 == 1);});

        // Lock acquried

        // count is greater than 100. odd thread is done
        if(count > 100) break;

        // Print the value of count which is odd
        std::cout << "Odd: " << count << std::endl;

        // Increase the value of count
        ++count;

        // Notify the even thread
        cv_even.notify_one();

        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    std::vector<std::thread> threads;

    threads.emplace_back(print_even);
    threads.emplace_back(print_odd);

    for(auto &thread : threads)
    {
        if(thread.joinable()) thread.join();
    }

    return 0;
}