#include <string>
#include <iostream>
#include <boost/flyweight.hpp>

struct User {
	boost::flyweight<std::string> first_name;
	boost::flyweight<std::string> last_name;

	User(const std::string& first_name, const std::string& last_name)
		: first_name(first_name), 
		  last_name(last_name) {};


};

int main(int num, char* av[]) {
	User user1{ "John", "Smith" };
	User user2{ "Jane", "Smith" };

	std::cout << user1.first_name << std::endl;
	
	std::cout << std::boolalpha;
	std::cout << ( &(user1.first_name.get()) == &(user2.first_name.get()) ) << std::endl;
	std::cout << ( &(user1.last_name.get()) == &(user2.last_name.get()) ) << std::endl;
	return 0;
}