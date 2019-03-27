
#include <iostream>

#include "PMTVTest/PMTVTest_MainTest.h"
#include <conio.h>

int main(int argc,char** argv)
{
    // Exécution des tests pour le tp4
    PMTVTest_MainTest mainTestBattery;
    mainTestBattery.initializeDataTP4();
    mainTestBattery.testProxy();
    mainTestBattery.testComposite();
    mainTestBattery.cleanupTP4();

    // Pause
    std::cout << "Appuyez sur une touche pour terminer le programme" << std::endl;
    _getch();

    return 0;
}