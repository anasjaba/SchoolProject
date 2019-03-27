///////////////////////////////////////////////////////////
//  PMTVMedia_LogicFilter.h
//  Implementation of the Class PMTVMedia_LogicFilter
//  Created on:      31-oct.-2010 17:38:41
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_LOGIC_FILTER_H
#define PMTV_MEDIA_LOGIC_FILTER_H

class PMTVMedia_Media;

#include "PMTVMedia_MediaFilter.h"
#include <list>

//
// Classe PMTVMedia_LogicFilter
//
// Classe composite regroupant des filtres li�s par une op�ration logique.
//
// L'op�ration logique est sp�cifi�e par param�tre et correspond au sous-ensemble
// {AND,OR}
//
class PMTVMedia_LogicFilter : public PMTVMedia_MediaFilter
{
private:
    bool m_andFilter;      // Indique si c'est un filtre 'AND' et dans le cas contraire 'OR'
    std::list<PMTVMedia_MediaFilter*> m_mediaFilterList; // Liste des filtres en op�ration logiques

public:
    // Constructeur & Destructeur
    PMTVMedia_LogicFilter(bool negative,bool andFilter) : PMTVMedia_MediaFilter(negative), m_andFilter(andFilter) {}
    ~PMTVMedia_LogicFilter() {};
	
    bool isAndFilter() { return m_andFilter; }
    void setAndFilter(bool b) { m_andFilter = b; } // Indique si oui ou non il s'agit d'un filtre AND

    //-----------------------------------
    // Interface du composite
    //-----------------------------------
    bool isComposite() { return true; }

    void filter(std::list<PMTVMedia_Media*>& mediaList); // Filtre le contenu m�dia
    bool isOk(PMTVMedia_Media* media); // Indique si 'media' passe le filtre composite ou non

    void addFilter(PMTVMedia_MediaFilter* f);    // Ajoute un filtre
    void removeFilter(PMTVMedia_MediaFilter* f); // Enl�ve un filtre
    void clearFilter();                     // Vide la liste de filtres
    bool containsFilter(PMTVMedia_MediaFilter* f); // D�termine si le filtre 'f' fait partie des filtres 
    unsigned int getNbFilter();
};

#endif
