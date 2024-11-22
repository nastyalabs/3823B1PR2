// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
	{
		throw  ("TBitField bf(", len,") throws an exception.");
	}
		
	BitLen = len;
	MemLen = BitLen >> raz;
	if ((BitLen & (bit - 1)) != 0)
		MemLen++;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.GetLength();
	/*if(BitLen <= 0)
	*	throw
	*/
	MemLen = BitLen >> raz;
	if ((BitLen & (bit - 1)) != 0)
		MemLen++;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
	for (int i = 0; i < BitLen; i++)
		if (bf.GetBit(i) == 1)
			SetBit(i);
}

TBitField::~TBitField()
{
	if (BitLen > 0)
		delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0)
		return -1; //исключение
	return n >> raz;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0)	
		return -1; //исключение
	return 1 << (n & (bit - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0)
	{
		throw ("bf.SetBit(", n, ") throws an exception.");
	}
	if (n > BitLen)
	{
		throw("Expected: bf.SetBit(",n,") throws an exception.");

	}
		int index = GetMemIndex(n);
		int mask = GetMemMask(n);
		if ((pMem[index] & mask) == 0)
			pMem[index] = pMem[index] + mask; //может быть ошибка, т.к. + а не |
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0)	//исключение
		throw("error: Expected: bf.ClrBit(",n,") throws an exception.");
	if (n > BitLen)
		throw("Expected: bf.ClrBit(", n, ") throws an exception.");
	int index = GetMemIndex(n);
	int mask = GetMemMask(n);
	if ((pMem[index] & mask) != 0)
		pMem[index] = pMem[index] - mask; //может быть ошибка, т.к. -
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0)
		throw("Expected: bf.GetBit(",n,") throws an exception.");
	if (n > BitLen)
		throw ("Expected: bf.GetBit(", n, ") throws an exception.");
	else
	{
		int index = GetMemIndex(n);
		int mask = GetMemMask(n);
		if ((pMem[index] & mask) != 0)
			return 1;
		return 0;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (BitLen != bf.GetLength())
	{
		if (BitLen > 0)
		{
			//delete[] pMem; //здесь происходит ошибка
		}
		BitLen = bf.GetLength();
		MemLen = BitLen >> raz;
		if ((BitLen & (bit - 1)) != 0)
			MemLen++;
		TELEM* pMem = new TELEM[MemLen];
		for (int i = 0; i < BitLen; i++)
			ClrBit(i);
		/*for (int i = 0; i < BitLen; i++)
			if (GetBit(i) == 1)
				cout << "1";
			else
				cout << "0";
		cout << endl;
		*/
	}
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i) == 1)
			SetBit(i);	
	/*for (int i = 0; i < BitLen; i++)
		if (GetBit(i) == 1)
			cout << "1";
		else
			cout << "0";
	cout << endl;
	for (int i = 0; i < BitLen; i++)
		if (bf.GetBit(i) == 1)
			cout << "1";
		else
			cout << "0";
	cout << endl;
	*/
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	int min = (BitLen > bf.GetLength()) ? bf.GetLength() : BitLen; //мб ошибка не омень помню тернарный оператор;
	for (int i = 0; i < min; i++)
		if (((GetBit(i) == 1) && (bf.GetBit(i) == 0)) || ((GetBit(i) == 0) && (bf.GetBit(i) == 1)))
		{
			return 0;
		}
	if (BitLen > bf.GetLength())
		for (int i = min; i < BitLen; i++)
			if (GetBit(i) == 1)
				return 0;
	if (BitLen < bf.GetLength())
		for (int i = min; i < bf.GetLength(); i++)
			if (bf.GetBit(i) == 1)
				return 0;
	return 1;

}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	int min = (BitLen > bf.GetLength()) ? bf.GetLength() : BitLen; //мб ошибка не омень помню тернарный оператор;
	for (int i = 0; i < min; i++)
		if ((GetBit(i) == 1) && (bf.GetBit(i) == 0) || (GetBit(i) == 0) && (bf.GetBit(i) == 1))
			return 1;
	if (BitLen > bf.GetLength())
		for (int i = min; i < BitLen; i++)
			if (GetBit(i) == 1)
				return 1;
	if (BitLen < bf.GetLength())
		for (int i = min; i < bf.GetLength(); i++)
			if (bf.GetBit(i) == 1)
				return 1;
	return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len = 0;
	if (BitLen < bf.GetLength())
		len = bf.GetLength();
	else
		len = BitLen;
	TBitField New(len);
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) == 1)
			New.SetBit(i);
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i) == 1)
			New.SetBit(i);
	return New;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int len = 0;
	if (BitLen >= bf.GetLength())
		len = bf.GetLength();
	else
		len = BitLen;
	TBitField New(len);
	for (int i = 0; i < len; i++)
		if ((GetBit(i) == 1) && (bf.GetBit(i) == 1))
			New.SetBit(i);
	return New;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField New(BitLen);
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) == 0)
			New.SetBit(i);
	return New;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		/*if (bf.GetBit(i) == 1)
			ostr << "1 ";
		else
			ostr << "0 ";
		ostr << endl;
		*/
	}
	return ostr;
}