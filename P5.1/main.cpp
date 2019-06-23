#include <iostream>
#include "CZufall.h"
#include "CLotto.h"

int main()
{
	CZufall random;
	// a)
	{
		std::cout << "1 a) ###################" << std::endl;
		random.initialisiere(10);
		const auto& result = random.test(3, 7, 10000);
		for (int i = 0; i < result.size(); ++i)
			std::cout << i + 3 << ": " << result.at(i) << std::endl;
	}
	// b)
	{
		std::cout << "1 b) ###################" << std::endl;
		for (int i = 0; i < 5; ++i)
		{
			random.initialisiere(10);
			const auto& result = random.test(3, 7, 10000);
			for (int i = 0; i < result.size(); ++i)
				std::cout << i + 3 << ": " << result.at(i) << std::endl;
			std::cout << "------------------" << std::endl;
		}
	}
	// c)
	{
		std::cout << "1 c) ###################" << std::endl;
		for (int i = 10; i < 15; ++i)
		{
			random.initialisiere(i);
			const auto& result = random.test(3, 7, 10000);
			for (int i = 0; i < result.size(); ++i)
				std::cout << i + 3 << ": " << result.at(i) << std::endl;
			std::cout << "------------------" << std::endl;
		}
	}
	// d)
	{
		std::cout << "1 d) ###################" << std::endl;
		for (int i = 0; i < 5; ++i)
		{
			int seed = time(NULL);
			std::cout << "Seed: " << seed << std::endl;
			random.initialisiere(seed);
			const auto& result = random.test(3, 7, 10000);
			for (int i = 0; i < result.size(); ++i)
				std::cout << i + 3 << ": " << result.at(i) << std::endl;
			std::cout << "------------------" << std::endl;
		}
	}
	// e)
	{
		std::cout << "1 e) ###################" << std::endl;		
		const auto& result = random.test_falsch(3, 7, 10000);
		for (int i = 0; i < result.size(); ++i)
			std::cout << i + 3 << ": " << result.at(i) << std::endl;		
	}


	// 3 a)
	CLotto lotto(-1);
	lotto.SetTippZettel({ 2, 6, 9, 12, 27, 42 });
	{
		auto eineLottoZiehungMitTippzettel = [&lotto](const int anzahlZiehung)
		{
			int anzahlDreiGleicheZahlen = 0;
			const int anzahlGleicherZahlen = 3;
			for (unsigned int i = 0; i < anzahlZiehung; ++i)
			{
				const int ziehungAnzahlGleicherZahlen = lotto.eineLottoZiehung();
				if (ziehungAnzahlGleicherZahlen == anzahlGleicherZahlen)
					++anzahlDreiGleicheZahlen;
			}
			std::cout << "Wahrscheinlichkeit genau " << anzahlGleicherZahlen << " uebereinstimmende Zahlen mit Tippzettel bei " << anzahlZiehung << " Ziehung: "
				<< ((double)anzahlDreiGleicheZahlen / (double)anzahlZiehung) * 100.0 << "%" << std::endl;
		};
		
		eineLottoZiehungMitTippzettel(100000);
		eineLottoZiehungMitTippzettel(1000000);
	}
	// 3 b)
	{
		auto zweiLottoZiehungMiteinanderVergleichen = [&lotto](const int anzahlZiehung)
		{
			int anzahlDreiGleicheZahlen = 0;		
			const int anzahlGleicherZahlen = 3;
			for (unsigned int i = 0; i < anzahlZiehung; ++i)
			{
				const int ziehungAnzahlGleicherZahlen = lotto.zweiLottoZiehung();
				if (ziehungAnzahlGleicherZahlen == anzahlGleicherZahlen)
					++anzahlDreiGleicheZahlen;
			}
			std::cout << "Wahrscheinlichkeit genau " << anzahlGleicherZahlen << " uebereinstimmende Zahlen bei 2 Lottoziehung bei insgesamt " << anzahlZiehung
				<< " Ziehung: " << ((double)anzahlDreiGleicheZahlen / (double)anzahlZiehung) * 100.0 << "%" << std::endl;
		};

		zweiLottoZiehungMiteinanderVergleichen(100000);
		zweiLottoZiehungMiteinanderVergleichen(1000000);
	}
	system("PAUSE");
}