#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

struct HTMLBuilder;

struct HTMLElement {

	std::string name;
	std::string text;
	std::vector<HTMLElement> elements;
	const size_t indent_size = 2;

	HTMLElement() {};
	HTMLElement(const std::string& name, const std::string& text)
		: name{ name }, text{ text } {}

	std::string str(int indent = 0) const {
		std::ostringstream oss;
		std::string i(indent_size * indent, ' ');
		oss << i << '<' << name << '>' << std::endl;

		if (text.size() > 0)
			oss << std::string(indent_size * (indent + 1), ' ') << text << std::endl;

		for (const auto& e : elements)
			oss << e.str(indent + 1);

		oss << i << "</" << name << '>' << std::endl;

		return oss.str();
	}

	static std::unique_ptr<HTMLBuilder> build(std::string  root_name) {
		return std::make_unique<HTMLBuilder>(root_name);
	}
};

struct HTMLBuilder {
	HTMLElement root;

	HTMLBuilder(std::string root_name) {
		root.name = root_name;
	}

	//void to start with
	HTMLBuilder& add_child(std::string child_name, std::string child_text) {
		HTMLElement e{ child_name, child_text };
		root.elements.emplace_back(e);
		return *this;
	}

	// pointer based
	HTMLBuilder* add_child_2(std::string child_name, std::string child_text) {
		HTMLElement e{ child_name, child_text };
		root.elements.emplace_back(e);
		return this;
	}

	std::string str() {
		return root.str();
	}

	operator HTMLElement() const {
		return root;
	}
};


int main() {

	HTMLBuilder builder{ "ul" };
	builder.add_child("li", "hello");
	builder.add_child("li", "world");
	std::cout << builder.str() << std::endl;

	auto builder2 = HTMLElement::build("ul")
		->add_child_2("li", "hello")
		->add_child_2("li", "world");
	std::cout << builder2 << std::endl;

}