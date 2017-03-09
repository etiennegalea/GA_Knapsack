#include "./Chromosome.h"
#include "Gene.h"

using namespace GA_KnapSack;

void Chromosome::popChromosome_random(){

    // for each gene in chromosome
    for (int i = 0; i < MAX_GENE; ++i) {
        int rValue = rand() % 25 + 1;
        int rSize = rand() % 10 + 1;
        Gene* g = new Gene(rValue, rSize);
        chrom[i] = g;
        std::cout << g->getSize() << "\t" << g->getValue() << endl;
    }
}
