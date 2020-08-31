#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


// Factory Methods Implementation

class PointV1 {
	// Note that the constructor is private
	PointV1(float x, float y) : x(x), y(y) {};

public:
	float x;
	float y;

	friend std::ostream& operator<<(std::ostream& os, const PointV1& p);

	// using static methods to create Factory Methods to create a Point.

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

	auto p{PointV1::NewPolar(5, M_PI_4)};

	std::cout << p;


	return 0;
}