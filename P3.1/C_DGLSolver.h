#pragma once
#include "CMyVektor.h"
#include <assert.h>

template<typename T, int Size>
class C_DGLSolver
{
public:
	C_DGLSolver(double(*afDGLnterOrdnung)(const CMyVektor<T, Size>& y, const double x)) 
		: m_fDGLnterOrdnung(afDGLnterOrdnung) {}
	C_DGLSolver(CMyVektor<T, Size>(*afDGLSystem)(const CMyVektor<T, Size>& y, const double x)) 
		: m_fDGLSystem(afDGLSystem) {}

	void Euler(double startX, double endX, int steps, const CMyVektor<T, Size>& y_Start)
	{
		const double h = (endX - startX) / steps;
		if (m_fDGLSystem)
			std::cout << "h = " << h << std::endl << std::endl;

		double x = startX;
		CMyVektor<T, Size> y = y_Start;

		for (int i = 0; i < steps; ++i)
		{
			CMyVektor<T, Size> slope = ableitungen(y, x);
			if (m_fDGLSystem)
			{
				std::cout << "Schritt " << i << ":" << std::endl;
				std::cout << "\t\tx = " << x << std::endl;
				std::cout << "\t\ty = (" << y[0] << "; " << y[1] << ")" << std::endl;
				std::cout << "\t\ty' = (" << slope[0] << "; " << slope[1] << ")" << std::endl << std::endl;
			}						
			y = y + (h * slope);			
			x += h;			
		}		

		if (m_fDGLnterOrdnung)
		{
			std::cout << "Abweichung bei Euler bei " << steps << " Schritten: " << y[0] - 0.5 << std::endl;
		}
		else
		{
			std::cout << "Ende bei " << std::endl;
			std::cout << "\t\tx = " << x << std::endl;
			std::cout << "\t\ty = (" << y[0] << "; " << y[1] << ")" << std::endl;
		}
	}

	void Heun(double startX, double endX, int steps, const CMyVektor<T, Size>& y_Start)
	{
		const double h = (endX - startX) / steps;
		if (m_fDGLSystem)
			std::cout << "h = " << h << std::endl << std::endl;

		double x = startX;
		CMyVektor<T, Size> y = y_Start;

		for (int i = 0; i < steps; ++i)
		{
			CMyVektor<T, Size> slopeY1 = ableitungen(y, x);
			CMyVektor<T, Size> yWithStep = y + (h * slopeY1);
			CMyVektor<T, Size> slopeY2 = ableitungen(yWithStep, x + h);
			CMyVektor<T, Size> middle = .5 * (slopeY1 + slopeY2);
			if (m_fDGLSystem)
			{
				std::cout << "Schritt " << i << ":" << std::endl;
				std::cout << "\t\tx = " << x << std::endl;
				std::cout << "\t\ty = (" << y[0] << "; " << y[1] << ")" << std::endl;
				std::cout << "\t\ty'_orig = (" << slopeY1[0] << "; " << slopeY1[1] << ")" << std::endl << std::endl;
				std::cout << "\t\ty_Test = (" << yWithStep[0] << "; " << yWithStep[1] << ")" << std::endl;
				std::cout << "\t\ty'_Test = (" << slopeY2[0] << "; " << slopeY2[1] << ")" << std::endl << std::endl;
				std::cout << "\t\ty'_Mittel = (" << middle[0] << "; " << middle[1] << ")" << std::endl << std::endl;
			}			

			x += h;
			y = y + (h * middle);
		}		

		if (m_fDGLnterOrdnung)
		{
			std::cout << "Abweichung bei Heun  bei " << steps << " Schritten: " << y[0] - 0.5 << std::endl;
		}
		else
		{
			std::cout << "Ende bei " << std::endl;
			std::cout << "\t\tx = " << x << std::endl;
			std::cout << "\t\ty = (" << y[0] << "; " << y[1] << ")" << std::endl;
		}
	}

private:
	CMyVektor<T, Size> ableitungen(const CMyVektor<T, Size>& y, const double x)
	{
		if (m_fDGLSystem)		
			return m_fDGLSystem(y, x);		

		assert(m_fDGLnterOrdnung != nullptr);
		CMyVektor<T, Size> derivedY;
		for (int i = 0; i < Size - 1; ++i)		
			derivedY[i] = y[i + 1];
		derivedY[Size - 1] = m_fDGLnterOrdnung(y, x);
		return derivedY;			
	}

	CMyVektor<T, Size>(*m_fDGLSystem)(const CMyVektor<T, Size>& y, const double x) = nullptr;
	double(*m_fDGLnterOrdnung)(const CMyVektor<T, Size>& y, const double x) = nullptr;
};