#include <iostream>

class Rectangle {
protected:
	int width, height;
public:
	Rectangle(const int width, const int height)
		: width{ width }, height{ height } {}

	int get_width() const { return width; }
	int get_height() const { return height; }

	virtual void set_width(const int width) {
		this->width = width;
	}

	virtual void set_height(const int height) {
		this->height = height;
	}

	int area() const {
		return width * height;
	}
};

class Square : public Rectangle {
public:
	Square(int size)
		: Rectangle{ size, size } {};

	void set_width(const int width) override {
		this->width = height = width;
	}

	void set_height(const int height) override {
		this->height = width = height;
	}
};

struct RectangleFactory {
	static Rectangle create_rectangle(int w, int h) { return Rectangle{ w, h };  }
	static Rectangle create_square(int size) { 
		// Even though we're constructing a Square type and returning the instantiated square, 
		// since: 
		// 1) the return type of the method is Rectangle 
		// 2) Square inherits from Rectangle
		// the object returned will be an Rectangle type.
		return Square{ size }; 
	}
};

void process(Rectangle& r) {
	int w = r.get_width();
	r.set_width(10);

	std::cout << "Expected area = " << (w * 10) << ", got " << r.area() << std::endl;
}

int main() {
	// Liskov Substituion Principle: Let f(x) be a property provable about objects x of type T. 
	// Then func(y) should be true for objects of y of type S, where S is a subtype of T.

	Rectangle r{ 5,5 };
	process(r);

	// This is an example of a broken Liskov Substitution Principle, because process does not behave
	// the same way for Square as it does for Rectangle. This is because we overrode the setters for 
	// the Square type.

	Square s{ 5 };
	process(s);
	
	// We can resolve this in many ways:
	// - Break the inheritance relationship between Rectangle and Square
	// - Get rid of the Square type and use a data member to indicate if a Rectangle is a square
	// - Create a Factory Class

	auto x = RectangleFactory::create_square(5);
	return 0;
}