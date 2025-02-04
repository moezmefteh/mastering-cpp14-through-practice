#include <iostream>
#include <typeinfo>

struct Widget {};

void sampleFunction(int, int) {}

int main() {
    std::cout << "Type name for int: " << typeid(int).name() << std::endl;
    std::cout << "Type name for double: " << typeid(double).name() << std::endl;
    std::cout << "Type name for void (*)(int, int): " << typeid(void (*)(int, int)).name() << std::endl;
    std::cout << "Type name for struct Widget: " << typeid(Widget).name() << std::endl;

    return 0;
}