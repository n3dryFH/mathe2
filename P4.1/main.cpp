#include <iostream>
#include <vector>
#include "Fourier.h"

int main()
{
	const auto& original = werte_einlesen("Daten_original.txt");
	const auto& originalTransformed = transform(original, true);
	werte_ausgeben("Daten_Default.txt", originalTransformed);
	werte_ausgeben("Daten_0_1.txt", originalTransformed, 0.1);
	werte_ausgeben("Daten_1_0.txt", originalTransformed, 1.0);

	const auto& defaultList = werte_einlesen("Daten_Default.txt");
	const auto& _0_1_List = werte_einlesen("Daten_0_1.txt");
	const auto& _1_0_List = werte_einlesen("Daten_1_0.txt");

	const auto& defaultListRueckTrans = transform(defaultList, false);
	const auto& _0_1_ListRueckTrans = transform(_0_1_List, false);
	const auto& _1_0_ListRueckTrans = transform(_1_0_List, false);

	std::cout << "Maximale Abweichung bei Standard - Epsilon: "
		<< maxDeviation(defaultListRueckTrans, original) << std::endl;

	std::cout << "Maximale Abweichung bei epsilon=0.1: "
		<< maxDeviation(_0_1_ListRueckTrans, original) << std::endl;

	std::cout << "Maximale Abweichung bei epsilon=1.0: "
		<< maxDeviation(_1_0_ListRueckTrans, original) << std::endl;

	system("PAUSE");
}