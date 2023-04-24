#pragma once

#include "Würfel.h"
#include "Spieler.h"
#include <vector>
#include <time.h>

class CSpiel
{
private:
	std::vector<CWuerfel*> wuerfel;
	std::vector<CSpieler*> spieler;	
	
	size_t maxAnzahlWuerfel = 5;
	const int maxAnzahlSpieler = 4;
	int aktZuege = 1;
	int aktSpieler = 0;

	std::string aktuellesDatum;
	std::string aktuelleUhrzeit;

public:
	CSpiel();		
	~CSpiel();
	CSpiel(std::vector<CSpieler*>& spielerAusDatei);
	CSpiel(const CSpiel& spiel);
	CSpiel operator=(const CSpiel& spiel);
	void neuerSpieler(std::string& name);
	void spielerLoeschen(const int& index);
	bool alleSpielerLoeschen();
	void aktDatumUndUhrzeit();
	void aktDatumUndUhrzeitAusgeben() const;
	void spielerWuerfeln();							
	void spielerWuerfeln(size_t& position);			
	void wuerfelAusgeben() const;
	bool aktuellerSpielzug(size_t& index);
	void wuerfelSort();
	void resetSpielzug();
	int gewinnerErmitteln();
	void lokalSpeichern();
	void datenbankSpeichern();
	void resetAnzSpieler();
	bool vergleicheCounter();
	CSpiel* spielLaden();
	std::vector<std::pair<std::string, int>> kombinationen();
	std::string getBewertungText(int zahl);

	const std::vector<CSpieler*>& getSpieler() const	// 1. nur zum lesen 
	{
		return spieler;
	}
	std::vector<CSpieler*>& getSpieler()				// 2. zum lesen und schreiben(verändern)
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

	std::string getDatum() const
	{
		return aktuellesDatum;
	}
	std::string getZeit() const
	{
		return aktuelleUhrzeit;
	}
	CSpiel getSpiel() const
	{
		return *this;
	}
	int getAktSpieler() const
	{
		return aktSpieler;
	}
};