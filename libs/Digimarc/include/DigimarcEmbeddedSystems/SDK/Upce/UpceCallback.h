// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_UPCECALLBACK_H
#define DMRC_DESSDK_UPCECALLBACK_H

namespace DigimarcEmbeddedSystems {

class UpceInformation;
class PayloadMetadata;

/** Describes the function pointer type of a UPC-E callback function. */
typedef void (*UpceCallback)(const UpceInformation& upceInformation, const PayloadMetadata* payloadMetadata, void* userData);

}

#endif
