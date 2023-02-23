//
// Created by roihas on 1/1/22.
//

#include "SheepFarm.h"
int SheepFarm::woolPrice =2;
SheepFarm::SheepFarm() {
    for (int i = 0; i < 3; ++i) {
        Animal* s = new Sheep();
        v_animalArray.push_back(s);
    }
}


void SheepFarm::buyAnimals() {
    int count =0;
    while(Money - Sheep::getPrice() >= 0 ){
        Animal *a = new Sheep();
        v_animalArray.push_back(a);
        Money -= Sheep::getPrice();
        count +=1;
    }
    if(count>0)
        cout<<"Sheep farm("<<getID()<<") bought "<<count<<" sheeps for "<<count*Sheep::getPrice()<< " dollars"<<endl;
}

void SheepFarm::buyWool(Farm *buyer) {
    buyer->buyFromSheepFarm(this);
}

void SheepFarm::buyFromCowFarm(Farm *seller) {
    int counter=0;

    while(Money - seller->productPrice() >=0 && seller->getMyProductsNum() > 0){
        m_milk +=1;
        Money -= seller->productPrice();
        seller->setMyProductsNum(seller->getMyProductsNum()-1);
        seller->setMoney(seller->getMoney()+seller->productPrice());
        counter++;
    }
    if(counter > 0) {
        cout << "Sheep farm(" << getID() << ") bought " << counter << " milk for " << counter * seller->productPrice()<< " dollars";
        cout << " from Cow farm(" << seller->getID() << ")" << endl;
    }

}

void SheepFarm::printFarm() {
    cout<<"Farm Id: "<<getID()<<", type: Sheep farm, Money: "<<Money;
    cout<<", Animals: "<<v_animalArray.size()<<" sheep, Products: Milk["<<m_milk<<"], ";
    cout<<"Wool["<<my_products<<"], Eggs["<<m_egg<<"]"<<endl;

}

void SheepFarm::farmProductivity() {
    int i;
    for(i = 0; i<v_animalArray.size();i++){
        my_products+=v_animalArray[i]->getAnimalAge();
    }

}

void SheepFarm::addToClientList(Farm *client) {
   client->addChickenToSheep(this);


}

void SheepFarm::addSheepToCow(Farm *seller) {

    cout<<"Cow farm("<<seller->getID()<<") Added Sheep farm("<<getID()<<") to his client list\n";

}
