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
std::vector<PMTVMedia_Frame> PMTVMedia_MediaExtractor::extractFrame(unsigned int startFrame, unsigned int endFrame)
{
	std::vector<PMTVMedia_Frame> extractedFrame;
	// � compl�ter...
	// RAPPEL : Utilisez la version SINGLETON de l'usine � codecs

	// Si le client inverse les param�tres, on les met comme il faut
	// Mauvais code, mais �a fait partis des requis -_-
	// Pour bien faire on devrait juste envoyer une exception et ne pas corriger unilat�ralement les erreurs de la classe client
	if (startFrame > endFrame) {
		unsigned int tmp = startFrame;
		startFrame = endFrame;
		endFrame = tmp;
	}

	// On s'assure qu'on est pas out of bound
	if (endFrame > m_mediaContainer->getNumberOfFrame()) {
		return extractedFrame;
	}

	auto codecFactory = PMTVCodec_CodecFactory::getInstance();
	auto codec = codecFactory->getCodecInterface(m_mediaContainer->getCodecCode());

	// Si notre codec n'existe pas, on ne fait rien
	if (codec == nullptr) {
		return extractedFrame;
	}

	m_mediaContainer->setFrameExtractionPosition(startFrame);

	for (unsigned int i = startFrame; i <= endFrame; i++)
	{
		// On alloue la m�moire pour extraire le frame
		void* frameBuffer = malloc(endFrame - startFrame);
		size_t extractedFrameSize = 0;
		m_mediaContainer->extractNextFrame(&frameBuffer, extractedFrameSize);

		// ON alloue la m�moir pour d�coder le frame
		void* decodedFrame = malloc(endFrame - startFrame);
		size_t decodedFrameSize = 0;
		codec->decode(frameBuffer, extractedFrameSize, &decodedFrame, decodedFrameSize);

		// On ajoute le frame d�cod�
		extractedFrame.push_back(PMTVMedia_Frame(decodedFrame, decodedFrameSize));
	}

    return extractedFrame;
}
