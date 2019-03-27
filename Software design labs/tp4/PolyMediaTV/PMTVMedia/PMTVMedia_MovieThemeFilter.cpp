///////////////////////////////////////////////////////////
//  PMTVMedia_MovieThemeFilter.cpp
//  Implementation of the Class PMTVMedia_MovieThemeFilter
//  Created on:      06-nov.-2010 18:13:12
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#include "PMTVMedia_MovieThemeFilter.h"
#include "PMTVMedia_MovieInfo.h"
#include "PMTVMedia_Movie.h"

//-----------------------------------------------------------------------------
// bool PMTVMedia_MovieThemeFilter::isOk(PMTVMedia_Media* media)
// Test si 'media' a le th�me demand� (ou non si neg est activ�)
//-----------------------------------------------------------------------------
bool PMTVMedia_MovieThemeFilter::isOk(PMTVMedia_Media* media)
{
    PMTVMedia_MediaInfo* mediaInfo = media->getMediaInfo();
    
    // Film?
    if(mediaInfo->getMediaType() == PMTVMEDIATYPE_MOVIE)
    {
        // R�cup�ration du th�me et filtre
        bool ok = ((PMTVMedia_MovieInfo*)mediaInfo)->getMovieTheme() == m_movieTheme;
        if(isNegative())
        { ok = !ok; }
        return ok;
    }
    else // Pas un film on s'en fou
    { return true; }
}
