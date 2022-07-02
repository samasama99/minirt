#pragma once
#include <deque>
#include <stack>
#include <iostream>
template<typename T, typename Cont = std::deque<T> >
class MutantStack : public std::stack<T, Cont> {
  public:
    typedef typename std::stack<T, Cont>::container_type::iterator iterator;
    typedef typename std::stack<T, Cont>::container_type::reverse_iterator reverse_iterator;

    MutantStack() : std::stack<T, Cont>() {};
  
    MutantStack(const MutantStack &rh) : std::stack<T, Cont>(rh) {};

    MutantStack &operator=(const MutantStack &rh) {
      if (this == &rh) return *this;
      *this = rh;
      return *this;
    };

    ~MutantStack() {};

    iterator begin() {
      return this->c.begin();
    };

    iterator end() {
      return this->c.end();
    };

    reverse_iterator rbegin() {
      return this->c.rbegin();
    };

    reverse_iterator rend() {
      return this->c.rend();
    };
};
