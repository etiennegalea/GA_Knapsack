#pragma once

#include "Item.h"
#include "../chromosome/Chromosome.h"
#include "../Population.h"

class ItemList {
private:
    static const int KNAPSACK_MAX_WEIGHT = 80;

    static const int MAX_ITEMS = 10; //corresponds to maxGene
    static const int MAX_VALUE_PER_ITEM = 50;
    static const int MAX_WEIGHT_PER_ITEM = 20;

    vector<Item*> list;

    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd{};
    // Use Mersenne twister engine to generate pseudo-random numbers.
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> rValue{1, MAX_VALUE_PER_ITEM};
    std::uniform_int_distribution<int> rWeight{1, MAX_WEIGHT_PER_ITEM};

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
    void printBestChromosomeLog();

    // populate the list with random items
    void populateList();
    void printList();

    Population* calcPopulationFitness(Population *pop);

};