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

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
PMTVCodec_CodecFactory::PMTVCodec_CodecFactory()
{}

//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
PMTVCodec_CodecFactory::~PMTVCodec_CodecFactory()
{
    // À compléter...
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createMPEG4Interface()
// Construit et retourne l'interface MPEG4 avec paramètres par défaut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createMPEG4Interface()
{
    // À compléter...
    return 0;
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createIndeoInterface()
// Construit et retourne l'interface INDEO avec paramètres par défaut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createIndeoInterface()
{
    // À compléter...
    return 0;
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createRawDataInterface()
// Construit et retourne l'interface RAW avec paramètres par défaut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createRawDataInterface()
{
    // À compléter...
    return 0;
}

//-----------------------------------------------------------------------------
// bool isCodecSupported(PMTVCodec_InterfaceType interfaceType)
// PMTVCodec_InterfaceType interfaceType : Code du CODEC
// Indique si oui ou non un codec est supporté (lire installé) par PMTV.
//-----------------------------------------------------------------------------
bool PMTVCodec_CodecFactory::isCodecSupported(PMTVCodec_InterfaceType interfaceType)
{
    // À compléter...
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
    return 0;
}

