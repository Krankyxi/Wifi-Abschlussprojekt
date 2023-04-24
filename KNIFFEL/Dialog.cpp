#include "Dialog.h"
#include "Historie.h"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <map>

#define cleanScreen std::system("CLS");									// leert die Konsolenoberfläche 
#define sleep std::this_thread::sleep_for(std::chrono::seconds(2));		// stoppt den Konsolen-Output für 2 Sekunden

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//									Hauptmenü
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::menue()	
{
	cleanScreen;
	std::string eingabe;
	int einzelspieler = 0;
	int mehrspieler = 0;

	for(;;)
	{
		cleanScreen;
		alleSpielerAusgeben();

		std::cout << "[1] Einzelspieler" << std::endl;
		std::cout << "[2] Mehrspieler" << std::endl;
		std::cout << "[3] Historie" << std::endl;
		std::cout << "[4] Spiel beenden" << std::endl;
		std::getline(std::cin, eingabe);

		if (!(std::isdigit(eingabe[0])))
		{
			std::cerr << "Falsche Eingabe - bitte versuchen Sie es noch einmal" << std::endl;
			sleep;
		}
		else
		{
			switch (stoi(eingabe))
			{
			case 1:			
				einzelspieler = stoi(eingabe);
				spielerMenue(einzelspieler);		// Einzelspieler MENÜ wird aufgerufen					
				break;
			case 2:
				mehrspieler = stoi(eingabe);
				spielerMenue(mehrspieler);			// Mehrspieler MENÜ wird aufgerufen
				break;
			case 3:
				// datenbank aufrufen statistik
				break;
			case 4:
				return;
			default:
				std::cerr << "Falsche Eingabe - bitte versuchen Sie es noch einmal" << std::endl;
				sleep;
			}
		}
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//							  Spieler - Menü
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::spielerMenue(int& auswahl)		
{
	std::string eingabe;
	std::string antwort;
	CSpiel spiel;

	for(;;)
	{
		cleanScreen;
		if (auswahl == 1)
		{
			std::cout << "--- Einzelspieler-Modus ---" << std::endl << std::endl;
		}
		if (auswahl == 2)
		{
			std::cout << "--- Mehrspieler-Modus ---" << std::endl << std::endl;
		}
		alleSpielerAusgeben();

		std::cout << "[1] Neuen Spieler anlegen" << std::endl;
		std::cout << "[2] Spiel Starten" << std::endl;
		std::cout << "[3] Spiel laden" << std::endl;
		std::cout << "[4] Spieler loeschen" << std::endl;
		std::cout << "[5] Auswahl beenden" << std::endl;
		std::getline(std::cin, eingabe);

		if (!(std::isdigit(eingabe[0])))
		{
			std::cerr << "Falsche Eingabe - Bitte versuchen Sie es noch einmal" << std::endl;
			sleep;
			cleanScreen;
		}
		else
		{
			switch (stoi(eingabe))
			{
			case 1:
				if (auswahl == 1)			// Einzelnen Spieler anlegen
				{
					neuerSpieler(auswahl);			
				}
				if (auswahl == 2)			// Mehrere Spieler anlegen
				{
					neuerSpieler(auswahl);			
				}
				break;
			case 2:						
				if (pdialog->getSpieler().size() > 0)
				{					
					if (auswahl == 1)
					{
						spielenDialog();		// Einzelspieler wird gestartet	
					}
					if (auswahl == 2)
					{
						if (pdialog->getSpieler().size() > 1)
						{
							spielenDialog();		// Mehrspieler wird gestartet
						}
						else
						{
							std::cerr << "Es sind zuwenig Spieler vorhanden! " << std::endl;
							sleep;
						}
					}
				}
				else
				{
					cleanScreen;
					std::cerr << "Es ist noch kein Spieler vorhanden!" << std::endl;
					sleep;
				}				
				break;
			case 3:
				pdialog = pdialog->spielLaden();				
				CDialog dialog(&spiel);
				break;
			case 4:
				spielerLoeschen();			// Spieler wird geloescht
				break;
			case 5:
				if (pdialog->getSpieler().size() == 0)
				{
					return;
				}
				else if(pdialog->getSpieler().size() > 0)
				{					
					cleanScreen;											
					std::cout << "Wollen Sie das Menue wirklich verlassen ?" << std::endl;
					std::cout << "Es werden danach alle Spieler geloescht! (j/n): " << std::endl;
					std::getline(std::cin, antwort);

					if (antwort[0] == 'j')
					{
						cleanScreen;
						pdialog->alleSpielerLoeschen();			// alle Spieler werden beim Verlassen des Menues geloescht

						if (pdialog->alleSpielerLoeschen() == true)
						{
							std::cout << "Spieler geloescht!" << std::endl;
							sleep;
						}
						if (pdialog->alleSpielerLoeschen() == false)
						{
							std::cerr << "Spieler konnten nicht geloescht werden!" << std::endl;
							sleep;
						}
						cleanScreen;
						return;
					}						
				}
				break;
			default:				
					std::cerr << "Falsche Eingabe - Bitte versuchen Sie es noch einmal" << std::endl;
					sleep;				
			}
		}
	} 
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//							Neuen Spieler anlegen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::neuerSpieler(int& auswahl)	
{
	std::string name;
	int zaehler = 1;

	for (;;)
	{
		cleanScreen;
		if (auswahl == 1 && pdialog->getSpieler().size() == 1 || auswahl == 2 && pdialog->getSpieler().size() == 4)
		{
			std::cout << "Maximale Spieleranzahl erreicht!" << std::endl;
			sleep;
			cleanScreen;
			return;
		}
		else
		{
			std::cout << "Bitte Spieler-Namen eingeben (min. 3 Buchstaben): ";
			std::getline(std::cin, name);

			if (!(isalpha(name[0])) || (!(isalpha(name[1]))) || (!(isalpha(name[2]))) )
			{
				std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut" << std::endl;
				sleep;
			}
			else
			{
				for (int i = 1; i < name.length(); ++i)
				{
					name[0] = toupper(name[0]);				// 1 Buchstabe Groß
					name[i] = tolower(name[i]);				// ab dem 2 Buchstaben klein initialisieren
				}
				pdialog->neuerSpieler(name);				
				return;
			}
		}
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					Einzelner Spieler wird nach Auswahl gelöscht
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::spielerLoeschen()		
{
	std::string eingabe;
	int index = 0;
	int zaehler = 1;

	cleanScreen;
	if (pdialog->getSpieler().size() > 0)
	{
		alleSpielerAusgeben();

		std::cout << "Welcher Spieler soll geloescht werden ?: ";
		std::getline(std::cin, eingabe);

		if(!(std::isdigit(eingabe[0])))
		{
			std::cerr << "Falsche Eingabe - Bitte versuchen Sie es noch einmal" << std::endl;
			sleep;
		}
		else
		{
			index = stoi(eingabe);

			if (index > 0 && index <= pdialog->getMaxAnzahlSpieler())
			{
				pdialog->spielerLoeschen(index);			// Spieler löschen Auswahl (einzeln per Index)
				std::cout << "Spieler erfolgreich geloescht!" << std::endl;
				sleep;
			}
			else
			{
				std::cerr << "Diesen Spieler gibt es nicht!" << std::endl;
				sleep;
			}
		}
	}
	else if (pdialog->getSpieler().size() == 0)
	{
		std::cout << "Kein Spieler vorhanden!" << std::endl;
		sleep;
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//					 Bildschirm-Ausgabe für alle Spieler
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::alleSpielerAusgeben() const		
{
	int zaehler = 1;

	if (pdialog->getSpieler().size() > 0)
	{
		for (int i = 0; i < pdialog->getSpieler().size(); ++i, ++zaehler)
		{
			std::cout << "Spieler " << zaehler << ": " << pdialog->getSpieler().at(i)->getSpielerName() << std::endl;
		}
		std::cout << std::endl;
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//							Speicherung Abfrage
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::frageSpeichern()
{
	std::string eingabe;
	
	do
	{
		std::cout << "Wollen Sie speichern? (j/n)" << std::endl;
		std::getline(std::cin, eingabe);

		if (eingabe[0] == 'j')
		{
			pdialog->lokalSpeichern();					// Spiel wird gespeichert 
			pdialog->alleSpielerLoeschen();				// alle Spieler werden gelöscht
			pdialog->resetAnzSpieler();
			return;
		}
		if (eingabe[0] == 'n')
		{
			pdialog->alleSpielerLoeschen();
			pdialog->resetAnzSpieler();
			return;
		}
	} while (eingabe[0] != 'j' || eingabe[0] != 'n');
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//								Spielen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::spielenDialog()				
{
	std::string eingabe;
	size_t zaehler = 0;
	int gewinner = 0;
	const std::vector<CSpieler*> meineKopie = pdialog->getSpieler();

	pdialog->aktDatumUndUhrzeit();

	for (;;)
	{		
		zaehler = 0;
		for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
		{	
			pdialog->resetSpielzug();

			if (wuerfelMenue(zaehler, meineKopie) == true)
			{
				return;
			}
			if (meineKopie.size() == 1)				// Einzelspieler abgeschlossenes Spiel Mitteilung
			{
				if (pdialog->getSpieler().at(zaehler)->getMaxEintrag() == pdialog->getSpieler().at(zaehler)->getCountEintrag())		// maximale Einträge
				{
					cleanScreen;
					spielerTabellen(zaehler);
					std::cout << std::endl;
					std::cout << "Glueckwunsch, " << pdialog->getSpieler().at(zaehler)->getSpielerName() << " du hast das Spiel zu Ende gespielt ;)" << std::endl;
					std::cout << "Du hast das Spiel mit ( " << pdialog->getSpieler().at(zaehler)->getKombi().find(19)->second.second << " ) Punkten abgeschlossen! " << std::endl;
					std::cout << std::endl;
					system("Pause");
					pdialog->datenbankSpeichern();
					pdialog->alleSpielerLoeschen();
					return;
				}
			}
			else if (meineKopie.size() > 1)			// Mehrspieler Gewinner ermitteln
			{
				if (iter == meineKopie.end().operator-(1) && pdialog->getSpieler().at(zaehler)->getMaxEintrag() == pdialog->getSpieler().at(zaehler)->getCountEintrag())
				{
					cleanScreen;
					spielerTabellen(zaehler);
					gewinner = pdialog->gewinnerErmitteln();
					if (gewinner == -1)
					{
						std::cerr << "Der Gewinner konnte nicht uebermittelt werden!" << std::endl;
						return;
					}
					std::cout << std::endl << "Der glueckliche Gewinner ist [ " << pdialog->getSpieler().at(gewinner)->getSpielerName() << " ] mit [ "
						<< pdialog->getSpieler().at(gewinner)->getKombi().find(19)->second.second << " ] Punkten!" << std::endl;
					std::cout << std::endl;

					pdialog->datenbankSpeichern();
					pdialog->alleSpielerLoeschen();
					return;
				}
			}
		}
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//								Würfel - Menü
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool CDialog::wuerfelMenue(size_t& zaehler, std::vector<CSpieler*> meineKopie)			
{
	std::string eingabe;
	bool aktiv = true;

	for (;;)
	{
		cleanScreen;
		spielerTabellen(zaehler);

		if (pdialog->getSpieler().size() == 2)
		{
			std::cout << std::endl << std::setw(0) << "Spieler " << (zaehler + 1) << ": [" << meineKopie[zaehler]->getSpielerName() << "] ist an der Reihe!" << std::endl << std::endl;
		}
		else if (pdialog->getSpieler().size() == 3)
		{
			std::cout << std::endl << std::setw(0) << "Spieler " << (zaehler + 1) << ": [" << meineKopie[zaehler]->getSpielerName() << "] ist an der Reihe!" << std::endl << std::endl;
		}
		else if (pdialog->getSpieler().size() == 4)
		{
			std::cout << std::endl << std::setw(0) << "Spieler " << (zaehler + 1) << ": [" << meineKopie[zaehler]->getSpielerName() << "] ist an der Reihe!" << std::endl << std::endl;
		}

		std::cout << "[1] Wuerfeln! " << std::endl;	
		bool vergleich = pdialog->vergleicheCounter();

		if (vergleich == true)
		{
			std::cout << "[2] Spiel Beenden" << std::endl;
		}			
		std::getline(std::cin, eingabe);

		if (!(isdigit(eingabe[0])))
		{
			std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
			sleep;
		}
		else
		{
			switch (stoi(eingabe))
			{
			case 1:
				pdialog->spielerWuerfeln();
				do
				{
					aktiv = wuerfelAuswahl(zaehler);							// solange der Spieler nicht 3 Spielzüge hatte, wird die Schleife nicht verlassen

				} while (aktiv != false);
				return aktiv;
			case 2:		
				if (vergleich == true)
				{
					frageSpeichern();												// Frage ob gespeichert werden soll nach Beenden Auswahl
					return aktiv;
				}
			default:
				std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
				sleep;
			}
		}
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//								Würfel - Auswahl-Menü
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool CDialog::wuerfelAuswahl(size_t& zaehler)
{
	size_t position = 0;
	bool checkOk = false;
	bool aktiv;
	std::string eingabe, posAuswahl;
	std::string b;
	
	do
	{
		aktiv = pdialog->aktuellerSpielzug(zaehler);

		std::cout << "Position:    1 2 3 4 5" << std::endl;			// Positionen über dem Würfel, damit die Auswahl übersichtlicher ist
		std::cout << "             | | | | |" << std::endl;
		pdialog->wuerfelSort();										// Würfel Sortierung
		pdialog->wuerfelAusgeben();									// Würfel am Bildschirm ausgeben

		if (aktiv == true)
		{
			std::cout << "[1] Position auswaehlen fuer erneutes wuerfeln" << std::endl;
			std::cout << "[2] Alle nochmals wuerfeln" << std::endl;
			std::cout << "[3] Wuerfel behalten" << std::endl;
			std::getline(std::cin, eingabe);
		}
		else if (aktiv == false)
		{
			kombinationsAuswahl(zaehler);
			return aktiv;
		}

		if (!(isdigit(eingabe[0])) || eingabe.size() > 1 || stoi(eingabe) < 1 || stoi(eingabe) > 3)
		{
			std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
			sleep;
		}
		else 
		{
			switch (stoi(eingabe))
			{
			case 1:
				do
				{
					std::cout << "Welche Wuerfel-Position(en) moechten Sie erneut wuerfeln ? ";
					std::getline(std::cin, posAuswahl);

					checkOk = checkStringPositionsAuswahl(posAuswahl);

					if (checkOk == false)
					{
						std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
					}
					else if(checkOk == true)
					{
						for (size_t i = 0; i < posAuswahl.size(); ++i)
						{
							b = zerlegeStringPositionsAuswahl(posAuswahl, i);		// eingabe wird zerlegt 
							position = static_cast<size_t>(stoi(b));
							pdialog->spielerWuerfeln(position);						// und hier dem Würfel übergeben
						}
					}
				} while (checkOk != true);
				break;
			case 2:	
				pdialog->spielerWuerfeln();											
				break;
			case 3:
				kombinationsAuswahl(zaehler);										
				aktiv = false;
				return aktiv;
			default:
				std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
				sleep;
			}
		}
	} while (!(isdigit(eingabe[0])) || eingabe.size() > 1 || stoi(eingabe) < 1 || stoi(eingabe) > 3);
	return aktiv;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						Kombinations Auswahl-Menü
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::kombinationsAuswahl(size_t& zaehler)
{
	std::string eingabe;
	std::vector<std::pair<std::string, int>> kombination;
	std::vector<std::pair<std::string, int>> kombinationOhneEintrag;

	for (;;)
	{
		kombination.clear();
		kombination = pdialog->kombinationen();	

		kombination = pdialog->getSpieler().at(zaehler)->pruefenEintragVorhanden(kombination);

		int zaehlerPos = 1;

		std::cout << "---------------------------------" << std::endl;
		for (auto& iter : kombination)											// Auflistung der zu auswählenden Kombinationen		
		{			
			std::cout << "[" << zaehlerPos << "] " << iter.first << std::endl;
			++zaehlerPos;			
		}
		std::cout << "---------------------------------" << std::endl;
		std::cout << std::endl << "Welche Kombination moechten Sie auswaehlen ? ";
		std::getline(std::cin, eingabe);

		if (!(isdigit(eingabe[0])) || stoi(eingabe) < 1 || stoi(eingabe) >= zaehlerPos || eingabe.size() > 1)
		{
			std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
		}
		else
		{			
			int index = stoi(eingabe) - 1;
			kombination.at(0) = kombination.at(index);							// ausgewählte Position der obigen Auflistung, wird an die Stelle 0 gesetzt			
			
			if (kombination.at(0).first == "STREICHEN")
			{
				int kombiIndex = 0;
				do
				{
					kombiIndex = 0;
					kombinationOhneEintrag = pdialog->getSpieler().at(zaehler)->kombinationenOhneEintrag();
					std::cout << "---------------------------------" << std::endl;

					for (auto& iter : kombinationOhneEintrag)					// Auflistung der zu auswählenden Kombinationen die noch nicht eingetragen wurden
					{
						++kombiIndex;
						std::cout << "[" << kombiIndex << "] " << iter.first << std::endl;
					}

					std::cout << "---------------------------------" << std::endl;
					std::cout << "Welche Kombination moechten Sie streichen lassen ? ";
					std::getline(std::cin, eingabe);

					if (!(isdigit(eingabe[0])) || stoi(eingabe) < 1 || stoi(eingabe) > kombiIndex)
					{
						std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
					}
					else
					{
						index = stoi(eingabe) - 1;
						kombinationOhneEintrag.at(0) = kombinationOhneEintrag.at(index);
						pdialog->getSpieler().at(zaehler)->kombinationOhneEintragStreichen(kombinationOhneEintrag);		// 0 Punkte werden eingetragen
					}
				} while (!(isdigit(eingabe[0])) || stoi(eingabe) < 1 || stoi(eingabe) > kombiIndex);
			}
			kombination.erase(kombination.begin() + 1, kombination.end());		// restliche Auflistung wird gelöscht	

			if (kombination.at(0).second != 0)
			{
				pdialog->getSpieler().at(zaehler)->kombinationSpeichern(kombination);
			}
			pdialog->getSpieler().at(zaehler)->tabelleSpielerGesamt();			
			return;
		}
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						String zerlegen (in einzelne Buchstaben)
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

std::string CDialog::zerlegeStringPositionsAuswahl(std::string& eingabe, size_t& index)
{
	std::string buchstabe;	
	
	buchstabe = eingabe[index];
	return buchstabe;		
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//		String-Check (ob alle eingegebenen Zeichen ausschließlich Zahlen sind)
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool CDialog::checkStringPositionsAuswahl(std::string& eingabe)
{
	int zahl = 0;

	if (eingabe.length() <= 5 && eingabe.size() != 0)					// prüft ob nicht mehr als 5 Positionen eingegeben werden
	{
		for (size_t i = 0; i < eingabe.length(); ++i)
		{
			if (isdigit(eingabe[i]) == false)							// prüft ob es sich um eine ganze Zahl handelt
			{
				return false;
			}
			for (size_t j = eingabe.length(); j > i; --j)
			{
				if (eingabe[i] == eingabe[j])							// prüft ob doppelte Werte (Positions-Auswahl) vorhanden sind
				{
					return false;
				}
			}
			zahl = stoi(zerlegeStringPositionsAuswahl(eingabe, i));		// string wird in einen buchstaben umgewandelt und anschließend in eine zahl konvertiert 

			if (zahl < 1 || zahl > 5)									// prüft die zahl ob sie zwischen 1 und 5 liegt 
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//								Spieler Tabellen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::spielerTabellen(size_t& zaehlerValue)
{
	size_t zaehler = 0;
	int breite = 3;
	std::string puffer = "   ";

	const std::vector<CSpieler*> meineKopie = pdialog->getSpieler();
	
	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)			// Bildschirm Ausgabe 
	{
		std::cout << " Spieler " << (zaehler)+1 << ": " << pdialog->getSpieler().at(zaehler)->getSpielerName() << std::setw(29);
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)			
	{
		std::cout << "#--------------------------------#  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Einser             [ ";				

		if ((*iter)->getKombi().find(1)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(1)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Zweier             [ ";

		if ((*iter)->getKombi().find(2)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(2)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Dreier             [ ";

		if ((*iter)->getKombi().find(3)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(3)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Vierer             [ ";

		if ((*iter)->getKombi().find(4)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(4)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Fuenfer            [ ";

		if ((*iter)->getKombi().find(5)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(5)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Sechser            [ ";

		if ((*iter)->getKombi().find(6)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(6)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "|--------------------------------|  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Gesamt                 [ ";

		if ((*iter)->getKombi().find(7)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(7)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "|--------------------------------|  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Bonus bei 63 oder mehr [ ";

		if ((*iter)->getKombi().find(8)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(8)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Gesamt oberer Teil     [ ";

		if ((*iter)->getKombi().find(9)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(9)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "|--------------------------------|  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Dreierparsch           [ ";

		if ((*iter)->getKombi().find(10)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(10)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;
	
	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Viererparsch           [ ";

		if ((*iter)->getKombi().find(11)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(11)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Full House             [ ";

		if ((*iter)->getKombi().find(12)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(12)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Kleine Strasse         [ ";

		if ((*iter)->getKombi().find(13)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(13)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Grosse Strasse         [ ";

		if ((*iter)->getKombi().find(14)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(14)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| KNIFFEL                [ ";

		if ((*iter)->getKombi().find(15)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(15)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Chance                 [ ";

		if ((*iter)->getKombi().find(16)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(16)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "#--------------------------------#  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Gesamt unterer Teil    [ ";

		if ((*iter)->getKombi().find(17)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(17)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Gesamt oberer Teil     [ ";

		if ((*iter)->getKombi().find(18)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(18)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "#--------------------------------#  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "#--------------------------------#  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| ENDSUMME               [ ";

		if ((*iter)->getKombi().find(19)->second.second != -1)
		{
			std::cout << std::setw(breite) << (*iter)->getKombi().find(19)->second.second;
		}
		else
		{
			std::cout << puffer;
		}
		std::cout << " ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "#--------------------------------#  "; 
	}
	std::cout << std::endl;
}