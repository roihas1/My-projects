//
// Created by roihas on 1/1/22.
//

#ifndef CPP_FARM_CHICKENFARM_H
#define CPP_FARM_CHICKENFARM_H
#include "Farm.h"
#include "Chicken.h"

class ChickenFarm: public Farm{
private:
    static int eggPrice;
public:

    ChickenFarm();
    void buyAnimals() override;
    void buyEgg(Farm *buyer) override;
    void buyMilk(Farm *buyer) override{};
    void buyWool(Farm *buyer) override{};
    void buyFromChickenFarm(Farm *seller) override{};
    void buyFromCowFarm(Farm *seller) override{};
    void buyFromSheepFarm(Farm *seller) override;
    void printFarm() override;
    void farmProductivity() override;
    void addToClientList(Farm *client) override;
    void addChickenToSheep(Farm *seller) override;
    int productPrice() override{return eggPrice;}
    ~ChickenFarm(){};
};


#endif //CPP_FARM_CHICKENFARM_H
