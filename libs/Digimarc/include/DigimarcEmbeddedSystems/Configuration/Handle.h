// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_HANDLE_H
#define DMRC_DESSDK_HANDLE_H

namespace DigimarcEmbeddedSystems {

/** A handle to a block within a configuration. */
typedef unsigned int BlockHandle;

/** A handle to a region within an adaptive configuration. */
typedef unsigned int AdaptiveRegionHandle;

/** A handle to an adaptive perspective within an adaptive region. */
typedef unsigned int AdaptivePerspectiveHandle;

/** A handle to a configuration. */
typedef unsigned int ConfigurationHandle;

/** A handle to a key. */
typedef unsigned int KeyHandle;

/** Represents an invalid handle to a block, region, or configuration. */
const unsigned int INVALID_HANDLE = 0;

}

#endif
