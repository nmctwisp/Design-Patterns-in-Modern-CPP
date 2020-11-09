//#include <fstream>
//#include <sstream>
//#include <memory>
//#include <cmath>
//#include <map>
//#include <functional>

#include <boost/signals2.hpp>
#include <iostream>

struct EventData {
	virtual ~EventData() = default;
	virtual void print() const = 0;
};

struct PlayerScoredData : EventData {
	std::string player_name;
	int goals_scored_so_far;

	PlayerScoredData(const std::string& player_name, int goals_scored_so_far) :
		player_name(player_name),
		goals_scored_so_far(goals_scored_so_far) {};

	void print() const override {
		std::cout << player_name << " has scored! (their ";
		std::cout << goals_scored_so_far << " goals)"; 
		std::cout << std::endl;
	};
};

struct Game {
	boost::signals2::signal<void(EventData*)> events;

};

struct Player {
	std::string name;
	int goals_scored{ 0 };
	Game& game;

	Player(const std::string& name, Game& game) :
		name(name),
		game(game) {};

	void score() {
		goals_scored++;
		PlayerScoredData ps{ name, goals_scored };
		game.events(&ps);
	};
};

struct Coach {
	Game& game;

	explicit Coach(Game& game) :
		game(game) {

		game.events.connect([](EventData* e) {
			PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(e);

			if (ps && ps->goals_scored_so_far < 3)
				std::cout << "coach says: well done, " << ps->player_name << std::endl;
			}
		);
	};

};

int main() {
	Game game;
	Player player{ "Sam", game };
	Coach coach{ game };

	player.score();
	player.score();
	player.score();

	getchar();
	return 0;
}