// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2017
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_NEGATIVERESULTCALLBACK_H
#define DMRC_DESSDK_NEGATIVERESULTCALLBACK_H

namespace DigimarcEmbeddedSystems {

class PayloadMetadata;

/**
* @brief Describes the function pointer type of a negative result callback function.
*/
typedef void (*NegativeResultCallback)(const PayloadMetadata* payloadMetadata, void* userData);

}

#endif

