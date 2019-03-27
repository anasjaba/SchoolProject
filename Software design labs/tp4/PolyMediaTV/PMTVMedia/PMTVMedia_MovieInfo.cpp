///////////////////////////////////////////////////////////
//  PMTVMedia_MovieInfo.cpp
//  Implementation of the Class PMTVMedia_MovieInfo
//  Created on:      03-nov.-2010 17:14:08
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVMedia_MovieInfo.h"
#include <algorithm>

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
PMTVMedia_MovieInfo::PMTVMedia_MovieInfo()
: PMTVMedia_MediaInfo(PMTVMEDIATYPE_MOVIE)
{}

//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
PMTVMedia_MovieInfo::~PMTVMedia_MovieInfo()
{}

//-----------------------------------------------------------------------------
// bool PMTVMedia_MovieInfo::containsContent(PMTVCore_MovieContent c)
// PMTVCore_MovieContent c : Drapeau de contenu à trouver
// Retourne la présence (ou non) d'un identificateur de contenu du film
//-----------------------------------------------------------------------------
bool PMTVMedia_MovieInfo::containsContent(PMTVCore_MovieContent c)
{
    std::list<PMTVCore_MovieContent>::iterator f = std::find(m_movieContentList.begin(),m_movieContentList.end(),c);

    if(f != m_movieContentList.end())
    { return true; }
    else
    { return false; }
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
bool PMTVMedia_MovieInfo::containsActor(std::string a)
{
    return false;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
bool PMTVMedia_MovieInfo::containsStudio(std::string s)
{
    return false;
}