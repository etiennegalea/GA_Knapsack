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

    static const int FITNESS_LIMIT = 700;
    static const int TIME_LIMIT = 20000;
    static const int GENERATION_LIMIT = 5;

    static const int MAX_KNAPSACK_WEIGHT = 10;
    static const int MAX_ITEMS = 10;
    static const int MAX_CHROM = 8;
    static const int MAX_ELITE = 1;
    static constexpr double CROSSOVER_PROB = 0.8;
    static constexpr double MUTATION_PROB = 0.1;

    ItemList* items = new ItemList(MAX_KNAPSACK_WEIGHT, MAX_ITEMS);
    cout << "create random list of items in 'itemlist'" << endl;
//    items->populateList();
//    items->writeItemListToFile();
    items->readItemListFromFile();
    items->calculateMaxValue();

    cout << "\n----- printing items -----" << endl;
    items->printList();


    Population* pop = new Population(MAX_ITEMS, MAX_CHROM, MAX_ELITE, CROSSOVER_PROB, MUTATION_PROB);
    cout << "\n ----- populating population with random chromosomes -----" << endl;
    pop->populatePopulation();



//    double acceptableSolutionLimit = (pop->getMaxGeneCount() - (pop->getMaxGeneCount() * 0.05));
    double acceptableSolutionLimit = (items->getKnapsackMaxWeight() - (items->getKnapsackMaxWeight() * 0.05));
    double maxFitness;

    pop = items->calcPopulationFitness(pop);
    pop->writePopulationToFile();
    pop->printPopulation();

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
            pop->elitism();


            pop = items->calcPopulationFitness(pop);
            maxFitness = pop->getBestChromFound()->getFitness();
//            if(maxFitness >= acceptableSolutionLimit){
//                cout << "Fitness [" << maxFitness
//                     << "] found at generation: "
//                     << i << "\n" << endl;
//                pop->getBestChromFound()->getChromosome();
//                 print best chromosome Log
//                items->printBestChromosomeLog();
//                break;
//            }
            cout << "\nFitness [" << maxFitness;
            cout << "] found at generation: " << i << endl;
        }

        items->printBestChromosomeLog();
    }

    return 0;
}