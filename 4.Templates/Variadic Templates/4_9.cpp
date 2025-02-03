#include <iostream>

// Base case: function template for a single argument
template<typename T>
T minimum(T a) {
    return a;
}

// Variadic template function
template<typename T, typename... Args>
T minimum(T a, Args... args) {
    T min_of_rest = minimum(args...);
    return (a < min_of_rest) ? a : min_of_rest;
}

int main() {
    std::cout << minimum(6, 5, 4, 3, 2) << std::endl; // Output: 2
    std::cout << minimum(1.0, 2.0, 3.0, 4.0, 5.0, 6.0) << std::endl; // Output: 1.0
    return 0;
}