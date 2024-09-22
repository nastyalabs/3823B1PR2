#include "TBitField.hpp"

int TBitField::GetMemIndex(const int n) const {
    return n >> 3;
}

TELEM TBitField::GetMemMask(const int n) const {
    return 1 << (n % 8);
}

TBitField::TBitField(int len) : BitLen(len) {
    MemLen = (len + 7) >> 3;
    pMem = new TELEM[MemLen];
    // if (pMem != NULL) {
    //     for (int i = 0; i < MemLen; i++) {
    //         pMem[i] = 0;
    //     }
    // }
}

TBitField::TBitField(const TBitField &bf) : BitLen(bf.BitLen), MemLen(bf.MemLen) {
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    delete[] pMem;
}

int TBitField::GetLength(void) const {
    return BitLen;
}

void TBitField::SetBit(const int n) {
    if ((n > -1) && (n < BitLen)) {
        pMem[GetMemIndex(n)] |= GetMemMask(n);
    }     
}

void TBitField::ClrBit(const int n) {
    if ((n > -1) && (n < BitLen)) {
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    }
}

int TBitField::GetBit(const int n) const {
    if ((n > -1) && (n < BitLen)) {
        return (pMem[GetMemIndex(n)] & GetMemMask(n)) ? 1 : 0;
    }
    return -1;
}

int TBitField::operator==(const TBitField &bf) {
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

TBitField& TBitField::operator=(const TBitField &bf) { // присваивание
    delete[] pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

TBitField TBitField::operator|(const TBitField &bf) {  // операция "или"
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

TBitField TBitField::operator&(const TBitField &bf) {  // операция "или"
    int len = BitLen;
    if (bf.BitLen > len) {
        len = bf.BitLen;
    }
    TBitField res(len);
    for (int i = 0; i < MemLen; i++) {
        res.pMem[i] = pMem[i];
    }
    for (int i = 0; i < bf.MemLen; i++) {
        res.pMem[i] &= bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) {
    TBitField result(BitLen);
    for (int i = 0; i < MemLen; i++) {
        result.pMem[i] = ~pMem[i];
    }
    return result;
}