#pragma once

#include "Spiel.h"
#include "Historie.h"

class CDialog
{
private:
	CSpiel* pdialog;																	// Objekt Zeiger auf das Spiel
	std::string zerlegeStringPositionsAuswahl(std::string& eingabe, size_t& index);		// String wird in ein einziges Teil zerlegt
	bool checkStringPositionsAuswahl(std::string& eingabe);								// String-Check (ob alle eingegebenen Zeichen ausschlie�lich Zahlen sind)

public:
	CDialog() = default;							// Default-Konstruktor
	CDialog(CSpiel* pdialog) : pdialog(pdialog)		// Konstruktor mit einem Zeiger auf ein Spiel Objekt (Parameter)
	{}
	void menue();									// Hauptmen�
	void spielerMenue(int& auswahl);				// Spieler Men�
	void neuerSpieler(int& auswahl);				// Neuer Spieler Men�
	void spielerLoeschen();							// Spieler l�schen
	void alleSpielerAusgeben() const;				// Alle Spieler werden ausgegeben
	void spielenDialog();							// Spiele Men� (Spiel gestartet)
	void frageSpeichern();							// Frage ob gespeichert werden soll
	void spielerTabellen(size_t& zaehler);			// Spieler Tabellen
	void historieMenue();							// Historie Men�
	const void spielanleitung() const;				// Spielanleitung (nachtr�gliche �nderung, wurde nicht in das Entwurfs Dokument aufgenommen)

	bool wuerfelMenue(size_t& zaehler, std::vector<CSpieler*> meineKopie);		// W�rfel Men�
	void kombinationsAuswahl(size_t& zaehler);									// Kombinations Auswahl Men�
	bool wuerfelAuswahl(size_t& zaehler);										// W�rfel Auswahl Men�

};

