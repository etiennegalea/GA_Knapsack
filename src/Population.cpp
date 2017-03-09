#include "./Population.h"

using namespace std;

void Population::popPopulation_random(){
    // for max population
    for (int i = 0; i < 100; ++i) {
        Chromosome c;
        c.popChromosome_random();
        this->pop[i] = c;
    }
}

void Population::printPopulation(){
    for (int i = 0; i < 100; ++i) {
        cout << this->pop[i] << ": "
             << "value: " << this->pop[i].getChromosome()->getValue()
             << "\tsize: " << this->pop[i].getChromosome()->getSize()
             << endl;
    }
}