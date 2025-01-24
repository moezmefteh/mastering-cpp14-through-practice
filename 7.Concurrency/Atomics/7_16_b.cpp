#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic_int data{0};
std::atomic_bool ready{false};

void writer(){
    for (int i=0;i<100;i++){
        data.store(i,std::memory_order_release);
        ready.store(true,std::memory_order_release);
        std::cout << "write data "<< i <<std::endl;
        while(ready.load(std::memory_order_acquire)){
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}
void reader(){
    for (int i=0;i<100;i++){
        while(!ready.load(std::memory_order_acquire)){
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::cout << "read data : " << data.load(std::memory_order_acquire) << std::endl;
        ready.store(false,std::memory_order_release);
    }
}
int main(){
    std::thread writer_thread(writer);
    std::thread reader_thread(reader);

    writer_thread.join();
    reader_thread.join();
    
    return 0;
}