#pragma once

#include "Würfel.h"
#include "Spieler.h"
#include <vector>
#include <time.h>

class CSpiel
{
private:
	std::vector<CWuerfel*> wuerfel;
	std::vector<CSpieler*> spieler;		// Zugriff dann auf std::map
	
	size_t maxAnzahlWuerfel = 5;
	int maxAnzahlSpieler = 4;
	int aktZuege = 1;

	std::string aktuellesDatum;
	std::string aktuelleUhrzeit;

public:
	CSpiel()
	{
		aktuellesDatum = "NODATE";
		aktuelleUhrzeit = "NOTIME";
		for (int i = 0; i < getMaxAnzahlWuerfel(); ++i)
		{
			wuerfel.push_back(new CWuerfel);
		}
	}
	void neuerSpieler(std::string& name);
	void spielerLoeschen(int& index);
	bool alleSpielerLoeschen();
	void aktDatumUndUhrzeit();
	void aktDatumUndUhrzeitAusgeben() const;
	void spielerWuerfeln();							
	void spielerWuerfeln(size_t& position);			
	void wuerfelAusgeben() const;
	bool aktuellerSpielzug(size_t& index);
	std::vector<std::pair<std::string, int>> kombinationen();
	void wuerfelSort();
	void resetSpielzug();
	std::string getBewertungText(int& zahl);

	std::vector<CSpieler*> getSpieler() const
	{
		return spieler;
	}
	std::vector<CWuerfel*> getWuerfel() const
	{
		return wuerfel;
	}

	size_t getMaxAnzahlWuerfel() const
	{
		return maxAnzahlWuerfel;
	}
	int getMaxAnzahlSpieler() const
	{
		return maxAnzahlSpieler;
	}
	
};

