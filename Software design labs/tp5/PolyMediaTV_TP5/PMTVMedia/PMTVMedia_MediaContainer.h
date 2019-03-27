///////////////////////////////////////////////////////////
//  PMTVMedia_MediaContainer.h
//  Implementation of the Class PMTVMedia_MediaContainer
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_MEDIA_CONTAINER_H
#define PMTV_MEDIA_MEDIA_CONTAINER_H

#include "PMTVCodec/PMTVCodec_InterfaceType.h"

//
// Classe PMTVMedia_MediaContainer
//
// Classe interface des conteneurs de média.
//
// Regroupe sous une même interface les opérations usuelles réalisées sur les conteneurs
// de média telles que la détermination du codec utilisé, la récupération d'une ou plusieurs trames
// encodées ou encore le nombre de pistes et le type de ces pistes (vidéo, audio, sous-titre).
//
class PMTVMedia_MediaContainer
{
protected:
    // À venir :
    // Regroupé ces paramètres dans la nouvelle entité PMTVMedia_MediaTrack
    PMTVCodec_InterfaceType m_codecCode;  // Code du CODEC utilisé pour les données
    unsigned int m_nbTrack;               // Nombre de pistes
    unsigned int m_resX,m_resY;           // Résolution du vidéo
    double m_videoScale;                  // Mise à l'échelle (4:3, 16:9, 21:11, etc.)
    unsigned int m_nbFrame;               // Nombre de trames

public:
    // Constructeur & Destructeur
    PMTVMedia_MediaContainer()          {};
    virtual ~PMTVMedia_MediaContainer() {};

    // Accesseurs
    PMTVCodec_InterfaceType getCodecCode() { return m_codecCode; }
    unsigned int GetNbTrack()              { return m_nbTrack;   }
    void getMediaResolution(unsigned int& resX,unsigned int& resY) { resX = m_resX; resY = m_resY; }
    unsigned int getNumberOfFrame() { return m_nbFrame; }

    // Opérations sur les trames (Note: Les pistes sont omises pour le moment.)
    virtual void extractNextFrame(void** frameBuffer,size_t& frameSize) = 0; // Extrait la prochaine trame encodées
    virtual void setFrameExtractionPosition(unsigned int frameNumber)   = 0; // Permet l'extraction à partir d'une trame donnée

    // À venir
    // virtual void extractFrame(XYZ);
    // virtual void extractFrame(PMTVMedia_Time& t,unsigned int frame,void** frameData);

};

#endif
