// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_EXPANDEDFRESHCALLBACK_H
#define DMRC_DESSDK_EXPANDEDFRESHCALLBACK_H

namespace DigimarcEmbeddedSystems {

class ExpandedFreshInformation;
class PayloadMetadata;

/** Describes the function pointer type of an Expanded Fresh callback function. */
typedef void (*ExpandedFreshCallback)(const ExpandedFreshInformation& expandedFreshInformation, const PayloadMetadata* payloadMetadata, void* userData);

}

#endif
