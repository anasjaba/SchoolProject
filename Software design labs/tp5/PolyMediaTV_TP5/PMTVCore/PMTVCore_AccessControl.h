///////////////////////////////////////////////////////////
//  PMTVCore_AccessControl.h
//  Implementation of the Class PMTVCore_AccessControl
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#ifndef PMTVCORE_ACCESS_CONTROL_H
#define PMTVCORE_ACCESS_CONTROL_H

#include "PMTVCore_MainControl.h"
#include "PMTVCore_AbstractInterface.h"

class PMTVMedia_Media;

//
// Classe PMTVCore_AccessControl
//
//
//
class PMTVCore_AccessControl : public PMTVCore_AbstractInterface
{
private:
	PMTVCore_MainControl* m_mainControl; // R�f�rence vers la classe de contr�le principale

public:
    // Constructeur & Destructeur
    PMTVCore_AccessControl(PMTVCore_MainControl* m) : m_mainControl(m) {};
    virtual ~PMTVCore_AccessControl() {};

    //--------------------------------------
    // Interfaces
    //--------------------------------------
    PMTVOnlineStore_OnlineStoreInterface* getOnlineStoreInterface() { return 0; } // Non support� pour le moment
    PMTVUser_UserManagement* getUserManagementInterface();
    PMTVMedia_MediaManager* getMediaManagerInterface();

    //--------------------------------------
    // Contr�le utilisateur
    //--------------------------------------
    void changeUser(std::string& userName); // Changement d'utilisateur

    //--------------------------------------
    // Contr�le m�dia
    //--------------------------------------
    
    // Suite aux messages de l'interface utilisateur
    // (Pour l'instant les pointeurs indexes les donn�es)
    void playMedia(PMTVMedia_Media* media);    // Joue le m�dia demand� si l'utilisateur le peut
    PMTVMedia_Media* getCurrentMediaPlaying(); // Retourne une r�f�rence vers le m�dia jouant pr�sentement

private:
    PMTVCore_AccessControl() {};
};

#endif
