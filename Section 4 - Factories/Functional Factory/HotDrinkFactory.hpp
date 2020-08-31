#pragma once
#include <memory>

struct Tea;
struct Coffee;

struct HotDrinkFactory {  // AbstractFactory
	virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory {
	std::unique_ptr<HotDrink> make() const override {
		return std::make_unique<Tea>();
	};
};

struct CoffeeFactory : HotDrinkFactory {
	std::unique_ptr<HotDrink> make() const override {
		return std::make_unique<Coffee>();
	};
};