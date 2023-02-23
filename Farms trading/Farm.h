#ifndef CPP_FARM_FARM_H
#define CPP_FARM_FARM_H
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include "Animal.h"

using namespace std;


class Farm {
private:
    int ID;
    static int numFarm;
protected:
    int Money;
    vector<Animal*> v_animalArray;
    int my_products;
    int m_milk;
    int m_wool;
    int m_egg;

public:

 Farm();
 virtual int getID() const;
 int getMyProductsNum()const{return my_products;}
 void setMyProductsNum(int num){my_products = num;}
 void setMoney(int num){Money = num;}
 int getMoney()const{return Money;}
 virtual void farmProductivity()=0;
 virtual void buyAnimals(){};
 virtual void buyMilk(Farm *buyer){};
 virtual void buyWool(Farm *buyer){};
 virtual void buyEgg(Farm*buyer){};
 virtual void buyFromCowFarm(Farm *seller){};
 virtual void buyFromSheepFarm(Farm *seller){};
 virtual void buyFromChickenFarm(Farm *seller){};
 virtual void increaseYearToAnimal();
 virtual void addToClientList(Farm * client)=0;
 virtual void addSheepToCow(Farm * seller){};
 virtual void addChickenToSheep(Farm* seller){};
 virtual void addCowToChicken(Farm* seller){};
 void addMoney();
 virtual void printFarm()=0;
 virtual int productPrice() =0;

 ~Farm();

};


#endif //CPP_FARM_FARM_H
