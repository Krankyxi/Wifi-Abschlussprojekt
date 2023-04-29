#include "Spiel.h"
#include "Historie.h"
#include "Dialog.h"

#include <iostream>

int main()         // MANI = MAIN ;)
{
    CSpiel spiel;
    CDialog dialog(&spiel);
    dialog.menue();   
    
    return 0;
}



