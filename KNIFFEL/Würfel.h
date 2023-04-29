#pragma once

#include <iostream>

class CWuerfel
{
private:
	int gewuerfelt = 0;						// Variable zum w�rfeln der Zahlen 
	const int wuerfel = 6;					// maximale W�rfel Zahl die gew�rfelt werden darf

public:
	int wuerfeln();							// W�rfeln 
	int getWuerfel() const			// 
	{
		return wuerfel;
	}			
	int getGeWuerfelt() const
	{
		return gewuerfelt;
	}

	friend std::ostream& operator<<(std::ostream& out, const CWuerfel& wurf);		// f�r die Darstellung des W�rfels am Bildschirm
};


