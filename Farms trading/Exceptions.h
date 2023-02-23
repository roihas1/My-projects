
#ifndef CPP_FARM_EXCEPTIONS_H
#define CPP_FARM_EXCEPTIONS_H
#include <exception>
#include <iostream>
using namespace std;

class CowFarmException:public exception {
public:
    CowFarmException()= default;;
    const char *what() const noexcept override {
        return "Insert valid number of cow farms\n";

    };

};

class SheepFarmException:public exception{
public:
    SheepFarmException()= default;;
    const char * what() const noexcept override{
        return "Insert valid number of sheep farms\n";
    }
};


class ChickenFarmException:public exception{
public:
    ChickenFarmException()=default;
    const char * what() const noexcept override{
        return "Insert valid number of chicken farms\n";
    }
};
#endif //CPP_FARM_EXCEPTIONS_H
