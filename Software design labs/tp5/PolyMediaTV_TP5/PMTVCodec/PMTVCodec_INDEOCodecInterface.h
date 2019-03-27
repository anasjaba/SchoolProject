///////////////////////////////////////////////////////////
//  PMTVCodec_INDEOCodecInterface.h
//  Implementation of the Class PMTVCodec_INDEOCodecInterface
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_CODEC_INDEO_CODEC_INTERFACE_H
#define PMTV_CODEC_INDEO_CODEC_INTERFACE_H

#include "PMTVCodec_CodecInterface.h"

class PMTVCodec_INDEOCodecInterface : public PMTVCodec_CodecInterface
{
private:
protected:
public:
    PMTVCodec_INDEOCodecInterface() : PMTVCodec_CodecInterface()  {};
    ~PMTVCodec_INDEOCodecInterface() {};

    void loadCodec()   {};
    void unloadCodec() {};

    // Encode / Decode
    void encode(void* rawFrame,size_t rawFrameSize,void** encodedFrame, size_t& encodedFrameSize) {}; // Encode une trame
    void decode(void* encodedFrame,size_t size,void** decodedFrame, size_t& decodedFrameSize)     
    {
        // Si on a reçu une trame encodé
        if(!encodedFrame)
        { return;}

        // Si c'est bien une trame INDEO encodée
        if(*((std::string*)encodedFrame) == std::string("ENCODED_INDEO"))
        {
            *decodedFrame = new std::string("DECODED_INDEO");
            decodedFrameSize = size; // Conserve le numéro de la trame
        } 
        else // Sinon on ne donne rien
        { *decodedFrame = 0; decodedFrameSize = 0;}    
    } // Decode une trame

};

#endif
