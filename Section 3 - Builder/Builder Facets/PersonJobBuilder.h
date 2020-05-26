#pragma once
#include <string>
#include "PersonBuilder.h"


class PersonJobBuilder :  public PersonBuilderBase {
	typedef PersonJobBuilder self;
public:
	explicit PersonJobBuilder(Person& person);

	self& at(std::string company_name);
	self& as_a(std::string position);
	self& earning(int annual_income);
};

