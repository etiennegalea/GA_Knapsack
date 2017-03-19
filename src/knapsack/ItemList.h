#pragma once

#include "Item.h"
#include "../chromosome/Chromosome.h"
#include "../Population.h"

class ItemList {
private:
    static const int MIN_VALUE_PER_ITEM = 8;
    static const int MAX_VALUE_PER_ITEM = 20;
    static const int MIN_WEIGHT_PER_ITEM = 1;
    static const int MAX_WEIGHT_PER_ITEM = 5;

    vector<Item*> list;
    int maxValueOfItemList;

    int maxKnapsackWeight;
    int maxItems; //corresponds to maxGene

    // Use random_device to generate a seed for Mersenne twister engine.
    std::random_device rd{};
    // Use Mersenne twister engine to generate pseudo-random numbers.
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> rValue{MIN_VALUE_PER_ITEM, MAX_VALUE_PER_ITEM};
    std::uniform_int_distribution<int> rWeight{MIN_WEIGHT_PER_ITEM, MAX_WEIGHT_PER_ITEM};

    struct Log{
        Chromosome* chrom;
        int index = 0;
        double fitness = 0;
        double maxValue = 0;
        double maxWeight = 0;
        vector<int> itemList;
    } bestChromLog;

public:
    ItemList(int p_maxKnapsackWeight, int p_maxItems){
        maxKnapsackWeight = p_maxKnapsackWeight;
        maxItems = p_maxItems;
    }
    ~ItemList(){
        vector<Item*>().swap(list);
        vector<int>().swap(bestChromLog.itemList);
    }

    int getKnapsackMaxWeight() { return maxKnapsackWeight; }
    int getMaxItems() { return maxItems; }
    void calculateMaxValue();

    void printBestChromosomeLog();

    // populate the list with random items
    void populateList();
    void printList();

    Population* calcPopulationFitness(Population *pop);
    Chromosome* calcChromosomeFitness(Chromosome* x, int count);

    void populateTestList();

    void writePopulationToFile();
};