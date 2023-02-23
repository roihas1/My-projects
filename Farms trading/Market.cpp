//
// Created by roihas on 1/1/22.
//

#include "Market.h"

Market::Market() {
    m_year =0;

}
bool Market::createFarms(){

    int cowNumFarms;
    int sheepNumFarms;
    int chickenNumFarms;
    cout << "How many new cow farms will be added this year?\n";
    cin >> cowNumFarms;
    if (cowNumFarms < 0)
        //cow exception
        throw CowFarmException();

    cout << "How many new sheep farms will be added this year?\n";
    cin >> sheepNumFarms;
    if (sheepNumFarms < 0) {
        //sheep exception
        throw SheepFarmException();

    }
    cout << "How many new chicken farms will be added this year?\n";
    cin >> chickenNumFarms;
    if (chickenNumFarms < 0) {
        //chicken exception
        throw ChickenFarmException();
    }
    int i,j;
    cout<<"----Adding new farms to market----\n";
    for (i = 0; i< cowNumFarms;i++){
        Farm* f = new CowFarm();
        for(j=0;j<Farms.size();j++) {
            f->addToClientList(Farms[j]);
            Farms[j]->addToClientList(f);
        }
        Farms.push_back(f);
    }
    for (i = 0; i< sheepNumFarms;i++){
        Farm *f = new SheepFarm();
        for(j=0;j<Farms.size();j++) {
            f->addToClientList(Farms[j]);
            Farms[j]->addToClientList(f);
        }
        Farms.push_back(f);
    }
    for (i = 0; i< chickenNumFarms;i++){
        Farm *f = new ChickenFarm();
        for(j=0;j<Farms.size();j++) {
            f->addToClientList(Farms[j]);
            Farms[j]->addToClientList(f);
        }
        Farms.push_back(f);
    }
    return true;



}
void Market::tradeDay(){
    int i,j;
    cout<<"----Begin Market----\n";
    for(i=0;i<Farms.size();i++)
        for ( j = 0; j <Farms.size() ; ++j) {
        Farms[i]->buyEgg(Farms[j]);
        Farms[i]->buyWool(Farms[j]);
        Farms[i]->buyMilk(Farms[j]);
    }
    cout<<"----Buy Animals----\n";
    buyAnimals();
}
void Market::buyAnimals(){
    int i;
    for(i=0 ; i< Farms.size() ;i++){
        Farms[i]->buyAnimals();
    }
}
void  Market::increaseYearToAnimalsAndAddMoney(){
    int i;
    for(i=0;i<Farms.size();i++){
        Farms[i]->increaseYearToAnimal();
        Farms[i]->addMoney();
    }

}


void Market::nextYear() {
    bool flag = true;
    cout<<"----Creating new farms----\n";
    while(flag) {
        try {
            createFarms();
            flag = false;
        }
        catch (exception &exception) {
           cout<<exception.what();
        }
    }
    productivity();
    tradeDay();
    increaseYearToAnimalsAndAddMoney();
    m_year++;
}

void Market::printMarketFarms() {
    cout<<"----Market Farms----\n";
    int i;
    for(i =0 ;i<Farms.size();i++)
        Farms[i]->printFarm();

}

void Market::productivity() {
    int i;
    for(i=0;i<Farms.size();i++){
        Farms[i]->farmProductivity();
    }
}

void Market::fastForwardYears() {
    cout<<"How many years to fast forward?\n";
    int years;
    cin>>years;
    int i;
    for(i=0;i<years;i++){
        productivity();
        tradeDay();
        increaseYearToAnimalsAndAddMoney();
        m_year++;
    }

}

Market::~Market() {
    int i;
    for(i=0;i<Farms.size();i++)
        delete Farms[i];

}


