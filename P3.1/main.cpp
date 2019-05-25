#include <iostream>
#include <array>
#include <assert.h>
#include "CMyVektor.h"
#include "C_DGLSolver.h"

CMyVektor<double, 2> DGLSystem(const CMyVektor<double, 2>& y, double x)
{
	CMyVektor<double, 2> result;
	result[0] = 2 * y[1] - x * y[0];
	result[1] = y[0] * y[1] - 2 * (x*x*x);
	return result;
}

double DGLSystemDritterOrdnung(const CMyVektor<double, 3>& y, double x)
{
	return (2 * x * y[1] * y[2]) + (2 * y[0] * y[0] * y[1]);
}

int main()
{
	// Aufgabe 4
	CMyVektor<double, 2> startPos({ 0, 1 });
	C_DGLSolver<double, 2> dglSystemSolver(DGLSystem);
	dglSystemSolver.Euler(0, 2, 100, startPos);
	dglSystemSolver.Heun(0, 2, 100, startPos);
	

	
	C_DGLSolver<double, 3> dglSolverNterOrdnung(DGLSystemDritterOrdnung);
	std::array<int, 4> steps{ 10, 100, 1000, 10000 };
	CMyVektor<double, 3> startPosNterOrdnung({ 1, -1, 2 });
	for (int i = 0; i < steps.size(); ++i)
	{
		dglSolverNterOrdnung.Euler(1, 2, steps[i], startPosNterOrdnung);
		dglSolverNterOrdnung.Heun(1, 2, steps[i], startPosNterOrdnung);
	}

	system("PAUSE");
}