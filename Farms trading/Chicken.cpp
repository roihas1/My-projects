//
// Created by roihas on 1/1/22.
//

#include "Chicken.h"
int Chicken::diedChicken =3;
int Chicken::chickenPrice=3;
bool Chicken::increaseAge() {
    if(animalAge+1 == diedChicken)
        return false;
    animalAge+=1;
    return true;
}

Chicken::~Chicken() = default;
