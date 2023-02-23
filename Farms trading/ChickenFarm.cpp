//
// Created by roihas on 1/1/22.
//

#include "ChickenFarm.h"
int ChickenFarm::eggPrice =1;
ChickenFarm::ChickenFarm() {
    for (int i = 0; i < 3; ++i) {
        Animal* c = new Chicken();
        v_animalArray.push_back(c);
    }
}

void ChickenFarm::buyAnimals() {
    int count=0;
    while(Money - Chicken::getPrice() >= 0){
        Animal * a = new Chicken();
        v_animalArray.push_back(a);
        Money-=Chicken::getPrice();
        count+=1;
    }
    if(count > 0)
        cout<<"Chicken farm("<<getID()<<") bought "<<count<<" chickens for "<<count*Chicken::getPrice()<<" dollars"<<endl;
}

void ChickenFarm::buyEgg(Farm *buyer) {
    buyer->buyFromChickenFarm(this);
}

void ChickenFarm::buyFromSheepFarm(Farm *seller) {
    int counter =0;

    while(Money - seller->productPrice() >= 0 && seller->getMyProductsNum() >0){
        m_wool += 1;
        Money -= seller->productPrice();
        seller->setMyProductsNum(seller->getMyProductsNum() -1);
        seller->setMoney(seller->getMoney()+2);
        counter++;
    }
    if(counter >0) {
        cout << "Chicken farm(" << getID() << ") bought " << counter << " wool for " << counter*seller->productPrice() << " dollars";
        cout << " from Sheep farm(" << seller->getID() << ")" << endl;
    }
}

void ChickenFarm::printFarm() {
    cout<<"Farm Id: "<<getID()<<", type: Chicken Farm, Money: "<<Money;
    cout<<", Animals: "<<v_animalArray.size()<<" chickens, Products: Milk["<<m_milk<<"], ";
    cout<<"Wool["<<m_wool<<"], Eggs["<<my_products<<"]"<<endl;

}

void ChickenFarm::farmProductivity() {
    int i;
    for(i = 0; i<v_animalArray.size();i++){
        my_products += v_animalArray[i]->getAnimalAge();
    }


}

void ChickenFarm::addToClientList(Farm *client) {
    client->addCowToChicken(this);

}

void ChickenFarm::addChickenToSheep(Farm *seller) {
    cout<<"Sheep farm("<<seller->getID()<<") Added Chicken farm("<<getID()<<") to his client list\n";

}






