#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>


class CZufall
{
public:
	void initialisiere(int n)
	{		
		srand(n);
	}

	int wert(int min, int max) const
	{
		return rand() % (max - min + 1) + min;
	}	

	std::vector<int> test(int a, int b, int N) const
	{
		std::vector<int> values(b-a+1);
		for (int i = 0; i < N; ++i)
		{
			int rnd = wert(a, b);
			++values.at(rnd - a);
		}
		return values;
	}

	std::vector<int> test_falsch(int a, int b, int N) const
	{
		std::vector<int> values(b - a + 1);
		for (int i = 0; i < N; ++i)
		{
			srand(time(NULL));
			int rnd = wert(a, b);
			++values.at(rnd - a);
		}
		return values;
	}

private:
};