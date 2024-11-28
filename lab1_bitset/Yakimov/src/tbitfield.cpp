// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>;

TBitField::TBitField(int len) : BitLen(len), MemLen((len >> 3) + 1) // (len >> 3) + 1 - высчитываем кол-во unsigned char (поразрядное деление 2^3)
{ // len - количество бит в поле. В конструкторе надо создать проверку отрицательное ли len, чтобы оно было только положительным 
	try
	{
		if (BitLen > 0) {
			pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; i++) { pMem[i] = 0; }
		}
		else {
			throw ("Массив не может иметь отрицательное или нулевое значение");
		}		
	}
	catch (const std::string& g) { std::cout << g << std::endl; }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new TELEM[this->MemLen];
	for (int i = 0; i < this->MemLen; i++) this->pMem[i] = 0;
	for (int i = 0; i < BitLen; i++) { if (bf.GetBit(i)) SetBit(i); else ClrBit(i); }
}

TBitField::~TBitField()
{
	if (BitLen>0) delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	try {
		if (n >= 0 && n < this->BitLen) return n >> 3;
		throw ("Index out of range!");
	}
	catch (const std::string& b) {
		std::cout << b << std::endl;
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	try {
		if (n >= 0 && n < this->BitLen) {
			return TELEM(1) << (n & ( this->BitsInElem - 1)); // деление с остатком реализуется
		}
		else throw ("Index out of range!");
	}
	catch (const std::string& b) {
		std::cout << b << std::endl;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	try {
		if (n >= 0 && n < this->BitLen) {
			this->pMem[GetMemIndex(n)] |= GetMemMask(n);
		}
		else throw ("Index out of range!");
	}
	catch (const std::string& b) {
		std::cout << b << std::endl;
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	this->pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	try {
		if (n >= 0 && n < this->BitLen) {
			if ((this->pMem[this->GetMemIndex(n)] & this->GetMemMask(n)) == (this->GetMemMask(n))) return 1;
			else return 0;
		}
		else throw ("Index out of range!");
	}
	catch (const std::string& b) {
		std::cout << b << std::endl;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	try {
		if (&bf != this) {
			if (bf.MemLen != this -> MemLen) {
				delete[] pMem;
				pMem = new TELEM[bf.BitLen];
			}
			this->BitLen = bf.BitLen;
			for (int i = 0; i < BitLen; i++) { if (bf.GetBit(i)) this->SetBit(i); else this->ClrBit(i); }
		}
		else throw("Мы не можем присвоить массиву свой же адрес!");
		return *this;
	}
	catch (std::string& p) { std::cout << p << std::endl; }
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	int min = std::min(MemLen, bf.MemLen);
	for (int i = 0; i < min; i++) if (pMem[i] != bf.pMem[i]) return 0;
	for (int i = min; i < MemLen; i++) if (pMem[i] != 0) return 0;
	for (int i = min; i < bf.MemLen; i++) if (bf.pMem[i] != 0) return 0;
	return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return !(this == &bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int max = std::max(this->BitLen, bf.BitLen);
	TBitField U(max);
	for (int i = 0; i < this->MemLen; i++) { U.pMem[i] |= this->pMem[i]; }
	for (int i = 0; i < bf.MemLen; i++) { U.pMem[i] |= bf.pMem[i]; }
	return U;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int r = std::min(BitLen, bf.BitLen);
	TBitField U(r);
	int min = std::min(this->MemLen, bf.MemLen);
	for (int i = 0; i < min; i++) { TELEM f = (bf.pMem[i] & this->pMem[i]); U.pMem[i] = f; }
	return U;
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < this->BitLen; i++) if (this->GetBit(i) == 0) this->SetBit(i); else this->ClrBit(i); return *this;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	try {
		static bool m = false;
		if (m) throw("Битовое поле заполнено полностью!");
		for (int i = 0; i < bf.BitLen; i++) { istr >> bf.pMem[i]; m = true; }
	}
	catch (const std::string& s) { std::cout << s << std::endl; }
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) { ostr << bf.pMem[i]; }
	return ostr;
}