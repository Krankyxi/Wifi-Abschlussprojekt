#include "Spiel.h"
#include <iostream>
#include <ctime>
#include <algorithm>

void CSpiel::neuerSpieler(std::string& name)
{	
	spieler.push_back(new CSpieler(name));
}

void CSpiel::spielerLoeschen(int& index)
{
	auto iterator = spieler.begin()+index -1;
	spieler.erase(iterator);
}

bool CSpiel::alleSpielerLoeschen()
{
	spieler.clear();

	if (spieler.empty())
		return true;
	else
		return false;
}

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

void CSpiel::spielerWuerfeln()
{
	int zaehler = 0;
	
	for (auto iter = wuerfel.begin(); iter != wuerfel.end(); ++iter, ++zaehler)
	{
		wuerfel[zaehler]->wuerfeln();
	}	
	wuerfelSort();
}

void CSpiel::spielerWuerfeln(int& position)
{
	wuerfel[position - 1]->wuerfeln();
	wuerfelSort();
}

void CSpiel::wuerfelSort()
{
	bool unsortiert;
	do 
	{
		unsortiert = false;
		for (int i = 0; i < (maxAnzahlWuerfel - 1); i++) 
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

void CSpiel::aktDatumUndUhrzeitAusgeben() const
{
	std::cout << aktuellesDatum << " - " << aktuelleUhrzeit << std::endl;
}

bool CSpiel::aktuellerSpielzug(int& index)
{
	if (aktZuege != spieler[index]->getMaxSpielzuege())
	{
		++aktZuege;
		return false;
	}
	else
	{
		aktZuege = 1;
		return true;
	}
}

void CSpiel::wuerfelAusgeben() const
{
	int zaehler = 0;
	char zeichen[5] = { '|','|', '|', '|', ' ' };

	if (wuerfel[0]->getGeWuerfelt() != 0)
	{
		std::cout << "Gewuerfelt:  ";
		for (auto iter = wuerfel.begin(); iter != wuerfel.end(); ++iter, ++zaehler)
		{
			std::cout << wuerfel[zaehler]->getGeWuerfelt() << zeichen[zaehler];
		}
		std::cout << std::endl << std::endl;
	}
}




