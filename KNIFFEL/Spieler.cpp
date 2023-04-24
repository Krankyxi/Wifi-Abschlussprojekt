#include "Spieler.h"

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Spieler Konstruktor (name)
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

CSpieler::CSpieler(std::string& name)
{
	this->name = name;

	kombi.insert(std::pair<int, std::pair<std::string, int>>(1, std::make_pair("Einser", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(2, std::make_pair("Zweier", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(3, std::make_pair("Dreier", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(4, std::make_pair("Vierer", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(5, std::make_pair("Fuenfer", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(6, std::make_pair("Sechser", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(7, std::make_pair("Gesamt", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(8, std::make_pair("Bonus bei 63 oder mehr", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(9, std::make_pair("Gesamt oberer Teil", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(10, std::make_pair("Dreierparsch", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(11, std::make_pair("Viererparsch", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(12, std::make_pair("Full House", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(13, std::make_pair("Kleine Strasse", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(14, std::make_pair("Grosse Strasse", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(15, std::make_pair("KNIFFEL", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(16, std::make_pair("Chance", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(17, std::make_pair("Gesamt unterer Teil", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(18, std::make_pair("Gesamt oberer Teil", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(19, std::make_pair("ENDSUMME", -1)));
	kombi.insert(std::pair<int, std::pair<std::string, int>>(20, std::make_pair("aktueller Punktestand", -1)));
}

void CSpieler::setPunkte(std::map<int, std::pair<std::string, int>>& kombination)
{
	auto it = kombination.begin();
	for (auto iter = this->kombi.begin(); iter != this->kombi.end() && it != kombination.end(); ++iter, ++it)
	{
		(*iter).second.second = it->second.second;
		this->aktPunkteStand = kombi.find(20)->second.second;
	}
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//							Kombinationen speichern
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

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

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						 Kombinationen Filter ohne Einträge
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

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

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//							Kombinationen Auswahl für "0" Punkte Eintrag
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

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

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						Prüft ob Einträge bereits vorhanden
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

std::vector<std::pair<std::string, int>> CSpieler::pruefenEintragVorhanden(std::vector<std::pair<std::string, int>> kombination)
{
	for (auto it = kombi.begin(); it != kombi.end(); ++it)
	{
		for (auto iter = kombination.begin(); iter != kombination.end(); ++iter)
		{
			if (iter->first == it->second.first)
			{
				if (it->second.second != -1)			// Mögliche Kombinations Einträge werden geprüft ob Sie schon vorhanden sind
				{					
					iter = kombination.erase(iter);		// falls vorhanden, werden hier die Vorschläge zum Eintragen gelöscht	
				}
			}
		}		
	}
	return kombination;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Tabellen Punkte Einträge 
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CSpieler::tabelleSpielerGesamt()
{
	int summeOben = 0, summeUnten = 0, bonusZaehler = 0, summeObererTeil = 0, summeUntererTeil = 0;
	int punkteBonus = 0, obererTeil = 0, untererTeil = 0, aktuellePunkte = 0;

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
			aktuellePunkte += it->second.second;
			aktPunkteStand = aktuellePunkte;
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
		if (it->second.second != -1)								// Berechnung untere Gesamt Punkte
		{
			aktuellePunkte += it->second.second;
			aktPunkteStand = aktuellePunkte;
			++untererTeil;
			summeUnten += it->second.second;
			kombi.find(17)->second.second = summeUnten;			
		}
	}
	eintragCount = untererTeil + obererTeil;

	if (eintragCount == eintragMax)									// Tabellen Einträge zählen, wenn gleich Maximum - Gesamt Punkte eintragen
	{
		summeUntererTeil = kombi.find(17)->second.second + kombi.find(18)->second.second;
		kombi.find(19)->second.second = summeUntererTeil;
	}
	kombi.find(20)->second.second = aktPunkteStand;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//						   Bildschirm-Ausgabe für die Spieler-klasse
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

std::ostream& operator<<(std::ostream& out, const CSpieler& spieler)
{
	out << spieler.name;
	return out;
}
