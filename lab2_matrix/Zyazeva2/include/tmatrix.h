#include "iostream"

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
        if (sz > MAX_VECTOR_SIZE) {
            throw invalid_argument(" ");
        }
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz](); // У типа T д.б. конструктор по умолчанию
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
        v.sz = 0;
        v.pMem = nullptr;
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
            std::copy(v.pMem, v.pMem + sz, pMem);
        }
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            delete[] pMem;
            sz = v.sz;
            pMem = v.pMem;
            v.sz = 0;
            v.pMem = nullptr;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // Индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }

    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }

    // Индексация с контролем
    T& at(size_t ind)
    {
        if ((ind >= sz) || (ind < 0)) throw out_of_range("Index out of range");
        return pMem[ind];
    }

    const T& at(size_t ind) const
    {
        if ((ind >= sz) || (ind < 0)) throw out_of_range("Index out of range");
        return pMem[ind];
    }

    // Сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // Скалярные операции
    TDynamicVector operator+(T val) const
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] + val;
        }
        return tmp;
    }

    TDynamicVector operator-(T val) const
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] - val;
        }
        return tmp;
    }

    TDynamicVector operator*(T val) const
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }

    TDynamicVector operator+(const TDynamicVector& v) const
    {
        if (sz != v.sz) throw invalid_argument("Vectors must be the same size");

        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] + v.pMem[i];
        }
        return tmp;
    }

    TDynamicVector operator-(const TDynamicVector& v) const
    {
        if (sz != v.sz) throw invalid_argument("Vectors must be the same size");

        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] - v.pMem[i];
        }
        return tmp;
    }

    T operator*(const TDynamicVector& v) const noexcept(noexcept(TDynamicVector()))
    {
        if (sz != v.sz) throw invalid_argument("Vectors must be of the same size");

        T result = NULL;
        for (size_t i = 0; i < sz; i++) {
            result += pMem[i] * v.pMem[i];
        }
        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++) {
            ostr << v.pMem[i] << ' ';
        }
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz > MAX_MATRIX_SIZE) {
            throw invalid_argument(" ");
        }
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                if (pMem[i][j] != m.pMem[i][j]) return false;
            }
        }
        return true;
    }

    // матрично-скалярные операции
    TDynamicVector<T> operator*(const T& val)
    {
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; i++) {
            result.pMem[i] = pMem[i];
            result.pMem[i] *= val;
        }
        return result;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != m.sz) throw invalid_argument("M must be of the same size");
        TDynamicVector<T> tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp[i] += pMem[i] * v;
        }
        return tmp;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        TDynamicMatrix tmp(sz);
        if (sz != m.sz) throw invalid_argument("M must be of the same size");
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                tmp.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
            }
        }
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        TDynamicMatrix tmp(sz);
        if (sz != m.sz) throw invalid_argument("M must be of the same size");
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                tmp.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
            }
        }
        return tmp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                tmp.pMem[i][j] = 0;
                for (size_t k = 0; k < sz; k++) {
                    tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }
        return tmp;
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
                ostr << v.pMem[i][j] << " ";
            }
            ostr << std::endl;
        }
        return ostr;
    }
};

//#endif