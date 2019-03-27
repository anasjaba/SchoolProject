///////////////////////////////////////////////////////////
//  PMTVMedia_MediaContainer.h
//  Implementation of the Class PMTVMedia_MediaContainer
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_MEDIA_CONTAINER_H
#define PMTV_MEDIA_MEDIA_CONTAINER_H

#include "PMTVCodec/PMTVCodec_InterfaceType.h"

//
// Classe PMTVMedia_MediaContainer
//
// Classe interface des conteneurs de m�dia.
//
// Regroupe sous une m�me interface les op�rations usuelles r�alis�es sur les conteneurs
// de m�dia telles que la d�termination du codec utilis�, la r�cup�ration d'une ou plusieurs trames
// encod�es ou encore le nombre de pistes et le type de ces pistes (vid�o, audio, sous-titre).
//
class PMTVMedia_MediaContainer
{
protected:
    // � venir :
    // Regroup� ces param�tres dans la nouvelle entit� PMTVMedia_MediaTrack
    PMTVCodec_InterfaceType m_codecCode;  // Code du CODEC utilis� pour les donn�es
    unsigned int m_nbTrack;               // Nombre de pistes
    unsigned int m_resX,m_resY;           // R�solution du vid�o
    double m_videoScale;                  // Mise � l'�chelle (4:3, 16:9, 21:11, etc.)
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

    // Op�rations sur les trames (Note: Les pistes sont omises pour le moment.)
    virtual void extractNextFrame(void** frameBuffer,size_t& frameSize) = 0; // Extrait la prochaine trame encod�es
    virtual void setFrameExtractionPosition(unsigned int frameNumber)   = 0; // Permet l'extraction � partir d'une trame donn�e

    // � venir
    // virtual void extractFrame(XYZ);
    // virtual void extractFrame(PMTVMedia_Time& t,unsigned int frame,void** frameData);

};

#endif
