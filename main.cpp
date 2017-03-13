#include <iostream>
#include <zconf.h>
#include "./src/Population.h"
#include "./src/knapsack/ItemList.h"

using std::cout;
using std::endl;

int main(){

    // termination conditions
    static const bool TERMINATION_BY_FITNESS = false;
    static const bool TERMINATION_BY_TIME = false;
    static const bool TERMINATION_BY_GENERATION = true;

    static const int GENERATION_LIMIT = 10;

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

    // termination by generation
    if(TERMINATION_BY_GENERATION){
        for (int i = 0; i < GENERATION_LIMIT; i++){
            cout << " ---- Generation: " << i+1 << " ----\n" << endl;

            // genetic algorithms (selection, crossover, mutation)
            pop->calcPopulationFitness();
            pop->rouletteSelection();
//        pop->printPopulation();
//            pop->crossover();

            pop->printPopulation();
        }
    }





//    pop->rouletteSelection();

    return 0;
}