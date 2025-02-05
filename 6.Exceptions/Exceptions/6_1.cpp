#include <iostream>
#include <stdexcept>

void initialize() {
    std::cout << "Initialization successful." << std::endl;
    // Uncomment the next line to simulate an exception during initialization
    // throw std::runtime_error("Initialization failed!");
}

void do_work() {
    std::cout << "Doing work..." << std::endl;
    // Uncomment the next line to simulate an exception during work
    throw std::runtime_error("Work failed!"); // <-- Uncomment this line
}

void cleanup() {
    std::cout << "Cleanup done." << std::endl;
}

void func() {
    try {
        initialize(); // perform initialization
        do_work(); // do some work
    } catch (const std::exception& e) {
        // Handle exceptions if necessary
        std::cerr << "An error occurred: " << e.what() << std::endl;
        cleanup(); // perform any necessary cleanup
        throw; // rethrow the exception
    }
    cleanup(); // perform any necessary cleanup
}

int main() {
    try {
        func();
    } catch (const std::exception& e) {
        std::cerr << "Caught exception in main: " << e.what() << std::endl;
    }
    return 0;
}