#pragma once

#include <iostream>

class Item {
private:
    int value;
    int weight;
public:
    //Genes will be creates either randomly or by an absolute list
    Item(int p_value, int p_weight){
        value = p_value;
        weight = p_weight;
    }

    ~Item(){

    }

    int getValue(){ return value; }
    int getWeight(){ return weight; }
};
