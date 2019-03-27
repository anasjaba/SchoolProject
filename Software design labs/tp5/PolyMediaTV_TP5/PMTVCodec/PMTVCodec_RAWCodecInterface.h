///////////////////////////////////////////////////////////
//  PMTVCodec_RAWCodecInterface.h
//  Implementation of the Class PMTVCodec_RAWCodecInterface
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_CODEC_RAW_CODEC_INTERFACE_H
#define PMTV_CODEC_RAW_CODEC_INTERFACE_H

#include "PMTVCodec_CodecInterface.h"

//
// Classe PMTVCodec_RAWCodecInterface
//
// Classe interface 
//
class PMTVCodec_RAWCodecInterface : public PMTVCodec_CodecInterface
{
private:
protected:
public:
    // Constructeur & Destructeur
    PMTVCodec_RAWCodecInterface() : PMTVCodec_CodecInterface()  {};
    ~PMTVCodec_RAWCodecInterface() {};

    // Charge / décharge le codec
    void loadCodec()   {};
    void unloadCodec() {};

    // Encode / Decode
    void encode(void* rawFrame,size_t rawFrameSize,void** encodedFrame, size_t& encodedFrameSize) {}; // Encode une trame
    void decode(void* encodedFrame,size_t size,void** decodedFrame, size_t& decodedFrameSize)     {}; // Decode une trame

};

#endif
