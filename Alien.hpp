//
//  Alien.hpp
//  Zoo
//
//  Created by Белов Егор on 05.09.2024.
//

#ifndef Alien_hpp
#define Alien_hpp
#include "Animal.h"
#include <iostream>

class Alien : public Animal {
protected:
    int intelligence;
public:
    Alien(std::string _breed, int _age, std::string _region, int _intelligence) : Animal(_breed, _age, _region), intelligence(_intelligence) {}
    virtual std::string voice() const { return "INVADE!"; }
};



#endif /* Alien_hpp */
