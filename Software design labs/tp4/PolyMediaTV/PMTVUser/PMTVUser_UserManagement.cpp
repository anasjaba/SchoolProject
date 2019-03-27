///////////////////////////////////////////////////////////
//  PMTVUser_UserManagement.cpp
//  Implementation of the Class PMTVUser_UserManagement
//  Created on:      31-oct.-2010 16:07:42
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVUser_UserManagement.h"
#include "PMTVUser_Permission.h"


//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
PMTVUser_UserManagement::PMTVUser_UserManagement()
{
    // Création de l'administrateur de base, fournit avec le système au départ
    PMTVUser_Permission p_admin;
    p_admin.setCreateUser(true);
    p_admin.setMovieStoreAccess(true);
    m_admin = new PMTVUser_User(p_admin);
    m_currentUserName = std::string("SUPER_ADMIN");
    m_currentUser     = m_admin;

    // Ajoute le super admin à la liste utilisateur
    addUser(std::string("SUPER_ADMIN"),m_admin);
}

//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
PMTVUser_UserManagement::~PMTVUser_UserManagement()
{
    // :TODO: Cleanup utilisateur
}

//-----------------------------------------------------------------------------
// void PMTVUser_UserManagement(PMTVUser_User* u)
// PMTVUser_User* 
//-----------------------------------------------------------------------------
void PMTVUser_UserManagement::addUser(std::string& userName,PMTVUser_User* u)
{
    // Si l'utilisateur n'existe pas au préalable
    if(!userExist(userName))
    { m_userMap[userName] = u; }
}

//-----------------------------------------------------------------------------
// void PMTVUser_UserManagement::changeUser(std::string& userName)
// userName : Nom de l'utilisateur
//-----------------------------------------------------------------------------
void PMTVUser_UserManagement::changeUser(std::string& userName)
{
    // Trouve l'utilisateur
    std::map<std::string,PMTVUser_User*>::const_iterator f;
    f = m_userMap.find(userName);

    // Change l'utilisateur courant
    if(f!=m_userMap.end())
    { m_currentUserName = f->first; m_currentUser = f->second; }
}

//-----------------------------------------------------------------------------
// bool PMTVUser_UserManagement::userExist(std::string& userName)
// userName : Identificateur utilisateur à retrouver
//-----------------------------------------------------------------------------
bool PMTVUser_UserManagement::userExist(std::string& userName)
{
    std::map<std::string,PMTVUser_User*>::iterator f;
    f = m_userMap.find(userName);
    if(f!=m_userMap.end())
    { return true; }
    else
    { return false; }
}


