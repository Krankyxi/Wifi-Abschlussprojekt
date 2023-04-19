#include "Historie.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

// 

std::string CHistorie::dateiName = "KNIFFEL-Einzelspieler.txt";
CSpiel* CHistorie::pSpiel;

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					    lokale Speicherung (datei.txt)
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::lokalSpeichern()
{
	std::ofstream schreibDatei;

	schreibDatei.open(dateiName, std::ios::trunc); 

	if (schreibDatei)	// erfolgreich geöffnet
	{
		schreibAuf(schreibDatei);
	}
	schreibDatei.close();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					 Speicherung aus der Datei(.txt) laden
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::spielLaden()
{
	// spiel objekt return 

	std::ifstream einleseDatei;

	einleseDatei.open(dateiName, std::ios::in);

	if (einleseDatei)
	{
		leseVon(einleseDatei);		
	}
	einleseDatei.close();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					 einlesen der Daten aus der Datei(.txt)
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool CHistorie::leseVon(std::ifstream& einleseDatei)
{
	// spieler objekt return 

	int einzelOderMehrSpieler = 0, spielerAnzahl = 0;
	int punkte[20];
	int spieler1 = 0, spieler2 = 0, spieler3 = 0, spieler4 = 0;
	std::string datum, uhrzeit, name, einlesen;
	char trenner;

	einleseDatei >> einzelOderMehrSpieler;		// Einzel(1) oder Mehrspieler(2)
	einleseDatei.get(trenner);
	if (trenner != '|')
	{
		return false;
	}
	einleseDatei >> spielerAnzahl;				// Wieviele Spieler
	einleseDatei.get(trenner);
	if (trenner != '|')
	{
		return false;
	}
	std::getline(einleseDatei, einlesen, '|');
	datum = einlesen;							// Datum
	std::getline(einleseDatei, einlesen, '|');
	uhrzeit = einlesen;							// Uhrzeit
	std::getline(einleseDatei, einlesen, '|');
	name = einlesen;							// Name des Spielers
	for (int i = 0; i < 20; ++i)
	{
		einleseDatei >> punkte[i];				// Punkte des Spielers
		einleseDatei.get(trenner);
		if (trenner != '|')
		{
			return false;
		}
	}
	std::cout << einzelOderMehrSpieler << "|" << spielerAnzahl << "|" << datum << "|" << uhrzeit << "|" << name << "|";
	for (int i = 0; i < 20; ++i)
	{
		std::cout << punkte[i] << "|";
	}
	std::cout << std::endl;
	return true;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//			     Werte des Spiels in die Datei(.txt) exportieren
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::schreibAuf(std::ofstream& schreibDatei)
{
	int zaehler = 0;
	int einspieler = 1;
	int mehrspieler = 2;	

	const std::vector<CSpieler*> meineKopie = pSpiel->getSpieler();

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		if (meineKopie.size() == 1)
		{
			schreibDatei << einspieler << "|" << zaehler+1 << "|" << pSpiel->getDatum() << "|" << pSpiel->getZeit() << "|" << meineKopie.at(0)->getSpielerName() << "|";
		}
		else if (meineKopie.size() > 1)
		{
			schreibDatei << mehrspieler << "|" << zaehler+1 << "|" << pSpiel->getDatum() << "|" << pSpiel->getZeit() << "|" << meineKopie.at(zaehler)->getSpielerName() << "|";
		}
		
		const std::map<int, std::pair<std::string, int>> kombiKopie = pSpiel->getSpieler().at(zaehler)->getKombi();

		for (auto it = kombiKopie.begin(); it != kombiKopie.end(); ++it)
		{				
			schreibDatei << (*it).second.second << "|";
		}
		schreibDatei << std::endl;
	}
	schreibDatei << std::endl;	
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					 Vector initialisierung 
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CHistorie::einfuegen(CSpiel* obj)
{
	pSpiel = obj;							// Historie-Pointer intialisieren (Spieler-Objekt)
}
