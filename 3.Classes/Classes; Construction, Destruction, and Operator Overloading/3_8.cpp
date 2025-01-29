#include <iostream>
#include <vector>
#include <stdexcept>

class IntArray2 {
private:
    std::vector<int> data;
    size_t width;
    size_t height;

public:
    IntArray2() : width{0}, height{0} {
        std::cout << "Default constructor\n";
    }

    IntArray2(size_t width, size_t height) : width{width}, height{height}, 
    data(static_cast<size_t>(width) * static_cast<size_t>(height)) {
        std::cout << "Parametrized constructor\n";
    }

    IntArray2(const IntArray2& other) : width{other.width}, height{other.height}, data{other.data} {
        std::cout << "Copy constructor\n";
    }

    IntArray2(IntArray2&& other) noexcept : width{std::move(other.width)}, height{std::move(other.height)}, data{std::move(other.data)} {
        other.width = 0;
        other.height = 0;
        std::cout << "Move constructor\n";
    }

    size_t getWidth() const {
        return width;
    }

    size_t getHeight() const {
        return height;
    }

    size_t getSize() const {
        return data.size();
    }

    int& operator()(size_t x, size_t y) {
        if (x >= width || y >= height) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[y * width + x];
    }

    const int& operator()(size_t x, size_t y) const {
        if (x >= width || y >= height) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[y * width + x];
    }

    friend std::ostream& operator<<(std::ostream& os, const IntArray2& arr) {
        for (size_t y = 0; y < arr.height; ++y) {
            for (size_t x = 0; x < arr.width; ++x) {
                os << arr(x, y) << " | ";
            }
            os << '\n';
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, IntArray2& arr) {
        for (size_t y = 0; y < arr.height; ++y) {
            for (size_t x = 0; x < arr.width; ++x) {
                if (!(is >> arr(x, y))) {
                    throw std::runtime_error("Input stream error");
                }
            }
        }
        return is;
    }

    ~IntArray2() = default;
};

int main() {
    IntArray2 arr(3, 2);
    std::cout << "Width: " << arr.getWidth() << std::endl;
    std::cout << "Height: " << arr.getHeight() << std::endl;
    std::cout << "Size: " << arr.getSize() << std::endl;

    // Fill the array with values
    for (size_t y = 0; y < arr.getHeight(); ++y) {
        for (size_t x = 0; x < arr.getWidth(); ++x) {
            arr(x, y) = static_cast<int>(y * arr.getWidth() + x);
        }
    }

    // Print the array
    std::cout << "Array contents:" << std::endl << arr;

    // Test stream extraction
    std::cout << "Enter " << arr.getSize() << " integers to fill the array:" << std::endl;
    std::cin >> arr;

    // Print the array again
    std::cout << "Updated array contents:" << std::endl << arr;

    return 0;
}