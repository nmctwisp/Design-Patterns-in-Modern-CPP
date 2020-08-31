#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


class PointV1 {

	PointV1(float x, float y) : x(x), y(y) {};

public:
	float x;
	float y;

	// PointFactory must be a friend in order to access the private Constructor
	// This can violate the Open-Close Principal if the Point class was initially
	// implemented w/o a factory and it would require you to make modifications 
	// to the Point class in order to support a factory.

	// An alternative is to make the Constructor public
	friend class PointFactory;
	friend std::ostream& operator<<(std::ostream& os, const PointV1& p);

};

struct PointFactory{
	// Separating the factory methods from the underlying Point class

	// Factory Method to create a Cartesian Point
	static PointV1 NewCartesian(float x, float y) {
		return { x, y };
	}

	// Factory Method to create a Polar Point
	static PointV1 NewPolar(float rho, float theta) {
		return { rho * std::cos(theta), rho * std::sin(theta) };
	}
};

std::ostream& operator<<(std::ostream& os, const PointV1& point) {
	os << "x: " << point.x << std::endl;
	os << "y: " << point.y << std::endl;

	return os;
}

int main() {

	auto p{ PointFactory::NewPolar(5, M_PI_4) };

	std::cout << p;


	return 0;
}