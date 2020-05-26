#pragma once
#include <string>
#include "PersonBuilder.h"


class PersonAddressBuilder : public PersonBuilderBase {
	typedef PersonAddressBuilder self;
public:
	explicit PersonAddressBuilder(Person& person);

	self& at(std::string stree_address);
	self& with_postcode(std::string post_code);
	self& in(std::string city);
};
