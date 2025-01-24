#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
class IntQueue {
private:
    std::list<int> queue;
    std::mutex queue_mutex;
    std::condition_variable queueCV;
    static std::mutex cout_mutex;
    
public:
	int get() {
		std::unique_lock<std::mutex> lock(queue_mutex);
		queueCV.wait(lock, [this] { return !queue.empty();});
		int data=queue.front();
		queue.pop_front();
		{
		    std::lock_guard<std::mutex> cout_lock(cout_mutex);
		    std::cout<<"get i = " << data << std::endl;
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
		    std::cout<<"put i = " << x << std::endl;

		}
	}
};

void producer(IntQueue& queue){
    for(int i=0;i<1000;i++){
        queue.put(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    queue.put(-1);
}
void consumer(IntQueue& queue){
    while(true){
        int value = queue.get();
        std::cout<<value << std::endl;
        if(value==-1) break;
    }
    queue.put(-1);
}
std::mutex IntQueue::cout_mutex;
int main()
{
    IntQueue IntQueue;
    std::vector<std::thread> threads;
	for(int i=0; i<1000; i++) {
		threads.emplace_back(producer, std::ref(IntQueue));
	}
    for(int i=0; i<1000; i++) {
		threads.emplace_back(consumer, std::ref(IntQueue));
	}
	for(auto& thread : threads){
	    thread.join();
	}
	return 0;
}