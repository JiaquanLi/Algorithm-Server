// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_GIAI17INFORMATION_H
#define DMRC_DESSDK_GIAI17INFORMATION_H

#include "../ApiDefs.h"
#include "../WatermarkInformation.h"

#include <stdint.h>

/**
* @brief The Giai17Information class holds the decoded information from GIAI-17 and related watermarks.
*		This class is passed to the registered @ref DigimarcEmbeddedSystems::Giai17Callback "Giai17Callback"
*		and is used for accessing the relevent data (i.e. the GIAI-17 string).
*/
namespace DigimarcEmbeddedSystems {

class Giai17Information : public WatermarkInformation {
public:
	friend class GiaiHelper;
	DMRC_API Giai17Information();

	/**
	 * @returns A string that holds the full 17 digits of numeric information found in the Watermark.
	 */
	DMRC_API const char* Get17DigitNumericData() const;

	/**
	 * @returns A string that holds the left zero-padded 8 digit Company Prefix found in the Watermark.
	 */
	DMRC_API const char* Get8DigitCompanyPrefix() const;

	/**
	 * @returns A string that holds the 9 digit Asset ID found in the Watermark.
	 */
	DMRC_API const char* Get9DigitAssetID() const;

	/**
	 * See @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString "GetAppIdentifierElementString" for details.
	 */
	DMRC_API const char* GetAppIdentifierElementString() const;

	/**
	 * See @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString(ApplicationIdentifierFormatOptions) const "GetAppIdentifierElementString(...)" for details.
	 */
	DMRC_API const char* GetAppIdentifierElementString(ApplicationIdentifierFormatOptions formatOptions) const;

private:
	char fullNumericData[18];
	char companyPrefix[9];
	char assetID[10];
};


}


#endif
