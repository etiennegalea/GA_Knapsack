#pragma once

#include <iostream>
#include "./Gene.h"

using namespace std;
namespace GA_KnapSack {

    class Chromosome {
    private:
        static const int MAX_GENE = 20;
        Gene* chrom[MAX_GENE]{nullptr};
        int fitness;
    public:
        Chromosome(){
            fitness = 0;
        }

        int getFitness() { return this->fitness; }

        Gene* getChromosome() { return *chrom; }

        void popChromosome_random();

        ~Chromosome(){}
    };

}
