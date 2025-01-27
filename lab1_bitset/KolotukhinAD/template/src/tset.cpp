// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int maxPow) : BitField(maxPow), MaxPower(maxPow) {}

// конструктор копирования
TSet::TSet(const TSet &set) : BitField(set.BitField), MaxPower(set.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {}


TSet::operator TBitField() {
    return BitField;
}

// получить макс. к-во эл-тов
int TSet::GetMaxPower(void) const {
    return MaxPower;
}

// элемент множества?
bool TSet::IsMember(const int Elem) const {
    if (Elem >= 0 && Elem < MaxPower) {
        return (bool)BitField.GetBit(Elem);
    }
    return false;
}

// включение элемента множества
void TSet::InsElem(const int Elem) {
    BitField.SetBit(Elem); // отрицательные и больше MemLen * sizeof(Telem)
    // if (Elem >= BitField.GetLength() * sizeof(Telem)) {
    //     BitField.AddMem(Elem); // довыделится память, чтобы хватило для включения элемента
    // }
    // BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) { // исключение элемента множества
    if (Elem >= 0 && Elem < MaxPower) {
        BitField.ClrBit(Elem);
    }
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &_other) {// присваивание
    if (this != &_other) {
        MaxPower = _other.MaxPower;
        BitField = _other.BitField;
    }
    return *this;
}

bool TSet::operator==(const TSet& _other) const { // сравнение
    if (BitField != _other.BitField) {
        return false;
    }
    return true;
}

bool TSet::operator!=(const TSet &_other) const { // сравнение
    return !(*this == _other);
}

TSet TSet::operator+(const TSet& s) {// объединение
    TSet tmpSet(MaxPower > s.MaxPower ? MaxPower : s.MaxPower);
    tmpSet.BitField = BitField | s.BitField;
    return tmpSet;
}

TSet TSet::operator+(const int Elem) { // объединение с элементом
    if (Elem > MaxPower) {
        throw 1; // универс мб мньше памяти.
    }
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