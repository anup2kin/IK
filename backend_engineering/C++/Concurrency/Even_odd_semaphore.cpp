#include <iostream>
#include <semaphore>
#include <thread>
#include <chrono>
#include <vector>

// Semaphore for even with max count as 1 and initial count as 0.
// Due to initial count as 0, even thread will wait since the count is 0.
std::counting_semaphore<1> sem_even(0);
// Semaphore for odd with max count as 1 and initial count as 1.
// Due to initial count as 1, odd thred will acquire the lock.
std::counting_semaphore<1> sem_odd(1);

int count = 1;

void print_even()
{
    while(true)
    {
        sem_even.acquire();

        if(count > 100)
        {
            sem_odd.release();
            break;
        }

        std::cout << "Even: " << count << std::endl;

        ++count;

        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        sem_odd.release();
    }
}

void print_odd()
{
    while(true)
    {
        sem_odd.acquire();

        if(count > 100)
        {
            sem_even.release();
            break;
        }

        std::cout << "Odd: " << count << std::endl;

        ++count;

        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        sem_even.release();
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
