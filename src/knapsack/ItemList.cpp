#include "ItemList.h"

void ItemList::populateList(){
    // for each gene in chromosome
    for (int i = 0; i < MAX_ITEMS; ++i) {
        list.push_back(new Item(rValue(engine), rWeight(engine)));
//        std::cout << list.at(i)->getValue() << "\t"
//                  << list.at(i)->getWeight() << endl;
    }
}

void ItemList::printList(){
    std::cout << "---- ITEMS IN LIST ----" << endl;
    for (int item = 0; item < MAX_ITEMS; ++item) {
        std::cout << item << ":\t";
        std::cout << "€" << list.at(item)->getValue()
                  << "\t\t" << list.at(item)->getWeight() << "kg"
                  << endl;
    }
}

Population* ItemList::calcPopulationFitness(Population *pop)
{
    double bestFitness = 0;
    double fitness;
    int totalWeight;
    bool overweightFlag = false;
    vector<int> temp;

    for (Chromosome* x : pop->getPopulation()){
        totalWeight = 0;
        fitness = 0;
        for (int i = 0; i < MAX_ITEMS; ++i) {
            // if item selected in individual
            if(x->getGene(i) == 1){
                if ((totalWeight + list.at(i)->getWeight()) <= KNAPSACK_MAX_WEIGHT){
                    // add value and weight to total
                    fitness += list.at(i)->getValue();
                    totalWeight += list.at(i)->getWeight();
                    temp.push_back(i);
                }else{
                    overweightFlag = true;
                }
            }
        }
        if(!overweightFlag){
            fitness -= fabs(totalWeight - KNAPSACK_MAX_WEIGHT);
            if( bestFitness < fitness){
                bestChromLog.chrom = x;
                bestChromLog.maxValue = fitness;
                bestChromLog.maxWeight = totalWeight;
                bestChromLog.itemList = temp;
            }
        }else{
            fitness = 0;
        }
        temp.clear();
        x->setFitness(fitness);
    }
    vector<int>().swap(temp); // clear allocated memory
    return pop;
}


void ItemList::printBestChromosomeLog()
{
    cout << "Best chromosome" << endl;
    cout << "Chromosome " << bestChromLog.chrom
         << " - value: " << bestChromLog.maxValue
         << " - weight: " << bestChromLog.maxWeight << endl;
    cout << "Items selected: ";
    for (int i : bestChromLog.itemList){
        cout << i << " ";
    }
    cout << endl;
}
































// page break (lmao)