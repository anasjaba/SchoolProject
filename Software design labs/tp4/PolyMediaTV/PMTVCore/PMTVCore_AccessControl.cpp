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

	// Aller chercher l'utilisateur connecté
	PMTVUser_User* user = m_mainControl->getUserManagementInterface()->getCurrentUser();

	if (user->getPermission().canCreateUser()) {
		return m_mainControl->getUserManagementInterface();
	}

    return 0;
}

//-----------------------------------------------------------------------------
// PMTVMedia_MediaManager* PMTVCore_AccessControl::getMediaManagerInterface()
// Retourne une référence sur l'interface de gestion de média
//-----------------------------------------------------------------------------
PMTVMedia_MediaManager* PMTVCore_AccessControl::getMediaManagerInterface()
{
    // À compléter...
	return m_mainControl->getMediaManagerInterface();
}


//-----------------------------------------------------------------------------
// void PMTVCore_AccessControl::changeUser(std::string& userName)
// std::string& userName : Change l'utilisateur pour l'utilisateur passé en paramètre
//-----------------------------------------------------------------------------
void PMTVCore_AccessControl::changeUser(std::string& userName)
{
    // À compléter...
	m_mainControl->changeUser(userName);
}

//-----------------------------------------------------------------------------
// PMTVMedia_Media* PMTVCore_AccessControl::getCurrentMediaPlaying()
// Retourne une référence vers le média jouant présentement 
//-----------------------------------------------------------------------------
PMTVMedia_Media* PMTVCore_AccessControl::getCurrentMediaPlaying()
{
    // À compléter...
	return m_mainControl->getMediaManagerInterface()->getCurrentMediaPlaying();
}

//-----------------------------------------------------------------------------
// void PMTVCore_AccessControl::playMedia(PMTVMedia_Media* media)
// Joue le média demandé en fonction des permissions utilisateurs
//-----------------------------------------------------------------------------
void PMTVCore_AccessControl::playMedia(PMTVMedia_Media* media)
{
    // À compléter...
    // Récupération de l'information sur le média
	PMTVMedia_MediaInfo* mediaInfo = media->getMediaInfo();

    // Test à savoir s'il s'agit d'un film
	if (mediaInfo->getMediaType() != PMTVMEDIATYPE_MOVIE) {
		return;
	}

	// Si oui, récupérer les permissions de l'utilisateur courant
	PMTVUser_Permission permissions = m_mainControl->getUserManagementInterface()->getCurrentUser()->getPermission();

    // Vérifie si l'utilisateur peut regarder le film en fonction du rating
	if (permissions.getRatingRestriction() < ((PMTVMedia_MovieInfo*)mediaInfo)->getMovieRating()) {
		return;
	}

    // Vérifie si l'utilisateur peut regarder en fonction du contenu du film
	for (PMTVCore_MovieContent content : permissions.getContentRestrictionList()) {
		if (((PMTVMedia_MovieInfo*)mediaInfo)->containsContent(content)) {
			return;
		}
	}

    // Jouer le film si les permissions le permettent
	getMediaManagerInterface()->playMedia(media);

}
