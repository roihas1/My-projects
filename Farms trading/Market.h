//
// Created by roihas on 1/1/22.
//

#ifndef CPP_FARM_MARKET_H
#define CPP_FARM_MARKET_H
#include <vector>
#include <algorithm>
#include <iostream>
//#include "Farm.h"
#include "CowFarm.h"
#include "SheepFarm.h"
#include "ChickenFarm.h"
#include "Exceptions.h"
using namespace std;
class Market {
private:
    int m_year;
    vector<Farm*>Farms;
    bool createFarms();
    void tradeDay();
    void buyAnimals();
    void increaseYearToAnimalsAndAddMoney();
    void productivity();
public:
    Market();
    void nextYear();
    int getYear()const{return m_year;}
    void printMarketFarms();
    void fastForwardYears();
    ~Market();


};


#endif //CPP_FARM_MARKET_H
