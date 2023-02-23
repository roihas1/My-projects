//
// Created by roihas on 1/1/22.
//

#ifndef CPP_FARM_COW_H
#define CPP_FARM_COW_H
#include "Animal.h"

class Cow: public Animal{
protected:
    static int cowPrice;
    static int diedCow;
public:

    Cow()= default;
    static int getPrice()  {return cowPrice;}
    static int getDied() {return diedCow;}
    bool increaseAge() override;
    ~Cow();

};


#endif //CPP_FARM_COW_H
