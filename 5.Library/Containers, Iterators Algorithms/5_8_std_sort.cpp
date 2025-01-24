#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::pair<T,T>& p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

int main(){
    using vec_it = std::vector<std::pair<double,double>>::iterator;
    using pr = std::pair<double,double>;
    std::vector<std::pair<double,double>> vec {{1.2,2.4},{5.3,0.5},{0.2,0.8}};
    
    std::sort(vec.begin(),vec.end(),[](pr a, pr b){
        return (a.first*a.second)<(b.first*b.second);
    });
    
    for(vec_it it=vec.begin();it!=vec.end();it++){
        std::cout<<*it;
    }
}