#include <iostream>
#include <cstring>

char* str_concat(const char* str1, const char* str2) {
    // Calculate the length of the new string
    size_t len1 = std::strlen(str1);
    size_t len2 = std::strlen(str2);
    size_t totalLen = len1 + len2 + 1; // +1 for the null terminator

    // Allocate memory for the new string
    char* result = new char[totalLen];

    // Copy the first string to the result
    std::strcpy(result, str1);

    // Concatenate the second string to the result
    std::strcat(result, str2);

    return result;
}

int main() {
    const char* str1 = "Hello, ";
    const char* str2 = "world!";
    char* result = str_concat(str1, str2);

    std::cout << result << std::endl;

    // Don't forget to free the allocated memory
    delete[] result;

    return 0;
}