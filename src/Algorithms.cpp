#include "Algorithms.h"

using namespace GA_Knapsack;

Population Algorithms::rouletteSelection(Population pop) {

}

Chromosome Algorithms::crossover(Chromosome father, Chromosome mother) {

}

Chromosome Algorithms::mutation(Chromosome c)
{
    for (int i = 0; i < MAX_GENE; ++i) {
        if (mutationRate(engine) > mutationProb){
            // mutate
        }
    }
}