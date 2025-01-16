#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <chrono>

std::shared_mutex mtx; // Shared mutex
int shared_resource = 0; // Shared resource that will be modified by writer and will be read by readers
bool done = false; // To communicate reader threads that writer is done

void reader(int id)
{
    while(true)
    {
        // Acquire shared lock
        std::shared_lock<std::shared_mutex> lock(mtx);

        // Lock acquired

        // Check if writer is done.
        if(done == true) break;

        // Read the shared data
        std::cout << "Reader " << id << " reads: " << shared_resource << std::endl;

        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void writer(int id)
{
    while(true)
    {
        // Acquire exclusive lock
        std::unique_lock<std::shared_mutex> lock(mtx);

        // Exclusive lock acquired

        // Check if all data has been written
        if(shared_resource == 20)
        {
            done = true;
            break;
        }

        // Write to shared resource
        shared_resource++;
        std::cout << "Writer " << id << " updates resource to: " << shared_resource << std::endl;

        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main()
{
    std::vector<std::thread> threads;

    // Start reader threads
    for(int i = 0; i < 3; i++) threads.emplace_back(reader, i);

    // Start writer thread
    threads.emplace_back(writer, 0);

    for(auto &thread : threads)
    {
        if(thread.joinable()) thread.join();
    }

    return 0;
}