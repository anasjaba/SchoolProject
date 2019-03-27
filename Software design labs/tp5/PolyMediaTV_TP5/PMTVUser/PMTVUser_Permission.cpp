///////////////////////////////////////////////////////////
//  PMTVUser_Permission.cpp
//  Implementation of the Class PMTVUser_Permission
//  Created on:      31-oct.-2010 16:09:13
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVUser_Permission.h"
#include <algorithm>

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
PMTVUser_Permission::PMTVUser_Permission()
: m_movieStoreAccess(false), m_userCreationRestriction(false)
{}

//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
PMTVUser_Permission::~PMTVUser_Permission() {}

//-----------------------------------------------------------------------------
// void PMTVUser_Permission::removeContentRestriction(PMTVCore_MovieContent& mc)
// PMTVCore_MovieContent& mc : Identificateur de contenu à retirer
// Cherche dans la liste si le contenu s'y retrouve et si oui le retirer.
//-----------------------------------------------------------------------------
void PMTVUser_Permission::removeContentRestriction(PMTVCore_MovieContent mc)
{
    std::list<PMTVCore_MovieContent>::iterator f;    
    f = std::find(m_contentRestriction.begin(),m_contentRestriction.end(),mc);

    if(f != m_contentRestriction.end())
    { m_contentRestriction.remove(mc); }
}
