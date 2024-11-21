// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField() {
    return BitField;
}

int TSet::GetMaxPower(void) const { // получить макс. к-во эл-тов
    return MaxPower;
}

int TSet::IsMember(const int Elem) const { // элемент множества?
    if (Elem >= 0 && Elem < MaxPower) {
        return BitField.GetBit(Elem);
    }
    return 0;
}

void TSet::InsElem(const int Elem) {// включение элемента множества
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) { // исключение элемента множества
    if (Elem >= 0 && Elem < MaxPower) {
        BitField.ClrBit(Elem);
    }
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) {// присваивание
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

int TSet::operator==(const TSet& s) const { // сравнение
    if (MaxPower != s.MaxPower) {
        return 0;
    }
    if (BitField != s.BitField) {
        return 0;
    }
    return 1;
}

int TSet::operator!=(const TSet& s) const { // сравнение
    if (MaxPower != s.MaxPower) {
        return 1;
    }
    if (BitField != s.BitField) {
        return 1;
    }
    return 0;
}

TSet TSet::operator+(const TSet& s) {// объединение
    TSet tmpSet(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
    tmpSet.BitField = BitField | s.BitField;
    return tmpSet;
}

TSet TSet::operator+(const int Elem) { // объединение с элементом
    TSet resSet(*this);
    resSet.InsElem(Elem);
    return resSet;
}

TSet TSet::operator-(const int Elem) { // разность с элементом
    TSet tmpSet(*this);
    tmpSet.DelElem(Elem);
    return tmpSet;
}

TSet TSet::operator*(const TSet& s) { // пересечение
    int minPower = MaxPower < s.MaxPower ? MaxPower : s.MaxPower; 
    TSet tmpSet(BitField & s.BitField);
    return tmpSet;
}

TSet TSet::operator~(void) { // дополнение
    TSet tmpSet(MaxPower);
    tmpSet.BitField = ~BitField;
    return tmpSet;
}

// перегрузка ввода/вывода

istream& operator>>(istream& is, TSet& s) { // ввод
    int n;
    is >> n;
    s = TSet(n);
    int elem;
    while (is >> elem) {
        s.InsElem(elem);
    }
    return is;
}

ostream& operator<<(ostream& os, const TSet& s) { // вывод   
    os << "{";
    for (int i = 0; i < s.MaxPower; i++) {
        if (s.IsMember(i)) {
            os << i << " ";
        }
    }
    os << "}";
    return os;
}