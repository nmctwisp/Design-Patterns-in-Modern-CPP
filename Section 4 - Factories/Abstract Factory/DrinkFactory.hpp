#pragma once
#include "HotDrink.hpp"
#include "HotDrinkFactory.hpp"
#include <map>

// DrinkFactory is going to keep track the kind of factories we have generally
// DrinkFactory is a Concrete Factory implementation of the HotDrinksFactory Abstract Factory
// - facilitator of actually using all the different factories we've made, have them in a sort of map
// and exposing them to whoever is interested in making a drink.


class DrinkFactory {
	std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;

public:
	DrinkFactory() {
		hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
		hot_factories["tea"] = std::make_unique<TeaFactory>();
	};

	std::unique_ptr<HotDrink> make_drink(const std::string name) {

		auto drink = hot_factories[name]->make();
		drink->prepare(200);

		return drink;
	}
};

