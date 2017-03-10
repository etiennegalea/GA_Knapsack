#include "./Population.h"

using std::cout;
using std::endl;
using namespace GA_Knapsack;

void Population::populatePopulation(){
    Chromosome* c = NULL;
    // for max population
    for (int i = 0; i < MAX_CHROM; ++i) {
        c = new Chromosome();
        c->populateChromosome();
        pop.push_back(c);
    }
}

void Population::printPopulation(){
    for (int i = 0; i < MAX_CHROM; ++i) {
        cout << "Chromosome " << i << " [" << getPop(i)->getFitness()
             << "/" << chromosomeSize << "]: ";
        getPop(i)->printChromosome();
    }
    cout << "\nAverage fitness: " << avgFitness << endl;
}

void Population::calcPopulationFitness() {
    cumulativeFitness = avgFitness = 0;
    for (int i = 0; i < MAX_CHROM; ++i) {
        pop.at(i)->calcChromosomeFitness();
        cumulativeFitness += pop.at(i)->getFitness();
    }
    avgFitness = (cumulativeFitness / MAX_CHROM);
}

void Population::getElite() {
//    Chromosome* tempChroms[MAX_ELITE]{nullptr};
    vector<Chromosome*> tempChroms = {nullptr};
    int fittest;
    int skipIndex[MAX_ELITE];
    bool skipIndexFlag;
    // iterate through out the list of chromosomes to find elite
    for (int i = 0; i < MAX_ELITE; ++i) {
        fittest = 0;
        skipIndex[i] = -1;
        skipIndexFlag = false;
        for (int index = 0; index < chromosomeSize; ++index) {
            if ((fittest < getPop(index)->getFitness())){
                // check all skipIndex array elements
                for (int j = 0; j < i; ++j) {
                    if(skipIndex[j] == index){
                        skipIndexFlag = true;
                        break;
                    }
                }
                if (skipIndexFlag == false){
                    fittest = getPop(index)->getFitness();
                    tempChroms.at(i) = getPop(index);
                    // on next iteration of 'i', it will skip this index
                    skipIndex[i] = index;
                }
            }
        }
        // store elite at element 'i'
        elite.at(i) = getPop(skipIndex[i]);
    }
}

void Population::replaceEliteWithWorst() {
    // save individual/s with best fitness as elite
    getElite();

    // find individuals with least fitness
    int unfit;
    int skipIndex[MAX_ELITE];
    bool skipIndexFlag;
    for (int i = 0; i < MAX_ELITE; ++i) {
        unfit = chromosomeSize; // start with max fitness
        skipIndex[i] = -1;
        skipIndexFlag = false;
        for (int index = 0; index < chromosomeSize; ++index) {
            if (unfit > getPop(index)->getFitness()){
                // check all skipIndex array elements
                for (int j = 0; j < i; ++j) {
                    if(skipIndex[j] == index){
                        skipIndexFlag = true;
                        break;
                    }
                }
                if (skipIndexFlag != false){
                    unfit = getPop(index)->getFitness();
                    // on next iteration of 'i', it will skip this index
                    skipIndex[i] = index;
                }
            }
        }
        // replace elite with individuals with worst fitness
        pop[skipIndex[i]] = elite.at(i);
    }
}

void Population::rouletteSelection() {
    vector<Chromosome*> newPop = {nullptr};
    double percentages[MAX_CHROM];

    for (int index = 0; index < MAX_CHROM; ++index) {
        percentages[index] = (getPop(index)->getFitness() / cumulativeFitness);
//        cout << percentages.at(index) << " ";
    }

    double spin;
    // generating new population via roulette wheel selection
    for (int i = 0; i < MAX_CHROM; ++i) {
        spin = roulette(engine);    // roulette spin
        for (int j = 0; j < MAX_CHROM; ++j) {
            spin -= percentages[j];
            if(spin < 0){
                newPop.at(i) = getPop(j);
                break;
            }
        }
    }

    // print newPop
    for(int index = 0; index < MAX_CHROM; index++)
    {
        pop.at(index) = newPop.at(index);
    }
//    calcPopulationFitness();
//    printPopulation();

}