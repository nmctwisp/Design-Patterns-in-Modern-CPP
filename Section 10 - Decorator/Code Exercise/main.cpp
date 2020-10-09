#include <string>
#include <iostream>
#include <sstream>

class Flower {
public:
    virtual std::string str() = 0;
};

class Rose : public Flower {
    const std::string name{ "rose" };
public:
    Rose() = default;

    std::string str() override {
        std::ostringstream oss;
        oss << "A " << name;
        
        return oss.str();
    }
};

class RedFlower : public Flower {
    Flower& flower;
    const std::string color{ "red" };
public:
    RedFlower(Flower& flower) : flower(flower) {};

    std::string str() override {
        std::ostringstream oss;
        std::string text = flower.str();
        auto hasRed = text.find("red") == std::string::npos ? false : true;
        auto hasBlue = text.find("blue") == std::string::npos ? false : true;

        if (hasRed)
            oss << flower.str();
        else if (hasBlue)
            oss << flower.str() << " and " << color;
        else
            oss << flower.str() << " that is " << color;

        return oss.str();
    };
};

class BlueFlower : public Flower {
    Flower& flower;
    const std::string color{ "blue" };
public:
    BlueFlower(Flower& flower) : flower(flower) {};

    std::string str() override {
        std::ostringstream oss;
        std::string text = flower.str();
        auto hasRed = text.find("red") == std::string::npos ? false : true;
        auto hasBlue = text.find("blue") == std::string::npos ? false : true;

        if (hasBlue)
            oss << flower.str();
        else if (hasRed)
            oss << flower.str() << " and " << color;
        else
            oss << flower.str() << " that is " << color;

        return oss.str();
    };
};


int main() {
    Rose rose;
    RedFlower red_rose{ rose };
    RedFlower red_red_rose{ red_rose };
    BlueFlower blue_red_rose{ red_rose };
    BlueFlower blue_rose{ rose };
    std::cout << red_red_rose.str() << std::endl;
    std::cout << blue_red_rose.str() << std::endl;
    std::cout << blue_rose.str() << std::endl;
    return 0;
}