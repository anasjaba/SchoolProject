///////////////////////////////////////////////////////////
//  PMTVMedia_MovieRatingFilter.cpp
//  Implementation of the Class PMTVMedia_MovieRatingFilter
//  Created on:      06-nov.-2010 18:13:04
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#include "PMTVMedia_MovieRatingFilter.h"

#include "PMTVMedia_Movie.h"
#include "PMTVMedia_MovieInfo.h"

//-----------------------------------------------------------------------------
// bool PMTVMedia_MovieRatingFilter::isOk(PMTVMedia_Media* media)
// Test si 'media' a le rating demand� (ou non si neg est activ�)
//-----------------------------------------------------------------------------
bool PMTVMedia_MovieRatingFilter::isOk(PMTVMedia_Media* media)
{
    PMTVMedia_MediaInfo* mediaInfo = media->getMediaInfo();
    
    // Film?
    if(mediaInfo->getMediaType() == PMTVMEDIATYPE_MOVIE)
    {
        // R�cup�ration du rating et filtre
        bool ok = ((PMTVMedia_MovieInfo*)mediaInfo)->getMovieRating() == m_rating;
        if(isNegative())
        { ok = !ok; }
        return ok;
    }
    else // Pas un film on s'en fou
    { return true; }
}