#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <fstream>
#include <cassert>
#include <math.h>
#include "CKomplex.h"

using namespace std;

std::vector<CKomplex> transform(const std::vector<CKomplex>& komplexVec, bool hinTransformation)
{
	std::vector<CKomplex> transformed(komplexVec.size());
	const double direction = hinTransformation ? -2 : 2;
	const int N = komplexVec.size();

	for (int n = 0; n < N; ++n)
	{
		for (int k = 0; k < N; ++k)		
			transformed.at(n) = transformed.at(n) + komplexVec.at(k) * CKomplex((direction * M_PI * k * n) / N);
		transformed.at(n) = (1 / std::sqrt(N)) * transformed.at(n);
	}
	return transformed;
}


double maxDeviation(const std::vector<CKomplex>& a, const std::vector<CKomplex>& b)
{
	assert(a.size() == b.size());
	double maxDeviation = .0;
	for (int i = 0; i < a.size(); ++i)
	{
		const double delta = std::abs(a.at(i).abs() - b.at(i).abs());
		if (delta > maxDeviation)
			maxDeviation = delta;
	}
	return maxDeviation;
}

vector<CKomplex> werte_einlesen(const char *dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const char *dateiname, vector<CKomplex> werte, double epsilon = -1.0)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
	// File schliessen
	fp.close();
}
