#include "MutantStack.hpp"
#include <iostream>
#include <iterator>
#include <list>
#include <stack>
#include <string>
#include <vector>

int main() {
  std::cout << "Subject Tests (deque<int>): \n";

  MutantStack<int> mstack;
  mstack.push(5);
  mstack.push(17);
  std::cout << mstack.top() << std::endl;
  mstack.pop();
  std::cout << mstack.size() << std::endl;
  mstack.push(3);
  mstack.push(5);
  mstack.push(737);
  mstack.push(0);
  MutantStack<int>::iterator it = mstack.begin();
  MutantStack<int>::iterator ite = mstack.end();
  ++it;
  --it;
  while (it != ite) {
    std::cout << *it << std::endl;
    ++it;
  }
  std::stack<int> s(mstack);
////////////////////////////////////////////////////////
  std::cout << "Subject Tests (list<int>): \n";

  MutantStack<int, std::list<int> > mstack_list;
  mstack_list.push(5);
  mstack_list.push(17);
  std::cout << mstack_list.top() << std::endl;
  mstack_list.pop();
  std::cout << mstack.size() << std::endl;
  mstack_list.push(3);
  mstack_list.push(5);
  mstack_list.push(737);
  mstack_list.push(0);
  MutantStack<int, std::list<int> >::iterator it_list = mstack_list.begin();
  MutantStack<int, std::list<int> >::iterator ite_list = mstack_list.end();
  ++it_list;
  --it_list;
  while (it_list != ite_list) {
    std::cout << *it_list << std::endl;
    ++it_list;
  }
////////////////////////////////////////////////////////
  std::cout << "My Tests : (vector<float>)\n";

  MutantStack<float, std::vector<float> > mstack2;
  mstack2.push(3.5f);
  mstack2.push(5.32f);
  mstack2.push(737.45f);
  mstack2.push(0.0f);
  MutantStack<float, std::vector<float> >::iterator it2 = mstack2.begin();
  MutantStack<float, std::vector<float> >::iterator ite2 = mstack2.end();
  while (it2 != ite2) {
    std::cout << *it2 << std::endl;
    ++it2;
  }
////////////////////////////////////////////////////////
  std::cout << "My Tests : (list<string>)\n";

  MutantStack<std::string, std::list<std::string> > stack_string;
  stack_string.push("hello");
  stack_string.push("***");
  stack_string.push("world");
  MutantStack<std::string, std::list<std::string> >::iterator it3 = stack_string.begin(); 
   MutantStack<std::string, std::list<std::string> >::iterator ite3 = stack_string.end();
  while (it3 != ite3)
  {
    std::cout << *it3 << std::endl;
    ++it3;
  }

  return 0;
}
