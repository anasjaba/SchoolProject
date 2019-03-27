///////////////////////////////////////////////////////////
//  PMTVMedia_LogicFilter.cpp
//  Implementation of the Class PMTVMedia_LogicFilter
//  Created on:      31-oct.-2010 17:38:41
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#include "PMTVMedia_LogicFilter.h"
#include <algorithm>

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::addFilter(PMTVMedia_MediaFilter* f)
// PMTVMedia_MediaFilter* f : Filtre media
// Ajoute un filtre � la liste de filtres
//-----------------------------------------------------------------------------
void PMTVMedia_LogicFilter::addFilter(PMTVMedia_MediaFilter* f)
{
    // � compl�ter...
}

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::removeFilter(PMTVMedia_MediaFilter* f)
// PMTVMedia_MediaFilter* f : Filtre media
// Enl�ve le filtre 'f' de la liste de filtres
//-----------------------------------------------------------------------------
void PMTVMedia_LogicFilter::removeFilter(PMTVMedia_MediaFilter* f)
{
    // � compl�ter...
}

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::clearFilter()
// Vide la liste de filtres
//-----------------------------------------------------------------------------
void PMTVMedia_LogicFilter::clearFilter()
{
    // � compl�ter...
}

//-----------------------------------------------------------------------------
// bool PMTVMedia_LogicFilter::containsFilter(PMTVMedia_MediaFilter* f)
// D�termine si 'f' fait partie de la liste de filtre (recherche r�cursive)
//-----------------------------------------------------------------------------
bool PMTVMedia_LogicFilter::containsFilter(PMTVMedia_MediaFilter* f)
{
    // � compl�ter...
    return false;
}

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::filter(std::list<PMTVMedia_Media*>& mediaList)
// std::list<PMTVMedia_Media*>& mediaList : Liste de media � filtrer
// Filtre la liste de media en utilisant les filtres contenus dans le composite (recursif)
//-----------------------------------------------------------------------------
void PMTVMedia_LogicFilter::filter(std::list<PMTVMedia_Media*>& mediaList)
{
    // � compl�ter...
    // Pour tous les media de la liste
        // Si le media n'est pas ok
            // Retrait du media de la liste
}

//-----------------------------------------------------------------------------
// void PMTVMedia_LogicFilter::isOk(PMTVMedia_Media* media)
// PMTVMedia_Media* media : media � filtrer
// D�termine si 'media' passe le groupe de filtres contenu dans le composite
// Retourne vrai si le media passe les filtres et faux autrement.
//-----------------------------------------------------------------------------
bool PMTVMedia_LogicFilter::isOk(PMTVMedia_Media* media)
{
    // � compl�ter...
    // Initialiser la valeur de retour bool�enne par d�faut en fonction du type and,or
    // Pour tous les filtres media
        // Test si le media passe les filtres en fonction de la relation sp�cifi�e par le filtre (AND,OR)
            // Relation AND
            // Relation OU
    return true;
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

    // Ajoute ce que les enfants poss�dent et ce de mani�re r�cursive
    for(;i!=e;++i)
    { count += (*i)->getNbFilter(); }

    return count;
}

