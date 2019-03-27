///////////////////////////////////////////////////////////
//  PMTVCore_AbstractInterface.h
//  Implementation of the Class PMTVCore_AbstractInterface
//  Created on:      31-oct.-2010 15:20:05
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTVCORE_ABSTRACT_INTERFACE_H
#define PMTVCORE_ABSTRACT_INTERFACE_H

class PMTVMedia_MediaManager;
class PMTVUser_UserManagement;
class PMTVUser_User;
class PMTVOnlineStore_OnlineStoreInterface;

#include <string>

//
// Classe PMTVCore_AbstractInterface
//
// Classe de base
//
class PMTVCore_AbstractInterface
{
private:
public:
    // Constructeur & Destructor
    PMTVCore_AbstractInterface();
    virtual ~PMTVCore_AbstractInterface() = 0;

    // Interfaces
    virtual PMTVOnlineStore_OnlineStoreInterface* getOnlineStoreInterface() = 0;
    virtual PMTVUser_UserManagement* getUserManagementInterface() = 0;
    virtual PMTVMedia_MediaManager* getMediaManagerInterface() = 0;

    // 
    virtual void changeUser(std::string& userName) = 0; // Changement d'utilisateur
};

#endif 
