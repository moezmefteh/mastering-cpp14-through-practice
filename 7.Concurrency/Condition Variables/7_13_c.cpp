#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <queue>

class IntQueue {
private:
    std::list<int> queue;
    std::mutex queue_mutex;
    std::condition_variable queueCV;
    static std::mutex cout_mutex;

public:
    int get() {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queueCV.wait(lock, [this] { return !queue.empty(); });
        int data = queue.front();
        queue.pop_front();
        {
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            std::cout << "get i = " << data << std::endl;
        }
        return data;
    }

    void put(int x) {
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            queue.push_back(x);
        }
        queueCV.notify_one();
        {
            std::lock_guard<std::mutex> cout_lock(cout_mutex);
            std::cout << "put i = " << x << std::endl;
        }
    }
};

// Static mutex for protecting std::cout
std::mutex IntQueue::cout_mutex;

void producer(IntQueue& queue, int start) {
    for (int i = start; i < start + 1000; i++) {
        queue.put(i);  // Put item into queue
        std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Sleep for 1 ms
    }
    queue.put(-1);  // Signal consumer to stop
}

void consumer(IntQueue& queue) {
    while (true) {
        int value = queue.get();  // Get item from queue
        if (value == -1) break;   // Stop if signal value is received
    }
}

int main() {
    IntQueue queue;
    std::vector<std::thread> threads;

    // Limit number of threads to avoid overwhelming the system
    const int num_threads = 5;  // Change this number to manage system load

    // Create a smaller number of producer threads
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(producer, std::ref(queue), i * 1000);
    }

    // Create a smaller number of consumer threads
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back(consumer, std::ref(queue));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
