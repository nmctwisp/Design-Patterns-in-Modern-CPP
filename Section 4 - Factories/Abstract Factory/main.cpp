#include <iostream>
#include "HotDrink.hpp"
#include "HotDrinkFactory.hpp"
#include "DrinkFactory.hpp"

std::unique_ptr<HotDrink> make_drink(std::string drink_type) {
	// One way of using the Factory is via a function
	// Another way is via a class...see DrinkFactory.

	std::unique_ptr<HotDrink> drink;
	
	if (drink_type == "tea") {
		drink = std::make_unique<Tea>();
		drink->prepare(200);
	}

	else if (drink_type == "coffee") {
		drink = std::make_unique<Coffee>();
		drink->prepare(50);
	}

	return drink;
}

int main() {

	auto d = make_drink("tea");


	DrinkFactory df{};
	auto c = df.make_drink("coffee");

	return 0;
}