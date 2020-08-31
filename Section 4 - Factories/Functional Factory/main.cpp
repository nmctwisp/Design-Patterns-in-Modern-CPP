#include <iostream>
#include "DrinkFactory.hpp"

int main() {

	DrinkWithVolumeFactory dVf{};
	auto c = dVf.make_drink("coffee");

	return 0;
}