#include "Spieler.h"

void CSpieler::kombinationSpeichern(std::vector<std::pair<std::string, int>> kombination)
{
	auto iter = kombination.begin();

	for (auto it = kombi.begin(); it != kombi.end(); ++it)
	{
		if (it->second.first == iter->first)
		{
			if (it->second.second == -1)
			{
				it->second.second = iter->second;
				break;
			}
		}
	}
}

std::vector<std::pair<std::string, int>> CSpieler::kombinationenOhneEintrag()
{
	int zaehler = 0;
	std::vector<std::pair<std::string, int>> kombiOhneEintrag;

	for (auto it = kombi.begin(); it != kombi.end(); ++it)
	{
		if ((*it).first != 7 && (*it).first != 8 && (*it).first != 9 && (*it).first != 17 && (*it).first != 18 && (*it).first != 19 && (*it).first != 20)
		{
			if ((*it).second.second == -1)
			{
				kombiOhneEintrag.push_back(std::pair<std::string, int>(std::make_pair((*it).second.first, (*it).second.second)));
			}
		}
	}
	return kombiOhneEintrag;
}

void CSpieler::kombinationOhneEintragStreichen(std::vector<std::pair<std::string, int>> kombination)
{
	auto iter = kombination.begin();

	for (auto it = kombi.begin(); it != kombi.end(); ++it)
	{
		if (it->second.first == iter->first)
		{
			if (it->second.second == -1)
			{
				it->second.second = 0;
				break;
			}
		}
	}
}

std::vector<std::pair<std::string, int>> CSpieler::pruefenEintragVorhanden(std::vector<std::pair<std::string, int>> kombination)
{
	for (auto it = kombi.begin(); it != kombi.end(); ++it)
	{
		for (auto iter = kombination.begin(); iter != kombination.end(); ++iter)
		{
			if (iter->first == it->second.first)
			{
				if (it->second.second != -1)
				{					
					iter = kombination.erase(iter);		// eintrag nicht ordentlich geprüft VORSICHT !!!
				}
			}
		}		
	}
	return kombination;
}

void CSpieler::tabelleSpielerGesamt()
{
	int summeOben = 0, summeUnten = 0, bonusZaehler = 0, summeObererTeil = 0, summeUntererTeil = 0;
	int punkteBonus = 0, obererTeil = 0, untererTeil = 0;

	if (kombi.find(7)->second.second >= 63 && bonusZaehler == 0)
	{
		punkteBonus = 35;
		kombi.find(8)->second.second = punkteBonus;
		++bonusZaehler;
	}
	for (auto it = kombi.begin(); it != kombi.find(7); ++it)		// Berechnung oberer Teil der Tabelle
	{ 
		if (kombi.find(7)->second.second == -1)
		{
			kombi.find(7)->second.second = 0;
		}
		if (it->second.second != -1)								// Berechnung obere Gesamt Punkte
		{
			++obererTeil;
			summeOben += it->second.second;
			kombi.find(7)->second.second = summeOben;
		}		
		if (obererTeil == 6)										// Berechnung obere Punkte + Bonus Punkte
		{
			summeObererTeil = kombi.find(7)->second.second += punkteBonus;
			kombi.find(9)->second.second = summeObererTeil;
			kombi.find(18)->second.second = summeObererTeil;
		}		
	}
	for (auto it = kombi.find(10); it != kombi.find(17); ++it)		// Berechnung unterer Teil der Tabelle
	{
		if (it->second.second != -1)
		{
			++untererTeil;
			summeUnten += it->second.second;
			kombi.find(17)->second.second = summeUnten;			
		}
	}
	eintragCount = untererTeil + obererTeil;
	if (eintragCount == eintragMax)
	{
		summeUntererTeil = kombi.find(17)->second.second + kombi.find(18)->second.second;
		kombi.find(19)->second.second = summeUntererTeil;
	}
}

std::ostream& operator<<(std::ostream& out, const CSpieler& spieler)
{
	out << spieler.name;
	return out;
}
