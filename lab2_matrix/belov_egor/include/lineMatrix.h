// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Белов Е.А.
//
//
#pragma once
#ifndef __LineMatrix_H__
#define __LineMatrix_H__

#include <iostream>
#include <math.h>

using namespace std;

template <typename T>
class LineMatrix {
protected:
    size_t sz;
    T* pMem;
public:
    LineMatrix(size_t sz_ = 1) {
        if (sz_ == 0 || sz_ > 10000) {
            throw -1;
        }
        sz = sz_ * sz_;
        pMem = new T[sz];
    }
    LineMatrix(const LineMatrix& m) : sz(m.sz) {
        pMem = new T[sz];
        memcpy(pMem, m.pMem, sz * sizeof(T));
    }
    LineMatrix(LineMatrix&& m) : sz(m.sz) {
        pMem = m.pMem;
        m.pMem = nullptr;
    }
    
    ~LineMatrix() { delete[] pMem; }
    
    
    
    LineMatrix& operator=(const LineMatrix& m) {
        if (*this == m) {
            return *this;
        }
        if (sz != m.sz) {
            T* temp = new T[sz];
            delete[] pMem;
            pMem = temp;
            sz = m.sz;
        }
        memcpy(pMem, m.pMem, sz * sizeof(T));
        return *this;
    }
    LineMatrix& operator=(LineMatrix&& m) {
        if (*this == m) {
            return *this;
        }
        delete[] pMem;
        pMem = m.pMem;
        m.pMem = nullptr;
        sz = m.sz;
        return *this;
    }
    
    
    
    size_t size() const { return sqrt(sz); }
    
    
    
    T& position(size_t i, size_t j) {
        if (i < 0 || j < 0 || i >= sz || j >= sz) {
            throw -1;
        }
        return pMem[i * sz + j];
    }
    const T& position(size_t i, size_t j) const {
        if (i < 0 || j < 0 || i >= sz || j >= sz) {
            throw -1;
        }
        return pMem[i * sz + j];
    }
    T& operator[](size_t i, size_t j) {
        if (i < 0 || j < 0 || i >= sz || j >= sz) {
            throw -1;
        }
        return pMem[i * sz + j];
    }
    const T& operator[](size_t i, size_t j) const {
        if (i < 0 || j < 0 || i >= sz || j >= sz) {
            throw -1;
        }
        return pMem[i * sz + j];
    }
    
    
    
    bool operator==(const LineMatrix& m) const {
        if (sz != m.sz) {
            return false;
        }
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const LineMatrix& m) const {
        if (sz != m.sz) {
            return true;
        }
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != m.pMem[i]) {
                return true;
            }
        }
        return false;
    }
    
    
    
    LineMatrix Transpon() const {
        LineMatrix temp(*this);
        T t;
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = i + 1; j < sz; j++) {
                t = temp[i, j];
                temp[i, j] = temp[j, i];
                temp[j, i] = t;
            }
        }
        return temp;
    }
    
    LineMatrix operator+(const LineMatrix& m) const {
        if (sz != m.sz) {
            throw -1;
        }
        LineMatrix temp(*this);
        for (size_t i = 0; i < sz; i++) {
            temp.pMem[i] += m.pMem[i];
        }
        return temp;
    }
    LineMatrix operator-(const LineMatrix& m) const {
        if (sz != m.sz) {
            throw -1;
        }
        LineMatrix temp(*this);
        for (size_t i = 0; i < sz; i++) {
            temp.pMem[i] -= m.pMem[i];
        }
        return temp;
    }
    LineMatrix operator*(T a) const {
        LineMatrix temp(*this);
        for (size_t i = 0; i < sz; i++) {
            temp.pMem[i] *= a;
        }
        return temp;
    }
    LineMatrix operator*(const LineMatrix& m) const {
        if (sz != m.sz) {
            throw -1;
        }
        LineMatrix temp(sz);
        LineMatrix mT(m.Transpon());
        T s;
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                s = T(0);
                for (size_t z = 0; j < sz; j++) {
                    s += position(i, j) * mT.position(j, z);
                }
                temp[i, j] = s;
            }
        }
        return temp;
        
    }
    
    
    
    friend istream& operator>>(istream& istr, LineMatrix& m) {
        for (size_t i = 0; i < m.sz; i++) {
            for (size_t j = 0; j < m.sz; j++) {
                istr >> m[i, j];
            }
        }
        return istr;
    }
    friend ostream& operator>>(ostream& ostr, LineMatrix& m) {
        for (size_t i = 0; i < m.sz; i++) {
            for (size_t j = 0; j < m.sz; j++) {
                ostr << m[i, j] << " ";
            }
            ostr << endl;
        }
        return ostr;
    }
};


#endif
