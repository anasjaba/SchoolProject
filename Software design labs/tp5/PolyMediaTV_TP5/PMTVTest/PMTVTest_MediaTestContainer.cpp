///////////////////////////////////////////////////////////
//  PMTVTest_MediaTestContainer.cpp
//  Implementation of the Class PMTVTest_MediaTestContainer
//  Created on:      31-oct.-2010 15:03:53
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVTest_MediaTestContainer.h"
#include <sstream>

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
PMTVTest_MediaTestContainer::~PMTVTest_MediaTestContainer()
{
    // Cleanup des trames
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void PMTVTest_MediaTestContainer::initializeMediaTestContainer()
{
    // Construction des trames
    for(int i = 0; i < 10; ++i)
    {
        //std::string frameNumberString;
        //std::stringstream s(i);
        //s >> frameNumberString;
        
        std::string mpeg4Frame("ENCODED_MPEG4");
        std::string indeoFrame("ENCODED_INDEO");
        std::string unknownFrame("ENCODEC_UNKNOWN");

        //mpeg4Frame   += frameNumberString;
        //indeoFrame   += indeoFrame;
        //unknownFrame += unknownFrame;

        m_mpeg4frame[i] = mpeg4Frame;     // Encodage MPEG4
        m_indeoframe[i] = indeoFrame;     // Encodage INDEO
        m_unknownFrame[i] = unknownFrame; // Encodage inconnu
    }
    setNbFrame(10);
}

//-----------------------------------------------------------------------------
// void PMTVTest_MediaTestContainer::extractNextFrame(void** frameBuffer,size_t frameSize)
// frameBuffer : Tampon de la trame extraite
// frameSize   : Taille en octets de la trame
//-----------------------------------------------------------------------------
void PMTVTest_MediaTestContainer::extractNextFrame(void** frameBuffer,size_t& frameSize)
{
    // Pour les tests, simplement extraire la prochaine trame en fonction du pointeur et du codec courant

    // Overflow
    if(m_frameNumber >= 10)
    { *frameBuffer = 0; frameSize = 0; }

    std::string f;

    // Fetch the frame
    if(getCodecCode() == PMTVCODEC_MPEG4)
    { f = m_mpeg4frame[m_frameNumber]; }
    else if(getCodecCode() == PMTVCODEC_INDEO)
    { f = m_indeoframe[m_frameNumber]; }
    else 
    { f = m_unknownFrame[m_frameNumber]; }

    std::string* frame = new std::string(f);

    *frameBuffer = (void*)frame;  // Chaine de caractère avec le bon format
    frameSize    = m_frameNumber; // # de la trame pour les tests aulieu de la taille

    // Next frame
    ++m_frameNumber;
}
