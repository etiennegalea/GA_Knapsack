#include "ItemList.h"
#include "../chromosome/Chromosome.h"

using std::cout;
using std::endl;

void ItemList::populateList(){
    // for each gene in chromosome
    for (int i = 0; i < MAX_ITEMS; ++i) {
        list.push_back(new Item(rValue(engine), rWeight(engine)));
        std::cout << list.at(i)->getValue() << "\t"
                  << list.at(i)->getWeight() << endl;
    }
}

void ItemList::printList(){
    std::cout << "---- ITEMS IN LIST ----" << endl;
    for (int item = 0; item < MAX_ITEMS; ++item) {
        std::cout << "[" << item << "] -> ";
        std::cout << "value: " << list.at(item)->getValue()
                  << "\tweight: " << list.at(item)->getWeight()
                  << endl;

    }
}