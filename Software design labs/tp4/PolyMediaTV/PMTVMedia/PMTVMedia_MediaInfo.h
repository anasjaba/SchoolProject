///////////////////////////////////////////////////////////
//  PMTVMedia_MediaInfo.h
//  Implementation of the Class PMTVMedia_MediaInfo
//  Created on:      03-nov.-2010 15:14:30
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_MEDIAINFO_H
#define PMTV_MEDIA_MEDIAINFO_H

#include <string>
#include "PMTVMedia_MediaType.h"

//
// Classe PMTVMedia_MediaInfo
//
// Classe contenant les informations de bases sur les media.
//
// Dérivez de cette classe lorsqu'un nouveau type de media s'ajoute au système.
//
class PMTVMedia_MediaInfo
{
private:
    PMTVMedia_MediaType m_mediaType; // Identification du type de média

public:
    // Constructeur & Destructeur
    PMTVMedia_MediaInfo(PMTVMedia_MediaType mt) : m_mediaType(mt) {};
    virtual ~PMTVMedia_MediaInfo() {};

    // Accesseurs
    PMTVMedia_MediaType getMediaType() { return m_mediaType; }
};

#endif 
