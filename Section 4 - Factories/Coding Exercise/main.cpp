#include <string>
using namespace std;

struct Person
{
    int id;
    string name;
};

class PersonFactory
{
    int id;
public:
    Person create_person(const string& name)
    {
        return {id++, name};
    }
};

int main() {

    PersonFactory pf1{};
    auto x = pf1.create_person("sdsd");
    auto y = pf1.create_person("sdsj");

    return 0;
}