///////////////////////////////////////////////////////////
//  PMTVTest_MainTest.h
//  Implementation of the Class PMTVTest_MainTest
//  Created on:      31-oct.-2010 15:03:53
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTVTEST_MAIN_TEST_H
#define PMTVTEST_MAIN_TEST_H

class PMTVCore_MainControl;
class PMTVCore_AccessControl;
class PMTVUser_UserManagement;
class PMTVMedia_MediaManager;
class PMTVOnlineStore_OnlineStoreInterface;
class PMTVTest_MediaTestContainer;

#include <list>

#include "PMTVMedia/PMTVMedia_Movie.h"
#include "PMTVMedia/PMTVMedia_MovieInfo.h"

//
// Classe PMTVTest_MainTest
//
// Classe interface du paquetage de test.
//
// Lance des batteries de tests dans plusieurs sous-système.
//
class PMTVTest_MainTest
{
private:
    // Références vers les différentes interfaces à tester
    PMTVCore_MainControl*    m_mainControl;
    PMTVCore_AccessControl*  m_accessControl;
    PMTVUser_UserManagement* m_userManagement;
    PMTVMedia_MediaManager*  m_mediaManager;
    PMTVOnlineStore_OnlineStoreInterface* m_onlineStore;

    // Films
    PMTVMedia_Movie* m1,*m2,*m3,*m4,*m5;
    PMTVMedia_MovieInfo* mi1,*mi2,*mi3,*mi4,*mi5;

    std::list<PMTVMedia_Media*> m_mediaList; // Liste de contenu media

    // Container
    PMTVTest_MediaTestContainer* m_testContainer;

protected:
    // Helper
    void printSuccess();
    void printFailure();
    void printMediaList(std::list<PMTVMedia_Media*>& m);

public:
    // Constructor & Destructor
	PMTVTest_MainTest();
	~PMTVTest_MainTest();

    void initializeDataTP4(); // Données TP4
    void initializeDataTP5(); // Données TP5
    void initializeDataTP6(); // Données TP6

    // Nettoyage mémoire
    void cleanupTP4();
    void cleanupTP5();
    void cleanupTP6();

    // TP4
    void testProxy();      // Lance les tests liés aux proxy
    void testComposite();  // Lance les tests liés aux composites

    // TP5
    void testFactory(); 
    void testMediator();
    void testObserver();

    // TP6
    // void testCommand();
    // void testStrategy();
    // void testState();
};

#endif
