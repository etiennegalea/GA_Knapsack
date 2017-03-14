#pragma once

#include <iostream>
#include "chromosome/Chromosome.h"
#include <vector>

using std::vector;

class Population {
private:
    static const bool eliteSwitch = false;

    static const int MAX_CHROM = 4;
    static const int MAX_ELITE = 2;
    static const int MAX_GENE = 10;
    static constexpr double CROSSOVER_PROB = 0.25;
    static constexpr double MUTATION_PROB = 0.1;

    vector<Chromosome*> pop;
    Chromosome* elite[MAX_ELITE]{nullptr};
    double avgFitness, cumulativeFitness;
    int chromosomeSize;

    // mersenne twister PRNG
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_real_distribution<double> randomProb{0,1};
    std::uniform_real_distribution<double> mutationRate{0.0, 1.0};
public:
    Population()
    {
        avgFitness = 0;
        cumulativeFitness = 0;
        chromosomeSize = MAX_GENE;
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
    void crossover();
    Chromosome* singlePointCrossover(Chromosome* p_father, Chromosome* p_mother);
    void mutation();
    Chromosome* singlePointMutation(Chromosome *p_chrom);

};
