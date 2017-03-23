#pragma once

#include <iostream>
#include <fstream>
#include "chromosome/Chromosome.h"
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class Population {
private:
    static const bool eliteBeforeCrossover = false;

    int maxGene;
    int maxChrom;
    int maxElite;
    double crossoverProb;
    double mutationProb;

    vector<Chromosome*> pop;
    vector<Chromosome*> elite;
    Chromosome* bestChrom;
    double avgFitness, cumulativeFitness;

    // mersenne twister PRNG
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_real_distribution<double> randomProb{0, 1};
    std::uniform_real_distribution<double> mutationRate{0.0, 1.0};

public:
    Population(int p_maxGene, int p_maxChrom, int p_maxElite, double p_crossover_prob, double p_mutation_prob) {
        avgFitness = 0;
        cumulativeFitness = 0;
        maxGene = p_maxGene;
        maxChrom = p_maxChrom;
        maxElite = p_maxElite;
        crossoverProb = p_crossover_prob;
        mutationProb = p_mutation_prob;
    }

    ~Population() {
        Chromosome *temp = nullptr;
        for (Chromosome *x : pop) {
            temp = x;
            delete temp;
            temp = nullptr;
        }
    }

    Chromosome *getPop(int p_index) { return pop.at(p_index); }

    void populatePopulation();
    void printPopulation();
    vector<Chromosome*> getPopulation() { return pop; }

    void calcPopulationFitness();

    // sets the elite individuals (according to maxElite)
    void getElite();
    void replaceWorstWithElite();
    void elitism();

    void rouletteSelection();

    void crossover();
    Chromosome *singlePointCrossover(Chromosome *p_father, Chromosome *p_mother);

    void mutation();
    Chromosome *singlePointMutation(Chromosome *p_chrom);

    int getMaxGeneCount() { return maxGene; }
    Chromosome *getBestChromFound();

    void writePopulationToFile();
};
