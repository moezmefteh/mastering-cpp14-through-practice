#include <iostream>
#include <cmath>
class Exponent{
public:
    Exponent(int a):a{a}{};
private: 
    int a;

friend Exponent operator^(double a, Exponent b){
    return Exponent(std::pow(b.a, a));
}
friend std::ostream& operator<<(std::ostream& os, Exponent& b){
    os<< b.a;
    return os;
}
};

int main()
{
    const double x = 2.0;
    Exponent y(4);
    auto it = x^y;
    std::cout << it << "\n";
    return 0;
}