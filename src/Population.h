#pragma once

#include <iostream>
#include "src/Chromosome/Chromosome.h"

using namespace std;

class Population {
private:
    Chromosome *pop[100]{nullptr};
//    Chromosome elite;
//    float avgFitness;
public:
    Population()
    {

    }

    void popPopulation_random();
    // for max population
//        for (int i = 0; i < 100; ++i) {
//            Chromosome c;
//            c.popChromosome_random();
//            this->pop[i] = c;
//        }


    void printPopulation();
//        for (int i = 0; i < 100; ++i) {
//            cout << this->pop[i] << ": "
//                 << "value: " << this->pop[i].getChromosome()->getValue()
//                 << "\tsize: " << this->pop[i].getChromosome()->getSize()
//                 << endl;
//        }


//    void setPop(Chromosome pop[100]){ this->pop = pop; }
    ~Population()
    {
        Chromosome* temp = nullptr;
        for(int index = 0; index < 100; index++)
        {
            temp = pop[index];
            delete temp;
            temp = nullptr;
        }
    }
};
