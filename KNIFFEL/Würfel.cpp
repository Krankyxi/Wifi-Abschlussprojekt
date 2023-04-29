#include "Würfel.h"

#include <random>

static std::random_device rd;

// Würfeln per "Zufall"
int CWuerfel::wuerfeln()
{	
	this->gewuerfelt = rd() % wuerfel +1;

	if (this->gewuerfelt == 0)
		this->gewuerfelt = rd() % wuerfel + 1;

	return this->gewuerfelt;	
}

// Bildschirm-Ausgabe für den Würfel
std::ostream& operator<<(std::ostream& out, const CWuerfel& wurf)
{
	out << wurf.gewuerfelt;
	return out;
}

