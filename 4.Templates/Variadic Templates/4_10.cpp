#include <iostream>

template<typename T>
T sum(T a){
    return a;
}
template<typename T, typename... Args>
T sum(T a, Args... args){
    return a + sum(args...);
}

int main(){
    std::cout << sum(1, 2, 4) << std::endl;
    std::cout <<  sum(2.0, 1.0, 1.0, 0.5) << std::endl;

    return 0;
}