//
// Created by roihas on 1/1/22.
//

#include "CowFarm.h"
int CowFarm::milkPrice=3;
CowFarm::CowFarm() {
    for (int i = 0; i < 3; ++i) {
        Animal* c = new Cow();
        v_animalArray.push_back(c);
    }
}


void CowFarm::buyAnimals() {
    int count =0;
    while(Money - Cow::getPrice() >= 0){
        Animal * a = new Cow();
        Money -= Cow::getPrice();
        v_animalArray.push_back(a);
        count += 1;
    }
    if(count > 0)
        cout<<"Cow farm("<<getID()<<") bought "<<count<<" cows for "<<count*Cow::getPrice()<<" dollars"<<endl;
}

void CowFarm::buyMilk(Farm *buyer) {
    buyer->buyFromCowFarm(this);
}

void CowFarm::buyFromChickenFarm(Farm *seller) {
    int counter=0;

   while( Money -seller->productPrice() >= 0 && seller->getMyProductsNum() > 0){
       m_egg += 1;
       Money -= seller->productPrice();
       seller->setMyProductsNum(seller->getMyProductsNum() -1);
       seller->setMoney(seller->getMoney()+1);
       counter++;
   }
   if(counter>0) {
       cout << "Cow farm(" << getID() << ") bought " << counter << " eggs for " << counter << " dollars";
       cout << " from Chicken farm(" << seller->getID() << ")" << endl;
   }
}

void CowFarm::printFarm() {
    cout<<"Farm Id: "<<getID()<<", type: Cow farm, Money: "<<Money;
    cout<<", Animals: "<<v_animalArray.size()<<" cows, Products: Milk["<<my_products<<"], ";
    cout<<"Wool["<<m_wool<<"], Eggs["<<m_egg<<"]"<<endl;

}

void CowFarm::farmProductivity() {
    int i;
    for(i = 0; i<v_animalArray.size();i++){
        my_products+=v_animalArray[i]->getAnimalAge();

    }
}

void CowFarm::addToClientList(Farm *client) {
    client->addSheepToCow(this);

}

void CowFarm::addCowToChicken(Farm *seller) {
    cout<<"Chicken farm("<<seller->getID()<<") Added Cow farm("<<getID()<<") to his client list\n";

}



