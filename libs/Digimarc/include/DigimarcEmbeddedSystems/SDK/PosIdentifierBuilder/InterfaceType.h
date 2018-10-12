// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_PROTOCOL_H
#define DMRC_DESSDK_PROTOCOL_H

namespace DigimarcEmbeddedSystems {

enum PosInterfaceType {
	PosInterfaceType_Invalid = -1				///< An invalid POS Protocol
	, PosInterfaceType_None						///< A way to get an undecorated AI string
	, PosInterfaceType_Serial					///< A simple serial implementation
	, PosInterfaceType_IsoIec_15424_Aim			///< ISO/IEC 15424 (commonly called AIM standard)
	, PosInterfaceType_UsbOem					///< USB-OEM
};
}

#endif
