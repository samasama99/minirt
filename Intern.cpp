#include "Intern.hpp"
#include <string>

typedef Form *(*MakeFunc)(std::string target);

Intern::Intern() {};

Intern::~Intern() {};

Intern::Intern(const Intern &src) {
    (void)src;
};

Intern &Intern::operator=(const Intern &src) {
    (void)src;
    return *this;
};

Form *makeShrubberyForm(std::string target) {
    std::cout << "Intern creates shrubbery creation form\n"; 
    return new ShrubberyCreationForm(target);
}
Form *makePresidentialPardonForm(std::string target) {
    std::cout << "Intern creates presidential pardon form\n"; 
    return new PresidentialPardonForm(target);
}
Form *makeRobotomyRequestForm(std::string target) {
    std::cout << "Intern creates robotomy form\n"; 
    return new RobotomyRequestForm(target);
}

Form *Intern::makeForm(std::string name, std::string target) {
    MakeFunc funcs[3] = {
      makeRobotomyRequestForm,
      makePresidentialPardonForm,
      makeShrubberyForm,
    };
    std::string types[3] = {
        "robotomy request",
        "presidential pardon request",
        "shrubbery creation request",
    };
    
    for (int type = 0; type < 3 ; ++type) {
      if (name == types[type]) return funcs[type](target);
    }

    std::cout << "Unknown type of forms\n";
    return NULL;
};

