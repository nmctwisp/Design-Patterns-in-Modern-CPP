#include "Person.hpp"
#include <iostream>

class PersonImpl {
public:
	void greet(Person* person);
};

void PersonImpl::greet(Person* person) {

	std::cout << "hello my name is " << person->name << std::endl;
}

void Person::greet() {
	pimpl->greet(this);
}