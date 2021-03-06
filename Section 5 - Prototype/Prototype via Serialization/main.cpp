#include <iostream>
#include <sstream>
#include <memory>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

// Prototype Factory
// Purpose: if you want to give the user of the API a prototype to work with

struct Address {
	std::string street;
	std::string city;
	int suite;

	Address() {};

	Address(std::string street, std::string city, int suite)
		: street(street), city(city), suite(suite) {};

	Address(const Address& other)
		: street(other.street), city(other.city), suite(other.suite) {};

	friend std::ostream& operator<<(std::ostream& os, const Address& contact);

private:
	friend class boost::serialization::access;

	template <typename archive>
	void serialize(archive& ar, const unsigned version) {
		ar & street;
		ar & city;
		ar & suite;
	}
};

struct Contact {
	std::string name;
	std::unique_ptr<Address> address;

	Contact() {};

	Contact(const std::string name, std::unique_ptr<Address> address)
		: name(name), address{ std::move(address) } {};

	Contact(const Contact& other)
		: name{ other.name },
		address{ std::make_unique<Address>(*other.address) }
	{}

	friend std::ostream& operator<<(std::ostream& os, const Contact& contact);
private:
	friend class boost::serialization::access;

	template <typename archive>
	void serialize(archive& ar, const unsigned version) {
		ar & name;
		ar & address;
	}
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

// This is one way to give users a prototype to work with
// Contact contact_proto{ "", std::make_unique<Address>("123 East Dr", "London", 0) };

// This is a better way
struct EmployeeFactory {

	// Gives us the ability to hide away someone of the constructor methods from Contact and make
	// users use the factory instead.
	static std::unique_ptr<Contact> new_main_office_employee(const std::string& name, const int suite) {

		// make new instance from this prototype with a predefined address
		static Contact proto{ "", std::make_unique<Address>("123 East Dr", "London", 0) };

		return new_employee(name, suite, proto);
	}

private:
	static std::unique_ptr<Contact> new_employee(const std::string& name, const int suite, const Contact& prototype) {
		auto new_contact = std::make_unique<Contact>(prototype);
		new_contact->name = name;
		new_contact->address->suite = suite;

		return new_contact;
	}

};

int main() {
	auto clone = [](const Contact& c) {
		std::ostringstream oss;
		boost::archive::text_oarchive output_archive{ oss };
		output_archive << c;
		std::string s{ oss.str() };
		
		std::cout << s << std::endl;

		std::istringstream iss;
		boost::archive::text_iarchive input_archive{ iss };
		Contact result;	
		input_archive >> result;

		return result;
	};

	auto john = EmployeeFactory::new_main_office_employee("john", 123);
	auto jane = clone(*john);
}