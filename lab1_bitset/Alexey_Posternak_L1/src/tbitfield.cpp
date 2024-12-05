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
        throw std::invalid_argument("Length must be positive");
    }
	MemLen = (len + 31) >> 5;
    pMem = new TELEM[MemLen];
    if (pMem != NULL) {
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = 0;
        }
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
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
	return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen)) {
        throw std::out_of_range("Index out of range");
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);    
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen)) {
        throw std::out_of_range("Index out of range");
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen) {
        throw std::out_of_range("Index out of range");
    }
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	int res = 1;
    if (BitLen != bf.BitLen) {
        res = 0;
    } else {
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                res = 0;
                break;
            }
        }
    }
    return res;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	int res = 0;
    if (BitLen != bf.BitLen) {
        res = 1;
    } else {
        for (int i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i]) {
                res = 1;
                break;
            }
        }
    }
    return res;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len = BitLen;
    if (bf.BitLen > len) {
        len = bf.BitLen;
    }
    TBitField res(len);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        res.pMem[i] |= bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int len = BitLen;
    if (bf.BitLen > len) {
        len = bf.BitLen;
    }
    TBitField res(len);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = pMem[i];
    }
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] &= bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = ~pMem[i];
    }
    int memBits = (MemLen * 32) - BitLen;
    if (memBits > 0) {
        TELEM mask = (1 << (32 - memBits)) - 1;
        res.pMem[MemLen - 1] &= mask;
    }
    return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	for (int i = 0; i < bf.BitLen; i++) {
        int bit;
        istr >> bit;
        if (bit) {
            bf.SetBit(i);
        } else {
            bf.ClrBit(i);
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}