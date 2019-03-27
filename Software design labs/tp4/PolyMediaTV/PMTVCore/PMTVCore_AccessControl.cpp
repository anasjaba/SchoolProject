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

	// Aller chercher l'utilisateur connect�
	PMTVUser_User* user = m_mainControl->getUserManagementInterface()->getCurrentUser();

	if (user->getPermission().canCreateUser()) {
		return m_mainControl->getUserManagementInterface();
	}

    return 0;
}

//-----------------------------------------------------------------------------
// PMTVMedia_MediaManager* PMTVCore_AccessControl::getMediaManagerInterface()
// Retourne une r�f�rence sur l'interface de gestion de m�dia
//-----------------------------------------------------------------------------
PMTVMedia_MediaManager* PMTVCore_AccessControl::getMediaManagerInterface()
{
    // � compl�ter...
	return m_mainControl->getMediaManagerInterface();
}


//-----------------------------------------------------------------------------
// void PMTVCore_AccessControl::changeUser(std::string& userName)
// std::string& userName : Change l'utilisateur pour l'utilisateur pass� en param�tre
//-----------------------------------------------------------------------------
void PMTVCore_AccessControl::changeUser(std::string& userName)
{
    // � compl�ter...
	m_mainControl->changeUser(userName);
}

//-----------------------------------------------------------------------------
// PMTVMedia_Media* PMTVCore_AccessControl::getCurrentMediaPlaying()
// Retourne une r�f�rence vers le m�dia jouant pr�sentement 
//-----------------------------------------------------------------------------
PMTVMedia_Media* PMTVCore_AccessControl::getCurrentMediaPlaying()
{
    // � compl�ter...
	return m_mainControl->getMediaManagerInterface()->getCurrentMediaPlaying();
}

//-----------------------------------------------------------------------------
// void PMTVCore_AccessControl::playMedia(PMTVMedia_Media* media)
// Joue le m�dia demand� en fonction des permissions utilisateurs
//-----------------------------------------------------------------------------
void PMTVCore_AccessControl::playMedia(PMTVMedia_Media* media)
{
    // � compl�ter...
    // R�cup�ration de l'information sur le m�dia
	PMTVMedia_MediaInfo* mediaInfo = media->getMediaInfo();

    // Test � savoir s'il s'agit d'un film
	if (mediaInfo->getMediaType() != PMTVMEDIATYPE_MOVIE) {
		return;
	}

	// Si oui, r�cup�rer les permissions de l'utilisateur courant
	PMTVUser_Permission permissions = m_mainControl->getUserManagementInterface()->getCurrentUser()->getPermission();

    // V�rifie si l'utilisateur peut regarder le film en fonction du rating
	if (permissions.getRatingRestriction() < ((PMTVMedia_MovieInfo*)mediaInfo)->getMovieRating()) {
		return;
	}

    // V�rifie si l'utilisateur peut regarder en fonction du contenu du film
	for (PMTVCore_MovieContent content : permissions.getContentRestrictionList()) {
		if (((PMTVMedia_MovieInfo*)mediaInfo)->containsContent(content)) {
			return;
		}
	}

    // Jouer le film si les permissions le permettent
	getMediaManagerInterface()->playMedia(media);

}
