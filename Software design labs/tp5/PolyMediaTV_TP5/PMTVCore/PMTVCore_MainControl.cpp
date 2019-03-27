///////////////////////////////////////////////////////////
//  PMTVCore_MainControl.cpp
//  Implementation of the Class PMTVCore_MainControl
//  Created on:      31-oct.-2010 15:20:14
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVCore_MainControl.h"

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
PMTVCore_MainControl::PMTVCore_MainControl() {}

//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
PMTVCore_MainControl::~PMTVCore_MainControl() {}

//-----------------------------------------------------------------------------
// PMTVOnlineStore_OnlineStoreInterface* PMTVCore_MainControl::getOnlineStoreInterface()
// Retourne une référence vers l'interface du magasin en ligne
//-----------------------------------------------------------------------------
PMTVOnlineStore_OnlineStoreInterface* PMTVCore_MainControl::getOnlineStoreInterface()
{ return m_onlineStoreInterface; }

//-----------------------------------------------------------------------------
// PMTVMedia_MediaManager* PMTVCore_MainControl::getMediaManager()
// Retourne une référence vers le gestionnaire de média
//-----------------------------------------------------------------------------
PMTVMedia_MediaManager* PMTVCore_MainControl::getMediaManagerInterface()
{ return m_mediaManagerInterface; }

//-----------------------------------------------------------------------------
// PMTVUser_UserManagement* PMTVCore_MainControl::getUserManagementInterface()
// Retourne une référence vers le gestionnaire des utilisateurs
//-----------------------------------------------------------------------------
PMTVUser_UserManagement* PMTVCore_MainControl::getUserManagementInterface()
{ return m_userManagementInterface; }

//-----------------------------------------------------------------------------
// void PMTVCore_MainControl::changeUser(PMTVUser_User* user)
// PMTVUser_User* user : Référence à un utilisateur
// Change l'utilisateur courant
//-----------------------------------------------------------------------------
void PMTVCore_MainControl::changeUser(std::string& userName)
{ 
    getUserManagementInterface()->changeUser(userName); 
}

