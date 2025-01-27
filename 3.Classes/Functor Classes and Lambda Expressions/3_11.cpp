#include <iostream>
#include <memory>

class Quadratic{
public:
    Quadratic(double a = 0.0, double b = 0.0, double c = 0.0):
    a{a}, b{b}, c{c} {}

    Quadratic(const Quadratic& other):
    a{other.a}, b{other.b}, c{other.c} {}
    Quadratic& operator=(Quadratic& other){
        std::swap(a, other.a);
        std::swap(b, other.b);
        std::swap(c, other.c);
        return *this;
    }

    Quadratic(Quadratic&& other) noexcept : a{std::move(other.a)}, b{std::move(other.b)}, c{std::move(other.c)} {
        other.a = 0.0;
        other.b = 0.0;
        other.c = 0.0;
    }
    Quadratic& operator=(Quadratic&& other) noexcept {
        if (this != &other) {
            a = std::move(other.a);
            b = std::move(other.b);
            c = std::move(other.c);
            other.a = 0.0;
            other.b = 0.0;
            other.c = 0.0;
        }
        return *this;
    }
    ~Quadratic(){}

    double operator()(double x) const {
        return a*x*x + b*x + c;
    }

private:
    double a,b,c;
};
int main()
{
const Quadratic f(1.0, 2.0, 3.0);
const Quadratic g = f;
std::cout << f(1.0) << " " << g(1.0) << "\n";
}
