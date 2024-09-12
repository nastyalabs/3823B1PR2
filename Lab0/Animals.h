#pragma once
#include "iostream"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Animal {
protected:
    string voice; // что произносит
    string type; // тип
    string name; // кличка
    string place; // где живет
    int age; // возраст

public:
	Animal(string _name = "", string _voice = "", string _type = "", string _place = "", int _age = 0);
    virtual string Bark() = 0;// голос
    virtual int GetAge() = 0;// возраст
    virtual string GetName() = 0;// имя
    // virtual void Replace(Animal &_other) = 0; // поменять местами
    virtual string GetType() = 0; // порода
};

Animal::Animal(string _name, string _voice, string _type, string _place, int _age) {
    name = _name;
    voice = _voice;
    type = _type;
    place = _place;
    age = _age;
}

// void Animal::Replace(Animal &_other) {
//     string Rplace = this->place;
//     this->place = _other.place;
//     _other.place = Rplace;
// }

class Dog: public Animal
{
    public:
        Dog(string _name, string _voice, string _type, string _place, int _age):
            Animal(_name, _voice, _type, _place, _age) {};
        string Bark() { return voice; };
        int GetAge() { return age; };
        string GetName() { return name; };
        string GetType() { return type; };
};

class Cat: public Animal
{
    public:
        Cat(string _name, string _voice, string _type, string _place, int _age):
            Animal(_name, _voice, _type, _place, _age) {};
        string Bark() { return voice; };
        int GetAge() { return age; };
        string GetName() { return name; };
        string GetType() { return type; };
};

class Cow: public Animal
{
    public:
        Cow(string _name, string _voice, string _type, string _place, int _age):
            Animal(_name, _voice, _type, _place, _age) {};
        string Bark() { return voice; };
        int GetAge() { return age; };
        string GetName() { return name; };
        string GetType() { return type; };
};

class Raccoon: public Animal
{
    public:
        Raccoon(string _name, string _voice, string _type, string _place, int _age):
            Animal(_name, _voice, _type, _place, _age) {};
        string Bark() { return voice; };
        int GetAge() { return age; };
        string GetName() { return name; };
        string GetType() { return type; };
};