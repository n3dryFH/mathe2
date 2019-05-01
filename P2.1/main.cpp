#include <iostream>
#include <array>
#include <cmath>
#include "CMyMatrix.h"
#include "CMyVektor.h"

template<typename T, int ParamVecSize, int ResultVecSize>
CMyVektor<T, ResultVecSize> f(const CMyVektor<T, ParamVecSize>& x)
{
	CMyVektor<T, ResultVecSize> result;
	result[0] = x[0] * x[1] * std::exp(x[2]);
	result[1] = x[1] * x[2] * x[3];
	result[2] = x[3];
	return result;
}

template<typename T, int ParamVecSize, int ResultVecSize>
CMyVektor<T, ResultVecSize> newton(const CMyVektor<T, ParamVecSize>& x)
{
	CMyVektor<T, ResultVecSize> result;
	result[0] = (x[0] * x[0] * x[0] * x[1] * x[1] * x[1]) - (2 * x[1]);
	result[1] = x[0] - 2;
	return result;
}

int main()
{
	CMyVektor<int, 3> vec{ { 2, 1, 3 } };
	std::array<std::array<int, 3>, 3> matArray{ { { 1, 2, 3 }, {4, 5, 6 }, {7, 8, 9} } };	
	CMyMatrix<int, 3, 3> matrix (matArray);
	//matrix.print();
	CMyVektor<int, 3> result = matrix * vec;

	std::array<std::array<double, 2>, 2> mat2x2Array{ { { 1, 2}, {4, 5} } };
	CMyMatrix<double, 2, 2> mat2x2(mat2x2Array);
	auto test = mat2x2.invers();
	//test.print();

	CMyVektor<double, 4> start { { 1, 2, 0, 3 } };
	CMyMatrix<double, 3, 4> jacobiMat = jacobi<double, 3, 4, 3>(start, f);
	//jacobiMat.print();

	CMyVektor<double, 2> startNewton{ { 1, 1 } };
	newtonIteration<double, 2>(startNewton, newton);

	system("PAUSE");
}