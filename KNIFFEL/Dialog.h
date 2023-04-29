#pragma once

#include "Spiel.h"
#include "Historie.h"

class CDialog
{
private:
	CSpiel* pdialog;																	// Objekt Zeiger auf das Spiel
	std::string zerlegeStringPositionsAuswahl(std::string& eingabe, size_t& index);		// String wird in ein einziges Teil zerlegt
	bool checkStringPositionsAuswahl(std::string& eingabe);								// String-Check (ob alle eingegebenen Zeichen ausschließlich Zahlen sind)

public:
	CDialog() = default;							// Default-Konstruktor
	CDialog(CSpiel* pdialog) : pdialog(pdialog)		// Konstruktor mit einem Zeiger auf ein Spiel Objekt (Parameter)
	{}
	void menue();									// Hauptmenü
	void spielerMenue(int& auswahl);				// Spieler Menü
	void neuerSpieler(int& auswahl);				// Neuer Spieler Menü
	void spielerLoeschen();							// Spieler löschen
	void alleSpielerAusgeben() const;				// Alle Spieler werden ausgegeben
	void spielenDialog();							// Spiele Menü (Spiel gestartet)
	void frageSpeichern();							// Frage ob gespeichert werden soll
	void spielerTabellen(size_t& zaehler);			// Spieler Tabellen
	void historieMenue();							// Historie Menü
	const void spielanleitung() const;				// Spielanleitung (nachträgliche Änderung, wurde nicht in das Entwurfs Dokument aufgenommen)

	bool wuerfelMenue(size_t& zaehler, std::vector<CSpieler*> meineKopie);		// Würfel Menü
	void kombinationsAuswahl(size_t& zaehler);									// Kombinations Auswahl Menü
	bool wuerfelAuswahl(size_t& zaehler);										// Würfel Auswahl Menü

};

