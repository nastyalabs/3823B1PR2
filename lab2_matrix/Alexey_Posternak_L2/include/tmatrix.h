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
    if (sz <= 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector with too large size");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    sz = v.sz;
    pMem = v.pMem;
    v.pMem = nullptr;
    v.sz = 0;
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this != &v) {
      delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      for (size_t i = 0; i < sz; i++) {
        pMem[i] = v.pMem[i];
      }
    }
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    sz = v.sz;
    pMem = v.pMem;
    v.pMem = nullptr;
    v.sz = 0;
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind >= sz) {
      throw out_of_range("index out of range");
    }
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz) {
      throw out_of_range("index out of range");
    }
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (v.sz != sz) {
      return false;
    }
    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != v.pMem[i]) {
        return false;
      }
    }
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    if (v.sz != sz) {
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
  TDynamicVector operator+(T val)
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] + val;
    }
    return res;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] - val;
    }
    return res;
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] * val;
    }
    return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (v.sz != sz) {
      throw out_of_range("Not equal sizes");
    }

    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] + v.pMem[i];
    }

    return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (v.sz != sz) {
      throw out_of_range("Not equal sizes");
    }

    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] - v.pMem[i];
    }

    return res;
  }
  T operator*(const TDynamicVector& v)
  {
    if (v.sz != sz) {
      throw out_of_range("Not equal sizes");
    }

    T res = T();
    for (size_t i = 0; i < sz; i++) {
      res += pMem[i] * v.pMem[i];
    }

    return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
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
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s == 0 || s > MAX_MATRIX_SIZE)
      throw out_of_range("Matrix size should be greater than zero and less than 10000");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;
  using TDynamicVector<TDynamicVector<T>>::size;
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    if (m.sz != sz) {
      return false;
    }
    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != m.pMem[i]) {
        return false;
      }
    }
    return true;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        res.pMem[i][j] = pMem[i][j] * val;
      }
    }
    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (v.sz != sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      res[i] = 0;
      for (size_t j = 0; j < sz; j++) {
        res[i] += pMem[i][j] * v[j]; //res[i] = pMem[i] * v
      }
    }
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (m.sz != sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        res.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
      }
    }
    return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (m.sz != sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        res.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
      }
    }
    return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (m.sz != sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicMatrix<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        res.pMem[i][j] = 0;
        for (size_t k = 0; k < sz; k++) {
          res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
        }  
      }
    }
    return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++) {
      for (size_t j = 0; j < v.sz; j++) {
        istr >> v.pMem[i][j];
      }
    }
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++) {
      for (size_t j = 0; j < v.sz; j++) {
        ostr << v.pMem[i][j] << ' ';
      }
      ostr << std::endl;
    }
    return ostr;
  }
};

#endif
