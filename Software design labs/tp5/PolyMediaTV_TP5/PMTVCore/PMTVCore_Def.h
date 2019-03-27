
#ifndef PMTVCORE_DEF_H
#define PMTVCORE_DEF_H

// Évaluation de film
typedef enum PMTVCore_MovieRating
{
    PMTV_MR_G  = 0, // Général
    PMTV_MR_PG,     // Discrétion des parents
    PMTV_MR_PG_13,  // Discrétion des parents + 13 ans+
    PMTV_MR_R,      // Pas pour enfant
    PMTV_MR_NC_17   // Adulte seulement
} PMTVCoreMovieRating;

// Identificateurs de contenu de films
typedef enum PMTVCore_MovieContent
{
    PMTV_MC_ALCOHOLUSE = 0,
    PMTV_MC_DRUGUSE,
    PMTV_MC_VIOLENCE,
    PMTV_MC_SEX,
    PMTV_MC_GORY_SCENE,
    PMTV_MC_TELETUBBIES
} PMTVCore_MovieContent;

// Thème des films
typedef enum PMTVCore_MovieTheme
{
    PMTV_MT_ACTION = 0,
    PMTV_MT_ADVENTURE,
    PMTV_MT_SCIENCEFICTION,
    PMTV_MT_ROMANCE,
    PMTV_MT_DRAMA,
    PMTV_MT_PORN,
    PMTV_MT_SUPERHERO
} PMTVCore_MovieTheme;

#endif