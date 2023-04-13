#include "Dialog.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <map>

#define cleanScreen std::system("CLS");										// leert die Konsolenoberfläche 
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
				// historieAbrufen();
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

	for(;;)
	{
		cleanScreen;
		alleSpielerAusgeben();

		std::cout << "[1] Neuen Spieler anlegen" << std::endl;
		std::cout << "[2] Spiel Starten" << std::endl;
		std::cout << "[3] Spieler loeschen" << std::endl;
		std::cout << "[4] Bestehenden Spieler anmelden" << std::endl;
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
				spielerLoeschen();			// Spieler wird geloescht
				break;
			case 4:
				// spielerAnmelden();		// bestehender Spieler wird angemeldet
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
				pdialog->spielerLoeschen(index);
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
//								Spielen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::spielenDialog()				
{
	std::string eingabe;
	size_t zaehler = 0;
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
		std::cout << "[2] Spiel Beenden" << std::endl;
			
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
					aktiv = wuerfelAuswahl(zaehler);

				} while (aktiv != false);
				return aktiv;
			case 2:			
				return aktiv;
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

		std::cout << "Position:    1 2 3 4 5" << std::endl;
		std::cout << "             | | | | |" << std::endl;
		pdialog->wuerfelSort();
		pdialog->wuerfelAusgeben();

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
					std::cout << "Welche Wuerfel-Position(en) moechten Sie erneut wuerfeln ?";
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
							b = zerlegeStringPositionsAuswahl(posAuswahl, i);
							position = static_cast<size_t>(stoi(b));
							pdialog->spielerWuerfeln(position);
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
	std::vector<std::pair<std::string, int>>::iterator it;
	std::cout << std::endl;

	kombination = pdialog->kombinationen();					// vector(pair) zurückgeliefert

	for (;;)
	{
		int zaehlerPos = 1;

		for (auto& iter : kombination)						// Auflistung der zu auswählenden Kombinationen		
		{
			std::cout << "[" << zaehlerPos << "] " << iter.first << std::endl;
			++zaehlerPos;
		}
		std::cout << std::endl << "Welche Kombination moechten Sie auswaehlen ?";
		std::getline(std::cin, eingabe);

		if (!(isdigit(eingabe[0])) || stoi(eingabe) < 1 || stoi(eingabe) >= zaehlerPos || eingabe.size() > 1)
		{
			std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
		}
		else
		{			
			int index = stoi(eingabe) - 1;
			kombination.at(0) = kombination.at(index);			// ausgewählte Position der obigen Auflistung, wird an die Stelle 0 gesetzt			
			
			kombination.erase(kombination.begin() + 1, kombination.end());		// restliche Auflistung wird gelöscht	

			pdialog->getSpieler().at(zaehler)->kombinationSpeichern(kombination);
			//tabellenEintrag(kombination, zaehler);		
			system("Pause");
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


void CDialog::tabellenEintrag(std::vector<std::pair<std::string, int>> kombination, size_t& zaehler)
{
	
}


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//								Spieler Tabellen
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDialog::spielerTabellen(size_t& zaehlerValue)
{
	size_t zaehler = 0;

	const std::vector<CSpieler*> meineKopie = pdialog->getSpieler();
	
	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << " Spieler " << (zaehler)+1 << ": " << pdialog->getSpieler().at(zaehler)->getSpielerName() << std::setw(30);
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "#-------------------------------#  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Einser             [" << std::cout.fill(' ');				// hier weitermachen

		if (pdialog->getSpieler().at(zaehlerValue)->getKombi().find(1)->second.second != -1)
		{
			std::cout << pdialog->getSpieler().at(zaehlerValue)->getKombi().find(1)->second.second;
		}
		std::cout << "] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Zweier             [" << std::cout.fill(' ');

		if (pdialog->getSpieler().at(zaehlerValue)->getKombi().find(2)->second.second != -1)
		{
			std::cout << pdialog->getSpieler().at(zaehlerValue)->getKombi().find(2)->second.second;
		}
		std::cout << "] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Dreier             [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Vierer             [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Fuenfer            [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Sechser            [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "|-------------------------------|  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Gesamt                 [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "|-------------------------------|  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Bonus bei 63 oder mehr [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Gesamt oberer Teil     [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "|-------------------------------|  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Dreierparsch           [    ] |  ";
	}
	std::cout << std::endl;
	
	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Viererparsch           [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Full-House             [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Kleine Strasse         [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Grosse Strasse         [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| KNIFFEL                [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Chance                 [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Gesamt unterer Teil    [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| Gesamt oberer  Teil    [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "#-------------------------------#  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "#-------------------------------#  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| ENDSUMME               [    ] |  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "#-------------------------------#  "; 
	}
	std::cout << std::endl;
}

