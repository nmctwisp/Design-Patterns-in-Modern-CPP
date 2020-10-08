#include "exercise.h"

int sum(const std::vector<ContainsIntegers*> items)
{
    int total{};
    for (auto& item : items) 
        total += item->sum();

    return total;
}