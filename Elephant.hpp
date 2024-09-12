//
//  Elephant.hpp
//  Zoo
//
//  Created by Белов Егор on 05.09.2024.
//

#ifndef Elephant_hpp
#define Elephant_hpp
#include "Animal.h"
#include <iostream>

class Elephant : public Animal {
protected:
    int power;
public:
    Elephant(std::string _breed, int _age, std::string _region, int _power) : Animal(_breed, _age, _region), power(_power) {}
    virtual std::string voice() const { return "PROOOOOOOOOH!"; }
};

#endif /* Elephant_hpp */
