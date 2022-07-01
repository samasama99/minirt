#include "data.hpp"
#include <iostream>
#include <stdint.h>

using std::cout;

uintptr_t serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
};

Data* deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
};

int main() {
    Data tmp = {10};
    cout << "value of x : ";
    cout << tmp.x << '\n';
    cout << "address of Data : ";
    cout << &tmp << '\n';
    uintptr_t s = serialize(&tmp);
    cout << "value of address of Data as unsigned long (uintptr_t) : ";
    cout << s << '\n';
    Data *des = deserialize(s);
    cout << "value of x after deserialize : ";
    cout << des->x << '\n';
}
