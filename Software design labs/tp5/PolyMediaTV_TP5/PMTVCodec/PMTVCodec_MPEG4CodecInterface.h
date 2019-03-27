///////////////////////////////////////////////////////////
//  PMTVCodec_MPEG4CodecInterface.h
//  Implementation of the Class PMTVCodec_MPEG4CodecInterface
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_CODEC_MPEG4_CODEC_INTERFACE_H
#define PMTV_CODEC_MPEG4_CODEC_INTERFACE_H

#include "PMTVCodec_CodecInterface.h"
#include <string>

class PMTVCodec_MPEG4CodecInterface : public PMTVCodec_CodecInterface
{
private:
protected:
public:
    PMTVCodec_MPEG4CodecInterface() : PMTVCodec_CodecInterface()  {};
    ~PMTVCodec_MPEG4CodecInterface() {};

    void loadCodec()   {};
    void unloadCodec() {};

    // Encode / Decode
    void encode(void* rawFrame,size_t rawFrameSize,void** encodedFrame, size_t& encodedFrameSize) {}; // Encode une trame
    
    //-------------------------------------------------------------------------
    // void decode(void* encodedFrame,size_t size,void** decodedFrame, size_t decodedFrameSize)
    //-------------------------------------------------------------------------
    void decode(void* encodedFrame,size_t size,void** decodedFrame, size_t& decodedFrameSize)
    {
        // Si on a reçu une trame encodé
        if(!encodedFrame)
        { return;}

        // Si c'est bien une trame MPEG4 encodée
        if(*((std::string*)encodedFrame) == std::string("ENCODED_MPEG4"))
        {
            *decodedFrame = new std::string("DECODED_MPEG4");
            decodedFrameSize = size; // Conserve le numéro de la trame
        } 
        else // Sinon on ne donne rien
        { *decodedFrame = 0; decodedFrameSize = 0;}
    } 

};

#endif
