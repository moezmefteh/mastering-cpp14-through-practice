#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic_int data{0};

void writer(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    data.store(42,std::memory_order_release);
    std::cout << "write data "<< std::endl;
}
void reader(){
    while(!data.load(std::memory_order_acquire)){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "read data : " << data.load(std::memory_order_acquire) << std::endl;
}
int main(){
    std::thread writer_thread(writer);
    std::thread reader_thread(reader);

    writer_thread.join();
    reader_thread.join();
    
    return 0;
}