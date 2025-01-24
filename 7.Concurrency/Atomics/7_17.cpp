#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

std::atomic_ullong counter;
unsigned long long count;
void worker(){
    for(int i=0; i<20000; i++){
        counter++;
        count++;
    }
}
int main()
{
    counter=0;
    std::thread threads[4];

    for(int i=0; i<4; i++){
        threads[i]=std::thread(worker);
    }
    for(auto& thread : threads){
        thread.join();
    }
    std::thread t([&](){std::cout << counter << " | " << count << std::endl;});
    t.join();
    return 0;
}