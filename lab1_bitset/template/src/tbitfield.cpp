// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include <bits/stdc++.h>
#include "tbitfield.h"
#include "math.h"

TBitField::TBitField(int len) : BitLen(len) , MemLen(0) {
    pMem = new TELEM[BitLen];
	for (int i = 0; i < BitLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField& _other) : BitLen(_other.BitLen), MemLen(_other.MemLen) { // конструктор копирования
	pMem = new TELEM[BitLen];
    for (int i = 0; i < BitLen; i++) {
		pMem[i] = _other.pMem[i];
		if (pMem[i]) {
			MemLen++;
		}
	}
}

TBitField::~TBitField() {
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const { // индекс Мем для бита n
	return n;
}

TELEM TBitField::GetMemMask(const int n) const { // битовая маска для бита n
	return 1U << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const { // получить длину (к-во битов)
	return BitLen;
}

void TBitField::SetBit(const int n) { // установить бит
    if (n < 0 || n > BitLen) {
		throw 1;
	} else if(pMem[n] != 1) {
		MemLen++;
		pMem[n] = 1;
	}
}

void TBitField::ClrBit(const int n) { // очистить бит
    if (n < 0 || n > BitLen) {
		throw 1;
	} else if (pMem[n] != 0) {
		pMem[n] = 0;
		MemLen--;
	}
}

int TBitField::GetBit(const int n) const { // получить значение бита
    if (n < 0 || n > BitLen) {
		throw 1;
	} else {
		return pMem[n];
	}
}

// битовые операции
TBitField& TBitField::operator=(const TBitField& _other) { // присваивание
	if (this != &_other) {
        delete[] pMem;
        BitLen = _other.BitLen;
        MemLen = _other.MemLen;
        pMem = new TELEM[BitLen];
		for (int i = 0; i < BitLen; i++) {
			pMem[i] = _other.pMem[i];
		}
	}
    return *this;
}

int TBitField::operator==(const TBitField& _other) const { // сравнение
	if (BitLen != _other.BitLen) {
		return 0;
	}
	for (int i = 0; i < BitLen; i++) {
		if (pMem[i] != _other.pMem[i]) {
			return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField& _other) const { // сравнение
	if (BitLen != _other.BitLen) {
		return 1;
	}
	for (int i = 0; i < BitLen; i++) {
		if (pMem[i] != _other.pMem[i]) {
			return 1;
		}
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField& _other) { // операция "или"
	int maxLen = max(BitLen, _other.BitLen);
    TBitField res(maxLen);
    for (int i = 0; i < res.BitLen; i++) {
        res.pMem[i] = (i < BitLen ? pMem[i] : 0) || (i < _other.BitLen ? _other.pMem[i] : 0);
    }
    return res;
}

TBitField TBitField::operator&(const TBitField& _other) { // операция "и"
	int maxLen = max(BitLen, _other.BitLen); // max -> min
    TBitField res(maxLen);
    for (int i = 0; i < maxLen; i++) {
		res.pMem[i] = (i < BitLen ? pMem[i] : 0) && (i < _other.BitLen ? _other.pMem[i] : 0);
    }
    return res;
}

TBitField TBitField::operator~(void) { // отрицание
	TBitField res(BitLen);
    for (int i = 0; i < BitLen; i++) {
		if (pMem[i] == 1) {
			res.ClrBit((const int)i);
		} else {
			res.SetBit((const int)i);
		}
    }
    return res;
}

istream& operator>>(istream& is, TBitField& _this) { // ввод
	for (int i = 0; i < _this.BitLen; i++) {
        int bit;
        is >> bit;
        if (bit) {
			_this.SetBit(i);
			_this.MemLen++;
		}
    }
    return is;
}

ostream& operator<<(ostream& os, const TBitField& _this) { // вывод
	for (int i = 0; i < _this.BitLen; i++) {
		os << _this.pMem[i];
	}
	return os;
}