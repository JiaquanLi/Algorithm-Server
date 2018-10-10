// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_SERIALSTRINGBUILDER_H
#define DMRC_DESSDK_SERIALSTRINGBUILDER_H

#include "ApplicationIdentifierStringBuilder.h"

namespace DigimarcEmbeddedSystems {

class SerialStringBuilder : public ApplicationIdentifierStringBuilder {
public:
	SerialStringBuilder();
	virtual PosInterfaceType GetBuilderType() const;
	virtual const char* GetSymbologyIdentifier() const;

protected:
};
}

#endif
