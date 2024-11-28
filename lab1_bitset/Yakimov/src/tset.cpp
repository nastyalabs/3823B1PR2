// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf.GetLength())
{
    this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (this->BitField.GetBit(Elem)) return 1;
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (this != &s)
    {
        BitField = s.BitField;
        this->MaxPower = s.GetMaxPower();
    }
    return *this;
}
 
int TSet::operator==(const TSet& s) const // сравнение
{
    if ((s.BitField == this -> BitField) && (s.MaxPower == this->MaxPower)) return 1;
    return 0;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet& s) // объединение
{
    int count = std::max(GetMaxPower(), s.GetMaxPower());
    TSet ks(count);
    for (int i = 0; i < GetMaxPower(); i++) { if (IsMember(i)) ks.InsElem(i); else ks.DelElem(i); }
    for (int i = 0; i < s.GetMaxPower(); i++) { if (s.IsMember(i)) ks.InsElem(i); }
    return ks;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet ks(this->GetMaxPower());
    if (this->IsMember(Elem) == 0) { ks.BitField = this->BitField;  ks.InsElem(Elem); }
    return ks;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet ks(this->GetMaxPower());
    if (this->IsMember(Elem) == 1) { ks.BitField = this->BitField;  ks.DelElem(Elem); }
    return ks;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    int count = std::min(GetMaxPower(), s.GetMaxPower());
    int count1 = std::max(GetMaxPower(), s.GetMaxPower());
    TSet ks(count1);
    for (int i = 0; i < count; i++) { if (IsMember(i)) ks.InsElem(i); else ks.DelElem(i); }
    for (int i = 0; i < count; i++) { if (!s.IsMember(i)) ks.DelElem(i); }
    return ks;
}

TSet TSet::operator~(void) // дополнение
{
    for (int i = 0; i < this->GetMaxPower(); i++) {
        if (this->IsMember(i) == 0) this->InsElem(i); else this->DelElem(i);
    }
    return *this;
}

//перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    try {
        static bool m = false;
        int r = 0;
        for (int i = 0; i < s.GetMaxPower(); i++) { istr >> r;  s.InsElem(r); m = true; }
        if (m) throw("Битовое поле заполнено полностью!");
    }
    catch (const std::string& s) { std::cout << s << std::endl; }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {if(s.IsMember(i)) ostr << i;}
    return ostr;
}