#include "Würfel.h"
#include <random>

static std::random_device rd;

int CWuerfel::wuerfeln()
{	
	this->gewuerfelt = rd() % maxAnzahlZahlen +1;

	if (this->gewuerfelt == 0)
		this->gewuerfelt = rd() % maxAnzahlZahlen + 1;

	return this->gewuerfelt;	
}

