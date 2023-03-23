#pragma once

#include "Spiel.h"

class CDialog
{
private:
	CSpiel* pdialog;
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
	void spielStartenDialog();
	void einspielerTabelle(int& x);
	void zweispielerTabelle(int& x);

	void mehrspielerMenue();
	

};

