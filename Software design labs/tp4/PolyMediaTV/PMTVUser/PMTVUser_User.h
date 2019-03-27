///////////////////////////////////////////////////////////
//  PMTVUser_User.h
//  Implementation of the Class PMTVUser_User
//  Created on:      31-oct.-2010 16:07:49
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#ifndef PMTVUSER_USER_H
#define PMTVUSER_USER_H

#include "PMTVUser_Permission.h"

class PMTVUser_UserProfile;

//
// Classe PMTVUser_User
//
// Classe repr�sentant l'entit� utilisateur.  Un utilisateur a des permissions qui 
// limitent les op�rations permises par celui-ci avec le reste du syst�me.
//
class PMTVUser_User
{
private:
    PMTVUser_Permission m_permission;    // Permission utilisateur
    PMTVUser_UserProfile* m_userProfile; // Profil utilisateur

public:
    // Constructeur & Destructeur
    PMTVUser_User() {};
    PMTVUser_User(PMTVUser_Permission& p) : m_permission(p) {};
    virtual ~PMTVUser_User() {};

    void setPermission(PMTVUser_Permission& p) { m_permission = p; }
    PMTVUser_Permission getPermission()        { return m_permission; }
};

#endif 
