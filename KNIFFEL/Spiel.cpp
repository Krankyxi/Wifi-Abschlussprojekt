#include "Spiel.h"
#include "Historie.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						    Default - Konstruktor
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

CSpiel::CSpiel()
{
	aktuellesDatum = "NODATE";
	aktuelleUhrzeit = "NOTIME";
	for (int i = 0; i < getMaxAnzahlWuerfel(); ++i)
	{
		wuerfel.push_back(new CWuerfel);
	}	
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						    neuen Spieler anlegen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpiel::neuerSpieler(std::string& name)
{	
	spieler.push_back(new CSpieler(name));
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   bestimmten Spieler löschen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpiel::spielerLoeschen(int& index)
{
	auto iterator = spieler.begin()+index -1;
	spieler.erase(iterator);
}

void CSpiel::lokalSpeichern()
{
	CHistorie::einfuegen(this);	
	CHistorie::lokalSpeichern();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   gesamte Spieler löschen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool CSpiel::alleSpielerLoeschen()
{
	spieler.clear();

	if (spieler.empty())
		return true;
	else
		return false;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//			   aktuelle Datum und Uhrzeit umwandeln und speichern
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpiel::aktDatumUndUhrzeit()
{
	time_t zeit = time(0);
	struct tm aktZeit;
	char str[60];

	localtime_s(&aktZeit, &zeit);

	strftime(str, sizeof str, "%d.%m.%Y", &aktZeit);
	this->aktuellesDatum = str;

	strftime(str, sizeof str, "%H:%M:%S", &aktZeit);
	this->aktuelleUhrzeit = str;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Standardmäßiges Würfeln
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpiel::spielerWuerfeln()
{
	int zaehler = 0;
	
	for (auto iter = wuerfel.begin(); iter != wuerfel.end(); ++iter, ++zaehler)
	{
		// wuerfel[zaehler]->wuerfeln();
		(*iter)->wuerfeln();
	}	
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Würfeln per bestimmter Postition
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpiel::spielerWuerfeln(size_t& position)
{
	wuerfel[position - 1]->wuerfeln();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Würfel Sortierung
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpiel::wuerfelSort()
{
	bool unsortiert;
	do 
	{
		unsortiert = false;
		for (size_t i = 0; i < (maxAnzahlWuerfel - 1); i++) 
		{
			if (wuerfel[i]->getGeWuerfelt() > wuerfel[i + 1]->getGeWuerfelt())
			{
				unsortiert = true;
				for (; i < (maxAnzahlWuerfel - 1); i++)
				{
					if (wuerfel[i]->getGeWuerfelt() > wuerfel[i + 1]->getGeWuerfelt())
					{
						std::swap(wuerfel[i], wuerfel[i + 1]);
					}
				}
			}
		}

	} while (unsortiert);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Datum und Uhrzeit Bildschirm - Ausgabe
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpiel::aktDatumUndUhrzeitAusgeben() const
{
	std::cout << aktuellesDatum << " - " << aktuelleUhrzeit << std::endl;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						     aktueller Spielzug
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool CSpiel::aktuellerSpielzug(size_t& index)
{
	if (aktZuege != spieler[index]->getMaxSpielzuege())
	{
		++aktZuege;
		return true;
	}
	else
	{
		aktZuege = 1;
		return false;
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Spieler - Spielzug zurücksetzen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpiel::resetSpielzug()
{
	aktZuege = 1;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						    Würfel - Bildschirmausgabe
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpiel::wuerfelAusgeben() const
{
	int zaehler = 0;
	char zeichen[5] = { '|','|', '|', '|', ' ' };

	if (wuerfel[0]->getGeWuerfelt() != 0)
	{
		std::cout << "Gewuerfelt:  ";
		for (auto iter = wuerfel.begin(); iter != wuerfel.end(); ++iter, ++zaehler)
		{
			std::cout << (*iter)->getGeWuerfelt() << zeichen[zaehler];
		}
		std::cout << std::endl << std::endl;
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   mögliche Kombinationen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

std::vector<std::pair<std::string, int>> CSpiel::kombinationen()
{
	int zahlen[6]{ 0,0,0,0,0,0 };		// nachträglich von size_t geändert im Falle das Fehler auftreten 
	std::string ausgabe;
	int zaehler = 0, parschSumme = 0, chanceSumme = 0;
	std::vector<std::pair<std::string, int>> kombi;

	for (auto iter = wuerfel.begin(); iter != wuerfel.end(); ++iter)
	{
		++zahlen[(*iter)->getGeWuerfelt() - 1];
		parschSumme += (*iter)->getGeWuerfelt();
		chanceSumme += (*iter)->getGeWuerfelt();
	}

	for (int zahl = 0; zahl < 6; ++zahl)		// 1,2,3,4,5,6  wuerfel-zahlen
	{
		int x = 0;
		
		if (zahlen[zahl] != 0)
		{
			++zaehler;
		}
		else
		{
			zaehler = 0;
		}

		if (zaehler == 4)
		{			
			kombi.push_back(std::pair<std::string, int>(getBewertungText(11), 30));				// kleine Strasse
		}
		if (zaehler == 5)
		{				
			kombi.push_back(std::pair<std::string, int>(getBewertungText(12), 40));				// grosse Strasse
		}

		switch (zahlen[zahl])					
		{
		case 0:				// Kein Eintrag
			zaehler = 0;			
			break;
		case 1:		
			kombi.push_back(std::pair<std::string, int>(getBewertungText(zahl+1), zahlen[zahl] * zahl+1));		// Einzelne
			break;
		case 2:
			kombi.push_back(std::pair<std::string, int>(getBewertungText(zahl+1), zahlen[zahl] * zahl+2));		// 2 gleiche
			break;
		case 3:
			zaehler = 0;

			kombi.push_back(std::pair<std::string, int>(getBewertungText(zahl+1), zahlen[zahl] * zahl+3));		// 3 gleiche

			kombi.push_back(std::pair<std::string, int>(getBewertungText(7), parschSumme));						// Dreierparsch

			for (int j = 0; j < 6; ++j)
			{
				if (zahlen[j] == 2)
				{
					kombi.push_back(std::pair<std::string, int>(getBewertungText(10), 25));						// Full-House
				}
			}
			break;
		case 4:
			zaehler = 0;

			kombi.push_back(std::pair<std::string, int>(getBewertungText(zahl+1), zahlen[zahl] * zahl+4));		// 4 gleiche

			kombi.push_back(std::pair<std::string, int>(getBewertungText(7), parschSumme));						// Dreierparsch

			kombi.push_back(std::pair<std::string, int>(getBewertungText(8), parschSumme));						// Viererparsch
			break;
		case 5:
			zaehler = 0;

			kombi.push_back(std::pair<std::string, int>(getBewertungText(zahl + 1), zahlen[zahl] * zahl + 5));		// 5 gleiche

			kombi.push_back(std::pair<std::string, int>(getBewertungText(7), parschSumme));						// Dreierparsch

			kombi.push_back(std::pair<std::string, int>(getBewertungText(8), parschSumme));						// Viererparsch				

			kombi.push_back(std::pair<std::string, int>(getBewertungText(9), 50));								// KNIFFEL
			break;
		}		
	}
	int x = 13;
	kombi.push_back(std::pair<std::string, int>(getBewertungText(x), chanceSumme));								// Chance

	x = 14;
	kombi.push_back(std::pair<std::string, int>(getBewertungText(x), 0));										// streichen / 0 Eintrag

	return kombi;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Kombination Text Zuordnung
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

std::string CSpiel::getBewertungText(int zahl)
{
	std::string eingabe;
	std::string fehler = "Fehler - BewertungText";

	switch (zahl)
	{
	case 0:
		// Kein Eintrag
		break;
	case 1:
		eingabe = "Einser";
		return eingabe;
	case 2:
		eingabe = "Zweier";
		return eingabe;
	case 3:
		eingabe = "Dreier";
		return eingabe;
	case 4:
		eingabe = "Vierer";
		return eingabe;
	case 5:
		eingabe = "Fuenfer";
		return eingabe;
	case 6:
		eingabe = "Sechser";
		return eingabe;
	case 7:
		eingabe = "Dreierparsch";
		return eingabe;
	case 8:
		eingabe = "Viererparsch";
		return eingabe;
	case 9:
		eingabe = "KNIFFEL";
		return eingabe;
	case 10:
		eingabe = "Full House";
		return eingabe;
	case 11:
		eingabe = "Kleine Strasse";
		return eingabe;
	case 12:
		eingabe = "Grosse Strasse";
		return eingabe;
	case 13:
		eingabe = "Chance";
		return eingabe;
	case 14:
		eingabe = "STREICHEN";
		return eingabe;
	}
	return fehler;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Gewinner berechnen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

int CSpiel::gewinnerErmitteln()
{
	int meistePunkte = 0;
	int zaehler = 0;

	for (auto iter = spieler.begin(); iter != spieler.end(); ++iter)		
	{
		if ((*iter)->getKombi().find(20)->second.second > meistePunkte)			// Sucht nach der höchsten Punktzahl, falls ja ...
		{
			meistePunkte = (*iter)->getKombi().find(20)->second.second;			// weist sie der Variable den Wert zu
		}
	}
	for (auto iter = spieler.begin(); iter != spieler.end(); ++iter)
	{
		++zaehler;
		if (meistePunkte == (*iter)->getKombi().find(20)->second.second)		// Überprüft nochmal auf gleichheit der Variablen meistePunkte und dem Eintrag des Gewinners
		{
			return zaehler-1;													// Gibt die Position zurück an der die Variable (meistePunkte) übereinstimmt
		}
	}
}



