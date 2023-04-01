#include "Dialog.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cctype>
#include <iomanip>
#include <algorithm>

#define clear std::system("CLS");										// leert die Konsolenoberfläche 
#define sleep std::this_thread::sleep_for(std::chrono::seconds(2));		// stoppt den Konsolen-Output für 2 Sekunden

void CDialog::menue()	//////////////////// HAUPTMENÜ ////////////////////
{
	clear;
	std::string eingabe;
	int einzelspieler = 0;
	int mehrspieler = 0;

	for(;;)
	{
		clear;
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
			clear;
			menue();
		}
		else
		{
			switch (stoi(eingabe))
			{
			case 1:				
				einzelspielerMenue();		// Einzelspieler MENÜ wird aufgerufen					
				break;
			case 2:
				mehrspielerMenue();			// Mehrspieler MENÜ wird aufgerufen
				break;
			case 3:
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

void CDialog::einzelspielerMenue()		//////////////////// Einzelspieler - Menü ////////////////////
{
	std::string eingabe;
	std::string antwort;

	for(;;)
	{
		clear;
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
			clear;
		}
		else
		{
			switch (stoi(eingabe))
			{
			case 1:
				neuerSpielerES();			// Neuer Spieler wird angelegt
				break;
			case 2:
				if (pdialog->getSpieler().size() > 0)
				{
					spielenDialog();		// Spiel wird im Einzelspieler-Modus gestartet
				}
				else
				{
					clear;
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
					clear;											
					std::cout << "Wollen Sie das Menue wirklich verlassen ?" << std::endl;
					std::cout << "Es werden danach alle Spieler geloescht! (j/n): " << std::endl;
					std::getline(std::cin, antwort);

					if (antwort[0] == 'j')
					{
						clear;
						pdialog->alleSpielerLoeschen();	
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
						clear;
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

void CDialog::neuerSpielerES()		//////////////////// Einzelspieler-Modus (1) Spieler anlegen ////////////////////
{
	std::string name;
	int zaehler = 1;
	for (;;)
	{
		clear;
		if (pdialog->getSpieler().size() == 1)
		{
			std::cout << "Maximale Spieleranzahl erreicht!" << std::endl;
			sleep;
			clear;
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

void CDialog::spielerLoeschen()		//////////////////// 1 ausgewählter Spieler wird gelöscht ////////////////////
{
	std::string eingabe;
	int index = 0;
	int zaehler = 1;

	clear;
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

void CDialog::mehrspielerMenue()		//////////////////// Mehrspieler - Menü ////////////////////
{
	std::string eingabe;
	std::string antwort;

	for(;;)
	{
		clear;
		alleSpielerAusgeben();

		std::cout << "[1] Neue Spieler anlegen" << std::endl;
		std::cout << "[2] Spiel Starten" << std::endl;
		std::cout << "[3] Spieler loeschen" << std::endl;
		std::cout << "[4] Bestehenden Spieler anmelden" << std::endl;
		std::cout << "[5] Auswahl beenden" << std::endl;
		std::getline(std::cin, eingabe);

		if (!(std::isdigit(eingabe[0])))
		{
			std::cerr << "Falsche Eingabe - Bitte versuchen Sie es noch einmal" << std::endl;
			sleep;
		}
		else
		{
			switch (stoi(eingabe))
			{
			case 1:
				neuerSpielerMS();			// Neue Spieler wird angelegt
				break;
			case 2:
				spielenDialog();				// Spiel wird im Mehrspieler-Modus gestartet
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
				else
				{
					do
					{
						clear;
						if (pdialog->getSpieler().size() > 0)
						{
							std::cout << "Wollen Sie das Menue wirklich verlassen ?" << std::endl;
							std::cout << "Es werden danach alle Spieler geloescht! (j/n): " << std::endl;
							std::getline(std::cin, antwort);

							if (antwort[0] == 'j')
							{
								clear;
								pdialog->alleSpielerLoeschen();
								if (pdialog->getSpieler().size() == 0)
								{
									std::cout << "Spieler wurden geloescht" << std::endl;
									sleep;
									return;
								}
								else
								{
									std::cout << "Spieler konnten nicht geloescht werden! " << std::endl;
									sleep;
								}
							}
							if (antwort[0] == 'n')
							{
								break;
							}
						}
					} while (antwort[0] != 'j' || antwort[0] != 'n');
					break;
				}
			default:
				std::cerr << "Falsche Eingabe - Bitte versuchen Sie es noch einmal" << std::endl;
				sleep;
			}
		}
	}
}

void CDialog::neuerSpielerMS()		//////////////////// Mehrspieler-Modus (1 bis 4) Spieler anlegen ////////////////////
{
	std::string name;
	int zaehler = 1;

	for (;;)
	{
		clear;
		if (pdialog->getSpieler().size() == 4)
		{
			std::cout << "Maximale Spieleranzahl erreicht!" << std::endl;
			sleep;
			clear;
			return;
		}
		else
		{
			std::cout << "Bitte Spieler-Namen eingeben (min. 3 Buchstaben): ";
			std::getline(std::cin, name);

			if (!(isalpha(name[0])) || (!(isalpha(name[1]))) || (!(isalpha(name[2]))))
			{
				std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut" << std::endl;
				sleep;
			}
			else
			{
				for (int i = 1; i < name.length(); ++i)
				{
					name[0] = toupper(name[0]);				// sorgt dafür das der erste Buchstabe des Namens immer großgeschrieben initialisiert wird
					name[i] = tolower(name[i]);				// sorgt dafür das die restlichen Buchstaben danach immer kleingeschrieben initialisiert werden
				}
				pdialog->neuerSpieler(name);
				return;
			}
		}
	}
}

void CDialog::alleSpielerAusgeben() const		//////////////////// Bildschirm-Ausgabe für alle Spieler ////////////////////
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

void CDialog::spielenDialog()				//////////////////// Spielen ////////////////////
{
	std::string eingabe;
	int zaehler = 0;
	const std::vector<CSpieler*> meineKopie = pdialog->getSpieler();

	pdialog->aktDatumUndUhrzeit();

	for (;;)
	{		
		zaehler = 0;
		for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
		{			
			wuerfelMenue(zaehler, meineKopie);
		}
	}
}

void CDialog::wuerfelMenue(int& zaehler, std::vector<CSpieler*> meineKopie)
{
	int eintrag = 0;
	std::string eingabe;
	bool beenden = false;
	bool aktiv = true;

	do
	{
		clear;
		spielerTabellen(eintrag);

		if (pdialog->getSpieler().size() == 2)
		{
			std::cout << std::endl << std::setw(28) << "Spieler " << (zaehler + 1) << ": [" << meineKopie[zaehler]->getSpielerName() << "] ist an der Reihe!" << std::endl << std::endl;
		}
		else if (pdialog->getSpieler().size() == 3)
		{
			std::cout << std::endl << std::setw(43) << "Spieler " << (zaehler + 1) << ": [" << meineKopie[zaehler]->getSpielerName() << "] ist an der Reihe!" << std::endl << std::endl;
		}
		else if (pdialog->getSpieler().size() == 4)
		{
			std::cout << std::endl << std::setw(62) << "Spieler " << (zaehler + 1) << ": [" << meineKopie[zaehler]->getSpielerName() << "] ist an der Reihe!" << std::endl << std::endl;
		}

		std::cout << "[1] Wuerfeln! " << std::endl;

		if (beenden == true)
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
					aktiv = wuerfelAuswahl(zaehler);
					beenden = aktiv;
				} while (aktiv != true);
				system("Pause");
				break;
			case 2:
				if (beenden == true)
				{
					return;
				}
			default:
				std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
				sleep;
			}
		}
	} while (aktiv != true);
}

bool CDialog::wuerfelAuswahl(int& zaehler)
{
	int position = 0;
	bool aktiv = false;
	bool checkOk = false;
	std::string eingabe, posAuswahl;
	std::string b;

	std::cout << "Position:    1 2 3 4 5" << std::endl;
	std::cout << "             | | | | |" << std::endl;
	pdialog->wuerfelAusgeben();

	aktiv = pdialog->aktuellerSpielzug(zaehler);

	if (aktiv == false)
	{
		do
		{
			std::cout << "[1] Position auswaehlen fuer erneutes wuerfeln" << std::endl;
			std::cout << "[2] Wuerfel behalten" << std::endl;
			std::getline(std::cin, eingabe);

			if (!(isdigit(eingabe[0])) || eingabe.size() > 1 || stoi(eingabe) < 1 || stoi(eingabe) > 2)
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
							for (int i = 0; i < posAuswahl.size(); ++i)
							{
								b = zerlegeStringPositionsAuswahl(posAuswahl, i);								
								position = stoi(b);
								pdialog->spielerWuerfeln(position);	
							}
						}
					} while (checkOk != true);
					break;
				case 2:
					aktiv = false;
					return aktiv;
				default:
					std::cerr << "Falsche Eingabe - Bitte versuchen Sie es erneut!" << std::endl;
					sleep;
				}
			}
		} while (!(isdigit(eingabe[0])) || eingabe.size() > 1 || stoi(eingabe) < 1 || stoi(eingabe) > 2);
	}
	return aktiv;
}

std::string CDialog::zerlegeStringPositionsAuswahl(std::string& eingabe, int& index)
{
	std::string buchstabe;

	buchstabe = eingabe[index];
	return buchstabe;
}

bool CDialog::checkStringPositionsAuswahl(std::string& eingabe)
{
	if (eingabe.length() <= 5)
	{
		for (int i = 0; i < eingabe.length(); ++i)
		{
			if (isdigit(eingabe[i]) == false)
				return false;
		}
		return true;
	}
	return false;
}

void CDialog::spielerTabellen(int& x)			//////////////////// Spieler Tabellen ////////////////////
{
	int zaehler = 0;

	const std::vector<CSpieler*> meineKopie = pdialog->getSpieler();
	
	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << " Spieler " << (zaehler)+1 << ": " << pdialog->getSpieler().at(zaehler)->getSpielerName() << std::setw(31);
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "#-------------------------------#  ";
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter)
	{
		std::cout << "| nur Einser             [ " << x << "  ] |  ";		
	}
	std::cout << std::endl;

	for (auto iter = meineKopie.begin(); iter != meineKopie.end(); ++iter, ++zaehler)
	{
		std::cout << "| nur Zweier             [    ] |  ";
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


/*
	std::cout << "#-------------------------------#  ";
	std::cout << "| nur Einser             [ " << x << "  ] | " << std::endl;
	std::cout << "| nur Zweier             [    ] |" << std::endl;
	std::cout << "| nur Dreier             [    ] |" << std::endl;
	std::cout << "| nur Vierer             [    ] |" << std::endl;
	std::cout << "| nur Fuenfer            [    ] |" << std::endl;
	std::cout << "| nur Sechser            [    ] |" << std::endl;
	std::cout << "|------------------------------ |" << std::endl;
	std::cout << "| Gesamt                 [    ] |" << std::endl;
	std::cout << "|------------------------------ |" << std::endl;
	std::cout << "| Bonus bei 63 oder mehr [    ] |" << std::endl;
	std::cout << "| Gesamt oberer Teil     [    ] |" << std::endl;
	std::cout << "|------------------------------ |" << std::endl;
	std::cout << "| Dreierparsch           [    ] |" << std::endl;
	std::cout << "| Viererparsch           [    ] |" << std::endl;
	std::cout << "| Full-House             [    ] |" << std::endl;
	std::cout << "| Kleine Strasse         [    ] |" << std::endl;
	std::cout << "| Grosse Strasse         [    ] |" << std::endl;
	std::cout << "| KNIFFEL                [    ] |" << std::endl;
	std::cout << "| Chance                 [    ] |" << std::endl;
	std::cout << "| Gesamt unterer Teil    [    ] |" << std::endl;
	std::cout << "| Gesamt oberer  Teil    [    ] |" << std::endl;
	std::cout << "#-------------------------------#" << std::endl << std::endl;
	std::cout << "#-------------------------------#" << std::endl;
	std::cout << "| ENDSUMME               [    ] |" << std::endl;
	std::cout << "#-------------------------------#" << std::endl;
	*/

