#include <algorithm>
#include <numeric>
#include <array>
#include <iostream>

class CreatureOLD {
	int strength;
	int agility;
	int intelligence;
	// if we decide to add a new data member that would be included in the func calc
	// then we would need to modify the aggregate/math functions as well.
public:
	void set_strength(int strength) { this->strength = strength; };
	void set_agility(int agility) { this->agility = agility; };
	void set_intelligence(int intelligence) { this->intelligence = intelligence; };

	int get_strength() const { return strength; };
	int get_agility() const { return agility; };
	int get_intelligence() const { return intelligence; };

	int sum() const { return strength + agility + intelligence; }
	int max() const { return std::max(std::max(strength, agility), intelligence); };

	double average() const { return sum() / 3.0; };
};

class CreatureNEW {
private:
	enum Abilities {str, agl, intl, count};
	std::array<int, Abilities::count> abilities;

public:
	void set_strength(int strength) { abilities[str] = strength; };
	void set_agility(int agility) { abilities[agl] = agility; };
	void set_intelligence(int intelligence) { abilities[intl] = intelligence; };

	int get_strength() const { return abilities[str]; };
	int get_agility() const { return abilities[agl]; };
	int get_intelligence() const { return abilities[intl]; };

	double sum() const { return std::accumulate(abilities.begin(), abilities.end(), 0); }
	double average() const {return sum() / 3.0; }

	int max() const {
		auto it = std::max_element(abilities.begin(), abilities.end());

		return *it;
	}

};

int main() {
	CreatureNEW orc;
	orc.set_strength(16);
	orc.set_agility(11);
	orc.set_intelligence(9);

	std::cout << "The orc has an average stat of "
		<< orc.average()
		<< " and a maximum stat of "
		<< orc.max()
		<< "\n";


	return 0;
}