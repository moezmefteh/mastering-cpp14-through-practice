#include <iostream>
#include <cstring>
#include <memory>

std::unique_ptr<char[]> str_concat(const char* str1, const char* str2) {
    // Calculate the length of the new string
    size_t len1 = std::strlen(str1);
    size_t len2 = std::strlen(str2);
    size_t totalLen = len1 + len2 + 1; // +1 for the null terminator

    // Allocate memory for the new string using unique_ptr
    std::unique_ptr<char[]> result(new char[totalLen]);

    // Copy the first string to the result
    std::strcpy(result.get(), str1);

    // Concatenate the second string to the result
    std::strcat(result.get(), str2);

    return result;
}

int main() {
    const char* str1 = "Hello, ";
    const char* str2 = "world!";
    std::unique_ptr<char[]> result = str_concat(str1, str2);

    std::cout << result.get() << std::endl;

    // No need to manually delete the allocated memory, unique_ptr will handle it

    return 0;
}