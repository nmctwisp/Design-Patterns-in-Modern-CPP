#include <iostream>
#include <sstream>

struct Shape {

	virtual std::string str() const = 0;
	friend std::ostream& operator<<(std::ostream& os, const Shape& self) {
		os << self.str();

		return os;
	};
};

struct Circle : Shape {
	float radius;

	Circle() = default;
	Circle(float radius) : radius(radius) {};
	
	std::string str() const override {
		std::ostringstream oss;
		oss << "A circle of radius " << radius;

		return oss.str();
	}

	void resize(float factor) { radius *= factor; }
};

struct Square : Shape {
	float side;

	Square() = default;
	Square(float side) : side(side) {};

	std::string str() const override {
		std::ostringstream oss;
		oss << "A square with side " << side;

		return oss.str();
	};
};

struct ColoredShape : Shape {
	Shape& shape;
	std::string color;

	ColoredShape(Shape& shape, const std::string& color)
		: shape(shape), color(color) {};

	std::string str() const override {
		std::ostringstream oss;
		oss << shape.str() << " has the color " << color;

		return oss.str();
	}
};

struct TransparentShape : Shape {
	Shape& shape;
	uint8_t transparency;

	TransparentShape(Shape& shape, uint8_t transparency)
		: shape(shape), transparency(transparency) {};

	std::string str() const override {
		std::ostringstream oss;
		oss << shape.str() 
			<< " has " 
			<< static_cast<float>(transparency) / 255.f * 100.f
			<< "% transparency";

		return oss.str();
	};
};

int main() {

	Square square{ 5 };
	ColoredShape red_square{ square, "red" };

	std::cout << square << std::endl << red_square << std::endl;

	TransparentShape my_square{ red_square, 51 };
	std::cout << my_square << std::endl;

	Circle circle{ 5 };
	ColoredShape red_circle{ circle, "red" };

	std::cout << circle << std::endl << red_circle << std::endl;

	TransparentShape my_circle{ red_circle, 51 };
	std::cout << my_circle << std::endl;
	return 0;
}