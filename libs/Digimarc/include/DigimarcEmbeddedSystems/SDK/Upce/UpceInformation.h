// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_UPCEINFORMATION_H
#define DMRC_DESSDK_UPCEINFORMATION_H

#include "../ApiDefs.h"
#include "../SimpleProductID/Spid96ExtraDataType.h"
#include "../WatermarkInformation.h"

#include <stdint.h>

namespace DigimarcEmbeddedSystems {

/**
* @brief The UpceInformation class holds the decoded information from UPC-E and related watermarks.
*		This class is passed to the registered @ref DigimarcEmbeddedSystems::UpceCallback "UpceCallback"
*		and is used for accessing the relevent data (i.e. the UPC-E string).
*/
class UpceInformation : public WatermarkInformation {
public:
	friend class UpceHelper;
	DMRC_API UpceInformation();

	/**
	 * @returns A string form of the UPC-E found in the Watermark.
	 */
	DMRC_API const char* GetUpce() const;

	/**
	* @brief This function returns the Simple Product ID 96 extra data, whether it is of type numeric or alpha numeric, or an empty string.
	* @warning in the case of a non-Simple Product ID 96 payload, this will be set to an empty string
	* @returns a null terminated string whose 15 other chars are in the ASCII range for the alpha numeric type (which
	*			is a superset of the range for the numeric type range) described above.
	*/
	DMRC_API const char* GetExtraData() const;

	/**
	* @brief When the payload is of a type called Simple Product ID 96 there can also be 'extra data' that is composed of either 8 alpha-numeric
	*			characters or 15 numeric characters.  If the extra data is numeric, the digits are limited to the range 0-9,
	*			whereas if it is alpha numeric, the characters are limited to the 64 ASCII characters spanning from Space (ASCII 32)
	*			to '_' (ASCII 95).  This includes all nine digits, capital English letters, and some additional symbols.
	* @returns an enumeration that communicates whether the extra data in the decoded payload is of type alpha numeric or numeric.
	*/
	DMRC_API Spid96ExtraDataType GetExtraDataType() const;

	/**
	 * See @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString "GetAppIdentifierElementString" for details.
	 */
	DMRC_API const char* GetAppIdentifierElementString() const;

	/**
	 * See @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString(ApplicationIdentifierFormatOptions) const "GetAppIdentifierElementString(...)" for details.
	 */
	DMRC_API const char* GetAppIdentifierElementString(ApplicationIdentifierFormatOptions formatOptions) const;

private:
	char value[9];
	char extraData[16];
	Spid96ExtraDataType extraDataType;
};

}

#endif
