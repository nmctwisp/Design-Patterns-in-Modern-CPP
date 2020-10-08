#include <iostream>
#include <vector>

struct GraphicObjects {
	virtual void draw() = 0;
};

struct Circle : public GraphicObjects {
	void draw() override {
		std::cout << "Circle" << std::endl;
	}
};

struct Group : public GraphicObjects{
	std::string name;
	std::vector<GraphicObjects*> objects;

	Group(const std::string& name) :name(name) {};

	void draw() override {
		std::cout << "Group " << name << " contains: " << std::endl;
		for (auto& o : objects) {
			o->draw();

		}
	};
};

int main() {
	Group root("root");
	Circle c1, c2;
	root.objects.push_back(&c1);

	Group subgroup("sub");
	subgroup.objects.push_back(&c2);

	root.objects.push_back(&subgroup);

	root.draw();
	return 0;
}