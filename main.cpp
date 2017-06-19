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
    static const int GENERATION_LIMIT = 100;

    static const int MAX_KNAPSACK_WEIGHT = 50;
    static const int MAX_ITEMS = 100;
    static const int MAX_CHROM = 50;
    static const int MAX_ELITE = 2;
    static constexpr double CROSSOVER_PROB = 0.85;
    static constexpr double MUTATION_PROB = 0.1;

    cout << "\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << ":::::::::::::::: GENETIC ALGORITHM FOR THE KNAPSACK PROBLEM ::::::::::::::::" << endl;
    cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: \n" << endl;

    cout << "\n\tMax Knapsack weight:\t\t" << MAX_KNAPSACK_WEIGHT << endl;
    cout << "\tMin & Max item value:\t\t5 - 20" << endl;
    cout << "\tMin & Max item weight:\t\t1 - 5\n" << endl;

    cout << "\tMax population size:\t\t" << MAX_CHROM << endl;
    cout << "\tMax chromosome length:\t\t" << MAX_ITEMS << endl;
    cout << "\tMax elite chromosomes:\t\t" << MAX_ELITE << endl;
    cout << "\tCrossover rate:\t\t\t\t" << CROSSOVER_PROB*100 << "%" << endl;
    cout << "\tMutation rate:\t\t\t\t" << MUTATION_PROB*100 << "%" << endl;

    cout << "\n\tTermination condition:\t\tGeneration limit [" << GENERATION_LIMIT << "]" << endl;

    cout << "\n\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: \n" << endl;


    cout << "\n\n\nPress 'enter' to continue..." << endl;
    getchar();

    cout << "\n\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: \n" << endl;

    ItemList* items = new ItemList(MAX_KNAPSACK_WEIGHT, MAX_ITEMS);
//    cout << "create random list of items in 'itemlist'" << endl;

    items->populateList();
    items->writeItemListToFile();
//    items->readItemListFromFile();

    items->calculateMaxValue();

    items->printList(); // print list of items w/ value and weight


    Population* pop = new Population(MAX_ITEMS, MAX_CHROM, MAX_ELITE, CROSSOVER_PROB, MUTATION_PROB);
    cout << "\n\n:::::::::::::::: populating population with random chromosomes ::::::::::::::::\n" << endl;
    pop->populatePopulation();


    double acceptableSolutionLimit = (items->getKnapsackMaxValue() - (items->getKnapsackMaxValue() * 0.05));
    double maxFitness;

    pop = items->calcPopulationFitness(pop);
    pop->writePopulationToFile();
    pop->printPopulation();

    // termination by generation
    if(TERMINATION_BY_GENERATION || TERMINATION_BY_FITNESS){
        for (int i = 1; i < GENERATION_LIMIT+1; i++){
            // calculate fitness of population

            // --- uncomment below line to see population changes ---
            // pop->printPopulation();

            // cout << "Generation: " << i << " -- ";
            // cout << "max fitness found: " << maxFitness << endl;
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
            cout << "Generation [" << i;
            cout << "] - Max Fitness -> " << maxFitness << endl;
        }
        items->printBestChromosomeLog();
    }

    return 0;
}