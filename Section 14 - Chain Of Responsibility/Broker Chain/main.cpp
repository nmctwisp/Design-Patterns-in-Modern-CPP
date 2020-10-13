#include <iostream>
#include <string>
#include <boost/signals2.hpp>

struct Query {

	std::string creature_name;
	
	enum class Argument {
		attack = 0,
		defense = 1
	} argument;

	int result;
	
	Query(const std::string& creature_name, const Argument argument, const int result) 
		: creature_name(creature_name), argument(argument), result(result) {}
};

struct Game { // mediator
	boost::signals2::signal<void(Query&)> queries;
};

class Creature {
	Game& game;
	int attack;
	int defense;

public:
	std::string name;
	Creature(Game& game, const std::string& name, const int attack, const int defense)
		: game(game), attack(attack), defense(defense), name(name) {};

	// no need for this to be virtual
	int GetAttack() const {
		Query q{ name, Query::Argument::attack, attack };
		game.queries(q);
		return q.result;
	}

	friend std::ostream& operator<<(std::ostream& os, const Creature& obj) {
		os << "name: " << obj.name;
		os << " attack: " << obj.GetAttack(); // note here
		os << " defense: " << obj.defense;

		return os;
	}
};

class CreatureModifier {
	Game& game;
	Creature& creature;
public:
	CreatureModifier(Game& game, Creature& creature) 
		: game(game), creature(creature) {};

	virtual ~CreatureModifier() = default;
	// there is no handle() function
};

class DoubleAttackModifier : public CreatureModifier {
private:
	boost::signals2::connection conn;
public:
	DoubleAttackModifier(Game& game, Creature& creature)
		: CreatureModifier(game, creature) {
		// whenever someone wants this creature's attack,
		// we return DOUBLE the value	

		auto doubleAttack = [&](Query& query) {
			if (query.creature_name == creature.name &&
				query.argument == Query::Argument::attack)

				query.result *= 2;
		};

		conn = game.queries.connect(doubleAttack);

	};

	~DoubleAttackModifier() { conn.disconnect(); };

};

// similar idea, but Query instead of Command
int main() {
	Game game;
	Creature goblin{ game, "Strong Goblin", 2, 2 };
	std::cout << goblin << std::endl;

	{
		DoubleAttackModifier dam{ game, goblin };
		std::cout << goblin << std::endl;
	}

	std::cout << goblin << std::endl;

	getchar();

	return 0;
}