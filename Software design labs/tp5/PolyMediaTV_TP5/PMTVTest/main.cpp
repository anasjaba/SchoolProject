
#include <iostream>

#include "PMTVTest/PMTVTest_MainTest.h"
#include <conio.h>

int main(int argc,char** argv)
{
    PMTVTest_MainTest mainTestBattery;

    // Exécution des tests pour le tp4
    //mainTestBattery.initializeDataTP4();
    //mainTestBattery.testProxy();
    //mainTestBattery.testComposite();
    //mainTestBattery.cleanupTP4();

    // Exécution des tests pour le tp5
    mainTestBattery.initializeDataTP5();
    mainTestBattery.testFactory();
    mainTestBattery.testMediator();

    mainTestBattery.cleanupTP5();

    // Exécution des tests pour le tp6
    //mainTestBattery.initializeDataTP6();
    //mainTestBattery.testObserver();
    //mainTestBattery.cleanupTP6();

    // Pause
    std::cout << "Appuyez sur une touche pour terminer le programme" << std::endl;
    _getch();

    return 0;
}