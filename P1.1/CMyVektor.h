#pragma once
#include <stdexcept>
#include <vector>
#include <cmath>

template<typename T>
class CMyVektor
{
public:
	template<typename T>
	friend CMyVektor<T> operator + (const CMyVektor<T>& a, const CMyVektor<T>& b);
	template<typename T>
	friend CMyVektor<T> operator * (double lambda, const CMyVektor<T>& a);
	template<typename T>
	friend CMyVektor<T> gradient(const CMyVektor<T>& x, double(*funktion)(const CMyVektor<T>& x));
	template<typename T>
	friend void gradientSteps(CMyVektor<T> x, double(*funktion)(const CMyVektor<T>& x), double lambda);
	template<typename T>
	friend std::ostream& operator << (std::ostream& ostream, const CMyVektor<T>& vec);

	CMyVektor(int dimension) : m_Dimension(dimension)
	{
		m_Vectors = new T[dimension];
	}

	CMyVektor(const std::vector<T>& vector)
	{
		m_Dimension = vector.size();
		m_Vectors = new T[m_Dimension];
		for (int i = 0; i < m_Dimension; ++i)
			m_Vectors[i] = vector[i];
	}

	~CMyVektor()
	{
		delete[] m_Vectors;
		m_Vectors = nullptr;
	}
	
	CMyVektor(const CMyVektor& vec)
	{
		m_Dimension = vec.m_Dimension;
		m_Vectors = new T[m_Dimension];
		for (int i = 0; i < m_Dimension; ++i)
			m_Vectors[i] = vec[i];
	}

	inline int GetDimension() const { return m_Dimension; }

	
	T operator [] (int index) const
	{
		if (index > m_Dimension || index < 0)
		{
			throw std::out_of_range("received index out of range");
		}

		return m_Vectors[index];
	}
	
	CMyVektor<T> & operator = (const CMyVektor<T>& vec)
	{
		if (m_Vectors)
		{
			delete m_Vectors;
			m_Vectors = nullptr;
		}			

		m_Dimension = vec.m_Dimension;
		m_Vectors = new T[m_Dimension];
		for (int i = 0; i < m_Dimension; ++i)
			m_Vectors[i] = vec[i];
		return *this;
	}

	T& operator [] (int index)
	{
		if (index > m_Dimension || index < 0)
		{
			throw std::out_of_range("received index out of range");
		}			
				
		return m_Vectors[index];
	}

	double Length() const
	{
		double len = .0;
		for (int i = 0; i < m_Dimension; ++i)		
			len += std::pow(m_Vectors[i], 2);
		return std::sqrt(len);		
	}

private:
	int m_Dimension;
	T* m_Vectors;
};

template<typename T>
CMyVektor<T> operator + (const CMyVektor<T>& a, const CMyVektor<T>& b)
{
	if (a.GetDimension() != b.GetDimension())
	{
		throw std::exception("Dimensions are not the same!");
	}

	CMyVektor<T> newVector(a.GetDimension());
	for (int i = 0; i < newVector.GetDimension(); ++i)
		newVector[i] = a[i] + b[i];
	return newVector;
}

template<typename T>
CMyVektor<T> operator * (double lambda, const CMyVektor<T>& a)
{
	CMyVektor<T> newVector(a.GetDimension());
	for (int i = 0; i < newVector.GetDimension(); ++i)
		newVector[i] = a[i] * lambda;
	return newVector;
}

template<typename T>
std::ostream& operator << (std::ostream& stream, const CMyVektor<T>& vec)
{
	std::cout << "( ";
	for (int i = 0; i < vec.m_Dimension; ++i)
		std::cout << vec[i] << ";";
	std::cout << " )";
	return stream;
}

template<typename T>
CMyVektor<T> gradient(const CMyVektor<T>& x, double(*funktion)(const CMyVektor<T>& x))
{
	CMyVektor<T> gradientVec(x.GetDimension());
	const double h = 0.00000001; // 10 ^ -8
	const double rightTerm = funktion(x);
	for (int i = 0; i < gradientVec.GetDimension(); ++i)
	{
		CMyVektor<T> tmpVec(x);
		tmpVec[i] += h;
		gradientVec[i] = (funktion(tmpVec) - rightTerm) / h;
	}
	return gradientVec;
}

template<typename T>
void gradientSteps(CMyVektor<T> x, double(*funktion)(const CMyVektor<T>& x), double lambda = 1.0)
{
	bool bAbort = false;
	for (int i = 0; i < 25; ++i)
	{		
		std::cout << "Schritt " << i << ":" << std::endl;
		std::cout << "x = " << x << std::endl;
		std::cout << "lambda = " << lambda << std::endl;		
		std::cout << "f(X) = " << funktion(x) << std::endl;
		CMyVektor<T> gradientVec = gradient(x, funktion);
		std::cout << "grad f(x) = " << gradientVec << std::endl;
		const double gradientVecProduct = gradientVec.Length();
		std::cout << "||grad f(x)|| = " << std::abs(gradientVecProduct) << std::endl << std::endl;

		CMyVektor<T> newVec(x + lambda * gradientVec);
		std::cout << "x_neu = " << newVec << std::endl;
		const double newVecProduct = funktion(newVec);
		std::cout << "f(x_neu) = " << newVecProduct << std::endl << std::endl;

		if (newVecProduct > funktion(x))
		{		
			std::cout << "Test mit doppelter Schrittweite (lambda = " << 2 * lambda << "):" << std::endl;
			CMyVektor<T> testVec(x + (2 * lambda) * gradient(x, funktion));
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