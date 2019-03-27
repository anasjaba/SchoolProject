///////////////////////////////////////////////////////////
//  PMTVMedia_LogicFilter.cpp
//  Implementation of the Class PMTVMedia_LogicFilter
//  Created on:      31-oct.-2010 17:38:41
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVMedia_LogicFilter.h"
#include <algorithm>

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::addFilter(PMTVMedia_MediaFilter* f)
// PMTVMedia_MediaFilter* f : Filtre media
// Ajoute un filtre à la liste de filtres
//-----------------------------------------------------------------------------
void PMTVMedia_LogicFilter::addFilter(PMTVMedia_MediaFilter* f)
{
    // À compléter...
	m_mediaFilterList.push_back(f);
}

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::removeFilter(PMTVMedia_MediaFilter* f)
// PMTVMedia_MediaFilter* f : Filtre media
// Enlève le filtre 'f' de la liste de filtres
//-----------------------------------------------------------------------------
void PMTVMedia_LogicFilter::removeFilter(PMTVMedia_MediaFilter* f)
{
    // À compléter...
	m_mediaFilterList.remove(f);
}

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::clearFilter()
// Vide la liste de filtres
//-----------------------------------------------------------------------------
void PMTVMedia_LogicFilter::clearFilter()
{
    // À compléter...
	m_mediaFilterList.clear();
}

//-----------------------------------------------------------------------------
// bool PMTVMedia_LogicFilter::containsFilter(PMTVMedia_MediaFilter* f)
// Détermine si 'f' fait partie de la liste de filtre (recherche récursive)
//-----------------------------------------------------------------------------
bool PMTVMedia_LogicFilter::containsFilter(PMTVMedia_MediaFilter* f)
{
    // À compléter...
	if (f == this) {
		return true;
	}

	for (PMTVMedia_MediaFilter* filter : m_mediaFilterList) {
		if (filter->containsFilter(f)) {
			return true;
		}
	}

    return false;
}

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::filter(std::list<PMTVMedia_Media*>& mediaList)
// std::list<PMTVMedia_Media*>& mediaList : Liste de media à filtrer
// Filtre la liste de media en utilisant les filtres contenus dans le composite (recursif)
//-----------------------------------------------------------------------------
void PMTVMedia_LogicFilter::filter(std::list<PMTVMedia_Media*>& mediaList)
{
    // À compléter...
    // Pour tous les media de la liste
	for (auto i = std::begin(mediaList); i != std::end(mediaList);) {
		if (!isOk(*i)) {
			// Si le media n'est pas ok, retrait du media de la liste
			i = mediaList.erase(i);
		}
		else {
			i++;
		}
	}
}

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::isOk(PMTVMedia_Media* media)
// PMTVMedia_Media* media : media à filtrer
// Détermine si 'media' passe le groupe de filtres contenu dans le composite
// Retourne vrai si le media passe les filtres et faux autrement.
//-----------------------------------------------------------------------------
bool PMTVMedia_LogicFilter::isOk(PMTVMedia_Media* media)
{
    // À compléter...
    // Pour tous les filtres media
	for (PMTVMedia_MediaFilter* filter : m_mediaFilterList) {
		// Test si le media passe les filtres en fonction de la relation spécifiée par le filtre (AND,OR)

		// Relation AND
		if (m_andFilter) {
			if (!filter->isOk(media)) {
				return false;
			}
		}
		// Relation OU
		else {
			if (filter->isOk(media)) {
				return true;
			}
		}
	}
        
	return (m_andFilter) ? true : false;
}

//-----------------------------------------------------------------------------
// unsigned int void PMTVMedia_LogicFilter::getNbFilter()
// Compte et retourne le nombre de filtres contenus dans le composite
//-----------------------------------------------------------------------------
unsigned int PMTVMedia_LogicFilter::getNbFilter()
{
    std::list<PMTVMedia_MediaFilter*>::iterator i = m_mediaFilterList.begin();
    std::list<PMTVMedia_MediaFilter*>::iterator e = m_mediaFilterList.end();

    // Compte d'abord ce que nous avons
    unsigned int count = m_mediaFilterList.size();

    // Ajoute ce que les enfants possèdent et ce de manière récursive
    for(;i!=e;++i)
    { count += (*i)->getNbFilter(); }

    return count;
}

