#include <string>
#include <vector>
#include <ostream>
#include <iostream>

class Field {
public:
    std::string name;
    std::string type;

    Field(const std::string& name, const std::string& type)
        : name{ name }, type{ type } {}

    friend std::ostream& operator<<(std::ostream& os, const Field& field);
};

std::ostream& operator<<(std::ostream& os, const Field& field) {
    os << field.type << ' ' << field.name << ';';
    return os;
}

class Class {
public:
    std::string name;
    std::vector<Field> fields;
    Class(std::string class_name)
        : name{ class_name } {}

    friend std::ostream& operator<<(std::ostream& os, const Class& cls);
};

std::ostream& operator<<(std::ostream& os, const Class& cls) {
    os << "class " << cls.name << '\n'
        << '{' << '\n';

    for (const auto& field : cls.fields) {
        os << "  " << field << '\n';
    }

    os << "};\n";
    return os;
}

class CodeBuilder
{
    Class the_class;
public:
    CodeBuilder(const std::string& class_name)
        : the_class{ Class{class_name} } {
    }

    CodeBuilder& add_field(const std::string& name, const std::string& type) {
        the_class.fields.emplace_back(name, type);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj);
};

std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj) {
    os << obj.the_class;
    return os;
}
int main() {

    // You are asked to implement the Builder Design Pattern for rendering simple chunks of code
    //
    // Sample use of the builder you are asked to create:
    //
    //   auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    //   std::cout << cb;
    //
    // The expected output of the above code is:
    //
    // class Person 
    // {
    //   string name;
    //   int age;
    // };
    //
    // Please observe the same placement of curly braces and use of two-space indentation.

    auto cb = CodeBuilder{ "Person" }
        .add_field("name", "string")
        .add_field("age", "int");

    std::cout << cb;
 }