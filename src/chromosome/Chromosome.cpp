#include "./Chromosome.h"


// test solution
//static constexpr int SOLUTION[30] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
static constexpr int SOLUTION[10] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
//static constexpr int SOLUTION[5] = {1, 1, 1, 1, 1};

void Chromosome::populateChromosome(){
    for (int i = 0; i < MAX_GENE; i++) {
        chrom.push_back(bin(engine));
    }
}

void Chromosome::printChromosome(){
    for (int i = 0; i < MAX_GENE; ++i) {
        std::cout << " " << getGene(i);
    }
    std::cout << std::endl;
}

void Chromosome::calcChromosomeFitness() {
    fitness = 0;
    for (int i = 0; i < MAX_GENE; ++i) {
        if (SOLUTION[i] == getGene(i)){
            fitness++;
        }
    }
}