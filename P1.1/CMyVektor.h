#pragma once
#include <stdexcept>
#include <array>
#include <cmath>

template<typename T, int Size>
class CMyVektor
{
public:
	template<typename T, int Size>
	friend CMyVektor<T, Size> operator + (const CMyVektor<T, Size>& a, const CMyVektor<T, Size>& b);
	template<typename T, int Size>
	friend CMyVektor<T, Size> operator * (double lambda, const CMyVektor<T, Size>& a);
	template<typename T, int Size>
	friend CMyVektor<T, Size> gradient(const CMyVektor<T, Size>& x, double(*funktion)(const CMyVektor<T, Size>& x));
	template<typename T, int Size>
	friend void gradientSteps(const CMyVektor<T, Size>& aX, double(*funktion)(const CMyVektor<T, Size>& x), double lambda);
	template<typename T, int Size>
	friend std::ostream& operator << (std::ostream& ostream, const CMyVektor<T, Size>& vec);

	CMyVektor() {}

	CMyVektor(const std::array<T, Size>& vector)
	{		
		for (int i = 0; i < Size; ++i)
			m_Vectors[i] = vector[i];
	}	
	
	CMyVektor(const CMyVektor<T, Size>& vec)
	{	
		for (int i = 0; i < Size; ++i)
			m_Vectors[i] = vec[i];
	}

	inline int GetDimension() const { return Size; }

	T operator [] (int index) const
	{
		if (index > Size || index < 0)
		{
			throw std::out_of_range("received index out of range");
		}

		return m_Vectors[index];
	}
	
	CMyVektor<T, Size> & operator = (const CMyVektor<T, Size>& vec)
	{	
		for (int i = 0; i < Size; ++i)
			m_Vectors[i] = vec[i];
		return *this;
	}

	T& operator [] (int index)
	{
		if (index > Size || index < 0)
		{
			throw std::out_of_range("received index out of range");
		}			
				
		return m_Vectors[index];
	}

	double Length() const
	{
		double len = .0;
		for (int i = 0; i < Size; ++i)
			len += std::pow(m_Vectors[i], 2);
		return std::sqrt(len);		
	}

private:	
	std::array<T, Size> m_Vectors;
};

template<typename T, int Size>
CMyVektor<T, Size> operator + (const CMyVektor<T, Size>& a, const CMyVektor<T, Size>& b)
{
	CMyVektor<T, Size> newVector;
	for (int i = 0; i < Size; ++i)
		newVector[i] = a[i] + b[i];
	return newVector;
}

template<typename T, int Size>
CMyVektor<T, Size> operator * (double lambda, const CMyVektor<T, Size>& a)
{
	CMyVektor<T, Size> newVector;
	for (int i = 0; i < Size; ++i)
		newVector[i] = a[i] * lambda;
	return newVector;
}

template<typename T, int Size>
std::ostream& operator << (std::ostream& stream, const CMyVektor<T, Size>& vec)
{
	std::cout << "( ";
	for (int i = 0; i < Size; ++i)
		std::cout << vec[i] << ";";
	std::cout << " )";
	return stream;
}

template<typename T, int Size>
CMyVektor<T, Size> gradient(const CMyVektor<T, Size>& x, double(*funktion)(const CMyVektor<T, Size>& x))
{
	CMyVektor<T, Size> gradientVec;
	const double h = 0.00000001; // 10 ^ -8
	const double rightTerm = funktion(x);
	for (int i = 0; i < Size; ++i)
	{
		CMyVektor<T, Size> tmpVec(x);
		tmpVec[i] += h;
		gradientVec[i] = (funktion(tmpVec) - rightTerm) / h;
	}
	return gradientVec;
}

template<typename T, int Size>
void gradientSteps(const CMyVektor<T, Size>& aX, double(*funktion)(const CMyVektor<T, Size>& x), double lambda = 1.0)
{
	CMyVektor<T, Size> x(aX);
	bool bAbort = false;
	for (int i = 0; i < 25; ++i)
	{		
		std::cout << "Schritt " << i << ":" << std::endl;
		std::cout << "x = " << x << std::endl;
		std::cout << "lambda = " << lambda << std::endl;		
		std::cout << "f(X) = " << funktion(x) << std::endl;
		CMyVektor<T, Size> gradientVec = gradient(x, funktion);
		std::cout << "grad f(x) = " << gradientVec << std::endl;
		const double gradientVecProduct = gradientVec.Length();
		std::cout << "||grad f(x)|| = " << std::abs(gradientVecProduct) << std::endl << std::endl;

		CMyVektor<T, Size> newVec(x + lambda * gradientVec);
		std::cout << "x_neu = " << newVec << std::endl;
		const double newVecProduct = funktion(newVec);
		std::cout << "f(x_neu) = " << newVecProduct << std::endl << std::endl;

		if (newVecProduct > funktion(x))
		{		
			std::cout << "Test mit doppelter Schrittweite (lambda = " << 2 * lambda << "):" << std::endl;
			CMyVektor<T, Size> testVec(x + (2 * lambda) * gradient(x, funktion));
			std::cout << "x_test = " << testVec << std::endl;
			const double testVecProduct = funktion(testVec);
			std::cout << "f(x_test) = " << testVecProduct << std::endl;
			if (testVecProduct > funktion(newVec))
			{
				x = testVec;
				lambda *= 2;
				std::cout << "verdoppele Schrittweite!" << std::endl;
			}
			else
			{
				x = newVec;
				std::cout << "behalte alte Schrittweite!" << std::endl;
			}
			
		}
		else if (funktion(newVec) <= funktion(x))
		{
			double newXProduct = .0;
			do
			{
				lambda /= 2;
				std::cout << "halbiere Schrittweite (lambda = " << lambda << "):" << std::endl;
				newVec = (x + lambda * gradientVec);
				std::cout << "x_neu = " << newVec << std::endl;
				newXProduct = funktion(newVec);
				std::cout << "f(x_neu) = " << newXProduct << std::endl << std::endl;

			} while (newXProduct <= funktion(x));
			x = newVec;
		}

		std::cout << std::endl;
		if (std::abs(gradient(x, funktion).Length()) < 0.00001)
		{
			bAbort = true;
			break;
		}
			
	}

	std::cout << "Ende wegen ";
	if (bAbort)
	{
		std::cout << " || grad f(x) || < " << std::abs(gradient(x, funktion).Length());		
	}
	else
	{
		std::cout << "Schrittanzahl = 25";
	}	
		
	std::cout << " bei" << std::endl
	<< "x = " << x << std::endl
	<< "lambda = " << lambda << std::endl
	<< "f(X) = " << funktion(x) << std::endl
	<< "grad f(x) = " << gradient(x, funktion) << std::endl
	<< "||grad f(x)|| = " << std::abs(gradient(x, funktion).Length()) << std::endl << std::endl;
}