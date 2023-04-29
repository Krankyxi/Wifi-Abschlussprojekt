#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>

class CSpieler
{
private:
	std::string name;
	std::map<int, std::pair<std::string, int>> kombi;		// Kombinationspaare Bsp: (1,<"Einser", Wert 1)
															//						  (2,<"Zweier", Wert 2)

	int aktPunkteStand = 0;									// zum berechnen des aktuellen Punketstands
	int eintragCount = 0;									// zum z�hlen der Eintr�ge die get�tigt wurden
	const int maxSpielzuege = 3;							// maximale Spielz�ge die nicht �berschritten werden d�rfen
	const int eintragMax = 13;								// maximale Eintr�ge die nicht �berschritten werden d�rfen

public:
	CSpieler() = default;									// Default - Konstruktor
	CSpieler(std::string& name);							// Konstruktor mit Parameter(Name)

	void neuerSpieler(const std::string& spielerName)		// initialisierung Name des Spielers
	{
		this->name = spielerName;
	}										
	std::string getSpielerName() const
	{
		return this->name;
	}
	int getMaxSpielzuege() const
	{
		return maxSpielzuege;
	}
	int getMaxEintrag() const
	{
		return eintragMax;
	}
	int getCountEintrag() const
	{
		return eintragCount;
	}
	std::map<int, std::pair<std::string, int>> getKombi() const
	{
		return kombi;
	}
	
	void setPunkte(std::map<int, std::pair<std::string, int>>& kombination);						// Spieler Kombo-Punkte initialisieren aus der Datei		
	void tabelleSpielerGesamt();																	// Tabelle f�r mehrere Spieler (Bildschirm-Ausgabe)
	void kombinationSpeichern(std::vector<std::pair<std::string, int>> kombination);				// Kombinationen speichern
	void kombinationOhneEintragStreichen(std::vector<std::pair<std::string, int>> kombination);		// Kombinationen ohne Eintrag k�nnen mit 0 eingetragen werden (streichen)

	std::vector<std::pair<std::string, int>> pruefenEintragVorhanden(std::vector<std::pair<std::string, int>> kombination);		// pr�ft ob Eintr�ge vorhanden sind
	std::vector<std::pair<std::string, int>> kombinationenOhneEintrag();							// gibt den Vector mit den Kombinationen ohne Eintr�gen zur�ck

	friend std::ostream& operator<<(std::ostream& out, const CSpieler& spieler);					// Darstellung des Spielers am Bildschirm
};

