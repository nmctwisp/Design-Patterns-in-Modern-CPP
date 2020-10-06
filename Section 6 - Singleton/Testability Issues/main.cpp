#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

class SingletonDatabase {

	std::map<std::string, int> capitals;

	SingletonDatabase() {
		std::cout << "Initializing Database" << std::endl;

		std::ifstream ifs("../capitals.txt");
		std::string name, pop_str;

		while (std::getline(ifs, name)) {
			std::getline(ifs, pop_str);
			int population = boost::lexical_cast<int>(pop_str);

			capitals[name] = population;
		}
	}
public:

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

struct SingletonRecordFinder {

	int total_population(const std::vector<std::string> names) {
		int result{ 0 };

		for (auto& name : names)
			result += SingletonDatabase::get().get_population(name);

		return result;
	}
};

TEST_CASE("SingletonRecordFinder") {

	SECTION("SingletonTotalPopulationTest") {

		// There is no issue with running this test; however,
		// we are strongly tied to the (production) database.
		// Since this is the case, we're essentially NOT unit testing 
		// the SingletonRecordFinder. Instead we're doing an 
		// integration test, as we're testing both SingletonRecordFinder &
		// SingletonDatabase operations.

		SingletonRecordFinder rf;
		std::vector<std::string> names{"Seoul", "Mexico City"};

		int tp = rf.total_population(names);

		REQUIRE(tp == 34900000);
	}
}