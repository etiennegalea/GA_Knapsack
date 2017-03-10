#pragma once

#include <iostream>
#include <random>
#include <functional>
#include "Population.h"

using std::mt19937;

class Algorithms {
private:
    static const int MAX_CHROM = 10;
    static const int MAX_GENE = 10;
    double crossoverProb, mutationProb;
    std::random_device rd{};
    std::mt19937 engine{rd()};
    std::uniform_real_distribution<double> mutationRate{0.0, 1.0};
public:
    Algorithms(){
        crossoverProb = 0.2;
        mutationProb = 0.01;
    }

    ~Algorithms(){

    }

    Population rouletteSelection(Population pop);
    Chromosome crossover(Chromosome father, Chromosome mother);
    Chromosome mutation(Chromosome c);

};
