#pragma once

#include "Item.h"
#include "../chromosome/Chromosome.h"
#include "../Population.h"

class ItemList {
private:
    static const int KNAPSACK_MAX_WEIGHT = 50;

    static const int MAX_ITEMS = 40; //corresponds to maxGene
    static const int MIN_VALUE_PER_ITEM = 8;
    static const int MAX_VALUE_PER_ITEM = 20;
    static const int MIN_WEIGHT_PER_ITEM = 1;
    static const int MAX_WEIGHT_PER_ITEM = 5;

    vector<Item*> list;
    int maxValueOfItemList;

    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd{};
    // Use Mersenne twister engine to generate pseudo-random numbers.
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> rValue{MIN_VALUE_PER_ITEM, MAX_VALUE_PER_ITEM};
    std::uniform_int_distribution<int> rWeight{MIN_WEIGHT_PER_ITEM, MAX_WEIGHT_PER_ITEM};

    struct Log{
        Chromosome* chrom;
        int index;
        double maxValue;
        double maxWeight;
        vector<int> itemList;
    } bestChromLog;

public:
    ItemList(){

    }
    ~ItemList(){
        vector<Item*>().swap(list);
        vector<int>().swap(bestChromLog.itemList);
    }

    int getKnapsackMaxWeight() { return KNAPSACK_MAX_WEIGHT; }
    int getMaxItems() { return MAX_ITEMS; }
    void calculateMaxValue();

    void printBestChromosomeLog();

    // populate the list with random items
    void populateList();
    void printList();

    Population* calcPopulationFitness(Population *pop);

    void populateTestList();
};