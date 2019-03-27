///////////////////////////////////////////////////////////
//  PMTVTest_MediaTestContainer.h
//  Implementation of the Class PMTVTest_MediaTestContainer
//  Created on:      31-oct.-2010 15:03:53
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_TEST_MEDIA_TEST_CONTAINER_H
#define PMTV_TEST_MEDIA_TEST_CONTAINER_H

#include "PMTVMedia/PMTVMedia_MediaContainer.h"
#include "PMTVCodec/PMTVCodec_InterfaceType.h"

#include <string>
#include <map>

//
// Classe PMTVTest_MediaTestContainer
//
// Classe stub représentant un conteneur de média.  Celle-ci est 
// utilisée pour tester la mécanique d'extraction en fournissant différentes
// trames encodées ou non.
//
class PMTVTest_MediaTestContainer : public PMTVMedia_MediaContainer
{
private:
    // Tampons de trames tests
    // Les trames ne sont que des chaines de caractères préalloués
    // C'est suffisant pour tester la mécanique d'extraction et de communication
    std::map<unsigned int, std::string> m_mpeg4frame;   // Encodage MPEG4
    std::map<unsigned int, std::string> m_indeoframe;   // Encodage INDEO
    std::map<unsigned int, std::string> m_unknownFrame; // Encodage inconnu

    unsigned int m_frameNumber; // # de la trame

protected:
public:
    // Constructeur & Destructeur
    PMTVTest_MediaTestContainer()   {};
    ~PMTVTest_MediaTestContainer();

    void initializeMediaTestContainer();

    // De PMTVMedia_MediaContainer
    void extractNextFrame(void** frameBuffer,size_t& frameSize); // Extrait la prochaine trame encodées    
    void setFrameExtractionPosition(unsigned int frameNumber) { m_frameNumber = frameNumber; }   // Indique le numéro de la trame à partir de laquelle on extrait

    // Accesseurs pour tests seulement
    void setCodecCode(PMTVCodec_InterfaceType codecCode) { m_codecCode = codecCode; }
    void setNbFrame(unsigned int nbFrame) { m_nbFrame = nbFrame; }
};

#endif
