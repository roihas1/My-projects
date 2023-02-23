//
// Created by roihas on 1/1/22.
//

#include "Sheep.h"
int Sheep::diedSheep = 5;
int Sheep::sheepPrice =5;
bool Sheep::increaseAge() {
    if(animalAge+1 == diedSheep)
        return false;
    animalAge+=1;
    return true;
}

Sheep::~Sheep() = default;
