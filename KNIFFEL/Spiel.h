#pragma once

#include "Würfel.h"
#include "Spieler.h"
#include <vector>

class CSpiel
{
private:
	std::vector<CWuerfel*> wuerfel;
	std::vector<CSpieler*> spieler;		// ********** Frage: wird der vector zerstört im Destruktor ?,
										// denn ich lösche nur die Elemente aus dem Vector und gebe den Speicherplatz nicht frei 
										// unter der Funktion alleSpielerLoeschen(); **************
	
	// CSpieler* spieler1, * spieler2, * spieler3, * spieler4;		// Frage 
	
	int maxAnzahlWuerfel = 5;
	int maxAnzahlSpieler = 4;
	int aktZuege = 0;
public:
	void neuerSpieler(std::string& name);
	void spielerLoeschen(int& index);
	bool alleSpielerLoeschen();
	void spielStarten();

	/*
	CSpieler* getSpieler1() const
	{
		return spieler1;
	}
	CSpieler* getSpieler2() const
	{
		return spieler2;
	}
	CSpieler* getSpieler3() const
	{
		return spieler3;
	}
	CSpieler* getSpieler4() const
	{
		return spieler4;
	}
	*/

	std::vector<CSpieler*> getSpieler() const
	{
		return spieler;
	}
	int getMaxAnzahlSpieler() const
	{
		return maxAnzahlSpieler;
	}
	
};

