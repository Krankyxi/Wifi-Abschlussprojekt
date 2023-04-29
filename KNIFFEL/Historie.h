#pragma once

#include "Spiel.h"
#include "sqlite3.h"
#include "cppSQLite3.h"

#include <exception>

class CHistorie
{
private:
	static std::string dateiName;	// Datei Name der lokalen Datei
	static CSpiel* pSpiel;			// Zeiger auf das Spielobjekt (aktuelle)
	static sqlite3* datenbank;		// Datenbank Zeiger
	static int ladeAuswahl;			// 

public:
	std::string getDateiName() const
	{
		return dateiName;
	}

	static const int setLadeAuswahl(int spielerauswahl);						// setzt die Auswahl für Einzel oder Mehrspieler-Modus
	static void einfuegen(CSpiel* obj);											// Vector Zeiger Initialisierung
	static CSpiel& spielLaden();												// lokale Datei wird zum lesen geöffnet
	static void lokalSpeichern();												// lokale Speicherung
	static void schreibAufDatei(std::ofstream& schreibDatei);					// es wird auf die lokale Datei geschrieben
	static std::vector<CSpieler*> leseVonDatei(std::ifstream& einleseDatei);	// es wird von der lokalen Datei gelesen
	static void datenbankSpeichern();											// Es wird in der Datenbank gespeichert
	static int datenbankOeffnen();												// Datenbank wird geöffnet
	static void datenbankTabelleErstellen();									// Datenbank Tabelle wird erstellt
	static void datenbankEinfuegen();											// Es wird in die Datenbank eingetragen
	static void datenbankStatistikLaden();										// Datenbank Statistik wird geladen
	static void datenbankTabelleAusgeben();										// Datenbank Tabelle wird ausgegeben
	static void ausDatenbankloeschen(std::string userEingabe);					// Löscht einen bestimmten Datensatz aus der Tabelle 
	static void datenbankLoeschen();											// Löscht alle Datensätze in der Datenbank (Datenbank bleibt weiter bestehen)

	static int callback(void* nichtbenutzt, int argc, char** argv, char** spaltenName);  // int argc - Anzahl der Zeilen // char** argv - Spaltenwert
};

class CHistorieException : public std::exception
{
private: 
	std::string message;
public:
	CHistorieException(const std::string& msg) : message(msg)
	{}
	const char* what() const override
	{
		return message.c_str();
	}
};