#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>

class SingletonDatabase {
	
	std::map<std::string, int> capitals;

	SingletonDatabase() {
		std::cout << "Initializing Database" << std::endl;
		
		std::ifstream ifs("../capitals.txt");
		std::string name, pop_str;

		while (std::getline(ifs, name)){
			std::getline(ifs, pop_str);
			int population = boost::lexical_cast<int>(pop_str);

			capitals[name] = population;
		}
	}
public:

	// explicitly delete copy constructor and assignment operator to prevent
	// people from creating more than one instance.
	SingletonDatabase(const SingletonDatabase& other) = delete;
	SingletonDatabase& operator=(const SingletonDatabase& rhs) = delete;

	static SingletonDatabase& get() {

		static SingletonDatabase db;
		return db;
	}

	int get_population(const std::string& name) {

		return capitals[name];
	}
};

int main() {

	int x = 1;

	// This call will initially call the class constructor
	auto tokyo_population = SingletonDatabase::get().get_population("Tokyo");

	// This call would not need to construct database again and will already have
	// all the data from the prior call because it is a static variable.
	auto newyork_population = SingletonDatabase::get().get_population("Tokyo");

	return 0;
}