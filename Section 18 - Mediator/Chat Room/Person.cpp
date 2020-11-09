#include "Person.hpp"
#include "ChatRoom.hpp"
#include <iostream>

Person::Person(const std::string& name) : name(name) {
}

void Person::say(const std::string& msg) const {
    room->broadcast(name, msg);
}

void Person::pm(const std::string& who, const std::string& msg) const {
    room->message(name, who, msg);
}

void Person::receive(const std::string& origin, const std::string& msg) {
    std::string s{ origin + ": \"" + msg + "\"" };
    std::cout << "[" << name << "'s chat session]" << s << "\n";
    chat_log.emplace_back(s);
}

bool Person::operator==(const Person& rhs) const {
    return name == rhs.name;
}

bool Person::operator!=(const Person& rhs) const {
    return !(rhs == *this);
}
