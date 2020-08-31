#pragma once
#include <iostream>

struct HotDrink {
	virtual ~HotDrink() = default;
	virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink {
	void prepare(int volume) override {
		std::cout << "Take a tea bag, boil water, pour ";
		std::cout << volume << "ml, add some lemon";
		std::cout << std::endl;
	}
};

struct Coffee : HotDrink {
	void prepare(int volume) override {
		std::cout << "Grind some beans, boil water, pour ";
		std::cout << volume << "ml, add cream, enjoy!";
		std::cout << std::endl;
	}
};