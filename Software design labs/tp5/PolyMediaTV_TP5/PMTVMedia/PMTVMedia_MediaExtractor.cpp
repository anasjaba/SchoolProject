///////////////////////////////////////////////////////////
//  PMTVMedia_MediaExtractor.cpp
//  Implementation of the Class PMTVMedia_MediaExtractor
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#include "PMTVMedia_MediaExtractor.h"
#include "PMTVCodec/PMTVCodec_CodecFactory.h"
#include "PMTVCodec/PMTVCodec_CodecInterface.h"

//-----------------------------------------------------------------------------
// std::vector<PMTVMedia_Frame> PMTVMedia_MediaExtractor::extractFrame(unsigned int startFrame,unsigned int endFrame)
// unsigned int startFrame : # trame de d�but
// unsigned int endFrame   : # trame de fin
// std::vector<PMTVMedia_Frame> : Vecteur de trames d�cod�es
// Extrait un certain nombre de trames � partir du conteneur avec le bon d�codeur et retourne
// les trames.
//-----------------------------------------------------------------------------
std::vector<PMTVMedia_Frame> PMTVMedia_MediaExtractor::extractFrame(unsigned int startFrame,unsigned int endFrame)
{
    std::vector<PMTVMedia_Frame> extractedFrame;
    // � compl�ter...
    // RAPPEL : Utilisez la version SINGLETON de l'usine � codecs

    return extractedFrame;
}
