#pragma once

#include "Spiel.h"

class CHistorie
{
private:
	static std::string dateiName;
	static CSpiel* pSpiel;

public:
	std::string getDateiName() const
	{
		return dateiName;
	}
	static void einfuegen(CSpiel* obj);
	static void spielLaden();
	static void lokalSpeichern();
	static void schreibAuf(std::ofstream& schreibDatei);
	static bool leseVon(std::ifstream& einleseDatei);
};

// einlesen von Daten in der Historie oder Spiel Klasse ? +
// beim einlesen initialisieren, wo bzw. wie soll ich das machen ?  +
// warum funktioniert das durch iterieren nur per Kopie ? (habe keine andere L�sung gefunden) +
// initialisieren in der Historie des Vectors ? (habe ich �ber einen Pointer gemacht) +
// m�ssen alle Attribute und Methoden static sein ? (sonst funktioniert ja das verwenden nicht, andere L�sung?) +
// Dokumentation des Codes - wie genau soll der aussehen ? (passt meine Doku.?) +

// Pr�fung zwecks Projekt (auf dem guten Weg zur 1? ) wie wird benotet ?
// 
// Datenbank beginnen ! 