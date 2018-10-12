// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_PAYLOADVERSIONFILTER_H
#define DMRC_DESSDK_PAYLOADVERSIONFILTER_H


#include "ApiDefs.h"
#include "../Configuration/StatusCode.h"
#include "WatermarkInformation.h"
#include "PayloadMetadata.h"

#include <stdint.h>

namespace DigimarcEmbeddedSystems {

class PayloadVersionFilter
{
public:
	DMRC_API PayloadVersionFilter();
	DMRC_API StatusCode Initialize(int Version, int Subtype = -1);

	DMRC_API bool operator==(const PayloadVersionFilter& that) const;
	DMRC_API bool operator!=(const PayloadVersionFilter& that) const;

	DMRC_API int GetPayloadVersion() const;
	DMRC_API int GetPayloadSubtype() const;

	DMRC_API bool IsValid() const;

	DMRC_API StatusCode Match(const WatermarkInformation& Info, const PayloadMetadata* Metadata, void* UserData);

private:
	static const int MIN_VERSION = 0;
	static const int MAX_VERSION = 15;
	static const int MIN_SUBTYPE = -1;

	int version;
	int subtype;

	bool Validate(int Version, int Subtype) const;

};

}
#endif
