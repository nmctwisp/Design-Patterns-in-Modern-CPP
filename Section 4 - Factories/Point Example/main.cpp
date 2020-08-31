#include <iostream>
#include <cmath>


// Implementation w/o using a Factory Pattern

enum class PointType {
	cartesian,
	polar
};

struct PointV1{
	float x;
	float y;

	//Point(float x, float y) : x( x ), y( y ) { }

	PointV1(float a, float b, PointType type = PointType::cartesian) {
		
		if (type == PointType::cartesian) {
			x = a;
			y = b;
		}

		else {
			x = a * std::cos(b);
			y = a * std::sin(b);
		}
	};
};
int main() {



	return 0;
}