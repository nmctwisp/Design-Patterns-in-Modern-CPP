#include <string>

class Person
{
    friend class ResponsiblePerson;
    int age;
public:
    Person(int age) : age(age) {}

    int get_age() const { return age; }
    void set_age(int age) { this->age = age; }

    std::string drink() const { return "drinking"; }
    std::string drive() const { return "driving"; }
    std::string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
public:
    ResponsiblePerson(const Person& person) : person(person) {}

    int get_age() const { return person.age; }
    void set_age(int age) { this->person = age; }

    std::string drink() const { 
        std::string response;
        if (get_age() < 18)
            response = "too young";
        else
            response = person.drink(); 

        return response;
    }
    std::string drive() const { 
        std::string response;
        if (get_age() < 16)
            response = "too young";
        else
            response = person.drink();

        return response;
    }
    std::string drink_and_drive() const { 
        return "dead"; 
    }

private:
    Person person;
};

int main() {
    Person p{ 10 };
    ResponsiblePerson rp{ p };
    return 0;
}