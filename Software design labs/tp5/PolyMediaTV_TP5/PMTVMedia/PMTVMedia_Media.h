///////////////////////////////////////////////////////////
//  PMTVMedia_Media.h
//  Implementation of the Class PMTVMedia_Media
//  Created on:      03-nov.-2010 15:14:23
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_H
#define PMTV_MEDIA_H

#include "PMTVMedia_MediaInfo.h"

//
// Classe PMTVMedia_Media
//
// Classe de base pour tous les media utilisés dans le système.
//
class PMTVMedia_Media
{
protected:
    PMTVMedia_MediaInfo* m_mediaInfo; // Référence vers l'entité d'information sur le media

public:
    // Constructeur & Destructeur
    PMTVMedia_Media(PMTVMedia_MediaInfo* mi) : m_mediaInfo(mi) {};
    virtual ~PMTVMedia_Media() { delete m_mediaInfo; }
	
    PMTVMedia_MediaInfo* getMediaInfo() { return m_mediaInfo; }

private:
    PMTVMedia_Media() : m_mediaInfo(0) {};
};

#endif
