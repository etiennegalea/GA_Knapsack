#include <sstream>
#include "./Chromosome.h"


void Chromosome::populateChromosome() {
    chrom.clear();
    for (int i = 0; i < maxGene; i++) {
        chrom.push_back(binary(engine));
    }
}

string Chromosome::getChromosome(){
    string genes = "";
    for (int i = 0; i < maxGene; ++i) {
        genes += getGene(i) + 48;
    }
    return genes;
}

void Chromosome::calcChromosomeFitness() {
    fitness = 0;
    for (int i = 0; i < maxGene; ++i) {
        if ((solution.at(i) - 48) == getGene(i)){
            fitness++;
        }
    }
}

void Chromosome::removeItemFromChromosome() {
    vector<int> temp;
    int selectedElement;
    // find all elements in chromosome where item is '1'
    for (int i = 0; i < chrom.size(); ++i) {
        if (chrom.at(i) == 1){
            temp.push_back(i);
        }
    }
    // get a random element from temp vector
    std::uniform_int_distribution<int> randomElement{0,temp.size()-1};
    selectedElement = temp.at(randomElement(engine));
    // remove item (element = 0)
    chrom.at(selectedElement) = 0;

    // unallocated memory for temp vector
    vector<int>().swap(temp);
}













// sakfgks