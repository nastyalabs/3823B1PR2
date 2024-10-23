// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) : BitLen(len)
{
    if (len < 0) {
        throw -1;
    }
    pMem = new TELEM[MemLen = len / 8 + ((len & 7) != 0)];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) : BitLen(bf.BitLen), MemLen(bf.MemLen)
{
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n >= BitLen || n < 0) {
        throw -1;
    }
    return MemLen - BitLen / 8 - ((BitLen & 7) != 0) + n / 8;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0) {
        throw -1;
    }
    return 1 << (7 - (n & 7)); // n & 7 ~ n % 8
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n >= BitLen || n < 0) {
        throw -1;
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n >= BitLen || n < 0) {
        throw -1;
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen || n < 0) {
        throw -1;
    }
    return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (BitLen < bf.BitLen) {
        delete[] pMem;
        pMem = new TELEM[bf.BitLen / 8 + ((bf.BitLen & 7) != 0)];
    }
    for (int i = 0; i < MemLen - bf.MemLen; i++) {
        pMem[i] = 0;
    }
    for (int i = MemLen - bf.MemLen; i < MemLen; i++) {
        pMem[i] = bf.pMem[i - MemLen + bf.MemLen];
    }
    BitLen = bf.BitLen;
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{

    if (MemLen > bf.MemLen) {
        for (int i = MemLen - bf.MemLen; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i - MemLen + bf.MemLen]) {
                return false;
            }
        }
    }
    else {
        for (int i = bf.MemLen - MemLen; i < bf.MemLen; i++) {
            if (bf.pMem[i] != pMem[i - bf.MemLen + MemLen]) {
                return false;
            }
        }
    }
    return true;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{

    if (MemLen > bf.MemLen) {
        for (int i = MemLen - bf.MemLen; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i - MemLen + bf.MemLen]) {
                return true;
            }
        }
    }
    else {
        for (int i = bf.MemLen - MemLen; i < bf.MemLen; i++) {
            if (bf.pMem[i] != pMem[i - bf.MemLen + MemLen]) {
                return true;
            }
        }
    }
    return false;
}

TBitField TBitField::operator|(const TBitField& bf) const // операция "или"
{
    if (MemLen > bf.MemLen) {
        TBitField temp(BitLen);
        for (int i = bf.GetMemIndex(0); i < bf.MemLen; i++) {
            temp.pMem[i - bf.GetMemIndex(0) + GetMemIndex(0)] = pMem[i - bf.GetMemIndex(0) + GetMemIndex(0)] | bf.pMem[i];
        }
        for (int i = bf.MemLen - bf.GetMemIndex(0) + GetMemIndex(0); i < MemLen; i++) {
            temp.pMem[i] = pMem[i] | 0;
        }
        return temp;
    }
    else {
        TBitField temp(bf.BitLen);
        for (int i = GetMemIndex(0); i < MemLen; i++) {
            temp.pMem[i - GetMemIndex(0) + bf.GetMemIndex(0)] = bf.pMem[i - GetMemIndex(0) + bf.GetMemIndex(0)] | pMem[i];
        }
        for (int i = MemLen - GetMemIndex(0) + bf.GetMemIndex(0); i < bf.MemLen; i++) {
            temp.pMem[i] = bf.pMem[i] | 0;
        }
        return temp;
    }
}

TBitField TBitField::operator&(const TBitField& bf) const // операция "и"
{
    if (MemLen > bf.MemLen) {
        TBitField temp(BitLen);
        for (int i = bf.GetMemIndex(0); i < bf.MemLen; i++) {
            temp.pMem[i - bf.GetMemIndex(0) + GetMemIndex(0)] = pMem[i - bf.GetMemIndex(0) + GetMemIndex(0)] & bf.pMem[i];
        }
        for (int i = bf.MemLen - bf.GetMemIndex(0) + GetMemIndex(0); i < MemLen; i++) {
            temp.pMem[i] = pMem[i] & 0;
        }
        return temp;
    }
    else {
        TBitField temp(bf.BitLen);
        for (int i = GetMemIndex(0); i < MemLen; i++) {
            temp.pMem[i - GetMemIndex(0) + bf.GetMemIndex(0)] = bf.pMem[i - GetMemIndex(0) + bf.GetMemIndex(0)] & pMem[i];
        }
        for (int i = MemLen - GetMemIndex(0) + bf.GetMemIndex(0); i < bf.MemLen; i++) {
            temp.pMem[i] = bf.pMem[i] & 0;
        }
        return temp;
    }
}

TBitField TBitField::operator~(void) const // отрицание
{
    TBitField temp(BitLen);
    for (int i = GetMemIndex(0); i < MemLen; i++) {
        temp.pMem[i - GetMemIndex(0)] = ~pMem[i];
    }
    temp.pMem[GetMemIndex(BitLen - 1)] = (temp.pMem[GetMemIndex(BitLen - 1)] >> (8 - BitLen & 7)) << (8 - BitLen & 7);
    return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    char elem;
    for (int i = 0; i < bf.BitLen; i++) {
        istr >> elem;
        if (elem) {
            bf.SetBit(i);
        }
        else {
            bf.ClrBit(i);
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.MemLen; i++) {
        for (int j = 0; j < 8; j++) {
            ostr << ((bf.pMem[i] & bf.GetMemMask(j)) != 0);
        }
    }
    return ostr;
}
