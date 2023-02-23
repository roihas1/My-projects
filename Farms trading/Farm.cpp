//
// Created by roihas on 1/1/22.
//

#include "Farm.h"
int Farm::numFarm=0;
Farm::Farm() {
    numFarm+=1;
    Money = 10;
    ID = numFarm;
    m_milk = 0;
    m_egg = 0;
    m_wool = 0;
    my_products =0;
}

int Farm::getID() const {
    return ID;
}


void Farm::increaseYearToAnimal() {
    int i=0;
    while( i != v_animalArray.size()){
        if(!v_animalArray[i]->increaseAge()){
                 delete v_animalArray[i];
                 v_animalArray.erase(v_animalArray.begin()+i);
        }
        else{
            i++;
        }
    }
}

void Farm::addMoney() {
    Money +=10;
}

Farm::~Farm() {
    int  i;
    for(i=0;i<v_animalArray.size();i++) {
        delete v_animalArray[i];
    }
    v_animalArray.clear();
}






