#pragma once

#include "Spiel.h"
#include "sqlite3.h"
#include "cppSQLite3.h"

class CHistorie
{
private:
	static std::string dateiName;
	static CSpiel* pSpiel;
	static sqlite3* datenbank;

public:
	std::string getDateiName() const
	{
		return dateiName;
	}

	static void einfuegen(CSpiel* obj);
	static CSpiel& spielLaden();
	static void lokalSpeichern();
	static void schreibAufDatei(std::ofstream& schreibDatei);
	static std::vector<CSpieler*> leseVonDatei(std::ifstream& einleseDatei);
	static void datenbankSpeichern();
	static int datenbankOeffnen();
	static void datenbankTabelleErstellen(int rc);
	static void datenbankEinfuegen();

	static int callback(void* nichtbenutzt, int argc, char** argv, char** spaltenName);  // int argc - Anzahl der Zeilen // char** argv - Spaltenwert
};

