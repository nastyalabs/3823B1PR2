// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.BitLen), BitField(bf)
{
}

TSet::operator TBitField()
{
    TBitField temp(BitField);
    return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem >= MaxPower) {
        return 0;
    }
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return MaxPower == s.MaxPower && BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return MaxPower != s.MaxPower || BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s) const // объединение
{
    TBitField tempB(BitField | s.BitField);
    TSet tempS(tempB.BitLen);
    tempS.BitField = tempB;
    return tempS;
}

TSet TSet::operator+(const int Elem) const // объединение с элементом
{
    TSet temp(*this);
    temp.InsElem(Elem);
    return temp;
}

TSet TSet::operator-(const int Elem) const // разность с элементом
{
    TSet temp(*this);
    temp.DelElem(Elem);
    return temp;
}

TSet TSet::operator*(const TSet& s) const // пересечение
{
    TBitField tempB(BitField & s.BitField);
    TSet tempS(tempB.BitLen);
    tempS.BitField = tempB;
    return tempS;
}

TSet TSet::operator~(void) const // дополнение
{
    TBitField tempB(~BitField);
    TSet tempS(tempB.BitLen);
    tempS.BitField = tempB;
    return tempS;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    return istr >> s.BitField;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    return ostr << s.BitField;
}
