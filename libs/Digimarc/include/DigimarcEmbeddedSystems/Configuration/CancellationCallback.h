// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_CANCELLATIONCALLBACK_H
#define DMRC_DESSDK_CANCELLATIONCALLBACK_H

namespace DigimarcEmbeddedSystems {

/** Describes the function pointer type of a cancellation callback function.
 *
 * See @ref DigimarcEmbeddedSystems::Configuration::RegisterCancellationCallback "RegisterCancellationCallback" for details about configuring this callback.
 *
 * @returns true will signal DES to cancel the current detection and return as soon as possible.
*/
typedef bool (*CancellationCallback)(void* userData);

}

#endif
