#include "Historie.h"
#include <fstream>

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iomanip>

#define cleanScreen std::system("CLS");									// leert die Konsolenoberfläche 
#define sleep std::this_thread::sleep_for(std::chrono::seconds(2));		// stoppt den Konsolen-Output für 2 Sekunden 

std::string CHistorie::dateiName = "KNIFFEL-Spieler-Speicher.txt";		// lokaler Pfad ("NICHT ABSOLUT")
CSpiel* CHistorie::pSpiel;												// static Zeiger auf Spiel Objekt
sqlite3* CHistorie::datenbank;											// static Zeiger auf Datenbank Variable
int CHistorie::ladeAuswahl = 0;											// static Variable zum Auswählen des Spiel-Modus (intern)

// lokale Speicherung (datei.txt)
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

// Speicherung aus der Datei(.txt) laden
CSpiel& CHistorie::spielLaden()
{
	std::vector<CSpieler*> spieler;								// neuer Vector wird erstellt
	std::ifstream einleseDatei;
	CSpiel* spiel = nullptr;		

	try
	{
		einleseDatei.open(dateiName, std::ios::in);
		if (einleseDatei)									// erfolgreich geöffnet
		{
			spieler = leseVonDatei(einleseDatei);			// Funktion zum schreiben auf die Datei wird geoeffnet			
			einleseDatei.close();							// Datei wird geschlossen

			if (spieler.empty())							// Im Falle das der Vector leer ist
			{
				throw CHistorieException("Fehler ist aufgetreten: Die Spielerliste ist leer!");			// Fehlermeldung		
			}
			else
			{
				spiel = new CSpiel(spieler);				// *spiel wird mit einem neuen Spiel initialisiert 
			}
		}
		else
		{
			einleseDatei.close();
			std::cout << "Es exisitieren keine gespeicherten Daten!" << std::endl;
			sleep;
		}
	}
	catch (const CHistorieException& e)
	{
		std::cerr << e.what() << std::endl;
		spiel = new CSpiel();
	}
	return *spiel;									// Zeiger auf Spiel wird zurück geliefert
}

// einlesen der Daten aus der Datei(.txt)
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
	
	try
	{
		einleseDatei >> einzelOderMehrSpieler;		// Einzel(1) oder Mehrspieler(2)
		einleseDatei.get(trenner);
		if (trenner != '|')
		{
			throw CHistorieException("Fehler aufgetreten : Spieler - Modus konnte nicht gelesen werden!");
		}
	}
	catch (const CHistorieException& e)
	{
		std::cerr << e.what() << std::endl;
		return {};									// leerer Vector wird zurückgegeben
	}

	if (ladeAuswahl == 1 && einzelOderMehrSpieler == 2)
	{
		std::cerr << "Es exisitieren keine Einzelspieler Daten im Speicher!" << std::endl;
	}
	if (ladeAuswahl == 2 && einzelOderMehrSpieler == 1)
	{
		std::cerr << "Es exisitieren keine Mehrspieler Daten im Speicher!" << std::endl;
	}	

	while (einleseDatei)
	{
		try
		{
			einleseDatei >> spielerAnzahl;			// Wieviele Spieler
			einleseDatei.get(trenner);
			if (trenner != '|')
			{
				throw CHistorieException("Fehler aufgetreten: Spieler-Anzahl konnte nicht gelesen werden!");
			}
		}
		catch (const CHistorieException& e)
		{
			std::cerr << e.what() << std::endl;
			return {};								// leerer Vector wird zurückgegeben
		}

		try
		{
			einleseDatei >> spielerNr;				// Spieler Nummer
			einleseDatei.get(trenner);
			if (trenner != '|')
			{
				throw CHistorieException("Fehler aufgetreten: Spieler Nummer konnte nicht gelesen werden!");
			}
		}
		catch (const CHistorieException& e)
		{
			std::cerr << e.what() << std::endl;
			return {};								// leerer Vector wird zurückgegeben
		}

		try
		{
			std::getline(einleseDatei, einlesen, '|');
			datum = einlesen;							// Datum
			std::getline(einleseDatei, einlesen, '|');
			uhrzeit = einlesen;							// Uhrzeit
		}
		catch (const CHistorieException& e)
		{
			std::cerr << "Fehler beim Lesen von Datum und Uhrzeit: " << e.what() << std::endl;
			return {};								// leerer Vector wird zurückgegeben
		}

		try
		{
			std::getline(einleseDatei, einlesen, '|');
			name = einlesen;							// Name des Spielers 
		}
		catch (const CHistorieException& e)
		{
			std::cerr << "Fehler aufgetreten: Spieler-Name konnte nicht gelesen werden: " << e.what() << std::endl;
			return {};								// leerer Vector wird zurückgegeben
		}

		spieler.push_back(new CSpieler(name));
		std::map<int, std::pair<std::string, int>> kombi = spieler.at(zaehler)->getKombi();			// map zum einfuegen in das Spieler Objekt wird erstellt 

		try
		{
			for (int i = 0; i < 20; ++i)
			{
				einleseDatei >> punkte[i];				// Punkte des Spielers
				einleseDatei.get(trenner);
				if (trenner != '|')
				{
					throw CHistorieException("Fehler aufgetreten: Punkte konnten nicht gelesen werden!");
				}
			}
		}
		catch (const CHistorieException& e)
		{
			std::cout << e.what() << std::endl;
			return {};								// leerer Vector wird zurückgegeben
		}

		try
		{
			einleseDatei >> trenner;
			einleseDatei.get(trenner);
			if (trenner != '|')
			{
				throw CHistorieException("Fehler aufgetreten: Trenn-Zeichen konnte nicht gelesen werden!");
			}
		}
		catch (const CHistorieException& e)
		{
			std::cout << e.what() << std::endl;
			return {};								// leerer Vector wird zurückgegeben
		}

		try
		{
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
		catch (const CHistorieException& e)
		{
			std::cerr << "Fehler aufgetreten : Spieler - Punkte konnte nicht gelesen werden : " << e.what() << std::endl;
			return {};								// leerer Vector wird zurückgegeben
		}
	}
	return spieler;	
}

// Werte des Spiels in die Datei(.txt) exportieren
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

// Vector Zeiger Initialisierung 
void CHistorie::einfuegen(CSpiel* obj)
{
	pSpiel = obj;							// Historie-Pointer intialisieren (Spieler-Objekt)
}

// Spiel Laden Auswahl 
const int CHistorie::setLadeAuswahl(int spielerauswahl)
{
	// beim Einzelspieler Modus darf kein Mehrspieler geladen werden 
	if (spielerauswahl == 1)
	{
		ladeAuswahl = spielerauswahl;		// static variable für die Kontrolle in welchen Spielmodus sich der Spieler befindet
		return ladeAuswahl;
	}
	// beim Mehrspieler Modus darf kein Einzelspieler geladen werden
	if (spielerauswahl == 2)
	{
		ladeAuswahl = spielerauswahl;
		return ladeAuswahl;
	}
	return 0;
}

// Datenbank Abfrage und Ausgabe
void CHistorie::datenbankTabelleAusgeben()
{
	sqlite3_stmt* statement;		// Zeiger auf Statement Objekt (Vorbereitung)
	const char* abfrage = "SELECT SpielID_PK, SpielDatum, SpielUhrzeit, SpielerAnzahl, SpielerNr, SpielerName, SpielerPkt "		
						  "FROM Spiel JOIN Spieler ON Spiel.SpielID_PK = Spieler.SpielID";

	int rc = sqlite3_prepare_v2(datenbank, abfrage, -1, &statement,  0);				// Statement Übergabe 

	if (rc != SQLITE_OK)	// Statement Check 
	{
		std::cerr << "SQL-Error: (" << sqlite3_errmsg(datenbank) << ")" << std::endl;
	}
	else
	{
		std::cout << std::left << std::setw(15) << "Datum" << "\t"						// Tabellen Format
			<< std::left << std::setw(15) << "Uhrzeit" << "\t"
			<< std::left << std::setw(10) << "SpielNr" << "\t"
			<< std::left << std::setw(15) << "Anzahl" << "\t"
			<< std::left << std::setw(10) << "Spieler" << "\t"
			<< std::left << std::setw(15) << "Name" << "\t"
			<< std::left << std::setw(10) << "Punkte" << std::endl;

		std::cout << std::setfill('-') << std::setw(102) << "-" << std::endl;			// Tabellen Format
		std::cout << std::setfill(' ');

		while (sqlite3_step(statement) == SQLITE_ROW)		// ist SQLITE_ROW OK dann enthält das Statement Zeilen 
		{
			int spielID = sqlite3_column_int(statement, 0);
			const char* spielDatum = (const char*)sqlite3_column_text(statement, 1);	// Wert aus der ersten Spalte in der aktuellen Zeile wird zurückgegeben
			const char* spielUhrzeit = (const char*)sqlite3_column_text(statement, 2);	// Wert aus der zweiten Spalte in der aktuellen Zeile wird zurückgegeben
			int spielerAnzahl = sqlite3_column_int(statement, 3);						// ......
			int spielerNr = sqlite3_column_int(statement, 4);
			const char* spielerName = (const char*)sqlite3_column_text(statement, 5);
			int spielerPkt = sqlite3_column_int(statement, 6);

			std::cout << std::left << std::setw(15) << spielDatum << "\t"				// Ausgabe der Werte Variablen aus der Tabelle
				<< std::left << std::setw(15) << spielUhrzeit << "\t"					// .....
				<< std::left << std::setw(10) << spielID << "\t"
				<< std::left << std::setw(15) << spielerAnzahl << "\t"
				<< std::left << std::setw(10) << spielerNr << "\t"
				<< std::left << std::setw(15) << spielerName << "\t"
				<< std::left << std::setw(10) << spielerPkt << std::endl;
		}
	}
	sqlite3_finalize(statement);		// Speicher von statement freigeben
	std::cout << std::endl;
}

// Datenbank Statistik Laden
void CHistorie::datenbankStatistikLaden()
{
	datenbankOeffnen();
	datenbankTabelleAusgeben();
}

// Datenbank Tabelle erstellen 
void CHistorie::datenbankTabelleErstellen()
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
	int rc = sqlite3_exec(datenbank, spiel, callback, 0, &fehlermeldung);	// 1 Tabelle
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

// Datenbank speichern
void CHistorie::datenbankSpeichern()
{
	int rc = datenbankOeffnen();	
	datenbankTabelleErstellen();	
	datenbankEinfuegen();
	sqlite3_close(datenbank);
}

// Datenbank Einträge
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

	if (rc != SQLITE_OK)	// Check Ergebnis
	{
		std::cerr << "SQL-Error: " << fehlermeldung << std::endl;
		sqlite3_free(fehlermeldung);
	}
	else 
	{
		std::cout << "Datensaetze erfolgreich erstellt!" << std::endl;
	}

	if (rc2 != SQLITE_OK)	// Check Ergebnis
	{
		std::cerr << "SQL-Error: " << fehlermeldung << std::endl;
		sqlite3_free(fehlermeldung);
	}
	else
	{
		std::cout << "Datensaetze erfolgreich erstellt!" << std::endl;
	}
}

// Datenkbank Öffnen
int CHistorie::datenbankOeffnen()
{	
	int rc = sqlite3_open("Kniffel.db",&datenbank);		// Datenbank öffnen

	if (rc) 
	{
		std::cerr << "Kann nicht geoeffnet werden! Fehler: " << sqlite3_errmsg(datenbank) << std::endl << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Oeffnen der Datenbank war erfolgreich!" << std::endl << std::endl;
		return rc;
	}
}

// Datenbank löschen
void CHistorie::datenbankLoeschen()
{
	datenbankOeffnen();

	const char* spielLoeschen = "DELETE FROM Spiel;";			// alle Datensätze aus der Tabelle 'Spiel'löschen
	const char* spielerLoeschen = "DELETE FROM Spieler;";		// alle Datensätze aus der Tabelle 'Spieler' löschen

	char* fehlermeldung = nullptr;

	int rc = sqlite3_exec(datenbank, spielLoeschen, callback, 0, &fehlermeldung);

	if (rc != SQLITE_OK)	// check
	{
		std::cerr << "SQL-Error: (" << fehlermeldung << ")" << std::endl;
	}
	else
	{
		std::cout << "Alle Eintraege wurden erfolgreich geloescht!" << std::endl;		
	}

	rc = sqlite3_exec(datenbank, spielerLoeschen, callback, 0, &fehlermeldung);

	if (rc != SQLITE_OK)	// check
	{
		std::cerr << "SQL-Error: (" << fehlermeldung << ")" << std::endl;
	}
	else
	{
		std::cout << "Alle Eintraege wurden erfolgreich geloescht!" << std::endl;
	}
	sqlite3_close(datenbank);
}

// bestimmte Datensätze löschen aus der Datenbank
void CHistorie::ausDatenbankloeschen(std::string userEingabe)
{
	int ergebnis = datenbankOeffnen();													// Datenbank öffnen

	std::string spielID = "DELETE FROM Spieler WHERE SpielID = " + userEingabe;			// zugehörige Spieler zur SpielID (Statement)

	char* fehlermeldung = nullptr;

	int rc = sqlite3_exec(datenbank, spielID.c_str(), callback, 0, &fehlermeldung);		// zugehörige Spieler zur SpielID werden gelöscht

	if (rc != SQLITE_OK)	// check 
	{
		std::cerr << "SQL-Error: " << fehlermeldung << std::endl;
	}
	else
	{
		std::cout << "Spieler erfolgreich geloescht!" << std::endl;
	}

	std::string SpielIDSpieler = "DELETE FROM Spiel WHERE SpielID_PK = " + userEingabe;	// Spiel (Statement)

	rc = sqlite3_exec(datenbank, SpielIDSpieler.c_str(), callback, 0, &fehlermeldung);	// Spiel wird gelöscht

	if (rc != SQLITE_OK)	// check
	{
		std::cerr << "SQL-Error: " << fehlermeldung << std::endl;
	}
	else
	{
		std::cout << "Spiel erfolgreich geloescht!" << std::endl;
	}

	sqlite3_close(datenbank);															// Datenbank schließen
}

// Callback Funktion (Datenbankabfrage SQLite / Spalten und Werte)
int CHistorie::callback(void* nichtbenutzt, int argc, char** argv, char** spaltenName) 
{	
	for (int i = 0; i < argc; i++) 
	{
		std::cout << spaltenName[i] << " = " << argv[i] ? argv[i] : "NULL";
	}
	std::cout << std::endl;
	return 0;
}

