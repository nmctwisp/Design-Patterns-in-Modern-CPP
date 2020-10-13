#include <vector>
#include <iostream>
#include <algorithm>

struct Creature;
struct Game
{
    std::vector<Creature*> creatures;
};

struct StatQuery
{
    enum Statistic { attack, defense } statistic;
    int result;
};

struct Creature
{
protected:
    Game& game;
    int base_attack;
    int base_defense;

public:
    Creature(Game& game, int base_attack, int base_defense) 
        : game(game), base_attack(base_attack), base_defense(base_defense) {}

    virtual int get_attack() = 0;
    virtual int get_defense() = 0;
};

class Goblin : public Creature
{
public:
    Goblin(Game& game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

    Goblin(Game& game) : Creature(game, 1, 1) {}

    int get_attack() override {
        auto countGoblins = [](Creature* creature) {
            if (typeid(*creature) == typeid(Goblin))
                return true;
            return false;
        };

        int goblin_cnt = std::count_if(game.creatures.begin(), game.creatures.end(), countGoblins);
        bool hasGoblinKing = game.creatures.size() - goblin_cnt == 0 ? false : true;

        if (hasGoblinKing)
            return base_attack + 1;
        return base_attack;
    }

    int get_defense() override {
        int goblin_cnt = game.creatures.size();
        if (goblin_cnt <= 1)
            return base_defense;
        return  goblin_cnt - 1 + base_defense;
    }
};

class GoblinKing : public Goblin
{
public:
    GoblinKing(Game& game) : Goblin(game, 3, 3) {}

    int get_attack() override {
        
        return base_attack;
    }
};

int main() {
    Game game;
    Goblin goblin{ game };
    game.creatures.push_back(&goblin);
    std::cout << "Checking that a baseline goblin is a 1/1...\n";
    goblin.get_attack(); // 1
    goblin.get_defense(); // 1

    std::cout << "Adding a second goblin, now they should be 1/2...\n";
    Goblin goblin2{ game };
    game.creatures.push_back(&goblin2);
    goblin.get_attack(); // 1
    goblin.get_defense(); // 2

    std::cout << "Adding a goblin king, now a goblin should be 2/3...\n";
    GoblinKing goblin3{ game };
    game.creatures.push_back(&goblin3);
    goblin.get_attack(); // 2
    goblin.get_defense(); // 3

    return 0;
}