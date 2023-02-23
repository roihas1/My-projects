//
// Created by roihas on 1/1/22.
//

#ifndef CPP_FARM_SHEEP_H
#define CPP_FARM_SHEEP_H
#include "Animal.h"

class Sheep: public Animal{
private:
    static int sheepPrice;
    static int diedSheep;
public:

    Sheep()= default;
    static int getPrice() {return sheepPrice;}
    static int getDied() {return diedSheep;}
    bool increaseAge() override;
    ~Sheep();

};


#endif //CPP_FARM_SHEEP_H
