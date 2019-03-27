///////////////////////////////////////////////////////////
//  PMTVMedia_MovieRatingFilter.h
//  Implementation of the Class PMTVMedia_MovieRatingFilter
//  Created on:      06-nov.-2010 18:13:03
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTVMEDIA_MOVIE_RATING_FILTER_H
#define PMTVMEDIA_MOVIE_RATING_FILTER_H

#include "PMTVMedia_MediaFilter.h"
#include "PMTVCore/PMTVCore_Def.h"

class PMTVMedia_MovieRatingFilter : public PMTVMedia_MediaFilter
{
private:
    PMTVCore_MovieRating m_rating;

public:
    PMTVMedia_MovieRatingFilter(bool negative,PMTVCore_MovieRating rating) 
        : PMTVMedia_MediaFilter(negative),m_rating(rating) {};
    virtual ~PMTVMedia_MovieRatingFilter() {};

    // Filtre par rating
    bool isOk(PMTVMedia_Media* media);
};
#endif

