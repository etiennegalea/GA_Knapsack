#pragma once

#include <iostream>
#include <random>
#include "../knapsack/Item.h"

using std::vector;

class Chromosome {
private:
    static const int MAX_GENE = 20;
    vector<int> chrom;
    int fitness;
    // mersenne twister
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> bin{0,1};
public:
    // constructor
    Chromosome(){
        fitness = 0;
    }

    // overloaded assignment

    // destructor
    ~Chromosome(){

    }

    int chromosomeSize() { return MAX_GENE; }
    void populateChromosome();
    void printChromosome();
    void calcChromosomeFitness();
    int getFitness() { return fitness; }
    int getChromosome(int p_index){ return chrom.at(p_index); }

};

