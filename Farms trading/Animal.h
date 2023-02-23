//
// Created by roihas on 1/1/22.
//

#ifndef CPP_FARM_ANIMAL_H
#define CPP_FARM_ANIMAL_H


class Animal {
protected:
    int animalAge;
public:

    Animal():animalAge(0){};
    virtual ~Animal();
    virtual bool increaseAge()=0;
//    virtual int getPrice()const=0;
//    virtual int getDied()const=0;
    int getAnimalAge() const{return animalAge;}
};



#endif //CPP_FARM_ANIMAL_H
