#pragma once
#include <iostream>
using namespace std;

template <typename T>
class MatrixInLine;

template <typename T>
class NoZeroMatrix;

template <typename T>
class Vector
{
public:
	T* pMem;
	size_t sz;
public:
	Vector(size_t s = 1) :sz(s)
	{
		pMem = new T[sz]();
	}

	~Vector()
	{
		delete[] pMem;
	}

	T& operator [] (size_t index)
	{
		return pMem[index];
	}

	Vector& operator = (const Vector& a)
	{
		if (this == &a)
			return *this;
		if (sz != a.sz)
		{
			sz = a.sz;
			int* p = new int[sz];
			delete[] pMem;
			pMem = p;
		}
		copy(a.pMem, a.pMem + sz, pMem);
		return *this;
	}

	bool operator == (const Vector & a) const noexcept
	{
		if (a.sz != sz)
			return 0;
		for (size_t i = 0; i < sz; i++)
			if (pMem[i] != a.pMem[i])
				return 0;
		return 1;
	}

	bool operator != (const Vector& a) const noexcept
	{
		if (a.sz != sz)
			return 1;
		for (size_t i = 0; i < sz; i++)
			if (pMem[i] != a.pMem[i])
				return 1;
		return 0;
	}

	T operator *(const Vector& a)
	{
		T res = {};
		for (size_t i = 0; i < sz; i++)
		{
			res = res + pMem[i] * a.pMem[i];
		}
		return res;
	}

	friend ostream& operator << (ostream& out, const Vector& a)
	{
		for (size_t i = 0; i < a.sz; i++)
			out << a.pMem[i] << " ";
		out << endl;
		return out;
	}
};

template <typename T>
class Matrix : public Vector<Vector<T>>
{
public:
	using Vector<Vector<T>>::pMem;
	using Vector<Vector<T>>::sz;
public:
	using Vector<Vector<T>>::operator[];
	using Vector<Vector<T>>::operator=;
	using Vector<Vector<T>>::operator==;

	Matrix(size_t s = 1) : Vector<Vector<T>>(s)
	{
		for (size_t i = 0; i < sz; i++)
			pMem[i] = Vector<T>(sz);
	}

	Matrix(MatrixInLine<T>& a) : Vector<Vector<T>>(a.sz)
	{
		for (size_t i = 0; i < sz; i++)
			pMem[i] = Vector<T>(sz);
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				pMem[i][j] = a.get(i, j);
	}

	Matrix(NoZeroMatrix<T>& a): Vector<Vector<T>>(a.size())
	{
		for (size_t i = 0; i < sz; i++)
			pMem[i] = Vector<T>(sz);
		for (int i = 0; i < a.sz; i++)
			if(a.NonZeroes[i] != NULL)
				pMem[a.IndRow[i]][a.IndCol[i]] =  a.NonZeroes[i];
	}

	Matrix operator * (const Matrix& a)
	{
		Matrix rez(sz);
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				for (size_t k = 0; k < sz; k++)
					rez.pMem[i][j] = rez.pMem[i][j] + pMem[i][k] * a.pMem[k][j];
		return rez;
	}

	size_t size()
	{
		return sz;
	}

	friend ostream& operator << (ostream& out, const Matrix& a)
	{
		out << "Matrix:" << endl;
		for (size_t i = 0; i < a.sz; i++)
			out << a.pMem[i];
		out << endl;
		return out;
	}
};

template <typename T>
class MatrixInLine
{
public:
	size_t sz;
	T* pMem;

	MatrixInLine(size_t s = 1) : sz(s)
	{
		pMem = new T[sz * sz]();
	}

	MatrixInLine(Matrix<T>& a) : sz(a.size())
	{
		pMem = new T[sz * sz]();
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				pMem[i * sz + j] = a[i][j];
	};

	MatrixInLine(NoZeroMatrix<T>& a) : sz(a.size())
	{
		pMem = new T[sz * sz]();
		for (size_t i = 0; i < a.sz; i++)
			if(a.NonZeroes[i] != NULL)
				pMem[a.IndRow[i] * a.size() + a.IndCol[i]] = a.NonZeroes[i];
	}

	T& operator [] (size_t i)
	{
		return pMem[i];
	}

	T& sget(size_t i, size_t j)
	{
		return pMem[i * sz + j];
	}


	MatrixInLine* operator = (const MatrixInLine& a)
	{
		if (this == &a)
			return *this;
		if (sz != a.sz)
		{
			sz = a.sz;
			T* p = new T[sz * sz - 1]();
			delete[] pMem;
			pMem = p;
		}
		copy(a.pMem, a.pMem + sz * sz - 1, pMem);
		return *this;
	}

	bool operator == (const MatrixInLine& a)
	{
		return Vector<Vector<T>>:: operator ==(a);
	}

	MatrixInLine operator * (const MatrixInLine& a)
	{
		MatrixInLine rez(sz);
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				for (size_t k = 0; k < sz; k++)
					rez.pMem[i * sz + j] = rez.pMem[i * sz + j] + pMem[i * sz + k] * a.pMem[k * sz + j];
		return rez;
	}

	T get(size_t i, size_t j)
	{
		return pMem[i * sz + j];
	}

	friend ostream& operator << (ostream& out, const MatrixInLine& a)
	{
		out << "Matrix in line:" << endl;
		for (size_t i = 0; i < a.sz; i++)
		{
			for (size_t j = 0; j < a.sz; j++)
				out << a.pMem[a.sz * i + j] << " ";
			out << endl;
		}
		out << endl;
		return out;
	}
};

template<typename T>
class NoZeroMatrix
{
public:
	size_t sz;
	T* NonZeroes;
	T* IndRow;
	T* IndCol;
	NoZeroMatrix(size_t s = 1) :sz(s)
	{
		NonZeroes = new T[sz]();
		IndRow = new T[sz]();
		IndCol = new T[sz]();
	}

	NoZeroMatrix(const Matrix <T>& a)
	{
		sz = 0;
		for (size_t i = 0; i < a.sz; i++)
			for (size_t j = 0; j < a.sz; j++)
				if (a.pMem[i][j] != NULL)
					sz++;
		NonZeroes = new T[sz]();
		IndRow = new T[sz]();
		IndCol = new T[sz]();
		size_t index = 0;
		for (size_t i = 0; i < a.sz; i++)
			for (size_t j = 0; j < a.sz; j++)
				if (a.pMem[i][j] != NULL)
				{
					NonZeroes[index] = a.pMem[i][j];
					IndRow[index] = i;
					IndCol[index] = j;
					index++;
				}
	}

	NoZeroMatrix(const MatrixInLine <T>& a)
	{
		sz = 0;
		for (size_t i = 0; i < a.sz; i++)
			for (size_t j = 0; j < a.sz; j++)
				if (a.pMem[i * a.sz + j] != NULL)
					sz++;
		NonZeroes = new T[sz]();
		IndRow = new T[sz]();
		IndCol = new T[sz]();
		size_t index = 0;
		for (size_t i = 0; i < a.sz; i++)
		{
			for (size_t j = 0; j < a.sz; j++)
				if (a.pMem[i * a.sz + j] != NULL)
				{
					NonZeroes[index] = a.pMem[i * a.sz + j];
					IndRow[index] = i;
					IndCol[index] = j;
					index++;
				}
		}
	}

	NoZeroMatrix operator * (NoZeroMatrix& a)
	{
		size_t index = 0;
		size_t end = 0; //заглушка
		NoZeroMatrix result(size() * a.size());
		for (size_t i = 0; i < sz; i++)
		{
			if ((i != 0) && (IndRow[i - 1] != IndRow[i]))
				end = 0;
			for (size_t j = end; j < a.sz; j++)
			{
				if (a.IndRow[j] > IndCol[i])
				{
					end = j;
					break;
				}
				if (IndCol[i] == a.IndRow[j])
				{
					int flag = 0;
					int k = index - 1;
					while ((k >= 0) && (result.IndRow[k] == IndRow[i]))
					{
						if (result.IndCol[k] == a.IndCol[j])
						{
							result.NonZeroes[k] = result.NonZeroes[k] + NonZeroes[i] * a.NonZeroes[j];
							flag = 1;
							break;
						}
						k--;
					}
					if (flag == 0)
					{
						result.NonZeroes[index] = result.NonZeroes[index] + NonZeroes[i] * a.NonZeroes[j];
						result.IndRow[index] = IndRow[i];
						result.IndCol[index] = a.IndCol[j];
						index++;
					}
				}
			}
		}
		return result;
	}

	NoZeroMatrix& operator = (NoZeroMatrix& a)
	{
		if (this == &a)
			return *this;
		if (sz != a.sz)
		{
			sz = a.sz;
			T* n = new T[sz]();
			T* ir = new T[sz]();
			T* ic = new T[sz]();
			delete[] NonZeroes;
			delete[] IndRow;
			delete[] IndCol;
			NonZeroes = n;
			IndRow = ir;
			IndCol = ic;
		}
		for (size_t i = 0; i < sz; i++)
		{
			NonZeroes[i] = a.NonZeroes[i];
			IndRow[i] = a.IndRow[i];
			IndCol[i] = a.IndCol[i];
		}
		return *this;
	}

	size_t size()
	{
		size_t max = 0;
		for (size_t i = 0; i < sz; i++)
			if ((IndRow[i] != NULL) && (IndRow[i] > max))
				max = IndRow[i];
		for (size_t i = 0; i < sz; i++)
			if ((IndCol[i] != NULL) && (IndCol[i] > max))
				max = IndCol[i];
		return max+1;
	}
	friend ostream& operator << (ostream& out, const NoZeroMatrix a)
	{
		out << "NonZeroes: ";
		for (size_t i = 0; i < a.sz; i++)
			out << a.NonZeroes[i] << " ";
		out << endl;
		out << "IndRow: ";
		for (size_t i = 0; i < a.sz; i++)
			out << a.IndRow[i] << " ";
		out << endl;
		out << "IndCol: ";
		for (size_t i = 0; i < a.sz; i++)
			out << a.IndCol[i] << " ";
		out << endl;
		out << endl;
		return out;
	}
};

