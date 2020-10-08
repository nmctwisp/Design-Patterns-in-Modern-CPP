#pragma once
#include <string>

// Benefits of PIMPL
// -----------------

// 1) This implementation would allow you to hide the definitions for PersonImpl,
// while allowing users visibility to the API, but hide proprietary code. This
// is because the consumer/users would only have visibility to the header file, 
// but not the cpp file which all the definitions are saved.

// 2) Compilation Speed - PIMPL allows you to change the internal implementation without
// changing the API. So you don't need to rebuild much of the application


class PersonImpl;

class Person {

public:
	std::string name;
	PersonImpl* pimpl;
	
	Person();
	~Person();

	void greet();
};

