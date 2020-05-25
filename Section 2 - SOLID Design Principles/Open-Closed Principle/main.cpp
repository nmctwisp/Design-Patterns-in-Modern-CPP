#include <string>
#include <vector>
#include <iostream>

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product {
	std::string name;
	Color color;
	Size size;
};

struct ProductFilter {

	typedef std::vector<Product*> Items;
	
	Items by_color(Items items, const Color color) {
		Items result;
		for (auto& i: items)
			if (i->color == color)
				result.push_back(i);
		return result;
	}

	Items by_size(Items items, const Size size) {
		Items result;
		for (auto& i : items)
			if (i->size == size)
				result.push_back(i);
		return result;
	}

	Items by_size_and_color(Items items, const Color color, const Size size) {
		Items result;
		for (auto& i : items)
			if (i->size == size && i->color == color)
				result.push_back(i);
		return result;
	}
};

// Open-Close Principle states that your system should be open for extensions but close for modifications
// * ProductFilter class does not satisfy this principle because with each new filter you would need to add 
// a new method to the class in order to support the new filter requirements.

// Enterprise Pattern 

template <typename T>
struct AndSpecification;

template <typename T>
struct OrSpecification;

template <typename T>
struct Specification {
	virtual ~Specification() = default;
	virtual bool is_satisfied(T* item) const = 0;

	// New: breaks Open-Close Principle if you add it post-hoc
	//AndSpecification<T> operator&&(Specification<T>&& other) {
	//	return AndSpecification<T>(*this, other);
	//}
};

template <typename T> 
AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second) {
	return { first, second };
}

template <typename T>
OrSpecification<T> operator||(const Specification<T>& first, const Specification<T>& second) {
	return { first, second };
}

template <typename T>
struct Filter {
	virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
	std::vector<Product*> filter(std::vector<Product*> items, Specification<Product>& spec) override {
		
		std::vector<Product*> result;
		for (auto& p : items)
			if (spec.is_satisfied(p))
				result.push_back(p);
		return result;
	}
};

struct ColorSpecification : Specification<Product> {
	Color color;

	ColorSpecification(Color color)
		: color{ color } {};
	
	bool is_satisfied(Product* item) const override {
		return item->color == color;
	}
};

struct SizeSpecification : Specification<Product> {
	Size size;

	SizeSpecification(Size size)
		: size{ size } {};

	bool is_satisfied(Product* item) const override {
		return item->size == size;
	}
};

template <typename T>
struct AndSpecification : Specification<T> {
	const Specification<T>& first_spec;
	const Specification<T>& second_spec;

	AndSpecification(const Specification<T>& first, const Specification<T>& second)
		: first_spec{ first }, second_spec{ second } {};
	
	bool is_satisfied(T* item) const override {
		return first_spec.is_satisfied(item) && second_spec.is_satisfied(item);
	}
};

template <typename T>
struct OrSpecification : Specification<T> {
	const Specification<T>& first_spec;
	const Specification<T>& second_spec;

	OrSpecification(const Specification<T>& first, const Specification<T>& second)
		: first_spec{ first }, second_spec{ second } {};

	bool is_satisfied(T* item) const override {
		return first_spec.is_satisfied(item) || second_spec.is_satisfied(item);
	}
};

int main() {
	Product apple{ "Apple", Color::green, Size::small };
	Product tree{ "Tree", Color::green, Size::large };
	Product house{ "House", Color::blue, Size::large };

	const std::vector<Product*> all{ &apple, &tree, &house };

	BetterFilter betterfilter;
	ColorSpecification spec_green{ Color::green };
	auto green_things = betterfilter.filter(all, spec_green);
	for (auto& thing : green_things)
		std::cout << thing->name << " is green.\n";

	SizeSpecification spec_large{ Size::large };

	AndSpecification<Product> spec_green_and_large{ spec_green, spec_large };
	auto  big_green_things = betterfilter.filter(all, spec_green_and_large);

	// alternate usage via operator&&
	auto spec_green_and_largev2 = spec_green && spec_large;
	for (auto& x : betterfilter.filter(all, spec_green_and_largev2))
		std::cout << x->name << " is green and large.\n";

	// warning: the following will compile but will NOT work
	// auto spec2 = SizeSpecification{Size::large} &&
	//              ColorSpecification{Color::blue};

	ColorSpecification spec_blue{ Color::blue };
	SizeSpecification size_small{ Size::small };
	auto spec_blue_or_small = spec_blue || size_small;
	for (auto& x : betterfilter.filter(all, spec_blue_or_small))
		std::cout << x->name << " is blue or small.\n";

	return 0;
}