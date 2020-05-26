#pragma once
#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
protected:
	Person& person;
	explicit PersonBuilderBase(Person& person);

public:
	operator Person() const; // type casting from PersonBuilderBase to Person 

	// builder facades
	PersonAddressBuilder lives() const;
	PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase {
	Person person;
public:
	PersonBuilder();
};