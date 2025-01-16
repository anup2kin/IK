#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
int count = 1;
void print_even()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [](){return (count > 100) || (count % 2 == 0);});

        if(count > 100) break;

        std::cout << "Even: " << count << std::endl;

        ++count;

        cv.notify_one();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void print_odd()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [](){return (count > 100) || (count % 2 == 1);});

        if(count > 100) break;

        std::cout << "Odd: " << count << std::endl;

        ++count;

        cv.notify_one();

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