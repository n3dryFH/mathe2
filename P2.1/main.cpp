#include <iostream>
#include <array>
#include <assert.h>
#include <cmath>
#include "CMyMatrix.h"
#include "CMyVektor.h"

template<typename T>
using Vector2 = CMyVektor<T, 2>;

template<typename T>
using Vector3 = CMyVektor<T, 3>;

template<typename T>
using Vector4 = CMyVektor<T, 4>;

template<typename T>
using Matrix2x2 = CMyMatrix<T, 2, 2>;

template<typename T>
using Matrix2x3 = CMyMatrix<T, 2, 3>;

template<typename T>
using Matrix3x4 = CMyMatrix<T, 3, 4>;

template<typename T>
Vector3<T> f(const Vector4<T>& x)
{
	Vector3<T> result;
	result[0] = x[0] * x[1] * std::exp(x[2]);
	result[1] = x[1] * x[2] * x[3];
	result[2] = x[3];
	return result;
}

template<typename T>
Vector2<T> newton(const Vector2<T>& x)
{
	Vector2<T> result;
	result[0] = (x[0] * x[0] * x[0] * x[1] * x[1] * x[1]) - (2 * x[1]);
	result[1] = x[0] - 2;
	return result;
}

int main()
{
	Vector3<int> vec{ { 1, 0, 4 } };
	std::array<std::array<int, 3>, 2> matArray{ { { 3, 2, 1 }, { 1, 0, 2 } } };
	Matrix2x3<int> matrix (matArray);
	const Vector2<int> result = matrix * vec;
	assert(result[0] == 7 && result[1] == 9);
	
	std::array<std::array<double, 2>, 2> mat2x2Array{ { { -3, 5}, {1, -1} } };
	Matrix2x2<double> mat2x2(mat2x2Array);
	const Matrix2x2<double> inverseTest = mat2x2.invers();
	assert(inverseTest.Get(0, 0) == 0.5 &&
		inverseTest.Get(0, 1) == 2.5 &&
		inverseTest.Get(1, 0) == 0.5 &&
		inverseTest.Get(1, 1) == 1.5);
	

	Vector4<double> start { { 1, 2, 0, 3 } };
	Matrix3x4<double> jacobiMat = jacobi<double, 4, 3>(start, f);
	jacobiMat.print();

	Vector2<double> startNewton{ { 1, 1 } };
	newtonIteration<double, 2>(startNewton, newton);

	system("PAUSE");
}