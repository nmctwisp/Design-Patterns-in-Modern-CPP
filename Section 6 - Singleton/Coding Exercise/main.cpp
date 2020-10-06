#include <functional>
using namespace std;

class Singleton {
public:
    Singleton() = default;
};

struct SingletonTester
{
    template <typename T>
    bool is_singleton(function<T*()> factory)
    {
        auto obj1 = factory();
        auto obj2 = factory();

        return &(*obj1) == &(*obj2);
    }
};