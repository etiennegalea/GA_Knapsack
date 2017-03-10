#pragma once

#include <iostream>
#include <random>
#include "../knapsack/Item.h"

using std::vector;

namespace GA_Knapsack {
    class Chromosome {
    private:
        static const int MAX_GENE = 20;
//        int chrom[MAX_GENE];
        vector<int> chrom;
        int fitness;
        // mersenne twister
        std::random_device rd;
        std::mt19937 engine{rd()};
        std::uniform_int_distribution<int> bin{0,1};
    public:
        Chromosome(){
            fitness = 0;
        }

        ~Chromosome(){}

        int chromosomeSize() { return MAX_GENE; }
        void populateChromosome();
        void printChromosome();
        void calcChromosomeFitness();
        int getFitness() { return fitness; }
        int getChromosome(int p_index){ return chrom[p_index]; }

    };

}
