#include <algorithm>
#include <bits/unique_ptr.h>
#include "./Population.h"


// solution will be composed of '1's for testing purposes
string Population::generateSolution() {
    for (int i = 0; i < maxGene; i++){
        solution.push_back('1');
    }
    return solution;
}


void Population::populatePopulation(){
    Chromosome* c = NULL;
    solution = generateSolution();
    // for max population
    for (int i = 0; i < MAX_CHROM; i++) {
        c = new Chromosome(maxGene, solution);
        c->populateChromosome();
        pop.push_back(c);
    }
}

void Population::printPopulation(){
//    calcPopulationFitness();
    int i = 0;
    for(Chromosome* x : pop){
        cout << "Chromosome " << i << " [" << getPop(i)->getFitness()
             << "/" << maxGene << "]:\t";
        cout << getPop(i)->getChromosome() << endl;
        i++;
    }
    cout << "\nAverage fitness: " << avgFitness << "\n" << endl;
}

void Population::calcPopulationFitness() {
    avgFitness = 0;
    cumulativeFitness = 0;
    int maxChrom = 0;
    for(Chromosome *x : pop){
        maxChrom++;
//        x->calcChromosomeFitness();
        cumulativeFitness += x->getFitness();
    }
    avgFitness = (cumulativeFitness / maxChrom);
}

Chromosome* Population::getBestChromFound(){
    bestChrom = pop.at(0);
    for (Chromosome* x : pop){
        if(bestChrom->getFitness() < x->getFitness()){
            bestChrom = x;
        }
    }
    return bestChrom;
}

// insert elite in population
void Population::elitism(){
    replaceWorstWithElite();
//    for (Chromosome* x : elite){
//        pop.push_back(x);
//    }
}

// find the best individuals from the population (best fitness)
void Population::getElite() {
    double fittest;
    int skipIndex[MAX_ELITE];
    bool skipIndexFlag;
    // iterate through out the list of chromosomes to find elite
    for (int i = 0; i < MAX_ELITE; ++i) {
        fittest = 0;
        skipIndex[i] = MAX_CHROM + 1;   // set value out of bounds
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
                    // on next iteration of 'i', it will skip this index
                    skipIndex[i] = index;
                }
            }
        }
        // store elite at element 'i'
        elite[i] = getPop(skipIndex[i]);
    }
}

// find the worst individuals from the population (least fitness)
void Population::replaceWorstWithElite() {
    double unfit;
    int skipIndex[MAX_ELITE];
    bool skipIndexFlag;
    for (int i = 0; i < MAX_ELITE; ++i) {
        unfit = maxGene; // start with max fitness
        skipIndex[i] = -1;
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
        // replace worst with elite
        pop.at(skipIndex[i]) = elite[i];
    }
}


void Population::rouletteSelection() {
    vector<Chromosome*> newPop;
    double percentages[MAX_CHROM];
    int rouletteSpins = (eliteBeforeCrossover) ? (MAX_CHROM - MAX_ELITE) : MAX_CHROM;
//    int rouletteSpins = MAX_CHROM - MAX_ELITE;

    calcPopulationFitness();
    getElite();

    if(eliteBeforeCrossover){
//        replaceWorstWithElite();
        for (Chromosome* x : elite){
            newPop.push_back(x);
        }
    }

    // also include elite individuals in randomProb selection
    for (int index = 0; index < MAX_CHROM; ++index) {
        percentages[index] = (pop.at(index)->getFitness() / cumulativeFitness);
    }

    double spin;
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
    pop.clear();
    for(Chromosome *x : newPop){
        pop.push_back(x);
    }

    // swapping newPop with an empty, unallocated vector to
    // deallocate memory taken by newPop
    vector<Chromosome*>().swap(newPop);
}

// traverse population one by one and mate each individual with the next one
// (last mates with first) if crossover condition is satisfied.
void Population::crossover() {
    vector<Chromosome*> newPop;
    // choose a random point from chromosome and
    // exchange parts between both parents

    for (int i = 0; i < MAX_CHROM-1; i++) {
        newPop.push_back(singlePointCrossover(pop.at(i), pop.at(i+1)));
    }
    // mate last and first parents
    newPop.push_back(singlePointCrossover(pop.back(), pop.front()));

    pop.clear();
    for(Chromosome *x : newPop)
        pop.push_back(x);

    vector<Chromosome*>().swap(newPop);
}

Chromosome* Population::singlePointCrossover(Chromosome *p_father, Chromosome *p_mother) {
    // if crossover condition is satisfied
//    auto child = std::unique_ptr<Chromosome>(new Chromosome());
    Chromosome *child = new Chromosome(maxGene, solution);
    if (randomProb(engine) < CROSSOVER_PROB) {
        int maxSize = 0;
        // set max boundary for random point
        maxSize = maxGene;
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
    vector<Chromosome*> newPop;
    for (Chromosome* x : pop){
        if(mutationRate(engine) < MUTATION_PROB){
            newPop.push_back(singlePointMutation(x));
        }else{
            newPop.push_back(x);
        }
    }

    // replace population
    pop.clear();
    for(Chromosome *x : newPop)
        pop.push_back(x);

    vector<Chromosome*>().swap(newPop);
}

Chromosome* Population::singlePointMutation(Chromosome *p_chrom) {
    int maxSize = maxGene-1;
    // set mersenne twister-based mutation point
    std::uniform_int_distribution<int> mPoint{1, maxSize};
    int mutationPoint = mPoint(engine);
    // switch gene at selected point
    int value = (p_chrom->getGene(mutationPoint) == 0) ? 1 : 0;
    p_chrom->setGene(mutationPoint, value);

    return p_chrom;
}

void Population::writePopulationToFile(){

    // get time/date as string
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer),"%d-%m-%Y_%I.%M.%S",timeinfo);
    std::string date(buffer);

    // concatenate string date/time with file name
    string fileName = "population_";
    string nameDateFile = fileName + date + ".txt";

    // write to file
    std::ofstream file (nameDateFile);
    if(file.is_open()){
        for(Chromosome* x : pop){
            file << x->getChromosome() << endl;
        }
        file.close();
    }
}























// ayyyyyyyyyyyy lmao page break