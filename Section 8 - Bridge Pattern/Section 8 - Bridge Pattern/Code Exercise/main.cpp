#include <string>
// You are given an example of inheritance hierarchy which results in Cartesian-product duplication.
// Please refactor this hierarchy, give the base class Shape an initializer that takes a Renderer defined as:

//  struct Renderer {
//    virtual std::string what_to_render_as() const = 0;
//  };

// as well as VectorRenderer and RasterRenderer.
// The expectation is that each constructed object has a member called str() that returns it textual representation, 
// for example:

// Triangle(RasterRederer()).str() // returns "Drawing Triangle as pixels"


struct Renderer {
    virtual std::string what_to_render_as() const = 0;
};

struct VectorRenderer : public Renderer {
    std::string what_to_render_as() const override {
        return " as lines";
    };
};

struct RasterRenderer : public Renderer {
    std::string what_to_render_as() const override {
        return " as pixels";
    };
};

struct Shape {
    std::string name;
    Renderer& renderer;

    Shape(Renderer&& renderer) : renderer(renderer) {};
    ~Shape() = default;
    
    std::string str() {
        return "Drawing " + name + renderer.what_to_render_as();
    };
};

struct Triangle : Shape {
    Triangle(Renderer&& renderer) 
        : Shape(std::forward<Renderer>(renderer)) {
        name = "Triangle";
    }
};

struct Square : Shape {
    Square(Renderer&& renderer) 
        : Shape(std::forward<Renderer>(renderer)) {
        name = "Square";
    }
};

int main() {
    auto t{ Triangle(RasterRenderer()).str() };
}
