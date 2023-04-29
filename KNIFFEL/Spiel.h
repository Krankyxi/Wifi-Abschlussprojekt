#pragma once

#include "W�rfel.h"
#include "Spieler.h"

#include <vector>
#include <time.h>

class CSpiel
{
private:
	std::vector<CWuerfel*> wuerfel;			// Vector mit Zeiger auf W�rfel Objekte
	std::vector<CSpieler*> spieler;			// Vector mit Zeiger auf Spieler Objekte
	
	size_t maxAnzahlWuerfel = 5;			// maximale Anzahl der W�rfel die im Spiel enthalten sein d�rfen
	const int maxAnzahlSpieler = 4;			// maximale Anzahl an Spielern die im Spiel enthalten sein d�rfen
	int aktZuege = 1;						// aktueller Zug Z�hler
	int aktSpieler = 0;						// aktuelle Spieler Z�hler

	std::string aktuellesDatum;				// aktuelles Datum zum speichern beim Spielstart
	std::string aktuelleUhrzeit;			// aktuelle Uhrzeit zum speichern beim Spielstart

public:
	CSpiel();											// Default Konstruktor
	~CSpiel();											// Destruktor
	CSpiel(std::vector<CSpieler*>& spielerAusDatei);	// Konstruktor mit Vector Parameter
	CSpiel(const CSpiel& spiel);						// Copy-Konstruktor mit Spiel Parameter
	CSpiel operator=(const CSpiel& spiel);				// Zuweisungsoperator= (Kopie)
	void neuerSpieler(std::string& name);				// Neuer Spieler wird angelegt
	void spielerLoeschen(const int index);				// Ein Spieler wird �ber die Auswahl gel�scht
	bool alleSpielerLoeschen();							// Alle Spieler werden gel�scht
	void aktDatumUndUhrzeit();							// aktuelles und lokales Datum inkl. Uhrzeit wird gespeichert	
	void spielerWuerfeln();								// Spieler w�rfelt 
	void spielerWuerfeln(size_t& position);				// Spieler w�rfelt nur eine bestimmte Position
	void wuerfelAusgeben() const;						// W�rfel wird am Bildschirm ausgegeben
	bool aktuellerSpielzug(size_t& index);				// aktueller Spielzug des Spielers
	void wuerfelSort();									// W�rfel Sortierung
	void resetSpielzug();								// Spielzug wird zur�ckgesetzt
	int gewinnerErmitteln();							// Gewinner wird hier ermittelt (Mehrspieler)
	void lokalSpeichern();								// Lokale Speicherung
	void datenbankSpeichern();							// Datenbank Speicherung
	void datenbankStatistikLaden();						// Datenbank Statistik wird geladen
	void resetAnzSpieler();								// Anzahl der Spieler wird zur�ckgesetzt
	bool vergleicheCounter();							// vergleicht die aktuellen Spielz�ge (Mehrspieler)
	CSpiel* spielLaden();								// Spiel wird geladen
	

	std::vector<std::pair<std::string, int>> kombinationen();	// m�gliche Kombinationen werden hier ausgewertet
	std::string getBewertungText(int zahl);						// Kombinations Text Zuordnung

	const std::vector<CSpieler*>& getSpieler() const	// 1. nur zum lesen 
	{
		return spieler;
	}
	std::vector<CSpieler*>& getSpieler()				// 2. zum lesen und schreiben(ver�ndern)
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
