///////////////////////////////////////////////////////////
//  PMTVCore_AccessControl.h
//  Implementation of the Class PMTVCodec_CodecFactory
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#ifndef PMTV_CODEC_CODEC_INTERFACE_H
#define PMTV_CODEC_CODEC_INTERFACE_H

//
// Classe PMTVCodec_CodecInterface
//
// Classe de base pour l'interface unifi�e des codecs.
//
// Le but g�n�ral d'un codec est de d�coder ou d'encoder un flux de donn�es.
// Ce flux est, dans le cas de PMTV, des trames (frames).
//
// Une trame est un tampon de donn�es d'une certaine taille et encod�
// selon un certain algorithme.  Les trames sont extraites des conteneurs
// et donn�es aux d�codeurs lorsque vient le temps d'en faire la visualisation.
// 
//
class PMTVCodec_CodecInterface
{
private:
protected:
public:
    // Constructeur & Destructeur
    PMTVCodec_CodecInterface() {};
    virtual ~PMTVCodec_CodecInterface() {};

    // Charge/d�charge le CODEC (initialisation)
    virtual void loadCodec()   = 0;
    virtual void unloadCodec() = 0;

    // Encodage / d�codage
    virtual void encode(void* rawFrame,size_t rawFrameSize,void** encodedFrame, size_t& encodedFrameSize) = 0; // Encode une trame
    virtual void decode(void* encodedFrame,size_t encodedFrameSize,void** decodedFrame,size_t& decodedFrameSize)  = 0; // Decode une trame

};

#endif
