///////////////////////////////////////////////////////////
//  PMTVTest_MainTest.cpp
//  Implementation of the Class PMTVTest_MainTest
//  Created on:      31-oct.-2010 15:03:53
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVTest_MainTest.h"
#include "PMTVCore/PMTVCore_MainControl.h"
#include "PMTVCore/PMTVCore_AccessControl.h"
#include "PMTVOnlineStore/PMTVOnlineStore_OnlineStoreInterface.h"

#include "PMTVMedia/PMTVMedia_MovieInfo.h"

// Filtres
#include "PMTVMedia/PMTVMedia_LogicFilter.h"
#include "PMTVMedia/PMTVMedia_MovieThemeFilter.h"
#include "PMTVMedia/PMTVMedia_MovieRatingFilter.h"

#include <iostream>

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
PMTVTest_MainTest::PMTVTest_MainTest()
: m_mainControl(0), m_accessControl(0), m_userManagement(0)
{}

//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
PMTVTest_MainTest::~PMTVTest_MainTest() 
{}

//-----------------------------------------------------------------------------
// Initialise les données pour le tp4
//-----------------------------------------------------------------------------
void PMTVTest_MainTest::initializeDataTP4()
{
    //-----------------------------------------------------
    // Création des systèmes & interfaces d'entrées des paquetages
    //-----------------------------------------------------
    m_mainControl    = new PMTVCore_MainControl();
    m_accessControl  = new PMTVCore_AccessControl(m_mainControl);
    m_userManagement = new PMTVUser_UserManagement();
    m_mediaManager   = new PMTVMedia_MediaManager();
    m_onlineStore    = new PMTVOnlineStore_OnlineStoreInterface();

    m_mainControl->setUserManagementInterface(m_userManagement);
    m_mainControl->setMediaManagerInterface(m_mediaManager);
    m_mainControl->setOnlineStoreInterface(m_onlineStore);

    //-----------------------------------------------------
    // Création de 3 utilisateurs au système & permissions
    //-----------------------------------------------------

    // Admin
    PMTVUser_Permission adminPermission;
    adminPermission.setCreateUser(true);
    adminPermission.setMovieStoreAccess(true);
    
    PMTVUser_User* admin = new PMTVUser_User(adminPermission);
    
    // Utilisateur 1 - David
    PMTVUser_User* user_david = new PMTVUser_User();
    PMTVUser_Permission p_david;
    p_david.setCreateUser(false);
    p_david.setMovieStoreAccess(false);
    p_david.setRatingRestriction(PMTV_MR_PG_13);
    p_david.addContentRestriction(PMTV_MC_ALCOHOLUSE);
    p_david.addContentRestriction(PMTV_MC_GORY_SCENE);
    user_david->setPermission(p_david);

    // Utilisateur 2 - Jonathan
    PMTVUser_User* user_jonathan = new PMTVUser_User();
    PMTVUser_Permission p_jonathan;
    p_jonathan.setCreateUser(false);
    p_jonathan.setMovieStoreAccess(true);
    p_jonathan.setRatingRestriction(PMTV_MR_NC_17);
    p_jonathan.addContentRestriction(PMTV_MC_TELETUBBIES);
    p_jonathan.addContentRestriction(PMTV_MC_SEX);
    user_jonathan->setPermission(p_jonathan);
    
    // Ajout des 3 utilisateurs
    m_userManagement->addUser(std::string("Admin"),admin);
    m_userManagement->addUser(std::string("David"),user_david);
    m_userManagement->addUser(std::string("Jonathan"),user_jonathan);

    // Construction de 5 films (librairie testé plus tard)
    mi1 = new PMTVMedia_MovieInfo();
    mi1->setMovieTitle("Batman Begins");
    mi1->setDirector("Christopher Nolan");
    mi1->setMovieRating(PMTV_MR_PG);
    mi1->setMovieTheme(PMTV_MT_SUPERHERO);
    mi1->addStudio("WB");
    mi1->addContent(PMTV_MC_VIOLENCE);
    

    mi2 = new PMTVMedia_MovieInfo();
    mi2->setMovieTitle("Serenity");
    mi2->setDirector("Joss Whedon");
    mi2->setMovieRating(PMTV_MR_PG_13);
    mi2->setMovieTheme(PMTV_MT_SCIENCEFICTION);
    mi2->addStudio("Universal");
    mi2->addContent(PMTV_MC_VIOLENCE);
    mi2->addContent(PMTV_MC_GORY_SCENE);

    mi3 = new PMTVMedia_MovieInfo();
    mi3->setMovieTitle("Superman Returns");
    mi3->setDirector("Brian Singer");
    mi3->setMovieRating(PMTV_MR_PG);
    mi3->setMovieTheme(PMTV_MT_SUPERHERO);
    mi3->addStudio("WB");
    mi3->addContent(PMTV_MC_VIOLENCE);

    mi4 = new PMTVMedia_MovieInfo();
    mi4->setMovieTitle("300");
    mi4->setDirector("Zach Snyder");
    mi4->setMovieRating(PMTV_MR_NC_17);
    mi4->setMovieTheme(PMTV_MT_ADVENTURE);
    mi4->addStudio("WB");
    mi4->addContent(PMTV_MC_VIOLENCE);
    mi4->addContent(PMTV_MC_GORY_SCENE);

    mi5 = new PMTVMedia_MovieInfo();
    mi5->setMovieTitle("La Romaine");
    mi5->setDirector("F. G. Shroedinger");
    mi5->setMovieRating(PMTV_MR_NC_17);
    mi5->setMovieTheme(PMTV_MT_PORN);
    mi5->addStudio("Cristal Inc.");
    mi5->addContent(PMTV_MC_VIOLENCE);
    mi5->addContent(PMTV_MC_GORY_SCENE);
    mi5->addContent(PMTV_MC_SEX);

    // Construction de la liste (mini BD!)
    m1 = new PMTVMedia_Movie(mi1);
    m2 = new PMTVMedia_Movie(mi2);
    m3 = new PMTVMedia_Movie(mi3);
    m4 = new PMTVMedia_Movie(mi4);
    m5 = new PMTVMedia_Movie(mi5);

    m_mediaList.push_back(m1);
    m_mediaList.push_back(m2);
    m_mediaList.push_back(m3);
    m_mediaList.push_back(m4);
    m_mediaList.push_back(m5);
   
    // Super admin au départ pour les tests
    m_userManagement->changeUser(std::string("SUPER_ADMIN"));
} 

//-----------------------------------------------------------------------------
// Initialise les donnée requises pour le tp5
//-----------------------------------------------------------------------------
void PMTVTest_MainTest::initializeDataTP5()
{}

//-----------------------------------------------------------------------------
// Initialise les données requises pour le tp6
//-----------------------------------------------------------------------------
void PMTVTest_MainTest::initializeDataTP6()
{}

//-----------------------------------------------------------------------------
// void PMTVTest_MainTest::cleanupTP4()
// Nettoyage éléments TP4
//-----------------------------------------------------------------------------
void PMTVTest_MainTest::cleanupTP4()
{
    delete m_mainControl;
    delete m_accessControl;
    delete m_userManagement;
    delete m_mediaManager;
    // Utilisateurs éliminés par user management
}

//-----------------------------------------------------------------------------
// void PMTVTest_MainTest::cleanupTP5()
// Nettoyage éléments TP5
//-----------------------------------------------------------------------------
void PMTVTest_MainTest::cleanupTP5()
{}

//-----------------------------------------------------------------------------
// void PMTVTest_MainTest::cleanupTP6()
// Nettoyage éléments TP6
//-----------------------------------------------------------------------------
void PMTVTest_MainTest::cleanupTP6()
{}

//-----------------------------------------------------------------------------
// Lance les tests liés aux proxy    
//-----------------------------------------------------------------------------
void PMTVTest_MainTest::testProxy() 
{
    std::cout << "Batterie de tests PROXY" << std::endl << std::endl;
    //---------------------------------------
    // Test 1 - Récupération de l'interface utilisateur
    //---------------------------------------
    std::cout << "Test 1 : Recuperation de l'interface utilisateur... ";
    PMTVUser_UserManagement* u = m_accessControl->getUserManagementInterface();
    if(u) { printSuccess(); }
    else  { printFailure(); }

    //---------------------------------------
    // Test 2 - Changement d'utilisateur
    //---------------------------------------
    std::cout << "Test 2 : Changement d'utilisateur..." << std::endl;
    
    std::cout << "  Administrateur "; 
    m_accessControl->changeUser(std::string("Admin"));
    if(m_userManagement->getCurrentUserName() == "Admin") { printSuccess(); }
    else { printFailure(); }

    std::cout << "  Jonathan ";
    m_accessControl->changeUser(std::string("Jonathan"));
    if(m_userManagement->getCurrentUserName() == "Jonathan") { printSuccess(); }
    else { printFailure(); }

    //---------------------------------------
    // Test 3 - Recuperation de l'interface media
    //---------------------------------------
    std::cout << "Test 3 : Recuperation de l'interface media...";
    m_userManagement->changeUser(std::string("Admin"));
    if(m_accessControl->getMediaManagerInterface()) { printSuccess(); }
    else { printFailure(); }

    //---------------------------------------
    // Test 4 - Visionnement contrôlé
    //---------------------------------------
    std::cout << "Test 4 : Visionnement avec limites..." << std::endl;
    std::cout << "  Utilisateur : David" << std::endl;
    m_userManagement->changeUser(std::string("David"));

    std::cout << "      Ecoute " << m3->getMovieInfo()->getMovieTitle();
    m_mediaManager->stopMedia();
    m_accessControl->playMedia(m3);
    if(m_accessControl->getCurrentMediaPlaying() == m3) { printSuccess(); } // Serenity joue
    else { printFailure(); } // Autre chose ou rien ne joue

    std::cout << "      Ne peut ecouter " << m4->getMovieInfo()->getMovieTitle();
    m_mediaManager->stopMedia();
    m_accessControl->playMedia(m4);
    if(m_accessControl->getCurrentMediaPlaying() == m4)     { printFailure(); } // 300 joue (âge, gore)
    else if(m_accessControl->getCurrentMediaPlaying() == 0) { printSuccess(); } // Rien ne joue
    else { printFailure(); } // Autre chose joue

    std::cout << "  Utilisateur : Jonathan" << std::endl;
    m_userManagement->changeUser(std::string("Jonathan"));

    std::cout << "      Ecoute " << m1->getMovieInfo()->getMovieTitle();
    m_mediaManager->stopMedia();
    m_accessControl->playMedia(m1);
    if(m_accessControl->getCurrentMediaPlaying() == m1) { printSuccess(); } // Batman joue
    else { printFailure(); } // Autre chose joue ou rien ne joue

    std::cout << "      Ne peut ecouter " << m5->getMovieInfo()->getMovieTitle();
    m_mediaManager->stopMedia();
    m_accessControl->playMedia(m5);
    if(m_accessControl->getCurrentMediaPlaying()) { printFailure(); } // La Romaine ou quelquechose joue
    else { printSuccess(); } // Rien ne joue

    //---------------------------------------
    // Fin batterie proxy
    //---------------------------------------
    std::cout << std::endl << std::endl;
} 

//-----------------------------------------------------------------------------
// Lance les tests liés aux composites
//-----------------------------------------------------------------------------
void PMTVTest_MainTest::testComposite() 
{
    std::cout << "Batterie de tests COMPOSITE" << std::endl << std::endl;

    //---------------------------------------
    // Test 1 - Constructions de filtre composites
    //---------------------------------------
    PMTVMedia_MediaFilter* testCompositeFilter   = new PMTVMedia_LogicFilter(false,true);
    PMTVMedia_MediaFilter* dummyCompositeFilter1 = new PMTVMedia_LogicFilter(true,true);
    PMTVMedia_MediaFilter* dummyCompositeFilter2 = new PMTVMedia_LogicFilter(false,false);
    PMTVMedia_MediaFilter* dummyThemeFilter  = new PMTVMedia_MovieThemeFilter(false,PMTV_MT_ADVENTURE);
    PMTVMedia_MediaFilter* dummyRatingFilter = new PMTVMedia_MovieRatingFilter(false,PMTV_MR_PG);

    std::cout << "Test 1 : Construction de filtres composites" << std::endl;
    std::cout << "  Ajout de filtres au composite";
    testCompositeFilter->addFilter(dummyCompositeFilter1);
    testCompositeFilter->addFilter(dummyCompositeFilter2);
    if(testCompositeFilter->getNbFilter() == 2) { printSuccess(); }
    else { printFailure(); }
    
    std::cout << "  Retrait de filtres au composite";
    testCompositeFilter->removeFilter(dummyCompositeFilter1);
    if(testCompositeFilter->getNbFilter() == 1) { printSuccess(); }
    else { printFailure(); }

    std::cout << "  Effacement de la liste de filtres";
    testCompositeFilter->clearFilter();
    if(testCompositeFilter->getNbFilter() == 0) { printSuccess(); }
    else { printFailure(); }



    //---------------------------------------
    // Test 2 - Test de contenu
    //---------------------------------------
    std::cout << "Test 2 : Test de composition..." << std::endl;
    testCompositeFilter->clearFilter();
    dummyCompositeFilter1->addFilter(dummyThemeFilter);
    dummyCompositeFilter2->addFilter(dummyRatingFilter);
    testCompositeFilter->addFilter(dummyCompositeFilter1);
    testCompositeFilter->addFilter(dummyCompositeFilter2);

    std::cout << "  Recherche du filtre par theme Aventure";
    if(testCompositeFilter->containsFilter(dummyThemeFilter)) { printSuccess(); }
    else { printFailure(); }

    std::cout << "  Recherche du filtre par rating PG";
    if(testCompositeFilter->containsFilter(dummyRatingFilter)) { printSuccess(); }
    else { printFailure(); }

    std::cout << "  Recherche du filtre composite racine";
    if(testCompositeFilter->containsFilter(testCompositeFilter)) { printSuccess(); }
    else { printFailure(); }

    std::cout << "  Recherche d'un filtre non existant";
    if(testCompositeFilter->containsFilter(0)) { printFailure(); }
    else { printSuccess(); }

    // Cleanup
    delete testCompositeFilter;
    delete dummyCompositeFilter1;
    delete dummyCompositeFilter2;
    delete dummyThemeFilter;
    delete dummyRatingFilter;

    //---------------------------------------
    // Test 3 - Filtre par directeur & filtre
    //---------------------------------------
    PMTVMedia_LogicFilter* rootFilter = new PMTVMedia_LogicFilter(false,true); // Relation ET
    PMTVMedia_MovieRatingFilter* movieRatingFilter = new PMTVMedia_MovieRatingFilter(true,PMTV_MR_NC_17); // Pas de 17+
    PMTVMedia_MovieThemeFilter* movieThemeFilter  = new PMTVMedia_MovieThemeFilter(false,PMTV_MT_SCIENCEFICTION); // En science fiction
    std::list<PMTVMedia_Media*> mediaList;

    std::cout << "Test 3 : Filtrage des films (Titre, # Theme, # Rating)" << std::endl;
    printMediaList(m_mediaList);

    std::cout << std::endl;
    std::cout << "  Filtre par theme Science-Fiction";
    rootFilter->clearFilter();
    mediaList = std::list<PMTVMedia_Media*>(m_mediaList);
    rootFilter->addFilter(movieThemeFilter);
    rootFilter->filter(mediaList);
    printMediaList(mediaList);

    std::cout << std::endl;
    std::cout << "  Filtre sans rating 17+";
    rootFilter->clearFilter();
    mediaList = std::list<PMTVMedia_Media*>(m_mediaList);
    rootFilter->addFilter(movieRatingFilter);
    rootFilter->filter(mediaList);
    printMediaList(mediaList);

    std::cout << std::endl;
    std::cout << "  Filtre par theme Science-Fiction ET sans rating 17+";
    rootFilter->clearFilter();
    mediaList = std::list<PMTVMedia_Media*>(m_mediaList);
    rootFilter->addFilter(movieThemeFilter);
    rootFilter->addFilter(movieRatingFilter);
    rootFilter->filter(mediaList);
    printMediaList(mediaList);

    std::cout << std::endl;
    std::cout << "  Filtre par theme Super Hero OU rating 17+";
    rootFilter->clearFilter();
    mediaList = std::list<PMTVMedia_Media*>(m_mediaList);
    rootFilter->setAndFilter(false);       // Passe en relation ou
    movieRatingFilter->setNegative(false); // On veut 17+
    movieThemeFilter->setMovieTheme(PMTV_MT_SUPERHERO); // Aventure
    rootFilter->addFilter(movieRatingFilter);
    rootFilter->addFilter(movieThemeFilter);
    rootFilter->filter(mediaList);
    printMediaList(mediaList);

    delete rootFilter;
    delete movieThemeFilter;
    delete movieRatingFilter;

    //---------------------------------------
    // Fin batterie composite
    //---------------------------------------
    std::cout << std::endl << std::endl;
} 

//-----------------------------------------------------------------------------
// Helper
//-----------------------------------------------------------------------------
void PMTVTest_MainTest::printSuccess() { std::cout << " [Reussi]" << std::endl; }
void PMTVTest_MainTest::printFailure() { std::cout << " [Echec]" << std::endl; }

// Utile jusqu'à l'implémentation d'une surcharge <<
void PMTVTest_MainTest::printMediaList(std::list<PMTVMedia_Media*>& m)
{
    std::cout << std::endl;

    std::list<PMTVMedia_Media*>::iterator i = m.begin();
    std::list<PMTVMedia_Media*>::iterator e = m.end();

    for(;i!=e;++i)
    {
        std::cout << "(" << ((PMTVMedia_MovieInfo*)(*i)->getMediaInfo())->getMovieTitle() 
                  << "," << ((PMTVMedia_MovieInfo*)(*i)->getMediaInfo())->getMovieTheme()
                  << "," << ((PMTVMedia_MovieInfo*)(*i)->getMediaInfo())->getMovieRating() 
                  << ")" << std::endl;
    }

}