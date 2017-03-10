#pragma once

#include <iostream>

using namespace std;

class Item {
private:
    int value;
    int size;
public:
    //Genes will be creates either randomly or by an absolute list
    Item(int p_value, int p_size){
        value = p_value;
        size = p_size;
    }

    ~Item(){

    }

    int getValue(){ return this->value; }
    int getSize(){ return this->size; }


};
