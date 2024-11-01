// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.GetMaxPower()) // не правильно, тут нужно вызывать конструктор копирования s BitField, можно реализовать через включение в наше множество всех элементов из s
{
    MaxPower = s.GetMaxPower();
    for (int i = 0; i < MaxPower; i++)
        if (s.IsMember(i))
            InsElem(i);
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    MaxPower = BitField.GetLength();
    for (int i = 0; i < MaxPower; i++)
        if (bf.GetBit(i) == 1)
            InsElem(i);
}

TSet::operator TBitField() // не понял
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0)
        return 0; //исключние
    if(BitField.GetBit(Elem) == 1)
        return 1;
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0)
        return; //исключение
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0)
        return; //исключение
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание    //тут есть ошибка, т.к. Витфиелд может быть большего размера, чем присвоенный ему и мы этот размер не уменьшаем
{
    if (MaxPower < s.GetMaxPower())
    {
       /* for (int i = 0; i < MaxPower; i++)
            if (s.IsMember(i) == 1)
                InsElem(i);
            else
                DelElem(i); 
        for (int i = MaxPower; i < s.GetMaxPower(); i++)
            if (s.IsMember(i))
                InsElem(i);
        */
        TBitField a(s.BitField);
        BitField = a;
        MaxPower = s.GetMaxPower();
    }
    else
    {
        for (int i = 0; i < s.GetMaxPower(); i++)
            if (s.IsMember(i) == 1)
                InsElem(i);
            else
                DelElem(i);
        for (int i = s.GetMaxPower(); i < MaxPower; i++)
            if (IsMember(i))
                DelElem(i);
        MaxPower = s.GetMaxPower();
    }
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    /*if (MaxPower <= s.GetMaxPower())
    {

        for (int i = 0; i < MaxPower; i++)
            if ((s.IsMember(i) == 1) && (IsMember(i) == 0) || (s.IsMember(i) == 0) && (IsMember(i) == 1))
                return 0;
        for (int i = MaxPower; i < s.GetMaxPower(); i++)
            if (s.IsMember(i) == 1)
                return 0;
    }
    else
    {
        for (int i = 0; i < s.GetMaxPower(); i++)
            if ((s.IsMember(i) == 1) && (IsMember(i) == 0) || (s.IsMember(i)  == 0) && (IsMember(i) == 1))
                return 0;
        for (int i = s.GetMaxPower(); i < MaxPower; i++)
            if (s.IsMember(i) == 1)
                return 0;
    }
    return 1;
    */
    if (MaxPower != s.GetMaxPower())
    {
        cout << MaxPower << " != " << s.GetMaxPower();
        return 0;
    }
    for (int i = 0; i < MaxPower; i++)
        if (((s.IsMember(i) == 1) && (IsMember(i) == 0)) || ((s.IsMember(i) == 0) && (IsMember(i) == 1)))
            return 0;
    return 1;
}

int TSet::operator!=(const TSet& s) const // сравнение
{

    /*if (MaxPower <= s.GetMaxPower())
    {

        for (int i = 0; i < MaxPower; i++)
            if ((s.IsMember(i) == 1) && (IsMember(i) == 0) || (s.IsMember(i) == 0) && (IsMember(i) == 1))
                return 1;
        for (int i = MaxPower; i < s.GetMaxPower(); i++)
            if (s.IsMember(i) == 1)
                return 1;
    }
    else
    {
        for (int i = 0; i < s.GetMaxPower(); i++)
            if ((s.IsMember(i) == 1) && (IsMember(i) == 0) || (s.IsMember(i) == 0) && (IsMember(i) == 1))
                return 1;
        for (int i = s.GetMaxPower(); i < MaxPower; i++)
            if (s.IsMember(i) == 1)
                return 1;
    }
    return 0;
    */
    if (MaxPower != s.GetMaxPower())
        return 1;
    for (int i = 0; i < MaxPower; i++)
        if ((s.IsMember(i) == 1) && (IsMember(i) == 0) || (s.IsMember(i) == 0) && (IsMember(i) == 1))
            return 1;
    return 0;
}

TSet TSet::operator+(const TSet& s) // объединение
{

    int len;
    if (MaxPower >= s.GetMaxPower())
        len = MaxPower;
    else
        len = s.GetMaxPower();
    TSet New(len);
    if (MaxPower <= s.GetMaxPower())
    {

        for (int i = 0; i < MaxPower; i++)
            if ((s.IsMember(i) == 1) || (IsMember(i) == 1))
                New.InsElem(i);
        for (int i = MaxPower; i < s.GetMaxPower(); i++)
            if (s.IsMember(i) == 1)
                New.InsElem(i);
    }
    else
    {
        for (int i = 0; i < s.GetMaxPower(); i++)
            if ((s.IsMember(i) == 1) || (IsMember(i) == 1))
                New.InsElem(i);
        for (int i = s.GetMaxPower(); i < MaxPower; i++)
            if (IsMember(i) == 1)
                New.InsElem(i);
    }
    return New;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0)
        return *this; //исключение
    TSet New(*this);
    if (New.IsMember(Elem) == 0)
        New.InsElem(Elem);
    return New;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0)
    {
        return *this;   //исключение
    }
    TSet New(*this);
    if (New.IsMember(Elem) == 1)
        New.DelElem(Elem);
    return New;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    int len = 0;
    if (MaxPower < s.GetMaxPower())
        len = s.GetMaxPower(); 
    else
        len = MaxPower;
    TSet New(len);
    if (MaxPower < s.GetMaxPower())
    {
        for (int i = 0; i < MaxPower; i++)
            if ((IsMember(i) == 1) && (s.IsMember(i) == 1))
                New.InsElem(i);
    }
    else
    {
        for (int i = 0; i < s.GetMaxPower(); i++)
            if ((IsMember(i) == 1) && (s.IsMember(i) == 1))
                New.InsElem(i);
    }
    return New;
}

TSet TSet::operator~(void) // дополнение
{
    TSet New(*this);
    for (int i = 0; i < MaxPower; i++)
        if (New.IsMember(i) == 1)
            New.DelElem(i);
        else
            New.InsElem(i);
    return New;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i) == 1)
            ostr << i << " ";
    }
    ostr << endl;
    return ostr;
}