#include <sstream>
#include "./Chromosome.h"


void Chromosome::populateChromosome(){
    for (int i = 0; i < maxGene; i++) {
        chrom.push_back(bin(engine));
    }
}

void Chromosome::printChromosome(){
    for (int i = 0; i < maxGene; ++i) {
        std::cout << getGene(i);
    }
    std::cout << std::endl;
}

void Chromosome::calcChromosomeFitness() {
    fitness = 0;
    for (int i = 0; i < maxGene; ++i) {
        if ((solution.at(i) - 48) == getGene(i)){
            fitness++;
        }
    }
}


