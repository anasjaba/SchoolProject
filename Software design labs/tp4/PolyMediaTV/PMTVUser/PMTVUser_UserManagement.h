///////////////////////////////////////////////////////////
//  PMTVUser_UserManagement.h
//  Implementation of the Class PMTVUser_UserManagement
//  Created on:      31-oct.-2010 16:07:42
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTVUSER_USERMANAGEMENT_H
#define PMTVUSER_USERMANAGEMENT_H

#include "PMTVUser_User.h"

#include <map>
#include <string>

//
// Classe PMTVUser_UserManagement
//
// Entité de contrôle pour les utilisateurs.
//
class PMTVUser_UserManagement
{
private:
    PMTVUser_User* m_admin;               // Administrateur du système
    
    std::string    m_currentUserName;     // Nom de l'utilisateur actif
    PMTVUser_User* m_currentUser;         // Référence au compte utilisateur actif

    std::map<std::string,PMTVUser_User*> m_userMap; // Map associatif ID-usager

public:
	PMTVUser_UserManagement();
	virtual ~PMTVUser_UserManagement();

    // Manipulation compte utilisateur
    void addUser(std::string& userName,PMTVUser_User* u);   
    void changeUser(std::string& userName);

    bool userExist(std::string& userName);

    std::string getCurrentUserName() { return m_currentUserName; }
    PMTVUser_User* getCurrentUser()  { return m_currentUser;     }

};

#endif
