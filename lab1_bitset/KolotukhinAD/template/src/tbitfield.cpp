// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// 
//__________БИТОВОЕ ПОЛЕ__________
#include <bits/stdc++.h>
#include "tbitfield.h"
#include "math.h"

TBitField::TBitField(int len) {
	if (len < 0) {
		throw 1;
	}
	MemLen = len / bitsInElem + 1;
	pMem = new TELEM[MemLen];
	BitLen = len;
	for (int i = 0; i < MemLen; i++) {
		pMem[i].bit0 = 0;
		pMem[i].bit1 = 0;
		pMem[i].bit2 = 0;
		pMem[i].bit3 = 0;
		pMem[i].bit4 = 0;
		pMem[i].bit5 = 0;
		pMem[i].bit6 = 0;
		pMem[i].bit7 = 0;
	}
}

// конструктор копирования
TBitField::TBitField(const TBitField &_other) : MemLen(_other.MemLen), BitLen(_other.BitLen) {
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i].bit0 = _other.pMem[i].bit0;
		pMem[i].bit1 = _other.pMem[i].bit1;
		pMem[i].bit2 = _other.pMem[i].bit2;
		pMem[i].bit3 = _other.pMem[i].bit3;
		pMem[i].bit4 = _other.pMem[i].bit4;
		pMem[i].bit5 = _other.pMem[i].bit5;
		pMem[i].bit6 = _other.pMem[i].bit6;
		pMem[i].bit7 = _other.pMem[i].bit7;
	}
}

TBitField::~TBitField() {
	delete[] pMem;
}

// индекс Мем для бита n
int TBitField::GetMemIndex(const int pos) const noexcept {
	return pos >> shiftSize; 
}

// битовая маска для бита n
int TBitField::GetMemMask (const int pos) const {
    return 1 << (pos & (bitsInElem - 1));
}

//__________ДОСТУП К БИТАМ БИТОВОГО ПОЛЯ__________
int TBitField::GetLength() const {
    return BitLen;
}

void TBitField::SetBit(const int pos) {
    if (pos < 0 || pos > BitLen) {
	    throw 1;
	}
    int bitInd = pos & (bitsInElem - 1);
    switch (bitInd) {
        case 0: pMem[GetMemIndex(pos)].bit0 = 1; break;
        case 1: pMem[GetMemIndex(pos)].bit1 = 1; break;
        case 2: pMem[GetMemIndex(pos)].bit2 = 1; break;
        case 3: pMem[GetMemIndex(pos)].bit3 = 1; break;
        case 4: pMem[GetMemIndex(pos)].bit4 = 1; break;
        case 5: pMem[GetMemIndex(pos)].bit5 = 1; break;
        case 6: pMem[GetMemIndex(pos)].bit6 = 1; break;
        case 7: pMem[GetMemIndex(pos)].bit7 = 1; break;
    }
}

void TBitField::ClrBit(const int pos) {
    if (pos < 0 || pos > BitLen) {
		  throw 1;
	    }
    int bitInd = pos & (bitsInElem - 1);
    switch (bitInd) {
        case 0: pMem[GetMemIndex(pos)].bit0 = 0; break;
        case 1: pMem[GetMemIndex(pos)].bit1 = 0; break;
        case 2: pMem[GetMemIndex(pos)].bit2 = 0; break;
        case 3: pMem[GetMemIndex(pos)].bit3 = 0; break;
        case 4: pMem[GetMemIndex(pos)].bit4 = 0; break;
        case 5: pMem[GetMemIndex(pos)].bit5 = 0; break;
        case 6: pMem[GetMemIndex(pos)].bit6 = 0; break;
        case 7: pMem[GetMemIndex(pos)].bit7 = 0; break;
    }
}

int TBitField::GetBit(const int pos) const {
    if (pos < 0 || pos > BitLen) {
		throw 1;
	}
    int bitInd = pos & (bitsInElem - 1);
    switch (bitInd) {
        case 0: return (int)pMem[GetMemIndex(pos)].bit0; break;
        case 1: return (int)pMem[GetMemIndex(pos)].bit1; break;
        case 2: return (int)pMem[GetMemIndex(pos)].bit2; break;
        case 3: return (int)pMem[GetMemIndex(pos)].bit3; break;
        case 4: return (int)pMem[GetMemIndex(pos)].bit4; break;
        case 5: return (int)pMem[GetMemIndex(pos)].bit5; break;
        case 6: return (int)pMem[GetMemIndex(pos)].bit6; break;
        case 7: return (int)pMem[GetMemIndex(pos)].bit7; break;
    }
    return -1;
}

// __________БИТОВЫЕ ОПЕРАЦИИ__________

// присваивание
TBitField& TBitField::operator=(const TBitField &_other) {
	if (this != &_other) {
        delete[] pMem;
        MemLen = _other.MemLen;
        BitLen = _other.BitLen;
        pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = _other.pMem[i];
		}
	}
    return *this;
}

// сравнение
bool TBitField::operator==(const TBitField &_other) const {
	if (BitLen != _other.BitLen) {
		return false;
	}
	for (int i = 0; i < BitLen; i++) {
		if (this->GetBit(i) != _other.GetBit(i)) {
			return false;
		}
	}
	return true;
}

// сравнение
bool TBitField::operator!=(const TBitField &_other) const {
	if (BitLen != _other.BitLen) {
		return true;
	}
	for (int i = 0; i < BitLen; i++) {
		cout << "\n\n\n this " << this->GetBit(i) << "  other " << _other.GetBit(i) << "\n\n\n";
		if (this->GetBit(i) != _other.GetBit(i)) {
			return true;
		}
	}
	return false;
}

// операция "или"
TBitField TBitField::operator|(const TBitField &_other) {
	int maxBitLen = max(BitLen, _other.BitLen);
    TBitField result(maxBitLen);
    for (int i = 0; i < result.MemLen; i++) {
        result.pMem[i].bit0 = (i < MemLen ? pMem[i].bit0 : 0) || (i < _other.MemLen ? _other.pMem[i].bit0 : 0);
		result.pMem[i].bit1 = (i < MemLen ? pMem[i].bit1 : 0) || (i < _other.MemLen ? _other.pMem[i].bit1 : 0);
		result.pMem[i].bit2 = (i < MemLen ? pMem[i].bit2 : 0) || (i < _other.MemLen ? _other.pMem[i].bit2 : 0);
        result.pMem[i].bit3 = (i < MemLen ? pMem[i].bit3 : 0) || (i < _other.MemLen ? _other.pMem[i].bit3 : 0);
 	    result.pMem[i].bit4 = (i < MemLen ? pMem[i].bit4 : 0) || (i < _other.MemLen ? _other.pMem[i].bit4 : 0);
		result.pMem[i].bit5 = (i < MemLen ? pMem[i].bit5 : 0) || (i < _other.MemLen ? _other.pMem[i].bit5 : 0);
		result.pMem[i].bit6 = (i < MemLen ? pMem[i].bit6 : 0) || (i < _other.MemLen ? _other.pMem[i].bit6 : 0);
		result.pMem[i].bit7 = (i < MemLen ? pMem[i].bit7 : 0) || (i < _other.MemLen ? _other.pMem[i].bit7 : 0);
    }
    return result;
}

// операция "и"
TBitField TBitField::operator&(const TBitField &_other) {
	int maxLen = max(BitLen, _other.BitLen);
    TBitField result(maxLen);
    for (int i = 0; i < result.MemLen; i++) {
        result.pMem[i].bit0 = (i <        MemLen ?        pMem[i].bit0 : 0) &&
						      (i < _other.MemLen ? _other.pMem[i].bit0 : 0);
		result.pMem[i].bit1 = (i <        MemLen ?        pMem[i].bit1 : 0) &&
						      (i < _other.MemLen ? _other.pMem[i].bit1 : 0);
		result.pMem[i].bit2 = (i <        MemLen ?        pMem[i].bit2 : 0) &&
						      (i < _other.MemLen ? _other.pMem[i].bit2 : 0);
        result.pMem[i].bit3 = (i <        MemLen ?        pMem[i].bit3 : 0) &&
	     				      (i < _other.MemLen ? _other.pMem[i].bit3 : 0);
 	    result.pMem[i].bit4 = (i <        MemLen ?        pMem[i].bit4 : 0) &&
						      (i < _other.MemLen ? _other.pMem[i].bit4 : 0);
		result.pMem[i].bit5 = (i <        MemLen ?        pMem[i].bit5 : 0) &&
						      (i < _other.MemLen ? _other.pMem[i].bit5 : 0);
		result.pMem[i].bit6 = (i <        MemLen ?        pMem[i].bit6 : 0) &&
						      (i < _other.MemLen ? _other.pMem[i].bit6 : 0);
		result.pMem[i].bit7 = (i <        MemLen ?        pMem[i].bit7 : 0) &&
						      (i < _other.MemLen ? _other.pMem[i].bit7 : 0);
    }
    return result;
}

// отрицание
TBitField TBitField::operator~(void) {
	TBitField result(BitLen);
	for (int i = 0; i < BitLen; i++) {
		if (!this->GetBit(i)) {
			result.SetBit(i);
		}
	}
    return result;
}

// ввод
istream& operator>>(istream &is, TBitField &_this) {
	for (int i = 0; i < _this.BitLen; i++) {
        int bit;
        is >> bit;
        if (bit) {
			_this.SetBit(i);
		}
    }
    return is;
}

// вывод
ostream& operator<<(ostream &os, const TBitField &_this) {
	for (int i = 0; i < _this.MemLen; i++) {
		os << 
		static_cast<int>(_this.pMem[i].bit0) << static_cast<int>(_this.pMem[i].bit1) <<
		static_cast<int>(_this.pMem[i].bit2) << static_cast<int>(_this.pMem[i].bit3) <<
		static_cast<int>(_this.pMem[i].bit4) << static_cast<int>(_this.pMem[i].bit5) <<
		static_cast<int>(_this.pMem[i].bit6) << static_cast<int>(_this.pMem[i].bit7);
	}
	os << endl;
	return os;
}
