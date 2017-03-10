#pragma once

#include "Item.h"
#include <random>
#include <functional>
#include <chrono>

using std::bind;
using std::mt19937;
using std::vector;

class ItemList {
private:
    static const int MAX_ITEMS = 20;
    static const int MAX_VALUE = 20;
    static const int MAX_WEIGHT = 20;

    vector<Item*> list = {nullptr};
    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd{};
    // Use Mersenne twister engine to generate pseudo-random numbers.
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> rValue{1, MAX_VALUE};
    std::uniform_int_distribution<int> rWeight{1, MAX_WEIGHT};

public:
    ItemList(){

    }
    ~ItemList(){

    }


    // populate the list with random items
    void populateList();
    void printList();

};