//
// Created by roihas on 1/1/22.
//

#ifndef CPP_FARM_SHEEPFARM_H
#define CPP_FARM_SHEEPFARM_H
#include "Farm.h"
#include "Sheep.h"
class SheepFarm: public Farm{
private:
    static int woolPrice;
public:

    SheepFarm();
    void buyAnimals() override;
    void buyEgg(Farm *buyer) override{};
    void buyMilk(Farm *buyer) override{};
    void buyWool(Farm *buyer) override;
    void buyFromChickenFarm(Farm *seller) override{};
    void buyFromCowFarm(Farm *seller) override;
    void buyFromSheepFarm(Farm *seller) override{};
    void printFarm() override;
    void farmProductivity() override;
    void addToClientList(Farm *client) override;
    void addSheepToCow(Farm *seller) override;
    int productPrice() override{return woolPrice;}
    ~SheepFarm(){};


};


#endif //CPP_FARM_SHEEPFARM_H
