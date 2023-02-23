//
// Created by roihas on 1/1/22.
//

#include "Cow.h"
int Cow::diedCow =10;
int Cow::cowPrice =10;
bool Cow::increaseAge() {
   if(animalAge +1 == diedCow)
       return false;
   animalAge +=1;
   return true;
}

Cow::~Cow() = default;
