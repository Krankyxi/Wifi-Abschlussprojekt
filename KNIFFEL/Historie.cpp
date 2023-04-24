#include "Historie.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <cstdlib>
#include <thread>
#include <chrono>

#define cleanScreen std::system("CLS");									// leert die Konsolenoberfläche 
#define sleep std::this_thread::sleep_for(std::chrono::seconds(2));		// stoppt den Konsolen-Output für 2 Sekunden 

std::string CHistorie::dateiName = "KNIFFEL-Spieler-Speicher.txt";
CSpiel* CHistorie::pSpiel;
sqlite3* CHistorie::datenbank;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					    lokale Speicherung (datei.txt)
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::lokalSpeichern()
{
	std::ofstream schreibDatei;

	schreibDatei.open(dateiName, std::ios::trunc); 

	if (schreibDatei)						// erfolgreich geöffnet
	{
		schreibAufDatei(schreibDatei);		// Funktion zum schreiben auf die Datei wird geoeffnet
	}
	else
	{
		std::cout << "Schreiben auf die Datei nicht moeglich!" << std::endl;
		sleep;
	}
	schreibDatei.close();					// File schließen
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					 Speicherung aus der Datei(.txt) laden
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

CSpiel& CHistorie::spielLaden()
{
	std::vector<CSpieler*> spieler;
	std::ifstream einleseDatei;
	CSpiel* spiel(new CSpiel(spieler));

	einleseDatei.open(dateiName, std::ios::in);

	if (einleseDatei)					// erfolgreich geöffnet
	{
		spieler = leseVonDatei(einleseDatei);		// Funktion zum schreiben auf die Datei wird geoeffnet
		einleseDatei.close();
		spiel = new CSpiel(spieler);				
	}
	else
	{
		std::cout << "Es exisitieren keine gespeicherten Daten!" << std::endl;
		sleep;
	}
	einleseDatei.close();				// FIle schließen
	return *spiel;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					 einlesen der Daten aus der Datei(.txt)
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

std::vector<CSpieler*> CHistorie::leseVonDatei(std::ifstream& einleseDatei)
{
	std::vector<CSpieler*> spieler;				// Vector mit Zeiger auf Spieler Objekte

	int einzelOderMehrSpieler = 0;
	int spielerNr = 0;
	int spielerCounter = 0;
	int spielerNummerZaehler = 1;
	int spielerAnzahl = 0;
	int zaehler = 0;
	int zaehlerPunkte = 0;
	int punkte[20]{};
	std::string datum, uhrzeit, name, einlesen;
	char trenner;

	einleseDatei >> einzelOderMehrSpieler;		// Einzel(1) oder Mehrspieler(2)
	einleseDatei.get(trenner);
	if (trenner != '|')
	{
		std::cerr << "Fehler aufgetreten: Spieler-Modus konnte nicht gelesen werden!";
	}

	while (einleseDatei)
	{
		einleseDatei >> spielerAnzahl;			// Wieviele Spieler
		einleseDatei.get(trenner);
		if (trenner != '|')
		{
			std::cerr << "Fehler aufgetreten: Spieler-Anzahl konnte nicht gelesen werden!";
		}
		einleseDatei >> spielerNr;				// Spieler Nummer
		einleseDatei.get(trenner);
		if (trenner != '|')
		{
			std::cerr << "Fehler aufgetreten: Spieler Nummer konnte nicht gelesen werden!";
		}
		std::getline(einleseDatei, einlesen, '|');
		datum = einlesen;							// Datum
		std::getline(einleseDatei, einlesen, '|');
		uhrzeit = einlesen;							// Uhrzeit

		/*einleseDatei >> spielerCounter;
		einleseDatei.get(trenner);
		if (trenner != '|')
		{
			std::cerr << "Fehler aufgetreten: Spieler Spielzug Zaehler konnte nicht gelesen werden!";
		}*/

		std::getline(einleseDatei, einlesen, '|');
		name = einlesen;							// Name des Spielers

		spieler.push_back(new CSpieler(name));
		std::map<int, std::pair<std::string, int>> kombi = spieler.at(zaehler)->getKombi();			// map zum einfuegen in das Spieler Objekt wird erstellt 

		for (int i = 0; i < 20; ++i)
		{
			einleseDatei >> punkte[i];				// Punkte des Spielers
			einleseDatei.get(trenner);
			if (trenner != '|')
			{
				std::cerr << "Fehler aufgetreten: Punkte konnten nicht gelesen werden!";
			}
		}
		einleseDatei >> trenner;
		einleseDatei.get(trenner);
		if (trenner != '|')
		{
			std::cerr << "Fehler aufgetreten: Trenn-Zeichen konnte nicht gelesen werden!";
		}

		auto iter = spieler.begin() + zaehler;

		if (spielerNummerZaehler == spielerNr)		// Zaehler == spielerNr
		{
			zaehlerPunkte = 0;
			for (auto& iterator : kombi)			// ranged based for schleife für kombo Punkte
			{
				if (zaehlerPunkte < 20)
				{
					iterator.second.second = punkte[zaehlerPunkte];		// Kombinationen einlesen
					++zaehlerPunkte;
				}
			}
			spieler.at(zaehler)->setPunkte(kombi);		// Kombo-Punkte in der SpielKlasse initialisieren (setpunkte)
		}
		++spielerNummerZaehler;
		++zaehler;
	}
	return spieler;		// vector mit zeigern zurück
}


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//			     Werte des Spiels in die Datei(.txt) exportieren
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::schreibAufDatei(std::ofstream& schreibDatei)
{
	int zaehler = 0;
	int einspieler = 1;
	int mehrspieler = 2;	

	const std::vector<CSpieler*> meineKopie = pSpiel->getSpieler();

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		if (meineKopie.size() == 1)
		{
			schreibDatei << einspieler << "|" << pSpiel->getSpieler().size() << "|" << zaehler + 1 << "|" << pSpiel->getDatum() << "|" << pSpiel->getZeit() << "|" << meineKopie.at(0)->getSpielerName() << "|";
		}
		else if (meineKopie.size() > 1)
		{
			schreibDatei << mehrspieler << "|" << pSpiel->getSpieler().size() << "|" << zaehler + 1 << "|" << pSpiel->getDatum() << "|" << pSpiel->getZeit() << "|" << meineKopie.at(zaehler)->getSpielerName() << "|";
		}
		
		const std::map<int, std::pair<std::string, int>> kombiKopie = pSpiel->getSpieler().at(zaehler)->getKombi();

		for (auto it = kombiKopie.begin(); it != kombiKopie.end(); ++it)
		{				
			schreibDatei << (*it).second.second << "|";
		}
		schreibDatei << std::endl;
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					 Vector Zeiger Initialisierung 
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::einfuegen(CSpiel* obj)
{
	pSpiel = obj;							// Historie-Pointer intialisieren (Spieler-Objekt)
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					 Datenbank Tabelle erstellen 
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::datenbankTabelleErstellen(int rc)
{
	const char* spiel;
	const char* spieler;
	// const char* spSp;

	spiel = "CREATE TABLE IF NOT EXISTS Spiel (" \
		"SpielID_PK INTEGER NOT NULL," \
		"SpielDatum TEXT NOT NULL," \
		"SpielUhrzeit TEXT NOT NULL," \
		"SpielerAnzahl INTEGER NOT NULL," \
		"PRIMARY KEY (SpielID_PK AUTOINCREMENT) )";

	spieler = "CREATE TABLE IF NOT EXISTS Spieler (" \
		"ID_PK INTEGER NOT NULL," \
		"SpielID INTEGER NOT NULL," \
		"SpielerNr INTEGER NOT NULL," \
		"SpielerName TEXT NOT NULL," \
		"SpielerPkt INTEGER NOT NULL," \
		"PRIMARY KEY (ID_PK AUTOINCREMENT)," \
		"FOREIGN KEY (SpielID) REFERENCES Spiel(SpielID_PK) )";

	/*spSp = "CREATE TABLE IF NOT EXISTS SpielSpieler (" \
		"SpSpSpielID_FK INTEGER NOT NULL," \
		"SpSpSpielerID_FK INTEGER NOT NULL," \
		"PRIMARY KEY (SpSpSpielID_FK, SpSpSpielerID_FK)," \
		"FOREIGN KEY (SpSpSpielID_FK) REFERENCES Spiel (SpielID_PK)," \
		"FOREIGN KEY (SpSpSpielerID_FK) REFERENCES Spieler (ID_PK) )";	*/

	char* fehlermeldung = nullptr;

	// rc = Result and Error Code / Ergebniscode zurückgeliefert 
	rc = sqlite3_exec(datenbank, spiel, callback, 0, &fehlermeldung);		// 1 Tabelle
	if (rc != SQLITE_OK)													// Check
	{
		std::cerr << "SQL-Error: (" << fehlermeldung << ")" << std::endl;
	}
	else
	{
		std::cout << "Tabelle wurde erfolgreich erstellt." << std::endl;
	}

	rc = sqlite3_exec(datenbank, spieler, callback, 0, &fehlermeldung);		// 2 Tabelle
	if (rc != SQLITE_OK)													// Check

	{
		std::cerr << "SQL-Error: (" << fehlermeldung << ")" << std::endl;
	}
	else
	{
		std::cout << "Tabelle wurde erfolgreich erstellt." << std::endl;
	}

	//rc = sqlite3_exec(datenbank, spSp, callback, 0, &fehlermeldung);		// 3 tabelle FOREIGN KEYS
	//if (rc != SQLITE_OK)													// check
	//{
	//	std::cerr << "sql-error: " << fehlermeldung << std::endl;
	//}
	//else
	//{
	//	std::cout << "tabelle wurde erfolgreich erstellt." << std::endl;
	//}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					       Datenbank speichern
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::datenbankSpeichern()
{
	int rc = datenbankOeffnen();	
	datenbankTabelleErstellen(rc);	
	datenbankEinfuegen();
	sqlite3_close(datenbank);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Datenbank Einträge
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::datenbankEinfuegen()
{
	std::string spielEintrag, spielerEintrag;
	char* fehlermeldung = nullptr;
	int zaehler = 0, spielerNummer = 1, rc = 0, rc2 = 0;
	std::vector<CSpieler*> spieler = pSpiel->getSpieler();
	std::string datum = pSpiel->getDatum();
	std::string zeit = pSpiel->getZeit();	
	std::string spAnzahl = std::to_string(pSpiel->getAktSpieler());

	spielEintrag = "INSERT INTO SPIEL (SpielDatum, SpielUhrzeit, SpielerAnzahl) " \
				"VALUES ('" + datum + "','" + zeit + "','" + spAnzahl + "');";
	rc = sqlite3_exec(datenbank, spielEintrag.c_str(), callback, 0, &fehlermeldung);

	int64_t spielID = sqlite3_last_insert_rowid(datenbank);		// Zeilen ID erstellen für INSERT (Warnung bei int zuweisung - evtl.Datenverlust)

	for (auto iter = spieler.begin(); iter != spieler.end(); ++iter)
	{
		std::map<int, std::pair<std::string, int>> punkte = (*iter)->getKombi();
		std::string pkt = "0";
		std::string spielerNr = std::to_string(spielerNummer);
		std::string name = spieler.at(zaehler)->getSpielerName();				
		pkt = std::to_string(punkte.find(20)->second.second);	
		
		spielerEintrag = "INSERT INTO SPIELER (SpielID, SpielerNr, SpielerName, SpielerPkt) " \
			"VALUES ('" + std::to_string(spielID) + "','" + spielerNr + "','" + name + "','" + pkt + "');";
		rc2 = sqlite3_exec(datenbank, spielerEintrag.c_str(), callback, 0, &fehlermeldung);

		++zaehler;
		++spielerNummer;
	}

	if (rc != SQLITE_OK) 
	{
		std::cerr << "SQL-Error: " << fehlermeldung << std::endl;
		sqlite3_free(fehlermeldung);
	}
	else 
	{
		std::cout << "Datensaetze erfolgreich erstellt!" << std::endl;
	}

	if (rc2 != SQLITE_OK)
	{
		std::cerr << "SQL-Error: " << fehlermeldung << std::endl;
		sqlite3_free(fehlermeldung);
	}
	else
	{
		std::cout << "Datensaetze erfolgreich erstellt!" << std::endl;
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					      Datenkbank Öffnen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

int CHistorie::datenbankOeffnen()
{	
	int rc = sqlite3_open("Kniffel.db",&datenbank);		// Datenbank öffnen

	if (rc) 
	{
		std::cerr << "Kann nicht geoeffnet werden! Fehler: " << sqlite3_errmsg(datenbank) << std::endl;
		return(0);
	}
	else 
	{
		std::cout << "Oeffnen der Datenbank war erfolgreich!" << std::endl;
		return rc;
	}
}

int CHistorie::callback(void* nichtbenutzt, int argc, char** argv, char** spaltenName) 
{	
	for (int i = 0; i < argc; i++) 
	{
		std::cout << spaltenName[i] << " = " << argv[i] ? argv[i] : "NULL";
	}
	std::cout << std::endl;
	return 0;
}


// Person und Interesse Tabelle

//CREATE TABLE "PerInt" (
//	"PerIntPersonFK"	INTEGER NOT NULL,
//	"PerIntInteresseFK"	INTEGER NOT NULL,
//	PRIMARY KEY("PerIntInteresseFK", "PerIntPersonFK"),
//	FOREIGN KEY("PerIntPersonFK") REFERENCES "Person"("PerPK"),
//	FOREIGN KEY("PerIntInteresseFK") REFERENCES "Interesse"("IntPK")
//	);

// Spiel und Spieler Tabelle

//CREATE TABLE "SpSp" (
//	"SpSpSpieler_FK"	INT NOT NULL,
//	"SpSpSpiel_FK"	INT NOT NULL,
//	FOREIGN KEY("SpSpSpieler_FK") REFERENCES "Spieler"("SpielerID_PK"),
//	FOREIGN KEY("SpSpSpiel_FK") REFERENCES "Spiel"("ID_PK"),
//	PRIMARY KEY("SpSpSpieler_FK", "SpSpSpiel_FK")
//	);