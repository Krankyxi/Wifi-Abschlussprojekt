#pragma once

#include <string>
#include <iostream>
#include <map>
#include <vector>

class CSpieler
{
private:
	std::string name;
	std::map<int, std::pair<std::string, int>> kombi;

	int aktPunkteStand = 0;
	int eintragCount = 0;
	const int maxSpielzuege = 3;
	const int eintragMax = 13;	

public:
	CSpieler() = default;
	CSpieler(std::string& name);

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
	int getMaxEintrag() const
	{
		return eintragMax;
	}
	int getCountEintrag() const
	{
		return eintragCount;
	}
	std::map<int, std::pair<std::string, int>> getKombi() const
	{
		return kombi;
	}
	
	void tabelleSpielerGesamt();
	void kombinationSpeichern(std::vector<std::pair<std::string, int>> kombination);
	void kombinationOhneEintragStreichen(std::vector<std::pair<std::string, int>> kombination);

	std::vector<std::pair<std::string, int>> pruefenEintragVorhanden(std::vector<std::pair<std::string, int>> kombination);
	std::vector<std::pair<std::string, int>> kombinationenOhneEintrag();

	friend std::ostream& operator<<(std::ostream& out, const CSpieler& spieler);
};

