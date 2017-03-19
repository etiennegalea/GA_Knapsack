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
    std::cout << "---- ITEMS IN LIST ----" << endl;
    for (int item = 0; item < maxItems; ++item) {
        std::cout << item << ":\t";
        std::cout << "€" << list.at(item)->getValue()
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
    cout << "\n--- Best chromosome ---" << endl;
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


void ItemList::writePopulationToFile(){

    // get time/date as string
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer),"%d-%m-%Y_%I.%M.%S",timeinfo);
    std::string date(buffer);

    // concatenate string date/time with file name
    string fileName = "../logs/itemlist_";
    string nameDateFile = fileName + date + ".dat";

    // write to file
    std::ofstream file (nameDateFile);
    if(file.is_open()){
        file << "Max knapsack weight: " << maxKnapsackWeight << "\n";
        file << "Max amount of items: " << maxItems << "\n\n";
        file << "#\tvalue\tweight\tmemloc\n";
        int count = 0;
        for(Item *i : list){
            file << count << "\t" << i->getValue() << "\t\t" << i->getWeight() << "\t\t" << i << "\n";
            count++;
        }
        file.close();
    }
}