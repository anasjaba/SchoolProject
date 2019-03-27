///////////////////////////////////////////////////////////
//  PMTVCore_MainControl.h
//  Implementation of the Class PMTVCore_MainControl
//  Created on:      31-oct.-2010 15:20:14
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTVCORE_MAIN_CONTROL_H
#define PMTVCORE_MAIN_CONTROL_H

class PMTVOnlineStore_OnlineStoreInterface;

#include "PMTVCore_AbstractInterface.h"
#include "PMTVUser/PMTVUser_UserManagement.h"
#include "PMTVMedia/PMTVMedia_MediaManager.h"

class PMTVCore_MainControl : public PMTVCore_AbstractInterface
{
private:
    PMTVUser_UserManagement* m_userManagementInterface; // Interface pour la gestion utilisateur
    PMTVOnlineStore_OnlineStoreInterface* m_onlineStoreInterface; // Interface du magasin en ligne
    PMTVMedia_MediaManager* m_mediaManagerInterface; // Gestionnaire de média

public:
    // Constructeur & Destructeur
	PMTVCore_MainControl();
	virtual ~PMTVCore_MainControl();

    //-------------------------------------------
    // Interfaces de communication vers les autres paquetages
    //-------------------------------------------
    PMTVOnlineStore_OnlineStoreInterface* getOnlineStoreInterface();
    PMTVMedia_MediaManager* getMediaManagerInterface();
    PMTVUser_UserManagement* getUserManagementInterface();
    //-------------------------------------------

    void setUserManagementInterface(PMTVUser_UserManagement* userInterface) { m_userManagementInterface = userInterface; }
    void setMediaManagerInterface(PMTVMedia_MediaManager* mediaManager)     { m_mediaManagerInterface = mediaManager; }
    void setOnlineStoreInterface(PMTVOnlineStore_OnlineStoreInterface* onlineStoreInterface) { m_onlineStoreInterface = onlineStoreInterface; }

    void changeUser(std::string& userName);

};
#endif