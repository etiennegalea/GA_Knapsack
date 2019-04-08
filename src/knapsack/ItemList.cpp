#include "ItemList.h"

void ItemList::populateList(){
    // for each gene in chromosome
    for (int i = 0; i < maxItems; ++i) {
        list.push_back(new Item(rValue(engine), rWeight(engine)));
//        std::cout << list.at(i)->getValue() << "\t"
//                  << list.at(i)->getWeight() << endl;
    }
}

// based on maxKnapsackWeight = 50kg
void ItemList::populateTestList(){
    list.push_back(new Item(6, 5));
    list.push_back(new Item(12, 7));
    list.push_back(new Item(17, 11));
    list.push_back(new Item(50, 32));
    list.push_back(new Item(75, 45));
}

void ItemList::printList(){
    std::cout << ":::: ITEMS IN LIST ::::\n" << endl;
    for (int item = 0; item < maxItems; ++item) {
        std::cout << item << ":\t";
        std::cout << "$" << list.at(item)->getValue()
                  << "\t\t" << list.at(item)->getWeight() << "kg"
                  << endl;
    }
}

Population* ItemList::calcPopulationFitness(Population *pop)
{
    int count = 0;
    for (Chromosome* x : pop->getPopulation()){
        x = calcChromosomeFitness(x, count);
        count++;
    }
    return pop;
}

Chromosome* ItemList::calcChromosomeFitness(Chromosome* x, int count){
    double fitness;
    double totalValue, totalWeight;
    bool overweightFlag = false;
    vector<int> temp;

    do{
        totalValue = totalWeight = fitness = 0;
        overweightFlag = false;
        for (int i = 0; i < maxItems; ++i) {
            // if item selected in individual
            if(x->getGene(i) == 1){
                // add value and weight to total
                totalValue += list.at(i)->getValue();
                totalWeight += list.at(i)->getWeight();
                temp.push_back(i);
                if(totalWeight > maxKnapsackWeight){
                    overweightFlag = true;
                    break;
                }
            }
        }
        // if knapsack overweight, remove one item from chromosome at random
        if (overweightFlag){
            // randomize chromosome
            x->removeItemFromChromosome();
        }else{
            fitness = totalValue;
            if(bestChromLog.fitness < fitness){
                bestChromLog.chrom = x;
                bestChromLog.index = count;
                bestChromLog.fitness = fitness;
                bestChromLog.maxValue = totalValue;
                bestChromLog.maxWeight = totalWeight;
                bestChromLog.itemList = temp;
            }
            temp.clear();
            x->setFitness(fitness);
        }
    }while(overweightFlag);

    vector<int>().swap(temp); // clear allocated memory
    return x;
}


void ItemList::printBestChromosomeLog()
{
    cout << "\n:::::::: Best chromosome ::::::::" << endl;
    cout << "\nvalue: " << bestChromLog.maxValue << endl;
    cout << "weight: " << bestChromLog.maxWeight << endl;
    cout << "Items selected: ";
    for (int i : bestChromLog.itemList){
        cout << i << " ";
    }
    cout << "\nchromosome " << bestChromLog.index << ": " << bestChromLog.chrom->getChromosome() << endl;
    cout << "memory location: " << bestChromLog.chrom << endl;
}


void ItemList::calculateMaxValue() {
    maxValueOfItemList = 0;
    for (Item* i : list){
        maxValueOfItemList += i->getValue();
    }
}


void ItemList::writeItemListToFile(){
    // write to file
    std::ofstream file ("../logs/itemlist.dat");
    if(file.is_open()){
        for(Item *i : list){
            file << i->getValue() << " " << i->getWeight() << " \n";
        }
        file.close();
    }
    else{
        cout << "file is closed!" << endl;
    }
}


void ItemList::readItemListFromFile() {
    // read from file
    int value, weight;
    std::ifstream myfile_read("../logs/itemlist.dat");
    if(myfile_read.is_open()){
        while(myfile_read >> value >> weight){
    // cout << "€" << value << " " << weight << "kg" << '\n';
            list.push_back(new Item(value, weight));
        }
        myfile_read.close();
    }else{
        cout << "unable to open file";
    }

}