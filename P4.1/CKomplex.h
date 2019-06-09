#pragma once
#include <cmath>

class CKomplex
{
public:
	CKomplex() : Real(.0), Imag(.0) {}
	CKomplex(double a, double b) : Real(a), Imag(b) {}
	explicit CKomplex(double phi) : Real(cos(phi)), Imag(sin(phi)) {}		

	inline double re() const { return Real; }
	inline double im() const { return Imag; }

	double abs() const
	{
		return std::sqrt((Real * Real) + (Imag * Imag));
	}

private:
	double Real, Imag;
};

CKomplex operator + (const CKomplex& a, const CKomplex& b)
{
	return CKomplex(a.re() + b.re(), a.im() + b.im());
}

CKomplex operator * (const CKomplex& a, const CKomplex& b)
{
	return CKomplex((a.re() * b.re()) - (a.im() * b.im()), (a.re() * b.im()) - (a.im() * b.re()));
}

CKomplex operator * (double b, const CKomplex& a)
{
	return CKomplex(a.re() * b, a.im() * b);
}

