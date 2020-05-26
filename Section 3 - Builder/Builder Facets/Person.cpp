#include "Person.h"
#include "PersonBuilder.h"

Person::Person() {
	std::cout << "Person created\n";
}

Person::Person(Person&& rhs) noexcept
	:	street_address{	std::move(rhs.street_address) },
		post_code{		std::move(rhs.post_code) },
		city{			std::move(rhs.city) },
		company_name{	std::move(rhs.company_name) },
		position{		std::move(rhs.position) },
		annual_income{ rhs.annual_income } {}

Person& Person::operator=(Person&& rhs) noexcept {
	if (this == &rhs)
		return *this;

	street_address = std::move(rhs.street_address);
	post_code = std::move(rhs.post_code);
	city = std::move(rhs.city);
	company_name = std::move(rhs.company_name);
	position = std::move(rhs.position);
	annual_income = rhs.annual_income;

	return *this;
}

Person::~Person() {
	std::cout << "Person destroyed\n";
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
	os << "street_address: " << person.street_address
		<< " post_code " << person.post_code
		<< " city: " << person.city
		<< " company_name: " << person.company_name
		<< " position: " << person.position
		<< " salary: " << person.annual_income;

	return os;
}

PersonBuilder Person::create() {
	return PersonBuilder();
}


