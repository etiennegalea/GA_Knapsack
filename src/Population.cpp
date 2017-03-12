#include "./Population.h"

using std::cout;
using std::endl;

void Population::populatePopulation(){
    Chromosome* c = NULL;
    // for max population
    for (int i = 0; i < MAX_CHROM; i++) {
        c = new Chromosome();
        c->populateChromosome();
        pop.push_back(c);
    }
}

void Population::printPopulation(){
    for (int i = 0; i < MAX_CHROM; ++i) {
        cout << "Chromosome " << i << " [" << getPop(i)->getFitness()
             << "/" << chromosomeSize << "]:\t";
        getPop(i)->printChromosome();
    }
    cout << "\nAverage fitness: " << avgFitness << endl;
}

void Population::calcPopulationFitness() {
    avgFitness = 0;
    cumulativeFitness = 0;
    for(Chromosome *x : pop){
        x->calcChromosomeFitness();
        cumulativeFitness += x->getFitness();
    }
    avgFitness = (cumulativeFitness / MAX_CHROM);
}

void Population::getElite() {
    Chromosome* tempChroms[MAX_ELITE]{nullptr};
    int fittest;
    int skipIndex[MAX_ELITE];
    bool skipIndexFlag;
    // iterate through out the list of chromosomes to find elite
    for (int i = 0; i < MAX_ELITE; ++i) {
        fittest = 0;
        skipIndex[i] = -1;
        skipIndexFlag = false;
        for (int index = 0; index < MAX_CHROM; ++index) {
            if ((fittest < getPop(index)->getFitness())){
                // check all skipIndex array elements
                for (int j = 0; j < i; ++j) {
                    if(skipIndex[j] == index){
                        skipIndexFlag = true;
//                        break;
                    }
                }
                if (skipIndexFlag == false){
                    fittest = getPop(index)->getFitness();
                    tempChroms[i] = getPop(index);
                    // on next iteration of 'i', it will skip this index
                    skipIndex[i] = index;
                }
            }
        }
        // store elite at element 'i'
        elite[i] = getPop(skipIndex[i]);
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
        skipIndex[i] = NULL;
        skipIndexFlag = false;
        for (int index = 0; index < MAX_CHROM; ++index) {
            if (unfit > getPop(index)->getFitness()){
                // check all skipIndex array elements
                for (int skipIterator = 0; skipIterator < i; ++skipIterator) {
                    if(skipIndex[skipIterator] == index){
                        skipIndexFlag = true;
                        break;
                    }
                }
                if (skipIndexFlag){
                    unfit = getPop(index)->getFitness();
                    // on next iteration of 'i', it will skip this index
                    skipIndex[i] = index;
                }
            }
        }
        // replace elite with individuals with worst fitness
//        pop.at(skipIndex[i]) = elite[i];
    }
}

void Population::rouletteSelection() {
    vector<Chromosome*> newPop;
    double percentages[MAX_CHROM];

    if(eliteSwitch){
        replaceEliteWithWorst();
        for(Chromosome *x : elite)
            newPop.push_back(x);
    }

    // also include elite individuals in roulette selection
    for (int index = 0; index < MAX_CHROM; ++index) {
        percentages[index] = (getPop(index)->getFitness() / cumulativeFitness);
//        cout << percentages.at(index) << " ";
    }

    double spin;
    // generating new population via roulette wheel selection
    for (int i = 0; i < (MAX_CHROM-MAX_ELITE); ++i) {
        spin = roulette(engine);    // roulette spin
        for (int j = 0; j < MAX_CHROM; ++j) {
            spin -= percentages[j];
            if(spin < 0){
                newPop.push_back(getPop(j));
                break;
            }
        }
    }

    // replace with newPop

    pop = newPop;
//    for(int index = 0; index < MAX_CHROM; index++)
//    {
//        pop.at(index) = newPop.at(index);
//    }

//    pop.swap(newPop);

    calcPopulationFitness();
    printPopulation();

}