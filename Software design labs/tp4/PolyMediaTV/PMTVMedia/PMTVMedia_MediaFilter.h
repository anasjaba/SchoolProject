///////////////////////////////////////////////////////////
//  PMTVMedia_MediaFilter.h
//  Implementation of the Class PMTVMedia_MediaFilter
//  Created on:      31-nov.-2010 17:38:33
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_MEDIA_FILTER_H
#define PMTV_MEDIA_MEDIA_FILTER_H

class PMTVMedia_Media;

#include <list>

//
// Classe PMTVMedia_MediaFilter
//
// Classe de base pour les filtres du contenu media.
//
class PMTVMedia_MediaFilter
{
private:
    bool m_negative; // Indique le test inverse

public:
    // Constructeur & Destructeur
    PMTVMedia_MediaFilter(bool negative) : m_negative(negative) {};
    virtual ~PMTVMedia_MediaFilter() {};

    bool isNegative() { return m_negative; }
    void setNegative(bool n) { m_negative = n; }

    virtual bool isComposite() { return false; }

    // Interface Composite
    virtual void filter(std::list<PMTVMedia_Media*>& mediaList) {}; // Filtre un groupe de media
    virtual bool isOk(PMTVMedia_Media* media) = 0; // Determine si oui ou non le media passe le filtre

    virtual void addFilter(PMTVMedia_MediaFilter* f) {};
    virtual void removeFilter(PMTVMedia_MediaFilter* f) {};
    virtual void clearFilter() {};
    virtual bool containsFilter(PMTVMedia_MediaFilter* f) 
    {
        if(f == this) { return true; }
        else { return false; }
    }

    virtual unsigned int getNbFilter() { return 0; }

};
#endif

