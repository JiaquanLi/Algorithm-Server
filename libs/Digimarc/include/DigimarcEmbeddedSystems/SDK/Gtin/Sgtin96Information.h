// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_SGTIN96INFORMATION_H
#define DMRC_DESSDK_SGTIN96INFORMATION_H

#include "../ApiDefs.h"

namespace DigimarcEmbeddedSystems {

class Sgtin96Information {
public:
	friend class GtinHelper;
	DMRC_API Sgtin96Information();

	DMRC_API const char* GetCompanyPrefix() const;
	DMRC_API const char* GetItemReference() const;
	DMRC_API const char* GetSerialNumber() const;
	DMRC_API char GetIndicatorDigit() const;
	DMRC_API int GetFilterValue() const;

private:
	char companyPrefix[13];
	char itemReference[7];
	char serialNumber[13];
	char indicatorDigit;
	int filterValue;
};

}

#endif
