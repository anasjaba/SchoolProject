///////////////////////////////////////////////////////////
//  PMTVCodec_CodecFactory.cpp
//  Implementation of the Class PMTVCodec_CodecFactory
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVCodec_CodecFactory.h"
#include "PMTVCodec_MPEG4CodecInterface.h"
#include "PMTVCodec_INDEOCodecInterface.h"
#include "PMTVCodec_RAWCodecInterface.h"

PMTVCodec_CodecFactory* PMTVCodec_CodecFactory::m_instance = nullptr;

PMTVCodec_CodecFactory* PMTVCodec_CodecFactory::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = new PMTVCodec_CodecFactory();
	}

	return m_instance;
}

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
PMTVCodec_CodecFactory::PMTVCodec_CodecFactory()
{
	m_codecMap[PMTVCODEC_MPEG4] = nullptr;
	m_codecMap[PMTVCODEC_INDEO] = nullptr;
	m_codecMap[PMTVCODEC_RAW] = nullptr;
}

//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
PMTVCodec_CodecFactory::~PMTVCodec_CodecFactory()
{
    // À compléter...
	for (auto& codec : m_codecMap) {
		delete codec.second;
	}
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createMPEG4Interface()
// Construit et retourne l'interface MPEG4 avec paramètres par défaut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createMPEG4Interface()
{
    // À compléter...
	return new PMTVCodec_MPEG4CodecInterface();
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createIndeoInterface()
// Construit et retourne l'interface INDEO avec paramètres par défaut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createIndeoInterface()
{
    // À compléter...
	return new PMTVCodec_INDEOCodecInterface();
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createRawDataInterface()
// Construit et retourne l'interface RAW avec paramètres par défaut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createRawDataInterface()
{
    // À compléter...
	return new PMTVCodec_RAWCodecInterface();
}

//-----------------------------------------------------------------------------
// bool isCodecSupported(PMTVCodec_InterfaceType interfaceType)
// PMTVCodec_InterfaceType interfaceType : Code du CODEC
// Indique si oui ou non un codec est supporté (lire installé) par PMTV.
//-----------------------------------------------------------------------------
bool PMTVCodec_CodecFactory::isCodecSupported(PMTVCodec_InterfaceType interfaceType)
{
	if (m_codecMap.find(interfaceType) != m_codecMap.end()) {
		return true;
	}

    return false;
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::getCodecInterface(PMTVCodec_InterfaceType interfaceType)
// PMTVCodec_InterfaceType interfaceType : 
//
// Récupère l'interface du codec en fonction du type demandé et construit l'interface avec paramètres par défauts
// si elle n'est pas disponible.
// Retourne 0 si l'interface demandée ne peut être construite.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::getCodecInterface(PMTVCodec_InterfaceType interfaceType)
{
    // À compléter...
    // PMTV supporte MPEG4, INDEO et RAW.

	if (m_codecMap.find(interfaceType) != m_codecMap.end()) {
		if (m_codecMap[interfaceType] != nullptr) {
			return m_codecMap[interfaceType];
		}
	}

	if (isCodecSupported(interfaceType)) {
		switch (interfaceType) {
		case PMTVCODEC_MPEG4:
			m_codecMap[interfaceType] = createMPEG4Interface();
			return m_codecMap[interfaceType];
			break;

		case PMTVCODEC_INDEO:
			m_codecMap[interfaceType] = createIndeoInterface();
			return m_codecMap[interfaceType];
			break;

		case PMTVCODEC_RAW:
			m_codecMap[interfaceType] = createRawDataInterface();
			return m_codecMap[interfaceType];
			break;

		}
	}
    return 0;
}

