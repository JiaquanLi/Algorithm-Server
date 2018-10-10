// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_KEY_H
#define DMRC_DESSDK_KEY_H

#include "../SDK/ApiDefs.h"

namespace DigimarcEmbeddedSystems {

class Key {
public:
	DMRC_API static const unsigned int MAX_KEY_LENGTH = 136;

	unsigned char bytes[MAX_KEY_LENGTH];
	unsigned int length;
};

}

#endif
