#include <vector>
#include <iostream>

int main() {

	std::vector<std::string> names{ "john", "jane", "jill", "jack" };
	std::vector<std::string>::iterator it = names.begin();
	
	std::cout << "first name is: " << *it << std::endl;

	++it;
	it->append(std::string(" goodall"));
	std::cout << "second name is: " << *it << std::endl;

	while (++it != names.end()) {
		std::cout << "another name: " << *it << std::endl;
	}

	for (auto ri = names.rbegin(); ri != names.rend(); ++ri) {
		std::cout << *ri;
		
		if (ri + 1 != names.rend())
			std::cout << ". ";
	}
	std::cout << std::endl;


	std::vector<std::string>::const_reverse_iterator cri = std::crbegin(names);

	for (auto& name : names)
		std::cout << "name= " << name << std::endl;


}