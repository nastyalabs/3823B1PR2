// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// __________ДИНАМИЧЕСКИЙ ВЕКТОР__________ 
//шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector {
protected:
  size_t size;
  T* pMem;

public:

  TDynamicVector(size_t _size = 1) : size(_size) {
    if (_size == 0) {
      throw out_of_range("Vector size should be greater than zero");
    } 
    if (_size > MAX_VECTOR_SIZE) {
      throw out_of_range("Vector size should be less than 10^8");
    }
    pMem = new T[_size]();
  }

  TDynamicVector(T* array, size_t _size) : size(_size) {
    if (_size > MAX_VECTOR_SIZE) {
      throw out_of_range("Vector size should be less than 10^8");
    }
    assert(array != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[size];
    std::copy(array, array + size, pMem);
  }

  TDynamicVector(const TDynamicVector& _other) : size(_other.size) {
    pMem = new T[size]();
    std::copy(_other.pMem, _other.pMem + size, pMem);
  }

  TDynamicVector(TDynamicVector&& _other) {
    pMem = nullptr;
    swap (*this, _other);
  }

  ~TDynamicVector() {
    delete[] pMem;
  }

  TDynamicVector& operator=(const TDynamicVector& _other) {
    if (*this != _other) {
      if (size != _other.size) {
        T *p = new T[_other.size];
        delete[] pMem;
        size = _other.size;
        pMem = p;
      }
      std::copy(_other.pMem, _other.pMem + size, pMem);
    }
    return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& _other) { 
    swap (*this, _other);
    return *this;
  }

  size_t GetSize() const { 
    return size;
  }

  //__________ИНДЕКСАЦИЯ__________
  T& operator[](size_t ind) {
    if (ind < 0 || ind >= size) {
      throw out_of_range("Memory index out of range");
    }
    return pMem[ind];
  }
  
  const T& operator[](size_t ind) const {
    if (ind < 0 || ind >= size) {
      throw out_of_range("Memory index out of range");
    }
    return pMem[ind];
  }

  //__________ИНДЕКСАЦИЯ С КОНТРОЛЕМ__________
  T& at(size_t ind) {
    if (ind < 0 || ind >= size) {
      throw out_of_range("Memory index out of range");
    }
    return pMem[ind];
  }

  const T& at(size_t ind) const {
    if (ind < 0 || ind >= size) {
      throw out_of_range("Memory index out of range");
    }
    return pMem[ind];
  }

  //__________СРАВНЕНИЯ__________
  bool operator==(const TDynamicVector& _other) const {
    if (size != _other.size) {
      return false;
    }
    for (int i = 0; i < size; i++) {
      if (pMem[i] != _other.pMem[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const TDynamicVector& _other) const {
    if (size != _other.size) {
      return true;
    }
    for(int i = 0; i < size; i++) {
      if(pMem[i] != _other.pMem[i]) {
        return true;
      }
    }
    return false;
  }

  //__________СКАЛЯРНЫЕ ОПЕРАЦИИ__________
  TDynamicVector operator+(T value) {
    TDynamicVector result(size);
    for(int i = 0; i < size; i++) {
      result.pMem[i] = pMem[i] + value;
    }
    return result;
  }

  TDynamicVector operator-(T value) {
    TDynamicVector result(size);
    for(int i = 0; i < size; i++) {
      result.pMem[i] = pMem[i] - value;
    }
    return result;
  }

  TDynamicVector operator*(T value) {
    TDynamicVector result(size);
    for(int i = 0; i < size; i++) {
      result.pMem[i] = pMem[i] * value;
    }
    return result;
  }

  //__________ВЕКТОРНЫЕ ОПЕРАЦИИ__________
  TDynamicVector operator+(const TDynamicVector& _other) {
    if (this->size != _other.size) {
      throw -1;
    }
    TDynamicVector result(size);
    for(int i = 0; i < size; i++) {
      result.pMem[i] = pMem[i] + _other.pMem[i]; 
    }
    return result;
  }

  TDynamicVector operator-(const TDynamicVector& _other) {
    if (this->size != _other.size) {
      throw -1;
    }
    TDynamicVector result(*this);
    for(int i = 0; i < size; i++) {
      result.pMem[i] -= _other.pMem[i]; 
    }
    return result;
  }

  T operator*(const TDynamicVector& _other) {
    if (this->size != _other.size) {
      throw -1;
    }
    T result = {};
    for(int i = 0; i < size; i++) {
      result = result + pMem[i] *_other.pMem[i]; 
    }
    return result;
}

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
    std::swap(lhs.size, rhs.size);
    std::swap(lhs.pMem, rhs.pMem);
  }

  //__________ВВОД/ВЫВОД__________
  friend istream& operator>>(istream& istr, TDynamicVector& v) {
    for (size_t i = 0; i < v.size; i++) {
      istr >> v.pMem[i]; // требуется оператор>> для типа Tw
    }
    return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
    for (size_t i = 0; i < v.size; i++) {
      ostr << "   "; 
      ostr << v.pMem[i]; // требуется оператор<< для типа T
    }
    ostr << endl;
    return ostr;
  }
};


//__________ДИНАМИЧЕСКАЯ МАТРИЦА__________
//шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::size;
public:
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::GetSize;
  
  TDynamicMatrix(size_t _size = 1) : TDynamicVector<TDynamicVector<T>>(_size) {
    if (_size <= 0 || _size >= MAX_MATRIX_SIZE) {
      throw -1;
    }
    for (size_t i = 0; i < _size; i++)
      pMem[i] = TDynamicVector<T>(_size);
  }
  
  TDynamicMatrix(const TDynamicMatrix& _other) : TDynamicVector<TDynamicVector<T>>(_other) {}

  TDynamicMatrix(TDynamicMatrix&& _other) {
    size = _other.size;
    pMem = _other.pMem;
    _other.pMem = nullptr;
  }
  
  TDynamicMatrix<T> operator=(const TDynamicMatrix& _other) {
    if (*this != _other) {
      if (size != _other.size) {
        TDynamicVector<T>* tmp = new TDynamicVector<T>[_other.size];
        size = _other.size;
        pMem = tmp;
      }
      std::copy(_other.pMem, _other.pMem + size, pMem);
    }    
    return *this;
  }

  TDynamicMatrix<T> operator=(TDynamicMatrix&& _other) {
    if (*this != _other) {
      pMem = _other.pMem;
      size = _other.size;
      _other.pMem = nullptr; 
    }
    return *this;
  }

  //__________СРАВНЕНИЕ__________
  bool operator==(const TDynamicMatrix& _other) const noexcept {
    return TDynamicVector<TDynamicVector<T>>::operator==(_other);
  }

  bool operator!=(const TDynamicMatrix& _other) const noexcept {
    return TDynamicVector<TDynamicVector<T>>::operator!=(_other);
  }

  //__________МАТРИЧНО-СКАЛЯРНЫЕ ОПЕРАЦИИ__________
  TDynamicMatrix<T> operator*(const T& value) const {
    TDynamicMatrix<T> result(size);
    for (int i = 0; i < size; i++) {
      result.pMem[i] = pMem[i] * value;
    }
    return result;
  }

  //__________МАТРИЧНО-ВЕКТОРНЫЕ ОПЕРАЦИИ__________
  TDynamicVector<T> operator*(const TDynamicVector<T>& vector) const {
    if (size != vector.size) {
      throw -1;
    }
    TDynamicVector<T> result(size);
    for (int i = 0; i < size; i++) {
      result[i] = pMem[i] * vector;
    }
    return result;
  }

  //__________МАТРИЧНО-МАТРИЧНЫЕ ОПЕРАЦИИ__________
  TDynamicMatrix operator+(const TDynamicMatrix& _other) const {
    TDynamicMatrix result(size);
    for (int i = 0; i < size; i++) {
      result[i] = pMem[i] + _other.pMem[i];      
    }
    return result;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& _other) const {
    TDynamicMatrix result(size);
    for (int i = 0; i < size; i++) {
      result[i] = pMem[i] - _other.pMem[i];
    }
    return result;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& _other) const {
    if (size != _other.size) {
      throw -1;
    }
    TDynamicMatrix result(size);
    for (size_t i = 0; i < size; i++) {
      for (size_t j = 0; j < size; j++) {
        for (size_t k = 0; k < size; k++) {
          result.pMem[i][j] += pMem[i][k] * _other.pMem[k][j];
        }
      }
    }
    return result;
  }

  //__________ВВОД/ВЫВОД__________
  friend istream& operator>>(istream& istr,       TDynamicMatrix& v) { 
    for (int i = 0; i < size; i++) {
      istr >> v.pMem[i];
    }
    return istr; 
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) {
    for (int i = 0; i < v.size; i++) {
      ostr << v.pMem[i];
    }
    return ostr;
  }
};

#endif
