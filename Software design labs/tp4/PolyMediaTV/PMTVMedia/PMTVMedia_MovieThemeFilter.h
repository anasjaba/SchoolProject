///////////////////////////////////////////////////////////
//  PMTVMedia_MovieThemeFilter.h
//  Implementation of the Class PMTVMedia_MovieThemeFilter
//  Created on:      06-nov.-2010 18:13:12
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_MOVIE_THEME_FILTER_H
#define PMTV_MEDIA_MOVIE_THEME_FILTER_H

#include "PMTVMedia_MediaFilter.h"
#include "PMTVCore/PMTVCore_Def.h"

class PMTVMedia_MovieThemeFilter : public PMTVMedia_MediaFilter
{
private:
    PMTVCore_MovieTheme m_movieTheme; // Thème à filtrer

public:
    PMTVMedia_MovieThemeFilter(bool negative,PMTVCore_MovieTheme mt) 
        : PMTVMedia_MediaFilter(negative), m_movieTheme(mt) {};
    virtual ~PMTVMedia_MovieThemeFilter() {};

    void setMovieTheme(PMTVCore_MovieTheme mt) { m_movieTheme = mt; }

    // Filtre par thème
    bool isOk(PMTVMedia_Media* media);
};

#endif

