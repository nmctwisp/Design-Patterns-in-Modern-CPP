#include <iostream>
#include <memory>

// Simple implementation of the Prototype Design Pattern

struct Address {
	std::string street;
	std::string city;
	int suite;

	Address(std::string street, std::string city, int suite)
		: street(street), city(city), suite(suite) {};

	Address(const Address& other)
		: street(other.street), city(other.city), suite(other.suite) {};

	friend std::ostream& operator<<(std::ostream& os, const Address& contact);
};

struct Contact {
	std::string name;
	std::unique_ptr<Address> address;

	Contact(const std::string name, std::unique_ptr<Address> address)
		: name(name), address{ std::move(address) } {};

	Contact(const Contact& other)
		: name{ other.name }, 
		address{ std::make_unique<Address>(*other.address) } 
	{}

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
	os << "Address: " << *contact.address << std::endl;

	return os;
}

int main() {

	Contact john{ "John Doe", std::make_unique<Address>("123 East Dr", "London", 123) };
	//Contact jane{ "Jane Smith", Address("123 East Dr", "London", 103) };
	Contact jane = john; //shallow copy
	jane.name = "Jane Smith";
	jane.address->suite = 103;

	std::cout << john << std::endl;
	std::cout << jane << std::endl;
}