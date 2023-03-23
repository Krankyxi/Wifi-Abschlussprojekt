#include "Dialog.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cctype>
#include <iomanip>

#define clear std::system("CLS");										// leert die Konsolenoberfläche 
#define sleep std::this_thread::sleep_for(std::chrono::seconds(2));		// stoppt den Konsolen-Output für 2 Sekunden

void CDialog::menue()	//////////////////// HAUPTMENÜ ////////////////////
{
	clear;
	std::string eingabe;

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
				clear;
				neuerSpielerES();			// Neuer Spieler wird angelegt
				break;
			case 2:
				clear;
				spielStartenDialog();				// Spiel wird im Einzelspieler-Modus gestartet
				break;
			case 3:
				clear;
				spielerLoeschen();			// Spieler wird geloescht
				break;
			case 4:
				clear;
				// spielerAnmelden();		// bestehender Spieler wird angemeldet
				break;
			case 5:
				if (pdialog->getSpieler().size() == 0)
				{
					return;
				}
				else
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
				}
				break;

			default:				
					std::cerr << "Falsche Eingabe - Bitte versuchen Sie es noch einmal" << std::endl;
					sleep;				
			}
		}
	} 
}

void CDialog::neuerSpielerES()		//////////////////// 1 Spieler anlegen im Einzelspielermodus ////////////////////
{
	std::string name;
	int zaehler = 1;

	clear;
	if (pdialog->getSpieler().size() == 1)
	{
		std::cout << "Maximale Spieleranzahl erreicht!" << std::endl;
		sleep;
		clear;
	}
	else
	{
		std::cout << "Bitte Spieler-Namen eingeben: ";
		std::getline(std::cin, name);

		for (int i = 1; i < name.length(); ++i)
		{
			name[0] = toupper(name[0]);				// sorgt dafür das der erste Buchstabe des Namens immer großgeschrieben initialisiert wird
			name[i] = tolower(name[i]);				// sorgt dafür das die restlichen Buchstaben danach immer kleingeschrieben initialisiert werden
		}
		pdialog->neuerSpieler(name);		
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
			break;
		}
		else
		{
			switch (stoi(eingabe))
			{
			case 1:
				neuerSpielerMS();			// Neue Spieler wird angelegt
				break;
			case 2:
				spielStartenDialog();				// Spiel wird im Mehrspieler-Modus gestartet
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

void CDialog::neuerSpielerMS()		//////////////////// mehrere Spieler anlegen im Mehrspielermodus ////////////////////
{
	std::string name;
	int zaehler = 1;

	clear;
	if (pdialog->getSpieler().size() == 4)
	{
		std::cout << "Maximale Spieleranzahl erreicht!" << std::endl;
		sleep;
		clear;
	}
	else
	{
		std::cout << "Bitte Spieler-Namen eingeben: ";
		std::getline(std::cin, name);

		for (int i = 1; i < name.length(); ++i)
		{
			name[0] = toupper(name[0]);				// sorgt dafür das der erste Buchstabe des Namens immer großgeschrieben initialisiert wird
			name[i] = tolower(name[i]);				// sorgt dafür das die restlichen Buchstaben danach immer kleingeschrieben initialisiert werden
		}
		pdialog->neuerSpieler(name);
	}
}

void CDialog::alleSpielerAusgeben() const		//////////////////// Alle aktuellen Spieler werden auf dem Bildschirm ausgegeben ////////////////////
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

void CDialog::spielStartenDialog()
{
	int x = 0;
	pdialog->spielStarten();
	einspielerTabelle(x);
	// zweispielerTabelle(x);
}

void CDialog::einspielerTabelle(int& x) 
{
	clear;
	std::cout << " Spieler 1   : " << pdialog->getSpieler().at(0)->getSpielerName() << std::endl << std::endl;
	std::cout << "#-------------------------------#" << std::endl;
	std::cout << "| nur Einser             [ "  << x << " ] | " << std::endl;
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

	std::system("Pause");
}

void CDialog::zweispielerTabelle(int& x) 
{
	clear;
	std::cout << " Spieler 1: " << pdialog->getSpieler().at(0)->getSpielerName() 
		<< std::setw(31) << "Spieler 2: " << pdialog->getSpieler().at(1)->getSpielerName() 
		<< std::endl << std::endl;

	std::cout << "#-------------------------------#  #-------------------------------#" << std::endl;
	std::cout << "| nur Einser             [    ] |  | nur Einser             [    ] |" << std::endl;
	std::cout << "| nur Zweier             [    ] |  | nur Zweier             [    ] |" << std::endl;
	std::cout << "| nur Dreier             [    ] |  | nur Dreier             [    ] |" << std::endl;
	std::cout << "| nur Vierer             [    ] |  | nur Vierer             [    ] |" << std::endl;
	std::cout << "| nur Fuenfer            [    ] |  | nur Fuenfer            [    ] |" << std::endl;
	std::cout << "| nur Sechser            [    ] |  | nur Sechser            [    ] |" << std::endl;
	std::cout << "|------------------------------ |  |------------------------------ |" << std::endl;
	std::cout << "| Gesamt                 [    ] |  | Gesamt                 [    ] |" << std::endl;
	std::cout << "|------------------------------ |  |------------------------------ |" << std::endl;
	std::cout << "| Bonus bei 63 oder mehr [    ] |  | Bonus bei 63 oder mehr [    ] |" << std::endl;
	std::cout << "| Gesamt oberer Teil     [    ] |  | Gesamt oberer Teil     [    ] |" << std::endl;
	std::cout << "|------------------------------ |  |------------------------------ |" << std::endl;
	std::cout << "| Dreierparsch           [    ] |  | Dreierparsch           [    ] |" << std::endl;
	std::cout << "| Viererparsch           [    ] |  | Viererparsch           [    ] |" << std::endl;
	std::cout << "| Full-House             [    ] |  | Full-House             [    ] |" << std::endl;
	std::cout << "| Kleine Strasse         [    ] |  | Kleine Strasse         [    ] |" << std::endl;
	std::cout << "| Grosse Strasse         [    ] |  | Grosse Strasse         [    ] |" << std::endl;
	std::cout << "| KNIFFEL                [    ] |  | KNIFFEL                [    ] |" << std::endl;
	std::cout << "| Chance                 [    ] |  | Chance                 [    ] |" << std::endl;
	std::cout << "| Gesamt unterer Teil    [    ] |  | Gesamt unterer Teil    [    ] |" << std::endl;
	std::cout << "| Gesamt oberer  Teil    [    ] |  | Gesamt oberer  Teil    [    ] |" << std::endl;
	std::cout << "#-------------------------------#  #-------------------------------#" << std::endl << std::endl;
	std::cout << "#-------------------------------#  #-------------------------------#" << std::endl;
	std::cout << "| ENDSUMME               [    ] |  | ENDSUMME               [    ] |" << std::endl;
	std::cout << "#-------------------------------#  #-------------------------------#" << std::endl;

	std::system("Pause");
}