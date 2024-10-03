// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

static int SIZE_TELEM = sizeof(TELEM)*8;

TBitField::TBitField(int len): BitLen(len)
{
	if(len<0){
		throw std::out_of_range("len is too smol");
	}
	
	MemLen = (len+SIZE_TELEM-1)/SIZE_TELEM;
	pMem = new TELEM[MemLen];
	if(pMem!=NULL){
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i]=0;
		}
	}	
}

TBitField::TBitField(const TBitField& bf): BitLen(bf.BitLen), MemLen(bf.MemLen)// конструктор копирования
{
	pMem= new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const  // индекс Мем для бита n
{
	return n/SIZE_TELEM;

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	
	return 1<<(n%SIZE_TELEM);
	
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if(n<0||n>BitLen){
		throw std::out_of_range("bit is out of range.");
	}
	pMem[GetMemIndex(n)]|=GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if(n<0||n>BitLen){
		throw std::out_of_range("bit is out of range.");
	}
	pMem[GetMemIndex(n)]&=~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if(n<0||n>BitLen){
			throw std::out_of_range("bit is out of range.");
	}
	return pMem[GetMemIndex(n)]&GetMemMask(n);

	
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{

	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i]=bf.pMem[i];
	}
	return *this;
	

}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if(BitLen==bf.BitLen){
		for (int i = 0; i < MemLen; i++)
		{
			if(pMem[i]!=bf.pMem[i]){
				return 0;

			}
		}
		return 1;
	}
	else{
		return 0;
	}
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if(BitLen!=bf.BitLen) return 1;
	for (int i = 0; i < MemLen; i++)
	{
		if(pMem[i]!=bf.pMem[i]){
			return 1;
		}
		
	}
	
	return 0;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	
	TBitField t(max(BitLen,bf.BitLen));

	for (int i = 0; i < MemLen; i++) {
		t.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++) {
		t.pMem[i] |= bf.pMem[i];
	}

	return t;
	

}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField t(max(BitLen,bf.BitLen));

	

	for (int i = 0; i < min( MemLen,bf.MemLen); i++) {
		t.pMem[i] = pMem[i] & bf.pMem[i];
	}

	return t;
	
}

TBitField TBitField::operator~(void) // отрицание
{

	TBitField t(BitLen);

	for (int i = 0; i < MemLen; i++)
	{
		t.pMem[i]=~pMem[i];
	}

	int last_index = BitLen%SIZE_TELEM;
	if(last_index>0){
		TELEM mask = (1<<last_index)-1;
		t.pMem[MemLen-1]&= mask; 
	}
	return t;
		

}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	for (int i = 0; i < bf.MemLen; i++) {
		istr >> bf.pMem[i];
	}
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.MemLen; i++) {
        ostr << bf.pMem[i];
    }
    return ostr;
}