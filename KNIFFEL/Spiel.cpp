#include "Spiel.h"
#include <iostream>

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
	spieler.clear();		// Nur Elemente zerstören, keine Freigabe des Speichers vom vector

	if (spieler.empty())
		return true;
	else
		return false;
}

void CSpiel::spielStarten()
{
	
}
