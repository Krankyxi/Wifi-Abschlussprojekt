#include "Spiel.h"
#include "Dialog.h"

#include <iostream>

void test()
{
    CSpiel spiel;
    CDialog dialog(&spiel);

    dialog.menue();
 
}

int main()
{
    test();
    
    return 0;
}



