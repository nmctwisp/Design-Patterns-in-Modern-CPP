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


// mixin inheritance
// perfect forwarding

template <typename T>
struct ColoredShape : T {
	std::string color;
	ColoredShape() = default;

	template <typename ...Args>
	ColoredShape(const std::string& color, Args ...args)
		: color(color), T(std::forward<Args>(args) ...) {};

	std::string str() const override {
		std::ostringstream oss;
		oss << T::str() << " has the color " << color;

		return oss.str();
	}
};

template <typename T>
struct TransparentShape : T {
	uint8_t transparency;

	TransparentShape() = default;

	template <typename ...Args>
	TransparentShape(const uint8_t transparency, Args ...args)
		: transparency(transparency), T(std::forward<Args>(args) ...) {};

	std::string str() const override {
		std::ostringstream oss;
		oss << T::str()
			<< " has "
			<< static_cast<float>(transparency) / 255.f * 100.f
			<< "% transparency";

		return oss.str();
	};

};

// concepts is a c++20 feature
//template <typename T>
//concept IsAShape = std::is_base_of<Shape, T>::value;
//
//template <IsAShape T>
//struct TransparentShape : T {
//	uint8_t transparency;
//
//	TransparentShape() = default;
//
//	template <typename ...Args>
//	TransparentShape(const uint8_t transparency, Args ...args)
//		: transparency(transparency), T(std::forward<Args>(args) ...) {};
//
//	std::string str() const override {
//		std::ostringstream oss;
//		oss << T::str()
//			<< " has "
//			<< static_cast<float>(transparency) / 255.f * 100.f
//			<< "% transparency";
//
//		return oss.str();
//	};
//
//};

int main() {
	ColoredShape<Circle> green_circle{"green", 5.f};
	std::cout << green_circle << std::endl;

	TransparentShape<ColoredShape<Square>> bis{ 0, "blue", 10.f };
	bis.color = "light blue";
	bis.side = 21;
	std::cout << bis.str() << std::endl;

	return 0;
}