///////////////////////////////////////////////////////////
//  PMTVMedia_MovieInfo.h
//  Implementation of the Class PMTVMedia_MovieInfo
//  Created on:      03-nov.-2010 17:14:07
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTVMEDIA_MOVIE_INFO_H
#define PMTVMEDIA_MOVIE_INFO_H

#include "PMTVMedia_MediaInfo.h"
#include "PMTVCore/PMTVCore_Def.h"

#include <list>

//
// Classe PMTVMedia_MovieInfo
//
// Classe contennt les informations relatives à un film.
//
// Ces informations doivent être chargées uniquement au besoin.
//
// Pour l'instant ces informations font partie intégrante de la classe mais il est
// fort possible que celles-ci soient conservés dans une BD interne et que cette classe
// en devienne l'interface.
//
class PMTVMedia_MovieInfo : public PMTVMedia_MediaInfo
{
private:
    std::string m_movieTitle; // Titre du film
    std::list<std::string> m_actorList; // Liste des acteurs/interprètes
    std::string m_director; // Directeur
    std::string m_producer; // Producteur
    std::string m_composer; // Compositeur
    std::list<std::string> m_studioList; // Studio

    PMTVCore_MovieRating m_rating;     // Classification du film
    PMTVCore_MovieTheme m_movieTheme; // Thème principal du film
    std::list<PMTVCore_MovieContent> m_movieContentList; // Identification du contenu du film

    std::string m_movieDescription; // Description du film

public:
    // Constructeur & Destructeur
	PMTVMedia_MovieInfo();
	virtual ~PMTVMedia_MovieInfo();

    // Accesseurs
    std::string getMovieTitle() { return m_movieTitle; }
    std::list<std::string> getActorList() { m_actorList; }
    std::string getDirector() { return m_director; }
    std::string getProducer() { return m_producer; }
    std::string getComposer() { return m_composer; }
    std::list<std::string> getStudioList() { return m_studioList; }
    std::string getMovieDescription() { return m_movieDescription; }

    PMTVCore_MovieRating getMovieRating() { return m_rating; }
    PMTVCore_MovieTheme getMovieTheme() { return m_movieTheme; }

    // Initialisation - Temporaire jusqu'à ce que la BD soit mise sur pied
    void setMovieTitle(std::string movieTitle) { m_movieTitle = movieTitle; }
    void setDirector(std::string director)     { m_director = director;     }
    void setComposer(std::string composer)     { m_composer = composer;     }

    void setMovieTheme(PMTVCore_MovieTheme t)    { m_movieTheme = t;  }
    void setMovieRating(PMTVCore_MovieRating r)  { m_rating = r; }

    void addStudio(std::string studio)        { m_studioList.push_back(studio);   }
    void addContent(PMTVCore_MovieContent mc) { m_movieContentList.push_back(mc); }

    //
    bool containsContent(PMTVCore_MovieContent c);
    bool containsActor(std::string a);
    bool containsStudio(std::string s);
};

#endif
