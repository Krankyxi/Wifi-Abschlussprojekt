#pragma once

#include "Spiel.h"

class CDialog
{
private:
	CSpiel* pdialog;
	std::string zerlegeStringPositionsAuswahl(std::string& eingabe, int& index);
	bool checkStringPositionsAuswahl(std::string& eingabe);
public:
	CDialog() = default;
	CDialog(CSpiel* pdialog) : pdialog(pdialog)
	{}
	void menue();
	void einzelspielerMenue();
	void neuerSpielerES();
	void neuerSpielerMS();
	void spielerLoeschen();
	void spielerLaden();
	void alleSpielerAusgeben() const;
	void spielenDialog();
	void spielerTabellen(int& x);
	void mehrspielerMenue();
	bool wuerfelAuswahl(int& zaehler);
	void wuerfelMenue(int& zaehler, std::vector<CSpieler*> meineKopie);
	
};

