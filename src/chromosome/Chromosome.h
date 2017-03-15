#pragma once

#include <iostream>
#include <random>
#include "../knapsack/Item.h"

using std::vector;
using std::string;

class Chromosome {
private:
    vector<int> chrom;
    int maxGene;
    int fitness;
    string solution;
    // mersenne twister
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> bin{0,1};
public:
    // constructor
    Chromosome(int p_maxGene, string p_solution){
        maxGene = p_maxGene;
        solution = p_solution;
        fitness = 0;
    }

    // overloaded assignment

    // destructor
    ~Chromosome(){

    }

//    int getChromosomeSize() { return chrom.size(); }
    void populateChromosome();
    void printChromosome();
    void calcChromosomeFitness();
    int getFitness() { return fitness; }
    int getGene(int p_index){ return chrom.at(p_index); }
    int setGene(int p_value){ chrom.push_back(p_value); }
    int setGene(int p_index, int p_value){ (chrom.at(p_index) = p_value); }


//    bool operator==(const char c, int number) {
//        return ((int)c == number);
//    }
};

