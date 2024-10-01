#include "tbitfield.h"

TBitField::TBitField(int len) {
    if (len < 0) {
        throw std::invalid_argument("Длина не может быть отрицательной");
    }
    BitLen = len;
    MemLen = (len + 31) >> 5;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
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
    if (n < 0 || n >= BitLen) {
        throw std::out_of_range("Битовый индекс вне диапазона");
    }
    return n >> 5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen) {
        throw std::out_of_range("Битовый индекс вне диапазона");
    }
    return 1 << (n & 31);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen) {
        throw std::out_of_range("Битовый индекс вне диапазона");
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen) {
        throw std::out_of_range("Битовый индекс вне диапазона");
    }
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen) {
        throw std::out_of_range("Битовый индекс вне диапазона");
    }
    return (pMem[GetMemIndex(n)] & GetMemMask(n)) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    if (this != &bf)
    {
        delete[] pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (BitLen != bf.BitLen) {
        return 0;
    }
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField result(maxLen);

    int minMemLen = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;

    for (int i = 0; i < minMemLen; i++) {
        result.pMem[i] = pMem[i] | bf.pMem[i];
    }

    if (MemLen > bf.MemLen) {
        for (int i = bf.MemLen; i < MemLen; i++) {
            result.pMem[i] = pMem[i];
        }
    }
    else {
        for (int i = MemLen; i < bf.MemLen; i++) {
            result.pMem[i] = bf.pMem[i];
        }
    }

    return result;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    int maxLen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
    TBitField result(maxLen);

    int minMemLen = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;

    for (int i = 0; i < minMemLen; i++) {
        result.pMem[i] = pMem[i] & bf.pMem[i];
    }

    return result;
}


TBitField TBitField::operator~(void) // отрицание
{
    TBitField result(BitLen);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = ~pMem[i];
    }

    int extraBits = (MemLen * 32) - BitLen;
    if (extraBits > 0) {
        TELEM mask = (1 << (32 - extraBits)) - 1;
        result.pMem[MemLen - 1] &= mask;
    }

    return result;
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
