#pragma once

#include <string>
#include <iostream>
#include <map>

class CSpieler
{
private:
	std::string name;
	int aktPunkteStand = 0;
	int maxSpielzuege = 3;

	std::map<int, std::pair<std::string, int>> kombi;		// aktuelle Punktestand miteintragen + Gesamt Punktestand 
public:
	CSpieler() = default;
	CSpieler(std::string& name) : name(name)
	{}
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

	void kombinationEintragen()
	{
		int zaehler = 1;
		kombi.insert(std::pair<int, std::pair<std::string, int>>(zaehler,std::make_pair("Name", 3)));
	}

	friend std::ostream& operator<<(std::ostream& out, const CSpieler& spieler);
};

