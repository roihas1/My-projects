//
// Created by roihas on 1/1/22.
//

#ifndef CPP_FARM_COWFARM_H
#define CPP_FARM_COWFARM_H
#include "Farm.h"
#include "Cow.h"

class CowFarm: public Farm{
private:
    static int milkPrice;
public:

    CowFarm();
    void buyAnimals() override;
    void buyEgg(Farm *buyer) override{};
    void buyMilk(Farm *buyer) override;
    void buyWool(Farm *buyer) override{};
    void buyFromChickenFarm(Farm *seller) override;
    void buyFromCowFarm(Farm *seller) override{};
    void buyFromSheepFarm(Farm *seller) override{};
    void printFarm() override;
    void farmProductivity() override;
    void addToClientList(Farm *client) override;
    void addCowToChicken(Farm *seller) override;
    int productPrice() override{return milkPrice;}
    ~CowFarm(){};
};


#endif //CPP_FARM_COWFARM_H
