#include <algorithm>
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
    cout << "\nAverage fitness: " << avgFitness << "\n" << endl;
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
//    Chromosome* tempChroms[MAX_ELITE]{nullptr};
    int fittest;
    int skipIndex[MAX_ELITE];
    bool skipIndexFlag;
    // iterate through out the list of chromosomes to find elite
    for (int i = 0; i < MAX_ELITE; ++i) {
        fittest = 0;
        skipIndex[i] = NULL;
        skipIndexFlag = false;
        for (int index = 0; index < MAX_CHROM; ++index) {
            if ((fittest < getPop(index)->getFitness())){
                // check all skipIndex array elements
                for (int j = 0; j < i; ++j) {
                    if(skipIndex[j] == index){
                        skipIndexFlag = true;
                        break;
                    }
                }
                if (!skipIndexFlag){
                    fittest = getPop(index)->getFitness();
//                    tempChroms[i] = getPop(index);
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
                if (!skipIndexFlag){
                    unfit = getPop(index)->getFitness();
                    // on next iteration of 'i', it will skip this index
                    skipIndex[i] = index;
                }
            }
        }
    }
}

void Population::rouletteSelection() {
    vector<Chromosome*> newPop;
    double percentages[MAX_CHROM];

    if(eliteSwitch){
//        replaceEliteWithWorst();
        getElite();
        for(Chromosome *x : elite)
            newPop.push_back(x);
    }

    // also include elite individuals in randomProb selection
    for (int index = 0; index < MAX_CHROM; ++index) {
        percentages[index] = (getPop(index)->getFitness() / cumulativeFitness);
//        cout << percentages.at(index) << " ";
    }

    double spin;

    int rouletteSpins = (eliteSwitch) ? (MAX_CHROM - MAX_ELITE) : MAX_CHROM;
    // generating new population via randomProb wheel selection
    for (int i = 0; i < rouletteSpins; ++i) {
        spin = randomProb(engine);    // randomProb spin
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

//    calcPopulationFitness();
//    printPopulation();
}

// traverse population one by one and mate each individual with the next one
// (last mates with first) if crossover condition is satisfied.
void Population::crossover() {
    vector<Chromosome*> crossoverPop;
    // choose a random point from chromosome and
    // exchange parts between both parents
    for (int i = 0; i < pop.size()-1; ++i) {
        crossoverPop.push_back(singlePointCrossover(pop.at(i), pop.at(i+1)));
    }
    // mate last and first parents
    crossoverPop.push_back(singlePointCrossover(pop.back(), pop.front()));

    pop = crossoverPop;
}

Chromosome* Population::singlePointCrossover(Chromosome *p_father, Chromosome *p_mother) {
    // if crossover condition is satisfied
    Chromosome *child = new Chromosome();
    if (randomProb(engine) < CROSSOVER_PROB) {
        int maxSize = 0;
        // set max boundary for random point
        maxSize = p_father->getChromosomeSize();
        // set mersenne twister-based crossover point
        std::uniform_int_distribution<int> cPoint{1, maxSize};
        double crossoverPoint = cPoint(engine);
        for (int j = 0; j < maxSize; ++j) {
            if (j < crossoverPoint) {
                // copy gene of first part of parent to child
                child->setGene(p_father->getGene(j));
            } else {
                // copy gene of last part of second parent to child
                child->setGene(p_mother->getGene(j));
            }
        }
        // push child to new population
        return child;
    }else{
        return p_father;
    }
}



void Population::mutation() {
    vector<Chromosome*> mutationPop;
    for (int chromIndex = 0; chromIndex < pop.size(); ++chromIndex) {
        if(mutationRate(engine) < MUTATION_PROB){
            singlePointMutation(pop.at(chromIndex));
        }
    }

    // replace population
    pop = mutationPop;
}

Chromosome* Population::singlePointMutation(Chromosome *p_chrom) {
    int maxSize = p_chrom->getChromosomeSize();
    // set mersenne twister-based mutation point
    std::uniform_int_distribution<int> mPoint{1, maxSize};
    int mutationPoint = mPoint(engine);
    // switch gene at selected point
    int value = (p_chrom->getGene(mutationPoint) == 0) ? 1 : 0;
    p_chrom->setGene(mutationPoint, value);

    return p_chrom;
}


// overload operator= assignment





























// ayyyyyyyyyyyy lmao page break