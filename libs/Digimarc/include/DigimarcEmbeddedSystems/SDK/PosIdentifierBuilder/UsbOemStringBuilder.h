// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_USBOEMSTRINGBUILDER_H
#define DMRC_DESSDK_USBOEMSTRINGBUILDER_H

#include "ApplicationIdentifierStringBuilder.h"

namespace DigimarcEmbeddedSystems {

class UsbOemStringBuilder : public ApplicationIdentifierStringBuilder {
public:
	UsbOemStringBuilder();
	virtual PosInterfaceType GetBuilderType() const;
	virtual const char* GetSymbologyIdentifier() const;
};
}

#endif
