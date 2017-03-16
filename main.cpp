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

    static const int GENERATION_LIMIT = 1000;


    ItemList* items = new ItemList();
    cout << "create random list of items in 'itemlist'" << endl;
//    items->populateTestList();
    items->populateList();

    items->calculateMaxValue();

    cout << "\n----- printing items -----" << endl;
    items->printList();


    Population* pop = new Population(items->getMaxItems());
    cout << "\n ----- populating population with random chromosomes -----" << endl;
    pop->populatePopulation();


    int maxGeneCount = pop->getMaxGeneCount();
//    double acceptableSolutionLimit = (pop->getMaxGeneCount() - (pop->getMaxGeneCount() * 0.05));
    double acceptableSolutionLimit = (items->getKnapsackMaxWeight() - (items->getKnapsackMaxWeight() * 0.05));
    double maxFitness;

    pop = items->calcPopulationFitness(pop);
    // termination by generation
    if(TERMINATION_BY_GENERATION || TERMINATION_BY_FITNESS){
        for (int i = 1; i < GENERATION_LIMIT+1; i++){
            // calculate fitness of population
//            pop->printPopulation();
            cout << "Generation: " << i << " -- ";
            cout << "max fitness found: " << maxFitness << endl;
            // genetic algorithms (selection, crossover, mutation)
            pop->rouletteSelection();
            pop->crossover();
            pop->mutation();

//            pop->printPopulation();
            pop = items->calcPopulationFitness(pop);
            maxFitness = pop->getBestChromFound()->getFitness();
//            if(maxFitness >= acceptableSolutionLimit){
//                cout << "Fitness [" << maxFitness
//                     << "] found at generation: "
//                     << i << "\n" << endl;
//                pop->getBestChromFound()->printChromosome();
//                 print best chromosome Log
//                items->printBestChromosomeLog();
//                break;
//            }
//            if(i == GENERATION_LIMIT)
                cout << "\nFitness [" << maxFitness
                     << "] found at generation: "
                     << i << endl;
//
        }
        items->printBestChromosomeLog();
    }

    return 0;
}