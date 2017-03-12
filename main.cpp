#include <iostream>
#include "./src/Population.h"
#include "./src/knapsack/ItemList.h"

using std::cout;
using std::endl;

int main(){

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
    pop->calcPopulationFitness();
    pop->printPopulation();
//    cout << "\n ----- printing whole population -----" << endl;
//    pop->replaceEliteWithWorst();
//    pop->printPopulation();

    pop->rouletteSelection();

//    pop->calcPopulationFitness();
//    pop->printPopulation();

    return 0;
}