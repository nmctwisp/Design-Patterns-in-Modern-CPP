#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

class PointV1 {

	PointV1(float x, float y) : x(x), y(y) {};
	float x;
	float y;

public:

	class PointFactory {
		PointFactory() = default;

	public:
		static PointV1 NewCartesian(float x, float y) {
			return { x, y };
		}

		static PointV1 NewPolar(float rho, float theta) {
			return { rho * std::cos(theta), rho * std::sin(theta) };
		}
	};

	friend std::ostream& operator<<(std::ostream& os, const PointV1& p);
};

class PointV2 {

	PointV2(float x, float y) : x(x), y(y) {};
	float x;
	float y;

	// Further hides/prevent direct access to the PointFactory class
	class PointFactory {
		PointFactory() = default;

	public:
		static PointV2 NewCartesian(float x, float y) {
			return { x, y };
		}

		static PointV2 NewPolar(float rho, float theta) {
			return { rho * std::cos(theta), rho * std::sin(theta) };
		}
	};

public:
	// in order to access the factory functionality, we add an static
	// PointFactory data memeber to the Point Class
	static PointFactory Factory;
	
	friend std::ostream& operator<<(std::ostream& os, const PointV2& p);
};

std::ostream& operator<<(std::ostream& os, const PointV1& point) {
	os << "x: " << point.x << std::endl;
	os << "y: " << point.y << std::endl;

	return os;
}

std::ostream& operator<<(std::ostream& os, const PointV2& point) {
	os << "x: " << point.x << std::endl;
	os << "y: " << point.y << std::endl;

	return os;
}

int main() {

	auto p1{ PointV1::PointFactory::NewPolar(5, M_PI_4) };
	std::cout << p1;
	
	auto p2{ PointV2::Factory.NewPolar(4, M_PI_4) };
	std::cout << p2;

	return 0;
}