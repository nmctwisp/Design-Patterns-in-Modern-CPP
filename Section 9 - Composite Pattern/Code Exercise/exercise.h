#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

struct ContainsIntegers {
    virtual int sum() const = 0;
};

struct SingleValue : public ContainsIntegers {
    int value{ 0 };

    SingleValue() = default;
    explicit SingleValue(const int value) : value(value) {};
    
    int sum() const override { return value; }
};

struct ManyValues : std::vector<int>, ContainsIntegers {
    void add(const int value) { push_back(value); }
 
    int sum() const override { return std::accumulate(begin(), end(), 0);  }
};



int sum(const std::vector<ContainsIntegers*> items);