///////////////////////////////////////////////////////////
//  PMTVCodec_CodecFactory.cpp
//  Implementation of the Class PMTVCodec_CodecFactory
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dub�
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
    // � compl�ter...
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createMPEG4Interface()
// Construit et retourne l'interface MPEG4 avec param�tres par d�faut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createMPEG4Interface()
{
    // � compl�ter...
    return 0;
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createIndeoInterface()
// Construit et retourne l'interface INDEO avec param�tres par d�faut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createIndeoInterface()
{
    // � compl�ter...
    return 0;
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createRawDataInterface()
// Construit et retourne l'interface RAW avec param�tres par d�faut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createRawDataInterface()
{
    // � compl�ter...
    return 0;
}

//-----------------------------------------------------------------------------
// bool isCodecSupported(PMTVCodec_InterfaceType interfaceType)
// PMTVCodec_InterfaceType interfaceType : Code du CODEC
// Indique si oui ou non un codec est support� (lire install�) par PMTV.
//-----------------------------------------------------------------------------
bool PMTVCodec_CodecFactory::isCodecSupported(PMTVCodec_InterfaceType interfaceType)
{
    // � compl�ter...
    return false;
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::getCodecInterface(PMTVCodec_InterfaceType interfaceType)
// PMTVCodec_InterfaceType interfaceType : 
//
// R�cup�re l'interface du codec en fonction du type demand� et construit l'interface avec param�tres par d�fauts
// si elle n'est pas disponible.
// Retourne 0 si l'interface demand�e ne peut �tre construite.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::getCodecInterface(PMTVCodec_InterfaceType interfaceType)
{
    // � compl�ter...
    // PMTV supporte MPEG4, INDEO et RAW.
    return 0;
}

