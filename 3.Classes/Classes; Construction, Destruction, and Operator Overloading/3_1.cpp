#include <iostream>

class Counter{
public:
    Counter(int count = 0): count{count} {
        track++;
    }
    // postfix
    Counter operator++(int){
        Counter tmp = *this;
        count+=3;
        return tmp;
    }
    Counter operator--(int){
        Counter tmp = *this;
        count-=2;
        return tmp;
    }
    // prefix increment
    Counter& operator++(){
        count+=5;
        return *this;
    }
    Counter& operator--(){
        count-=3;
        return *this;
    }
    int getValue(){
        return count;
    }
    static int getTrack(){
        return track;
    }
    ~Counter() {
        count--;
    }
private:
    int count;
    static int track;
};
int Counter::track = 0;

int main(){
    Counter c1(2);
    std::cout<< "track : " << Counter::getTrack() <<std::endl;
    std::cout<< "C1 init value " << c1.getValue() <<std::endl;
    // postfix
    c1++;
    std::cout<< "postfix increment " << c1.getValue() <<std::endl;
    c1--;
    std::cout<< "postfix decrement " << c1.getValue() <<std::endl;
    // prefix
    ++c1;
    std::cout<< "prefix increment " << c1.getValue() <<std::endl;
    --c1;
    std::cout<< "prefix decrement " << c1.getValue() <<std::endl;
    Counter c2(1);
    std::cout<< "track : " << Counter::getTrack() <<std::endl;
}