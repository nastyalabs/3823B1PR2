#ifndef Cat_hpp
#define Cat_hpp

#include "Animal.h"
#include <iostream>

class Cat : public Animal {
protected:
    int cuteness;
public:
    Cat(std::string _breed, int _age, std::string _region, int _cuteness) : Animal(_breed, _age, _region), cuteness(_cuteness) {}
    virtual std::string voice() const { return "MEEEEEEEW!"; }
};



#endif /* Cat_hpp */
