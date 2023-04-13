#include "Spieler.h"

void CSpieler::kombinationSpeichern(std::vector<std::pair<std::string, int>> kombination)
{
	auto iter = kombination.begin();

	for (auto it = kombi.begin(); it != kombi.end(); ++it)
	{
		if (it->second.first == iter->first)
		{
			it->second.second = iter->second;
		}
	}
	/*for (auto it = kombi.begin(); it != kombi.end(); ++it)
	{
		std::cout << it->first << "|" << it->second.first << "|" << it->second.second << std::endl;
	}*/
}

std::ostream& operator<<(std::ostream& out, const CSpieler& spieler)
{
	out << spieler.name;
	return out;
}
