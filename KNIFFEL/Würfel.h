#pragma once
#include <iostream>

class CWuerfel
{
private:
	int wuerfel[6]{ 1,2,3,4,5,6 };

	int maxAnzahlZahlen = 6;
	int gewuerfelt = 0;
public:
	int wuerfeln();
	int getWuerfel() const
	{
		return wuerfel[maxAnzahlZahlen];
	}
};

