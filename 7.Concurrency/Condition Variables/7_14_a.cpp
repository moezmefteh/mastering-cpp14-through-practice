#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int data = 0;
bool ready = false;

std::mutex mtx;
std::condition_variable cv;

void producer() {
    std::unique_lock<std::mutex> lock(mtx);
    data = 42;
    ready = true;
    std::cout << "Producer: Data produced: " << data << std::endl;
    cv.notify_one();
}

void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });
    std::cout << "Consumer: Data consumed: " << data << std::endl;
    ready = false;
}

int main() {

    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
