///////////////////////////////////////////////////////////
//  PMTVMedia_Frame.h
//  Implementation of the Class PMTVMedia_MediaContainer
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_FRAME_H
#define PMTV_MEDIA_FRAME_H

//
//
// Classe contenant les données d'une trame.
//
//
//
class PMTVMedia_Frame
{
private:
    void* m_frameData;  // Pointeur vers les données
    size_t m_frameSize; // Taille en octets des données de la trame

protected:
public:
    // Constructeur & Destructeur
    PMTVMedia_Frame(void* frameData, size_t frameSize) : m_frameData(frameData), m_frameSize(frameSize) {};
    PMTVMedia_Frame() : m_frameData(0), m_frameSize(0) {};
    ~PMTVMedia_Frame() {}

    // Accesseurs
    void* getFrameData()  { return m_frameData; }
    size_t getFrameSize() { return m_frameSize; }
};

#endif

