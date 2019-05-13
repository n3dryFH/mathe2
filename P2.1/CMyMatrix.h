#pragma once

#include <array>
#include <exception>
#include "CMyVektor.h"

template <typename T, int Row, int Column> // Colum = spalte, row = zeile
class CMyMatrix
{
public:
	template<typename T, int Row, int Column>
	friend CMyVektor<T, Row> operator*(const CMyMatrix<T, Row, Column> matrix, const CMyVektor<T, Column> vector);
	
	CMyMatrix() 
	{
		m_matrix = { 0 };
	}

	CMyMatrix(std::array< std::array<T, Column>, Row> matrix) : m_matrix(matrix) {}
	
	T Get(int rowId, int columnId) const
	{
		return m_matrix[rowId][columnId];
	}	

	void Set(int rowId, int columnId, T value)
	{
		m_matrix[rowId][columnId] = value;
	}
	
	CMyMatrix<T, 2, 2> invers() const
	{
		if (Column != 2 || Row != 2)
			throw std::exception("Only 2x2 Matrices supported!");

		CMyMatrix<T, 2, 2> inverse_matrix;
		const T factor = (1 / ((m_matrix[0][0] * m_matrix[1][1]) - (m_matrix[0][1] * m_matrix[1][0])));
		inverse_matrix.Set(0, 0, m_matrix[1][1] * factor); // d
		inverse_matrix.Set(0, 1, -m_matrix[0][1] * factor); // -b
		inverse_matrix.Set(1, 0, -m_matrix[1][0] * factor); // -c
		inverse_matrix.Set(1, 1, m_matrix[0][0] * factor); // a
		return inverse_matrix;
	}

	void print() const
	{
		std::cout << "Matrix" << std::endl;
		for (unsigned int i = 0; i < Row; ++i)
		{
			for (unsigned int j = 0; j < Column; ++j)
				std::cout << m_matrix[i][j] << " ";
			std::cout << std::endl;
		}			
	}

private:
	std::array<std::array<T, Column>, Row> m_matrix;

};

template<typename T, int Row, int Column>
CMyVektor<T, Row> operator * (const CMyMatrix<T, Row, Column> matrix, const CMyVektor<T, Column> vector)
{
	CMyVektor<T, Row> newVector;
	for (unsigned int row = 0; row < Row; ++row)
		for (unsigned int column = 0; column < Column; ++column)		
			newVector[row] += matrix.Get(row, column) * vector[column];

	return newVector;
}

template<typename T, int FVectorSize, int DerivedVectorSize>
CMyMatrix<T, DerivedVectorSize, FVectorSize> jacobi(const CMyVektor<T, FVectorSize>& x, CMyVektor<T, DerivedVectorSize> (*function) (const CMyVektor<T, FVectorSize>& x))
{
	CMyMatrix<T, DerivedVectorSize, FVectorSize> jacobiMatrix;
	const double h = 1e-4; // 10 ^ -4
	CMyVektor<T, DerivedVectorSize> f = function(x);
	for (unsigned int i = 0; i < FVectorSize; ++i)
	{
		CMyVektor<T, FVectorSize> tmpVec(x);
		tmpVec[i] += h;
		CMyVektor<T, DerivedVectorSize> fx = (function(tmpVec) - f) / h;
		for (unsigned int j = 0; j < DerivedVectorSize; ++j)
			jacobiMatrix.Set(j, i, fx[j]);		
	}
	
	return jacobiMatrix;
}

template<typename T, int VectorSize>
void newtonIteration(const CMyVektor<T, VectorSize>& aX, CMyVektor<T, VectorSize>(*function) (const CMyVektor<T, VectorSize>& x))
{
	CMyVektor<T, VectorSize> x(aX);
	bool bAbort = false;
	for (unsigned int i = 0; i < 50; ++i)
	{		
		std::cout << "Schritt " << i << " :" << std::endl;
		std::cout << "\tx = (" << x[0] << "; " << x[1] << ")" << std::endl;

		CMyVektor<T, VectorSize> fx = function(x);
		std::cout << "\tf(x) = (" << fx[0] << "; " << fx[1] << ")" << std::endl;	
	
		CMyMatrix<T, VectorSize, VectorSize> xJacobiMatrix = jacobi<T, VectorSize, VectorSize>(x, function);
		std::cout << "\tf'(x) = " << std::endl
			<< "\t\t( " << xJacobiMatrix.Get(0, 0) << "; " << xJacobiMatrix.Get(0, 1) << std::endl
			<< "\t\t" << xJacobiMatrix.Get(1, 0) << "; " << xJacobiMatrix.Get(1, 1) << " )" << std::endl;

		CMyMatrix<T, VectorSize, VectorSize> xJacobiMatrixInverse = xJacobiMatrix.invers();
		std::cout << "\t(f'(x))^(-1) = " << std::endl
			<< "\t\t( " << xJacobiMatrixInverse.Get(0, 0) << "; " << xJacobiMatrixInverse.Get(0, 1) << std::endl
			<< "\t\t" << xJacobiMatrixInverse.Get(1, 0) << "; " << xJacobiMatrixInverse.Get(1, 1) << " )" << std::endl;

		CMyVektor<T, VectorSize> deltaX = xJacobiMatrixInverse * fx;
		deltaX = -1 * deltaX;
		std::cout << "\tdx = (" << deltaX[0] << "; " << deltaX[1] << ")" << std::endl;		
		
		std::cout << "\t||f(x)|| = " << fx.Length() << std::endl;

		x = x + deltaX;		

		if (function(x).Length() < 1e-5)
		{
			bAbort = true;
			break;
		}		
	}

	std::cout << "Ende wegen ";
	if (bAbort)
	{
		std::cout << " ||f(x)||<1e-5 bei " << std::endl;
	}
	else
	{
		std::cout << "Schrittanzahl = 50" << std::endl;
	}

	CMyVektor<T, VectorSize> fx = function(x);
	std::cout << "\tx = (" << x[0] << "; " << x[1] << ")" << std::endl;
	std::cout << "\tf(x) = (" << fx[0] << "; " << fx[1] << ")" << std::endl;
	std::cout << "\t||f(x)|| = " << fx.Length() << std::endl;
}