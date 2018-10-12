// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_GTINCALLBACK_H
#define DMRC_DESSDK_GTINCALLBACK_H

namespace DigimarcEmbeddedSystems {

class Gtin14Information;
class PayloadMetadata;

/** Describes the function pointer type of a GTIN-14 callback function. */
typedef void (*Gtin14Callback)(const Gtin14Information& gtinInformation, const PayloadMetadata* payloadMetadata, void* userData);

}

#endif
