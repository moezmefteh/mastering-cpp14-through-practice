#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

std::mutex mutex_thread;

void f() {
    for (int i = 0; i < 128; i++) {
        {
            // Lock the mutex using scoped_lock
            std::lock_guard<std::mutex> lock(mutex_thread);
            std::cout << "Greetings from thread ";
            std::cout << " with id=0x" << std::hex << std::this_thread::get_id() << std::dec << std::endl;
        }
        // Sleep for 100 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    const int num_threads = 16; // Number of threads
    std::vector<std::thread> threads;

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(f);
        std::cout << "Thread number: " << i << " created." << std::endl;
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
