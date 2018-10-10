// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_AIMSTRINGBUILDER_H
#define DMRC_DESSDK_AIMSTRINGBUILDER_H

#include "ApplicationIdentifierStringBuilder.h"

namespace DigimarcEmbeddedSystems {

class AimStringBuilder : public ApplicationIdentifierStringBuilder {
public:
	AimStringBuilder();
	virtual PosInterfaceType GetBuilderType() const;
	virtual const char* GetSymbologyIdentifier() const;

protected:
};
}

#endif
