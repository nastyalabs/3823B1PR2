// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (size > MAX_MATRIX_SIZE)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz)
    {
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
    {
        v.pMem = nullptr;
        v.sz = 0;
    }

    ~TDynamicVector()
    {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;

        TDynamicVector tmp(v);
        swap(*this, tmp);
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v)
        {
            delete[] pMem;
            sz = v.sz;
            pMem = v.pMem;
            v.pMem = nullptr;
            v.sz = 0;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    T& operator[](size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    const T& operator[](size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
            return false;
        return std::equal(pMem, pMem + sz, v.pMem);
    }

    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    TDynamicVector operator+(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] + val;
        return result;
    }

    TDynamicVector operator-(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] - val;
        return result;
    }

    TDynamicVector operator*(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] * val;
        return result;
    }

    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw out_of_range("Vectors must be of the same size");
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] + v.pMem[i];
        return result;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw out_of_range("Vectors must be of the same size");
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] - v.pMem[i];
        return result;
    }

    T operator*(const TDynamicVector<T>& v) const
    {
        if (sz != v.sz)
            throw out_of_range("Vectors must be of the same size");

        T result = T();
        for (size_t i = 0; i < sz; i++)
            result += pMem[i] * v.pMem[i];

        return result;
    }


    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }



    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';
        return ostr;
    }
};

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix size exceeds the maximum allowed size");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }
    using TDynamicVector<TDynamicVector<T>>::size;

    using TDynamicVector<TDynamicVector<T>>::operator[];

    using TDynamicVector<TDynamicVector<T>>::at;

    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz)
            return false;
        for (size_t i = 0; i < sz; i++)
            if (pMem[i] != m.pMem[i])
                return false;
        return true;
    }

    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw out_of_range("Matrices must be of the same size");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] + m.pMem[i];
        return result;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw out_of_range("Matrices must be of the same size");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] - m.pMem[i];
        return result;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw out_of_range("Matrices must be of the same size");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < sz; j++)
            {
                result[i][j] = T();
                for (size_t k = 0; k < sz; k++)
                    result[i][j] += pMem[i][k] * m.pMem[k][j];
            }
        return result;
    }

    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
            throw out_of_range("Vector sizes must match for multiplication");

        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            result[i] = T();
            for (size_t j = 0; j < sz; j++)
            {
                result[i] += pMem[i][j] * v[j];
            }
        }

        return result;
    }


    TDynamicVector<T> operator*(const T& val)
    {
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++)
            result.pMem[i] = pMem[i] * val;
        return result;
    }

    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << '\n';
        return ostr;
    }
};

#endif
