#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int data = 0;
bool ready = false;

std::mutex mtx;
std::condition_variable cv_producer, cv_consumer;

void producer() {
    for (int i = 0; i < 10000; i++) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until the consumer consumes the previous data
        cv_producer.wait(lock, [] { return !ready; });

        data = i;
        ready = true;
        std::cout << "Producer: Data produced: " << data << std::endl;
        cv_consumer.notify_one();
    }
}

void consumer() {
    for (int i = 0; i < 10000; i++) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until the producer produces new data
        cv_consumer.wait(lock, [] { return ready; });

        std::cout << "Consumer: Data consumed: " << data << std::endl;
        ready = false;
        cv_producer.notify_one();
    }
}

int main() {
    
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
