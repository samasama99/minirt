#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <cstdlib>
#include <iostream>


int main() {
  // subject test
  {
    Intern someRandomIntern;
    Form* rrf;
    rrf = someRandomIntern.makeForm("robotomy request", "Bender");
  }
  // my test
  {
      std::string types[4] = {
          "robotomy request",
          "presidential pardon request",
          "shrubbery creation request",
          "random",
      };
      Intern someRandomIntern;
      Form *tmp[4];
      for (int i = 0; i < 4 ; ++i) {
        tmp[i] = someRandomIntern.makeForm(types[i], "ouss");   
      }
  }

  // system("leaks Bur");

}
