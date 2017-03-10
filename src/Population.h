#pragma once

#include <iostream>
#include "chromosome/Chromosome.h"

using namespace GA_Knapsack;
using std::vector;

class Population {
private:
    static const int MAX_CHROM = 5;
    static const int MAX_ELITE = 2;

//    Chromosome* pop[MAX_CHROM]{nullptr};
    vector<Chromosome*> pop = {nullptr};
    //    Chromosome* elite[MAX_ELITE];
    vector<Chromosome*> elite = {nullptr};

    double avgFitness, cumulativeFitness;
    int chromosomeSize;
    // mersenne twister PRNG
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_real_distribution<double> roulette{0,1};
public:
    Population()
    {
        avgFitness = cumulativeFitness = 0;
        chromosomeSize = pop.at(0)->chromosomeSize();
    }

    ~Population()
    {
        Chromosome* temp = nullptr;
        for(Chromosome* x : pop)
        {
            temp = x;
            delete temp;
            temp = nullptr;
        }
    }

    Chromosome* getPop(int p_index){ return pop.at(p_index); }
    void populatePopulation();
    void printPopulation();
    void calcPopulationFitness();
    // sets the elite individuals (according to MAX_ELITE)
    void getElite();
    void replaceEliteWithWorst();

    void rouletteSelection();
};
