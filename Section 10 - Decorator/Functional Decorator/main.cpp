#include <functional>
#include <iostream>

struct Logger {
	std::function<void()> func;
	std::string name;

	Logger(const std::function<void()>& func, const std::string& name)
		: func(func), name(name) {};

	void operator()() const {
		std::cout << "Entering " << name << std::endl;
		func();
		std::cout << "Exiting " << name << std::endl;
	}
};

template <typename Func>
struct Logger2 {
	Func func;
	std::string name;

	Logger2(const Func& func, const std::string& name) : func(func), name(name) {};

	void operator()() const {
		std::cout << "Entering " << name << std::endl;
		func();
		std::cout << "Exiting " << name << std::endl;
	}
};

template <typename Func>
auto make_logger2(const Func&& func, const std::string& name) {
	return Logger2<Func>{func, name};
}

double add(double a, double b) {
	std::cout << a << " + " << b << " = " << (a + b) << std::endl;
	return a + b;
}


template <typename> struct Logger3; // need partial specialization for this to work

template <typename R, typename... Args> // Function's return type and argument list
struct Logger3<R(Args...)> {

	std::function<R(Args ...)> func;
	std::string name;

	Logger3(std::function<R(Args...)> func, const std::string& name)
		: func( func ), name(name) {};

	R operator() (Args... args) {
		std::cout << "Entering " << name << std::endl;
		R result = func(args...);
		std::cout << "Exiting " << name << std::endl;
		return result;
	}
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const std::string& name) {
	return Logger3<R(Args...)>(
		std::function<R(Args...)>(func),
		name);
}

int main() {
	std::function<void()> HelloFunction = []() {std::cout << "Hello" << std::endl; };
	Logger logger{ HelloFunction, "HelloFunction" };

	logger();

	Logger2<std::function<void()>> logger2{ HelloFunction, "HelloFunction" };
	logger2();

	auto logger22 = make_logger2([]() {std::cout << "Hello" << std::endl; }, "HelloFunction");
	logger22();

	auto logged_add = make_logger3(add, "Add");
	auto result = logged_add(2, 3);
	std::cout << "result = " << result << std::endl;

	return 0;
}

