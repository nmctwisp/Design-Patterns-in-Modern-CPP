#include <iostream>
#include <vector>

//CRTP - Curiously Recursive Template Pattern
struct Neuron;

template <typename self>
struct SomeNeurons {

	template <typename T> 
	void connect_to(T& other) {

		for (Neuron& from : *static_cast<self*>(this)) {
			
			for (Neuron& to: other) {
				from.out.push_back(&to);
				to.in.push_back(&from);
			}
		}
	}
};

struct Neuron : SomeNeurons<Neuron> {
	unsigned int id;
	std::vector<Neuron*> in; // incoming connections
	std::vector<Neuron*> out; // outgoing connections 

	Neuron() {
		static int id{ 0 };
		this->id = id++;
	}

	// SomeNeurons Implementation negates the need for defining connect_to under the Neuron class
	//void connect_to(Neuron& other) {
	//	out.push_back(&other);
	//	other.in.push_back(this);
	//}

	Neuron* begin() { return this; }
	Neuron* end() { return this + 1; }

	friend std::ostream& operator<<(std::ostream& os, const Neuron& obj) {
		for (Neuron* n : obj.in) {
			os << n->id << "\t-->\t[" << obj.id << "]" << std::endl;
		}

		for (Neuron* n : obj.out) {
			os << "[" << obj.id << "]\t-->\t" << n->id << std::endl;
		}

		return os;
	};
};

struct NeuronLayer : std::vector<Neuron>, SomeNeurons<NeuronLayer> {
	NeuronLayer(int count) {
		while (count-- > 0)
			emplace_back(Neuron{});
	}

	friend std::ostream& operator<<(std::ostream& os, const NeuronLayer& obj) {
		for (auto& n : obj)
			os << n;

		return os;
	}
};

int main() {
	Neuron n1, n2;
	n1.connect_to(n2);

	std::cout << n1 << n2 << std::endl;

	NeuronLayer l1{ 5 };
	Neuron n3;
	l1.connect_to(n3);

	std::cout << "Neuron " << n3.id << std::endl << n3 << std::endl;
	std::cout << "Layer " << std::endl << l1 << std::endl;

	NeuronLayer l2{ 2 }, l3{ 3 };
	l2.connect_to(l3);
	std::cout << "Layer l2" << std::endl << l2;
	std::cout << "Layer l3" << std::endl << l3;

	return 0;
}