#include <string>
#include <boost/iterator/iterator_facade.hpp>
#include <algorithm>
#include <iostream>

struct Node {
	std::string value;
	Node* next{ nullptr };
	Node(const std::string& value) : value(value) {}
	Node(const std::string& value, Node* parent) : value(value) {
		parent->next = this;
	}
};

struct ListIterator : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag> {
	Node* current{ nullptr };

	ListIterator() {};
	ListIterator(Node* current) : current(current) {}

private:
	friend class boost::iterator_core_access;

	void increment() { current = current->next; };

	bool equal(const ListIterator& other) const {
		return other.current == current;
	}

	Node& dereference() const {
		return *current;
	}
};

int main() {

	Node alpha{ "alpha" };
	Node beta{ "beta", &alpha };
	Node gamma{ "gamma", &beta };

	std::for_each(ListIterator{ &alpha }, ListIterator{}, [](const Node& n) {
		std::cout << n.value << std::endl;
	});

	return 0;
}