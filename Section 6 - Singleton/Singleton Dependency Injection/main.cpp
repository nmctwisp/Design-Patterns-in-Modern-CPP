#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

class Database {

public:
	virtual int get_population(const std::string& name) = 0;
};

class DummyDatabase : public Database {
	std::map<std::string, int> capitals;

public:
	DummyDatabase() {
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
		capitals["gamma"] = 3;
	}
	int get_population(const std::string& name) override {
		return capitals[name];
	}
};

class SingletonDatabase : public Database {

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

struct ConfigurableRecordFinder {
	Database& db;
	ConfigurableRecordFinder(Database& db) : db(db) {}

	int total_population(const std::vector<std::string> names) {
		
		int result{ 0 };
		for (auto& name : names)
			result += db.get_population(name);

		return result;
	}
};

TEST_CASE("RecordFinderTests") {

	SECTION("SingletonTotalPopulationTest") {

		SingletonRecordFinder rf;
		std::vector<std::string> names{ "Seoul", "Mexico City" };

		int tp = rf.total_population(names);

		REQUIRE(tp == 34900000);
	}

	SECTION("DependentTotalPopulationTest") {

		DummyDatabase db;
		ConfigurableRecordFinder rf{ db };

		std::vector<std::string> names{ "alpha", "gamma" };

		int tp = rf.total_population(names);

		REQUIRE(tp == 4);
	}
}
