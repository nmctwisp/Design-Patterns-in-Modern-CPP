#include <iostream>

struct Address{
	std::string street;
	std::string city;
	int suite;

	Address(std::string street, std::string city, int suite) 
		: street(street), city(city), suite(suite) {};

	friend std::ostream& operator<<(std::ostream& os, const Address& contact);
};

struct Contact{
	std::string name;

	// in some cases one would choose to define the address data member as an
	// pointer; however, given the current implementation this would cause issues
	// as C++ would shallow copy by default and we did not provide a copy constructor
	// to create a new instance of address when a Contact is copied.
	Address address;

	Contact(const std::string name, Address& address)
		: name(name), address(address) {};

	friend std::ostream& operator<<(std::ostream& os, const Contact& contact);
};

std::ostream& operator<<(std::ostream& os, const Address& address) {
	os << "Street: " << address.street << std::endl;
	os << "City: " << address.city << std::endl;
	os << "Suite: " << address.suite;

	return os;
}

std::ostream& operator<<(std::ostream& os, const Contact& contact) {
	os << "Name: " << contact.name << std::endl;
	os << "Address: " << contact.address << std::endl;

	return os;
}

int main() {

	Contact john{ "John Doe", Address("123 East Dr", "London", 123) };
	//Contact jane{ "Jane Smith", Address("123 East Dr", "London", 103) };
	Contact jane = john;
	jane.name = "Jane Smith";
	jane.address.suite = 103;

	std::cout << john << std::endl;
	std::cout << jane << std::endl;
}