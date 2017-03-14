#include <iostream>
#include "./src/Population.h"
#include "./src/knapsack/ItemList.h"

using std::cout;
using std::endl;

int main(){

    // termination conditions
    static const bool TERMINATION_BY_FITNESS = true;
    static const bool TERMINATION_BY_TIME = false;
    static const bool TERMINATION_BY_GENERATION = true;

    static const int GENERATION_LIMIT = 2000;

//    cout << "Create a population of items (chromosomes)..." << endl;
//    Population *p = new Population();
//    p->populatePopulation();
//    cout << "OK... Printing random generated population..." << endl;
//    p->printPopulation();

    ItemList* item = new ItemList();
//    cout << "create random list of items in 'itemlist'" << endl;
//    item->populateList();
//    cout << "\n----- printing items -----" << endl;
//    item->printList();
    Population* pop = new Population();

    cout << "\n ----- populating population with random chromosomes -----" << endl;
    pop->populatePopulation();
//    pop->calcPopulationFitness();
//    pop->printPopulation();

    int maxGeneCount = pop->getMaxGeneCount();
    double acceptableSolutionLimit = (pop->getMaxGeneCount() - (pop->getMaxGeneCount() * 0.05));
    double maxFitness;
    // termination by generation
    if(TERMINATION_BY_GENERATION || TERMINATION_BY_FITNESS){
        for (int i = 0; i < GENERATION_LIMIT; i++){
            cout << "Generation: " << i+1 << " -- ";
            cout << "max fitness found: " << maxFitness << endl;

//            pop->printPopulation();
            // genetic algorithms (selection, crossover, mutation)
            pop->rouletteSelection();
            pop->crossover();
//            pop->elitism();
            pop->mutation();

//            pop->printPopulation();

            maxFitness = pop->getBestChromFound()->getFitness();
//            if(maxFitness < acceptableSolutionLimit){
            if(maxFitness >= acceptableSolutionLimit){

                cout << "Fitness [" << maxFitness
                     << "] found at generation: "
                     << i << endl;
                pop->getBestChromFound()->printChromosome();
                break;
            }
        }
    }

    return 0;
}