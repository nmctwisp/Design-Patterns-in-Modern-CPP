#include <iostream>

// Behavioral Chain of Responsibility

struct Creature {
	std::string name;
	int attack;
	int defense;

	Creature(const std::string& name, int attack, int defense)
		: name(name), attack(attack), defense(defense) {};

	friend std::ostream& operator<<(std::ostream& os, const Creature& obj) {
		os << "name: " << obj.name << " attack: " << obj.attack;
		os << " defense: " << obj.defense;

		return os;
	}
};

class CreatureModifier {
	CreatureModifier* next{ nullptr };
protected:
	Creature& creature;
public:
	CreatureModifier(Creature& creature) : creature(creature) {};
	virtual ~CreatureModifier() = default;
	void add(CreatureModifier* cm) {
		if (next)
			next->add(cm);
		else
			next = cm;
	};

	virtual void handle() {
		if (next)
			next->handle();
	};
};

class DoubleAttackModifier : public CreatureModifier {
public:
	DoubleAttackModifier(Creature& creature) : CreatureModifier(creature) {};

	void handle() override {
		creature.attack *= 2;
		CreatureModifier::handle();
	};
};

class IncreaseDefenseModifier : public CreatureModifier {
public:
	IncreaseDefenseModifier(Creature& creature) : CreatureModifier(creature) {};

	void handle() override {
		if (creature.attack <= 2)
			creature.defense++;
		CreatureModifier::handle();
	};
};

class NoBonusModifier : public CreatureModifier {
public: 
	NoBonusModifier(Creature& creature) : CreatureModifier(creature) {};
	void handle() override {};
};

int main() {
	Creature goblin{ "Goblin", 1, 1 };
	CreatureModifier root{ goblin };
	DoubleAttackModifier r1{ goblin };
	DoubleAttackModifier r1_2{ goblin };
	IncreaseDefenseModifier r2{ goblin };
	
	//// If added at the beginning this would distrupt the chain of responsiblity.
	//NoBonusModifier curse{ goblin };
	//root.add(&curse);
	
	root.add(&r1); // 
	root.add(&r1_2); // attack = 4
	root.add(&r2); // no-op

	root.handle();

	std::cout << goblin << std::endl;

	return 0;
};