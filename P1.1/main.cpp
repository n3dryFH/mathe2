#include <iostream>
#include <assert.h>
#include "CMyVektor.h"

template<typename T, int Size>
double calcGradient(const CMyVektor<T, Size>& x)
{
	double result = 0.0;
	result += x[0] + std::pow(x[1], 2) + std::pow(x[2], 3);
	return result;
}

template<typename T, int Size>
double f(const CMyVektor<T, Size>& x)
{
	return std::sin(x[0] * x[1]) + std::sin(x[0]) + std::cos(x[1]);
}

template<typename T, int Size>
double g(const CMyVektor<T, Size>& x)
{
	return -(2 * std::pow(x[0], 2) - (2 * x[0] * x[1]) + std::pow(x[1], 2) + std::pow(x[2], 2) - (2 * x[0]) - (4 * x[2]));
}

int main()
{	
	CMyVektor<double, 3> vec2({ 1.0, 2.0, 2.0 });
	CMyVektor<double, 3> vec3({ 1.0, 2.0, 2.0 });
	CMyVektor<double, 3> vec4 = vec2 + vec3;
	CMyVektor<double, 3> vecScala = 2.0 * vec2;
	assert(vecScala[0] == 2.0 && vecScala[1] == 4.0 && vecScala[2] == 4.0);
	assert(vec4[0] == 2.0 && vec4[1] == 4.0 && vec4[2] == 4.0);
	assert(vec2.Length() == 3.0);	
	
	CMyVektor<double, 3> test0({ 3.0, 4.0, 5.0 });
	CMyVektor<double, 3> gradientVec = gradient(test0, calcGradient);

	CMyVektor<double, 3> test1({ 0.2, -2.1});	
	gradientSteps(test1, f);

	//CMyVektor<double, 3> test2({ .0, .0, .0 });
	//gradientSteps(test2, g, .1);

	system("PAUSE");
}