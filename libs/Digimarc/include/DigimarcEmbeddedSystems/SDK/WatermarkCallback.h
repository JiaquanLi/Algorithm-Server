// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_WATERMARKCALLBACK_H
#define DMRC_DESSDK_WATERMARKCALLBACK_H

namespace DigimarcEmbeddedSystems {

class WatermarkInformation;
class PayloadMetadata;

/**
* @brief Describes the function pointer type of a watermark callback function.
*/
typedef void (*WatermarkCallback)(const WatermarkInformation& watermarkInformation, const PayloadMetadata* payloadMetadata, void* userData);

}

#endif
