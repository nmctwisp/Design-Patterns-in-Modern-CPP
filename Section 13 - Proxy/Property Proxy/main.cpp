#include <iostream>

template <typename T>
struct Property {
	T value;

	Property(T value) { 
		*this = value; 
	};

	T operator=(T new_value) {
		std::cout << "Assignment!\n";
		value = new_value;

		return value;
	}

	operator T() {
		return value;
	};
};

struct Creature{
	Property<int> strength{ 10 };
	Property<int> agility{ 5 };
};

int main() {

	Creature c;
	c.strength = 11;
	int x = c.agility;

	return 0;
};