///////////////////////////////////////////////////////////
//  PMTVCodec_CodecFactory.h
//  Implementation of the Class PMTVCodec_CodecFactory
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#ifndef PMTV_CODEC_CODEC_FACTORY_H
#define PMTV_CODEC_CODEC_FACTORY_H

class PMTVCodec_CodecInterface;

#include "PMTVCodec_InterfaceType.h"
#include <map>

//
// Classe PMTVCodec_CodecFactory
//
// Construit, initialise et contient les interfaces des encodeurs/d�codeurs
// utilis� par PMTV. (codec)
//
//
class PMTVCodec_CodecFactory
{
private:
    std::map<PMTVCodec_InterfaceType,PMTVCodec_CodecInterface*> m_codecMap; // Map associatif codecCode-Interface Codec
	static PMTVCodec_CodecFactory* m_instance;

protected:
    // M�thodes de construction / initialisation
    PMTVCodec_CodecInterface* createMPEG4Interface();
    PMTVCodec_CodecInterface* createIndeoInterface();
	PMTVCodec_CodecInterface* createRawDataInterface();

	// Constructeur & Destructeur
	PMTVCodec_CodecFactory();
	~PMTVCodec_CodecFactory();

public:
	static PMTVCodec_CodecFactory* getInstance();

    // Accesseurs
    PMTVCodec_CodecInterface* getCodecInterface(PMTVCodec_InterfaceType interfaceType);
    bool isCodecSupported(PMTVCodec_InterfaceType interfaceType);

    // :TEST:
    // NE PAS TOUCHER.
    friend class PMTVTest_MainTest;
};

#endif
