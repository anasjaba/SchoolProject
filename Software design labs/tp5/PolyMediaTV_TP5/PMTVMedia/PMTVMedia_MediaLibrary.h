///////////////////////////////////////////////////////////
//  PMTVMedia_MediaLibrary.h
//  Implementation of the Class PMTVMedia_MediaLibrary
//  Created on:      03-nov.-2010 15:14:16
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_MEDIA_LIBRARY_H
#define PMTV_MEDIA_MEDIA_LIBRARY_H

class PMTVMedia_Media;

#include <list>

class PMTVMedia_MediaLibrary
{
private:
    std::list<PMTVMedia_Media*> m_mediaLibrary;  // Contient les références au contenu media 
public:
    // Constructeur & Destructeur
	PMTVMedia_MediaLibrary();
	virtual ~PMTVMedia_MediaLibrary();

};

#endif
