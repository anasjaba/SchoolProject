///////////////////////////////////////////////////////////
//  PMTVMedia_Movie.h
//  Implementation of the Class PMTVMedia_Movie
//  Created on:      03-nov.-2010 15:15:47
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_MOVIE_H
#define PMTV_MEDIA_MOVIE_H

#include "PMTVMedia_Media.h"
#include "PMTVMedia_MovieInfo.h"
//
// Classe PMTVMedia_Movie
//
// Classe entité représentant un film
//
//
class PMTVMedia_Movie : public PMTVMedia_Media
{
public:
    PMTVMedia_Movie(PMTVMedia_MovieInfo* mi);
	virtual ~PMTVMedia_Movie();

    // Accesseur de l'information sur le film
    PMTVMedia_MovieInfo* getMovieInfo() { return (PMTVMedia_MovieInfo*)m_mediaInfo; }
};

#endif

