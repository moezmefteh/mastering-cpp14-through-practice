#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    
    int count{0};
    std::vector<double> vect{1,6,12.6,15,8};

    std::is_sorted(vect.begin(),vect.end(),[&](double a, double b){
        count++;
        return a < b;
    });

    std::cout<< count << std::endl;
    for(std::vector<double>::iterator it = vect.begin(); it!= vect.end(); it++){
        std::cout<< *it <<" ";
    }
    std::cout<<std::endl;
    return 0;
}