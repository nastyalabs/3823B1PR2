#include "classesess.h"
#include <random>
#include <chrono>

//#define RAND_MAX 1 //устанавливаю макс границу
int main()
{
	/*Matrix <int> a(2);
	Matrix <int> b(2);
	b[0][0] = 2;
	b[1][1] = 2;
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			a[i][j] = i + j;
	cout << a << b << a * b;

	MatrixInLine <int> aa(2);
	MatrixInLine <int> bb(2);
	MatrixInLine <int> f(a);
	Matrix <int> h(f);
	bb.sget(0, 0) = 2;
	bb.sget(1, 1) = 2;
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			aa.sget(i, j) = i + j;
	NoZeroMatrix<int> jj(a);
	NoZeroMatrix<int> ll(aa);
	Matrix<int> ss(jj);
	MatrixInLine<int> cc(ll);
	cout << aa << bb << aa * bb << f << h << jj << ll << ss << cc;
	cout << "NoZeroLine '*' :" << endl;
	NoZeroMatrix<int> a1(a);
	NoZeroMatrix<int> b1(b);
	cout << a1 << b1 << a1 * b1;
	*/
	int start = 0;
	int end = 1;
	const int size = 500;
	Matrix <int> a(size);
	Matrix <int> b(size);

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			a[i][j] = rand() % (end - start + 1) + start;;

	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			b[i][j] = rand() % (end - start + 1) + start;;

	//cout << a << b << a * b;

	MatrixInLine<int> la(a);
	MatrixInLine<int> lb(b);

	NoZeroMatrix<int> na(a);
	NoZeroMatrix<int> nb(b);

	cout << "Matrix '*': " << endl;
	//cout  << a << b << a * b;

	//ЗАМЕР перемножения квадратных матриц
	auto start_time = std::chrono::steady_clock::now();
	Matrix<int> matrix = a * b;
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << elapsed_ns.count()<< "nanoseconds = " << elapsed_ns.count()/1000000000 <<" seconds" << endl;

	cout << "MatrixInLine '*': " << endl;
	//cout << la << lb << la * lb;

	//ЗАМЕР перемножения матриц - линий
	start_time = std::chrono::steady_clock::now();
	MatrixInLine<int> l = la * lb;
	end_time = std::chrono::steady_clock::now();
	elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << elapsed_ns.count() << "nanoseconds = " << elapsed_ns.count() / 1000000000 << " seconds" << endl;

	Matrix<int> line(l);
	if (matrix == line)
		cout << "TRUE" << endl << endl;
	else
		cout << "FALSE" << endl << endl;

	cout << "NoZeroMatrix '*': " << endl;
	//cout << na << nb << na * nb;

	//ЗАМЕР перемножения матриц без 0
	start_time = std::chrono::steady_clock::now();
	NoZeroMatrix<int> n = na * nb;
	end_time = std::chrono::steady_clock::now();
	elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << elapsed_ns.count() << "nanoseconds = " << elapsed_ns.count() / 1000000000 << " seconds" << endl;

	Matrix<int> nozero(n);
	 if (matrix == nozero)
		 cout << "TRUE" << endl << endl;
	else
		cout << "FALSE" << endl << endl;
	return 0;
}