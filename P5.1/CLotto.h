#pragma once
#include <array>
#include <set>
#include "CZufall.h"

class CLotto
{
public:
	CLotto(int n)
	{
		m_ZufallszahlenGenerator.initialisiere(n < 0 ? time(NULL) : n);
	}

	inline void SetTippZettel(const std::array<int, 6>& tippZettel) { m_TippZettel = tippZettel; }
	inline const std::array<int, 6>& GetTippZettel() const { return m_TippZettel; }

	// Vergleiche Ziehung mit Tippzettel 
	int eineLottoZiehung()
	{
		int gleicheZahlen = 0;
		const std::set<int>& ziehung = Ziehung6aus49();
		for (const int zahl : ziehung)
			for (const int tippZettelZahl : m_TippZettel)
				if (zahl == tippZettelZahl)
					++gleicheZahlen;
		return gleicheZahlen;
	}

	// Vergleiche zweier Ziehungen
	int zweiLottoZiehung()
	{
		int gleicheZahlen = 0;
		const std::set<int>& ersteZiehung = Ziehung6aus49();
		const std::set<int>& zweiteZiehung = Ziehung6aus49();
		for (const int zahlErsteZiehung : ersteZiehung)
			for (const int zahlZweiteZiehung : zweiteZiehung)
				if (zahlErsteZiehung == zahlZweiteZiehung)
					++gleicheZahlen;
		return gleicheZahlen;
	}

private:
	std::set<int> Ziehung6aus49() const
	{
		std::set<int> values;
		for (int i = 0; i < 6; ++i)
		{
			bool bNumberIsUnique = true;			
			do
			{
				int number = m_ZufallszahlenGenerator.wert(1, 49);
				const auto& it = values.insert(number);
				bNumberIsUnique = it.second;
							
			} while (!bNumberIsUnique);			
		}
		return values;
	}

private:
	CZufall m_ZufallszahlenGenerator; 
	std::array<int, 6> m_TippZettel;
};