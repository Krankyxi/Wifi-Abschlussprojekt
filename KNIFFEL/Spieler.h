#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>

class CSpieler
{
private:
	std::string name;
	int aktPunkteStand = 0;
	int maxSpielzuege = 3;

	std::map<int, std::pair<std::string, int>> kombi;	
public:
	CSpieler() = default;
	CSpieler(std::string& name) : name(name)
	{
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
	void neuerSpieler(const std::string& spielerName)
	{
		this->name = spielerName;
	}
	std::string getSpielerName() const
	{
		return this->name;
	}
	int getMaxSpielzuege() const
	{
		return maxSpielzuege;
	}

	std::map<int, std::pair<std::string, int>> getKombi() const
	{
		return kombi;
	}

	void kombinationSpeichern(std::vector<std::pair<std::string, int>> kombination);

	friend std::ostream& operator<<(std::ostream& out, const CSpieler& spieler);
};

