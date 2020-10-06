#include "..\di.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

struct IFoo {
	virtual std::string name() = 0;
};

struct Foo : IFoo {
	static int id;
	Foo() { ++id; };

	std::string name() override {
		return "foo s" + boost::lexical_cast<std::string>(id);
	}
};

int Foo::id = 0;

struct Bar {
	std::shared_ptr<IFoo> foo;
};

int main() {

	auto injector = boost::di::make_injector(
		boost::di::bind<IFoo>.to<Foo>()
	);

	auto bar1 = injector.create<std::shared_ptr<Bar>>();
	auto bar2 = injector.create<std::shared_ptr<Bar>>();
	return 0;
}