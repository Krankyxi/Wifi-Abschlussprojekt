#pragma once

#include <iostream>

class CWuerfel
{
private:
	int gewuerfelt = 0;						// Variable zum würfeln der Zahlen 
	const int wuerfel = 6;					// maximale Würfel Zahl die gewürfelt werden darf

public:
	int wuerfeln();							// Würfeln 
	int getWuerfel() const			// 
	{
		return wuerfel;
	}			
	int getGeWuerfelt() const
	{
		return gewuerfelt;
	}

	friend std::ostream& operator<<(std::ostream& out, const CWuerfel& wurf);		// für die Darstellung des Würfels am Bildschirm
};


