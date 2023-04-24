#pragma once

#include "Spiel.h"
#include "Historie.h"

class CDialog
{
private:
	CSpiel* pdialog;
	std::string zerlegeStringPositionsAuswahl(std::string& eingabe, size_t& index);
	bool checkStringPositionsAuswahl(std::string& eingabe);

public:
	CDialog() = default;
	CDialog(CSpiel* pdialog) : pdialog(pdialog)
	{}
	void menue();
	void spielerMenue(int& auswahl);
	void neuerSpieler(int& auswahl);
	void spielerLoeschen();
	void alleSpielerAusgeben() const;
	void spielenDialog();
	void frageSpeichern();
	void spielerTabellen(size_t& zaehler);
	bool wuerfelAuswahl(size_t& zaehler);
	bool wuerfelMenue(size_t& zaehler, std::vector<CSpieler*> meineKopie);
	void kombinationsAuswahl(size_t& zaehler);	

};

