#pragma once

#include <string>
#include <iostream>

class CSpieler
{
private:
	std::string name;
	int aktPunkteStand = 0;
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

	friend std::ostream& operator<<(std::ostream& out, const CSpieler& spieler);
};

