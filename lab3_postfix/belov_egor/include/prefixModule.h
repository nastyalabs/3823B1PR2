// ННГУ, ВМК, Курс "Алгоритмы и структуры данных", С++, ООП
//
// prefixModule.cpp - Copyright (c) Белов Е.А.
//
// Модуль работы с арифметическими операциями

#ifndef __PREFIXMODULE_H__
#define __PREFIXMODULE_H__

#include <iostream>
#include <string>
#include "stack.h"
#include <vector>
#include "polishList.h"

using namespace std;

// Между различными числами и арифметическими операциями должен стоять один пробел.
// Скобки стоят вплотную к числам.
// После скобок не может быть операций. Числа и операции чередуются (в нормальном способе записи).
// Все открытые скобки должны быть закрыть.

typedef string normalArith;

typedef string prefixArith;



class PrefixModule {
protected:
    normalArith nArith;
    prefixArith pArith;
    PolishList calculator;
public:
    PrefixModule(normalArith str);
    //PrefixModule(prefixArith str);
    
    double step_push();
    double calculate();
    
    normalArith get_normal() { return nArith; }
    prefixArith get_prefix() { return pArith; }
    
};



#endif
