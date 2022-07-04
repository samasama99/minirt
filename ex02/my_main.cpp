#include "Array.hpp"
#include <exception>
#include <iostream>
#include <string>

int main() {
    Array<int> arr(5);
    arr[0] = 1; 
    arr[1] = 2; 
    arr[2] = 3; 
    arr[3] = 4; 
    arr[4] = 5; 
    
    for (size_t i = 0; i < arr.size(); ++i) std::cout << arr[i] << " ";
    for (size_t i = 0; i < arr.size(); ++i) arr[i] *= arr[i];
    std::cout << '\n';
    for (size_t i = 0; i < arr.size(); ++i) std::cout << arr[i] << " ";
    std::cout << '\n';

    try {
        arr[5];
    } catch (std::exception &e) {
        std::cout << e.what() << '\n';
    }
    
    Array<std::string> arr_string(3);
    arr_string[0] = "Hello "; 
    arr_string[1] = "night "; 
    arr_string[2] = "city"; 
    Array<std::string> arr_string_cpy(arr_string);
    Array<std::string> arr_string_cpy2;
    arr_string_cpy2 = arr_string;
    
    arr_string[0] = "not Hello ";

    std::cout << "the original : " << arr_string[0] << '\n';
    std::cout << "the original : " << arr_string[1] << '\n';
    std::cout << "the original : " << arr_string[2] << '\n';
    std::cout << "the copy 1 : " << arr_string_cpy[0] << '\n';
    std::cout << "the copy 1 : " << arr_string_cpy[1] << '\n';
    std::cout << "the copy 1 : " << arr_string_cpy[2] << '\n';
    std::cout << "the copy 2 : " << arr_string_cpy2[0] << '\n';
    std::cout << "the copy 2 : " << arr_string_cpy2[1] << '\n';
    std::cout << "the copy 2 : " << arr_string_cpy2[2] << '\n';
}
