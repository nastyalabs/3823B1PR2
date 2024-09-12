#pragma once
#ifndef Animal_h
#define Animal_h
#include <iostream>


class Animal {
protected:
    std::string breed;
    int age;
    std::string region;
public:
    Animal(std::string _breed, int _age, std::string _region) : breed(_breed), age(_age), region(_region) {}
    virtual std::string voice() const = 0;
    virtual void replace(std::string place) { region = place; }
    virtual int getage() const { return age; }
};



#endif /* Animal_h */
