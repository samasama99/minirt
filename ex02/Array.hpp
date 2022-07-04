#ifndef ARRAY_H
#define ARRAY_H
#include <stdexcept>
template<typename T>
class Array {
  private:
    T *Begin;
    unsigned int n;
  public:
    Array() : Begin(NULL), n(0){};
    Array(unsigned int n) : Begin(new T[n]), n(n) {};
    Array(const Array &src)  : Begin(new T[src.n]), n(src.n) {
       memcpy(Begin, src.Begin, src.n * sizeof(T)); 
    } 
    Array &operator=(const Array &rh) {
        this->n = rh.n;
        this->Begin = new T[rh.n];
        memcpy(Begin, rh.Begin, rh.n * sizeof(T)); 
        return *this;
    }
    T &getElem(unsigned int index) {
        return Begin[index];
    }
    T getElem(unsigned int index) const {
        return Begin[index];
    }
    T &operator[](unsigned int index) {
        if (index >= n || index < 0) throw std::out_of_range("out of range");
        return getElem(index);
    }
    T operator[](unsigned int index) const {
        if (index >= n || index < 0) throw std::out_of_range("out of range");
        return getElem(index);
    }
    unsigned int size() const {
        return n;
    }
};
#endif
