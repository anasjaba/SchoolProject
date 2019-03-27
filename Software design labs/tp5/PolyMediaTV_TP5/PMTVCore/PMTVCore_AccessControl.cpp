///////////////////////////////////////////////////////////
//  PMTVCore_AccessControl.cpp
//  Implementation of the Class PMTVCore_AccessControl
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVCore_AccessControl.h"
#include "PMTVMedia/PMTVMedia_Media.h"
#include "PMTVMedia/PMTVMedia_MovieInfo.h"
#include "PMTVUser/PMTVUser_User.h"
#include "PMTVUser/PMTVUser_Permission.h"

//-----------------------------------------------------------------------------
// PMTVUser_UserManagement* PMTVCore_AccessControl::getUserManagementInterface()
// Retourne une référence sur l'interface de gestion utilisateur
//-----------------------------------------------------------------------------
PMTVUser_UserManagement* PMTVCore_AccessControl::getUserManagementInterface()
{
    // À compléter...
    return 0;
}

//-----------------------------------------------------------------------------
// PMTVMedia_MediaManager* PMTVCore_AccessControl::getMediaManagerInterface()
// Retourne une référence sur l'interface de gestion de média
//-----------------------------------------------------------------------------
PMTVMedia_MediaManager* PMTVCore_AccessControl::getMediaManagerInterface()
{
    // À compléter...
    return 0;
}


//-----------------------------------------------------------------------------
// void PMTVCore_AccessControl::changeUser(std::string& userName)
// std::string& userName : Change l'utilisateur pour l'utilisateur passé en paramètre
//-----------------------------------------------------------------------------
void PMTVCore_AccessControl::changeUser(std::string& userName)
{
    // À compléter...
}

//-----------------------------------------------------------------------------
// PMTVMedia_Media* PMTVCore_AccessControl::getCurrentMediaPlaying()
// Retourne une référence vers le média jouant présentement 
//-----------------------------------------------------------------------------
PMTVMedia_Media* PMTVCore_AccessControl::getCurrentMediaPlaying()
{
    // À compléter...
    return 0;
}

//-----------------------------------------------------------------------------
// void PMTVCore_AccessControl::playMedia(PMTVMedia_Media* media)
// Joue le média demandé en fonction des permissions utilisateurs
//-----------------------------------------------------------------------------
void PMTVCore_AccessControl::playMedia(PMTVMedia_Media* media)
{
    // À compléter...
    // Récupération de l'information sur le média
    // Test à savoir s'il s'agit d'un film
      // Si oui, récupérer les permissions de l'utilisateur courant
        // Vérifie si l'utilisateur peut regarder le film en fonction du rating
        // Vérifie si l'utilisateur peut regarder en fonction du contenu du film
        // Jouer le film si les permissions le permettent
      // Sinon, ne rien faire du tout.
}
