#pragma once

#include "Würfel.h"
#include "Spieler.h"

#include <vector>
#include <time.h>

class CSpiel
{
private:
	std::vector<CWuerfel*> wuerfel;			// Vector mit Zeiger auf Würfel Objekte
	std::vector<CSpieler*> spieler;			// Vector mit Zeiger auf Spieler Objekte
	
	size_t maxAnzahlWuerfel = 5;			// maximale Anzahl der Würfel die im Spiel enthalten sein dürfen
	const int maxAnzahlSpieler = 4;			// maximale Anzahl an Spielern die im Spiel enthalten sein dürfen
	int aktZuege = 1;						// aktueller Zug Zähler
	int aktSpieler = 0;						// aktuelle Spieler Zähler

	std::string aktuellesDatum;				// aktuelles Datum zum speichern beim Spielstart
	std::string aktuelleUhrzeit;			// aktuelle Uhrzeit zum speichern beim Spielstart

public:
	CSpiel();											// Default Konstruktor
	~CSpiel();											// Destruktor
	CSpiel(std::vector<CSpieler*>& spielerAusDatei);	// Konstruktor mit Vector Parameter
	CSpiel(const CSpiel& spiel);						// Copy-Konstruktor mit Spiel Parameter
	CSpiel operator=(const CSpiel& spiel);				// Zuweisungsoperator= (Kopie)
	void neuerSpieler(std::string& name);				// Neuer Spieler wird angelegt
	void spielerLoeschen(const int index);				// Ein Spieler wird über die Auswahl gelöscht
	bool alleSpielerLoeschen();							// Alle Spieler werden gelöscht
	void aktDatumUndUhrzeit();							// aktuelles und lokales Datum inkl. Uhrzeit wird gespeichert	
	void spielerWuerfeln();								// Spieler würfelt 
	void spielerWuerfeln(size_t& position);				// Spieler würfelt nur eine bestimmte Position
	void wuerfelAusgeben() const;						// Würfel wird am Bildschirm ausgegeben
	bool aktuellerSpielzug(size_t& index);				// aktueller Spielzug des Spielers
	void wuerfelSort();									// Würfel Sortierung
	void resetSpielzug();								// Spielzug wird zurückgesetzt
	int gewinnerErmitteln();							// Gewinner wird hier ermittelt (Mehrspieler)
	void lokalSpeichern();								// Lokale Speicherung
	void datenbankSpeichern();							// Datenbank Speicherung
	void datenbankStatistikLaden();						// Datenbank Statistik wird geladen
	void resetAnzSpieler();								// Anzahl der Spieler wird zurückgesetzt
	bool vergleicheCounter();							// vergleicht die aktuellen Spielzüge (Mehrspieler)
	CSpiel* spielLaden();								// Spiel wird geladen
	

	std::vector<std::pair<std::string, int>> kombinationen();	// mögliche Kombinationen werden hier ausgewertet
	std::string getBewertungText(int zahl);						// Kombinations Text Zuordnung

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
	int getAktSpieler() const
	{
		return aktSpieler;
	}
	CSpiel getSpiel() const
	{
		return *this;
	}
};
