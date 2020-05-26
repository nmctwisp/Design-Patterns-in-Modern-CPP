#pragma once
#include <string>
#include <iostream>

class PersonBuilder;

class Person {

	// address 
	std::string street_address, post_code, city;

	// employment
	std::string company_name, position;
	int annual_income{ 0 };
	Person();

public:
	static PersonBuilder create();

	friend class PersonBuilder;
	friend class PersonJobBuilder;
	friend class PersonAddressBuilder;
	friend std::ostream& operator<<(std::ostream& os, const Person& person);

	Person(Person&& rhs) noexcept;
	Person& operator=(Person&& rhs) noexcept;
	~Person();
};