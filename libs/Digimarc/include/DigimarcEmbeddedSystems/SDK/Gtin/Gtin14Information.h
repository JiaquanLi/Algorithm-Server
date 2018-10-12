// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_GTIN14INFORMATION_H
#define DMRC_DESSDK_GTIN14INFORMATION_H

#include "../ApiDefs.h"
#include "../SimpleProductID/Spid96ExtraDataType.h"
#include "../WatermarkInformation.h"
#include "Sgtin96Information.h"

#include <stdint.h>

namespace DigimarcEmbeddedSystems {

/**
* @brief The Gtin14Information class holds the decoded information from GTIN-14 and related watermarks.
*		This class is passed to the registered @ref DigimarcEmbeddedSystems::Gtin14Callback "Gtin14Callback"
*		and is used for accessing the relevent data (i.e. the GTIN-14 string).
*/
class Gtin14Information : public WatermarkInformation {
public:
	friend class GtinHelper;
	DMRC_API Gtin14Information();

	/**
	 * @returns A string form of the GTIN-14 found in the Watermark.
	 */
	DMRC_API const char* GetGtin14() const;

	/**
	 * @brief A reference to a GtinDataType enum is passed into @ref GetGtinInTruncatedFormat. That function sets the value
	 * of the enum to the data type of the truncated gtin that the function will return.
	 */
	DMRC_API enum GtinDataType {
		GTIN14,
		GTIN13,
		GTIN12,
		GTIN8,
		InvalidType
	};

	/**
	  * @brief This function counts the number of leading zeros in the found Gtin, sets the value of gtinDataType appropriately,
	  *	 		truncates those leading zeros, and returns the resulting string. If the dataType is any other than those available
	  *	 		in GtinDataType, then this function will not truncate any zeros and will return the full gtin, setting the value
	  *	 		of gtinDataType to GtinDataType::InvalidType.
	  *	@returns A string form of the GTIN found in the Watermark, with leading zeros truncated according to gtinDataType.
	  */
	DMRC_API const char* GetGtinInTruncatedFormat(GtinDataType& gtinDataType) const;

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
	 * @returns A pointer to the SGTIN-96 information associated with this GTIN, or NULL if the GTIN is not serialized.
	 */
	DMRC_API const Sgtin96Information* GetSgtin96Information() const;

	/**
	 * See @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString "GetAppIdentifierElementString" for details.
	 */
	DMRC_API const char* GetAppIdentifierElementString() const;

	/**
	 * See @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString(ApplicationIdentifierFormatOptions) const "GetAppIdentifierElementString(...)" for details.
	 */
	DMRC_API const char* GetAppIdentifierElementString(ApplicationIdentifierFormatOptions formatOptions) const;

private:
	char value[15];
	char extraData[16];
	Spid96ExtraDataType extraDataType;
	bool hasSgtin96Information;
	Sgtin96Information sgtin96Information;
};

}

#endif
