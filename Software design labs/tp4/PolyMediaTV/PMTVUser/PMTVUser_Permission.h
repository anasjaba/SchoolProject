///////////////////////////////////////////////////////////
//  PMTVUser_Permission.h
//  Implementation of the Class PMTVUser_Permission
//  Created on:      31-oct.-2010 16:09:13
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTVUSER_PERMISSION_H
#define PMTVUSER_PERMISSION_H

#include "PMTVCore/PMTVCore_Def.h"
#include <list>

class PMTVUser_Permission
{
private:
    bool m_movieStoreAccess;        // Détermine si on peut accéder au magasin en ligne ou non
    bool m_userCreationRestriction; // Indique si peut créer des utilisateurs

    PMTVCore_MovieRating m_ratingRestriction; // Limite par évaluation
    std::list<PMTVCore_MovieContent> m_contentRestriction; // Liste de restriction par thème

public:
    // Constructeur & Destructeur
	PMTVUser_Permission();
	virtual ~PMTVUser_Permission();

    // Restriction par évaluation
    void setRatingRestriction(PMTVCore_MovieRating mr) { m_ratingRestriction = mr;   }
    PMTVCore_MovieRating getRatingRestriction()        { return m_ratingRestriction; }

    // Restriction du magasin
    void setMovieStoreAccess(bool l)  { m_movieStoreAccess = l; }
    bool getMovieStoreAccess() { return m_movieStoreAccess; }

    // Restriction par contenu
    void clearContentRestrictionList()                   { m_contentRestriction.clear();    }
    void addContentRestriction(PMTVCore_MovieContent mc) { m_contentRestriction.push_back(mc); }
    void removeContentRestriction(PMTVCore_MovieContent mc); 
    std::list<PMTVCore_MovieContent> getContentRestrictionList() { return m_contentRestriction; }

    // Restriction création utilisateur
    bool canCreateUser()       { return m_userCreationRestriction; }
    void setCreateUser(bool b) { m_userCreationRestriction = b;    }
};

#endif 
