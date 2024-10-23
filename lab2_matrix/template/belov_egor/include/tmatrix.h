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

// Динамический вектор -
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0) {
        throw out_of_range("Vector size should be greater than zero");
    }
    if (sz > MAX_VECTOR_SIZE) {
        throw out_of_range("Vector's size is too big");
      }
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
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
  TDynamicVector(TDynamicVector&& v) : sz(v.sz), pMem(v.pMem)
  {
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (*this == v) {
          return *this;
      }
      if (sz != v.sz) {
          T* t = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = t;
      }
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v)
  {
      if (*this == v) {
          return *this;
      }
      delete[] pMem;
      pMem = v.pMem;
      sz = v.sz;
      v.pMem = nullptr;
      return *this;
  }


  size_t size() const { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind < 0 || ind >= sz) {
          throw out_of_range("Out of vector's range!");
      }
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind >= sz) {
          throw out_of_range("Out of vector's range!");
      }
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz) {
          throw out_of_range("Out of vector's range!");
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz) {
          throw out_of_range("Out of vector's range!");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const
  {
      if (sz != v.sz) {
          return false;
      }
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const
  {
      if (sz != v.sz) {
          return true;
      }
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return true;
          }
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val) const
  {
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++) {
          temp.pMem[i] = pMem[i] + val;
      }
      return temp;
  }
  TDynamicVector operator-(T val) const
  {
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++) {
          temp.pMem[i] = pMem[i] - val;
      }
      return temp;
  }
  TDynamicVector operator*(T val) const
  {
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++) {
          temp.pMem[i] = pMem[i] * val;
      }
      return temp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) const
  {
      if (sz != v.sz) {
          throw -1;
      }
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++) {
          temp.pMem[i] = pMem[i] + v.pMem[i];
      }
      return temp;
  }
    TDynamicVector operator+=(const TDynamicVector& v) const
    {
        if (sz != v.sz) {
            throw -1;
        }
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = pMem[i] + v.pMem[i];
        }
        return *this;
    }
  TDynamicVector operator-(const TDynamicVector& v) const
  {
      if (sz != v.sz) {
          throw -1;
      }
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++) {
          temp.pMem[i] = pMem[i] - v.pMem[i];
      }
      return temp;
  }
  T operator*(const TDynamicVector& v) const
  {
      if (sz != v.sz) {
          throw -1;
      }
      T s = T(0);
      for (size_t i = 0; i < sz; i++) {
          s += pMem[i] * v.pMem[i];
      }
      return s;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs)
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица -
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T> >
{
    using TDynamicVector<TDynamicVector<T> >::pMem;
    using TDynamicVector<TDynamicVector<T> >::sz;
public:
    using TDynamicVector<TDynamicVector<T> >::operator[];
    using TDynamicVector<TDynamicVector<T> >::operator==;
    using TDynamicVector<TDynamicVector<T> >::operator=;
    using TDynamicVector<TDynamicVector<T> >::operator!=;
    using TDynamicVector<TDynamicVector<T> >::operator+;
    using TDynamicVector<TDynamicVector<T> >::operator-;
    using TDynamicVector<TDynamicVector<T> >::size;
    
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T> >(s)
    {
        if (s >= MAX_MATRIX_SIZE) {
            throw -1;
        }
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }
    TDynamicMatrix(const TDynamicMatrix& m) : TDynamicVector<TDynamicVector<T> >(m) {
    }
    TDynamicMatrix(TDynamicMatrix&& m) {
        sz = m.sz;
        pMem = m.pMem;
        m.pMem = nullptr;
    }
    TDynamicMatrix<T> operator=(const TDynamicMatrix& m) {
        if (*this == m) {
            return (*this);
        }
        if (sz != m.sz) {
            TDynamicVector<T>* t = new TDynamicVector<T>[m.sz];
            sz = m.sz;
            pMem = t;

        }
        std::copy(m.pMem, m.pMem + sz, pMem);
        return *this;
    }
    TDynamicMatrix<T> operator=(TDynamicMatrix&& m) {
        if (*this == m) {
            return (*this);
        }
        pMem = m.pMem;
        sz = m.sz;
        m.pMem = nullptr;
        return *this;
    }
    
    friend TDynamicMatrix Transpon(const TDynamicMatrix& m) {
        TDynamicMatrix temp(m);
        T swap;
        for (size_t i = 0; i < m.sz; i++) {
            for (size_t j = i + 1; j < m.sz; j++) {
                swap = m.pMem[i][j];
                temp.pMem[i][j] = m.pMem[j][i];
                temp.pMem[j][i] = swap;
            }
        }
        return temp;
    }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val) const
  {
      TDynamicVector<T> temp(sz);
      for (size_t i = 0; i < sz; i++) {
          temp.pMem[i] = pMem[i] * val;
      }
      return temp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
      if (v.size() != sz) {
          throw out_of_range("Impossible operation");
      }
      TDynamicVector<T> temp(sz);
      for (size_t i = 0; i < sz; i++) {
          temp[i] = pMem[i] * v;
      }
      return temp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator*(const TDynamicMatrix& m) const
  {
      if (sz != m.sz) {
          throw -1;
      }
      TDynamicMatrix<T> temp(sz);
      TDynamicMatrix<T> mT = Transpon(m);
      std::cout << mT;
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              temp.pMem[j][i] = pMem[j] * mT.pMem[i];
          }
      }
      return temp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++)
          istr >> m.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++)
          ostr << m.pMem[i] << std::endl;
      return ostr;
  }
};

#endif

