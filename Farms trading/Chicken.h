//
// Created by roihas on 1/1/22.
//

#ifndef CPP_FARM_CHICKEN_H
#define CPP_FARM_CHICKEN_H
#include "Animal.h"

class Chicken:public Animal {
protected:
    static int chickenPrice;
    static int diedChicken;


public:

    Chicken()= default;
    static int getPrice() {return chickenPrice;}
    static int getDied() {return diedChicken;}
    bool increaseAge() override;
    ~Chicken();



};


#endif //CPP_FARM_CHICKEN_H
