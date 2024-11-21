// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__
#include <bitset>
#include <iostream>

using namespace std;

struct TELEM {
  unsigned char bit0: 1;
  unsigned char bit1: 1;
  unsigned char bit2: 1;
  unsigned char bit3: 1;
  unsigned char bit4: 1;
  unsigned char bit5: 1;
  unsigned char bit6: 1;
  unsigned char bit7: 1;
};

// using Telem = unsigned char;

class TBitField {
private:
  
  int  BitLen; // длина битового поля - макс. к-во битов, кол-во элементов в множестве 
               // (универс - здесь в большинстве случаев будет больше чем универс)
               // 
               // значит нужно задавать точным кол-вом эл-тов универса. 

  TELEM *pMem; // память для представления битового поля, наш массив ( массив структур по 8бит )
               //
  int  MemLen; // к-во эл-тов pМем для представления бит.поля, количество эл-тов в массиве 
               // (фактическая длина pMem, целое число в 8 раз меньшее чем общее число битов из-за char'а)
               //  
  int bitsInElem = 8;
  int shiftSize = 3;

  // индекс в pМем для бита n
  int GetMemIndex(const int pos) const noexcept; // поиски структуры для изменения
  
  // битовая маска для бита n
  int GetMemMask (const int pos) const;

public:
  TBitField(int len); // len - длина универса (м.б. меньше или равной кол-ву общей памяти массива pMem)
  TBitField(const TBitField &otherBitFeild);
  ~TBitField();

  // __________ДОСТУП К БИТАМ__________

  // получить длину (к-во битов) длина универса
  int GetLength(void) const;

  // установить бит
  void SetBit(const int pos);

  // очистить бит
  void ClrBit(const int pos);

  // получить значение бита
  int GetBit(const int pos) const;

  // __________БИТОВЫЕ ОПЕРАЦИИ__________

  bool operator==(const TBitField &bitFeild) const; // сравнение
  bool operator!=(const TBitField &bitFeild) const; // сравнение
  TBitField& operator=(const TBitField &bitFeild); // присваивание
  TBitField  operator|(const TBitField &bitFeild); // операция "или"
  TBitField  operator&(const TBitField &bitFeild); // операция "и"
  TBitField  operator~(void); // отрицание

  friend istream &operator>>(istream &is,       TBitField &bitFeild); // ввод
  friend ostream &operator<<(ostream &os, const TBitField &bitFeild); // вывод
};
#endif
