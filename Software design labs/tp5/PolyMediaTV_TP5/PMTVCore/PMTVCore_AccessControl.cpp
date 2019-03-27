///////////////////////////////////////////////////////////
//  PMTVCore_AccessControl.cpp
//  Implementation of the Class PMTVCore_AccessControl
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#include "PMTVCore_AccessControl.h"
#include "PMTVMedia/PMTVMedia_Media.h"
#include "PMTVMedia/PMTVMedia_MovieInfo.h"
#include "PMTVUser/PMTVUser_User.h"
#include "PMTVUser/PMTVUser_Permission.h"

//-----------------------------------------------------------------------------
// PMTVUser_UserManagement* PMTVCore_AccessControl::getUserManagementInterface()
// Retourne une r�f�rence sur l'interface de gestion utilisateur
//-----------------------------------------------------------------------------
PMTVUser_UserManagement* PMTVCore_AccessControl::getUserManagementInterface()
{
    // � compl�ter...
    return 0;
}

//-----------------------------------------------------------------------------
// PMTVMedia_MediaManager* PMTVCore_AccessControl::getMediaManagerInterface()
// Retourne une r�f�rence sur l'interface de gestion de m�dia
//-----------------------------------------------------------------------------
PMTVMedia_MediaManager* PMTVCore_AccessControl::getMediaManagerInterface()
{
    // � compl�ter...
    return 0;
}


//-----------------------------------------------------------------------------
// void PMTVCore_AccessControl::changeUser(std::string& userName)
// std::string& userName : Change l'utilisateur pour l'utilisateur pass� en param�tre
//-----------------------------------------------------------------------------
void PMTVCore_AccessControl::changeUser(std::string& userName)
{
    // � compl�ter...
}

//-----------------------------------------------------------------------------
// PMTVMedia_Media* PMTVCore_AccessControl::getCurrentMediaPlaying()
// Retourne une r�f�rence vers le m�dia jouant pr�sentement 
//-----------------------------------------------------------------------------
PMTVMedia_Media* PMTVCore_AccessControl::getCurrentMediaPlaying()
{
    // � compl�ter...
    return 0;
}

//-----------------------------------------------------------------------------
// void PMTVCore_AccessControl::playMedia(PMTVMedia_Media* media)
// Joue le m�dia demand� en fonction des permissions utilisateurs
//-----------------------------------------------------------------------------
void PMTVCore_AccessControl::playMedia(PMTVMedia_Media* media)
{
    // � compl�ter...
    // R�cup�ration de l'information sur le m�dia
    // Test � savoir s'il s'agit d'un film
      // Si oui, r�cup�rer les permissions de l'utilisateur courant
        // V�rifie si l'utilisateur peut regarder le film en fonction du rating
        // V�rifie si l'utilisateur peut regarder en fonction du contenu du film
        // Jouer le film si les permissions le permettent
      // Sinon, ne rien faire du tout.
}
