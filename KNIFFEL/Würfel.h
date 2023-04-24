#pragma once

#include <iostream>

class CWuerfel
{
private:
	int gewuerfelt = 0;
	const int wuerfel = 6;

public:
	int wuerfeln();
	int getWuerfel() const
	{
		return wuerfel;
	}
	int getGeWuerfelt() const
	{
		return gewuerfelt;
	}

	friend std::ostream& operator<<(std::ostream& out, const CWuerfel& wurf);
};

