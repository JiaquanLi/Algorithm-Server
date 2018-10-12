// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_GIAICALLBACK_H
#define DMRC_DESSDK_GIAICALLBACK_H

namespace DigimarcEmbeddedSystems {

class Giai17Information;
class PayloadMetadata;

/** Describes the function pointer type of a GIAI-17 callback function. */
typedef void (*Giai17Callback)(const Giai17Information& giaiInformation, const PayloadMetadata* payloadMetadata, void* userData);

}

#endif
