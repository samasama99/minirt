#ifndef INTERN_H
#define INTERN_H
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

#include <string>

class Intern {
public:
  Intern();
  ~Intern();
  Intern(const Intern &src);
  Intern &operator=(const Intern &src);
  Form *makeForm(std::string name, std::string target);
};
#endif
