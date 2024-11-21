// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество

#ifndef __SET_H__
#define __SET_H__

#include "tbitfield.h"

using Telem = unsigned char;

class TSet {
  
private:

  int MaxPower;       // максимальная мощность множества
  TBitField BitField; // битовое поле для хранения характеристического вектора

public:

  TSet(int maxPow);
  TSet(const TSet &set);           // конструктор копирования
  TSet(const TBitField &bitFeild); // конструктор преобразования типа
  operator TBitField();            // преобразование типа к битовому полю

  //__________ДОСТУП К БИТАМ__________
  int GetMaxPower(void) const;         // максимальная мощность множества
  void InsElem(const int Elem);        // включить элемент в множество
  void DelElem(const int Elem);        // удалить элемент из множества
  bool IsMember(const int Elem) const; // проверить наличие элемента в множестве
  
  //__________ТЕОРЕТИКО-МНОЖЕСТВЕННЫЕ ОПЕРАЦИИ__________
  bool operator== (const TSet &set) const; // сравнение
  bool operator!= (const TSet &set) const; // сравнение
  TSet& operator=(const TSet &set);  // присваивание
  TSet operator+ (const int Elem);   // объединение с элементом ( элемент должен быть из того же универса )
  TSet operator- (const int Elem);   // разность с элементом ( элемент должен быть из того же универса )
  TSet operator+ (const TSet &set);  // объединение
  TSet operator* (const TSet &set);  // пересечение
  TSet operator~ (void);             // дополнение

  friend istream &operator>>(istream &is,       TSet &bf); // ввод
  friend ostream &operator<<(ostream &os, const TSet &bf); // вывод
};
#endif
