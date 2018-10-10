// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_APPLICATIONIDENTIFIERSTRINGBUILDER_H
#define DMRC_DESSDK_APPLICATIONIDENTIFIERSTRINGBUILDER_H

#include "../ApiDefs.h"
#include "../ExpandedFresh/ExpandedFreshDecodedValues.h"
#include "../SimpleProductID/Spid96ExtraDataType.h"
#include "InterfaceType.h"
#include "ApplicationIdentifierFormatOptions.h"
#include <stdint.h>

namespace DigimarcEmbeddedSystems {

class ExpandedFreshInformation;

/**
 * @brief Constructs an element string based on GS1 standards.
 *			An Application Identifier (App ID or AI) is a standard code that is related to a specifically formatted type of data.
 *			For example, a GTIN-14 has an AI of 01. An element string contains the AI followed by the data, so in the case of GTIN-14 being 12345678901234, the following string is constructed:
 *			'0112345678901234'. This string is often printed for human readability by adding parenthesis around the AI: (01)12345678901234
 */
class ApplicationIdentifierStringBuilder {

public:
	ApplicationIdentifierStringBuilder();
	virtual PosInterfaceType GetBuilderType() const;

	/**
	 * @brief Sets the payload version and subtype. Must be set before calling the various build functions, in order to get the correct information.
	 * @param[in] payloadVersion version of the discovered payload.
	 * @param[in] payloadSubtype subtype of the discovered payload.
	 */
	virtual void SetPayloadVersioning(int payloadVersion, int payloadSubtype);

	virtual void SetFormatOptions(ApplicationIdentifierFormatOptions FormatOptions);

	virtual const char* GetSymbologyIdentifier() const;

	virtual int BuildGtin(const char* GtinValue, char* AppIdString);
	virtual int BuildGtinFromUpce(const char* UpceValue, char* AppIdString);
	virtual int BuildGtinFromUpceWithExtraData(const char* UpceValue, const char* ExtraData, Spid96ExtraDataType ExtraDataType, char* AppIdString);
	virtual int BuildGtinSerialized(const char* GtinValue, const char* SerialNumber, char* AppIdString);
	virtual int BuildGtinWithExtraData(const char* GtinValue, const char* ExtraData, char* AppIdString);
	virtual int BuildGtinSpid96(const char* GtinValue, const char* SpidValue, char* AppIdString);
	virtual int BuildExpandedFresh(ExpandedFreshDecodedValues Decoded, const ExpandedFreshInformation& Information, char* AppIdString);
	virtual int BuildGiai(const char* GiaiValue, char* AppIdString);
	virtual int BuildDigimarcContainer(const unsigned char* payloadBytes, unsigned int numPayloadBytes, char* AppIdString);

protected:
	static int ExpandUpceToGtin(const char* UpceValue, char* AppIdString);

	/**
	 * @brief Addeds the Digimarc data carrier details to AppIdString provided.
	 * @note SetPayloadVersioning sets up the version and subtype values used in this function, needs to be called before the main build... functions.
	 * @param[in,out] AppIdString String that needs the data carrier info added.
	 * @param[in] PrependGroupSeparator is a boolean (false by default) to conditionally add a GROUP_SEPARATOR character before adding the Digimarc Identifier.
	 * @return Number of characters written to the buffer.
	 */
	int AppendDwcodeIdentifier(char* AppIdString, bool PrependGroupSeparator = false);

	int payloadVersion;	///< Set via SetPayloadVersioning and used in AppendDwcodeIdentifier.
	int payloadSubtype;	///< Set via SetPayloadVersioning and used in AppendDwcodeIdentifier.

	ApplicationIdentifierFormatOptions formatOptions;	///< Used when creating strings to decide on optional parts of the format.

	static const uint32_t AI_GTIN = 01;
	static const uint32_t AI_SELLBY = 16;
	static const uint32_t AI_SERIAL_NUMBER = 21;
	static const uint32_t AI_COUNT = 30;
	static const uint32_t AI_MUTUAL_INFORMATION = 90;
	static const uint32_t AI_COMPANY_INTERNAL91 = 91;
	static const uint32_t AI_COMPANY_INTERNAL99 = 99;
	static const uint32_t AI_APPLICATION_IDENTIFIER = 240;
	static const uint32_t AI_CUSTOMER_PART_NUMBER = 241;
	static const uint32_t AI_WEIGHT_KILOS_3_DECIMAL_FRACTION = 3103;
	static const uint32_t AI_WEIGHT_POUNDS_3_DECIMAL_FRACTION = 3203;
	static const uint32_t AI_WEIGHT_KILOS_2_DECIMAL_FRACTION = 3102;
	static const uint32_t AI_WEIGHT_POUNDS_2_DECIMAL_FRACTION = 3202;
	static const uint32_t AI_PRICE = 3922;
	static const uint32_t AI_GIAI = 8004;


															//	 App ID				Length /w AI
	// Fixed length AI's
	static const uint32_t LENGTH_GTIN_14 = 16;				///< AI 01				16
	static const uint32_t LENGTH_SELLBY = 8;				///< AI 16				8
	static const uint32_t LENGTH_WEIGHT_KILOS = 10;			///< AI 3103 or 3102	10
	static const uint32_t LENGTH_WEIGHT_POUNDS = 10;		///< AI 3203 or 3202	10

	// Variable length AI's
	static const uint32_t LENGTH_MAX_SERIAL_NUMBER = 22;			///< AI 21		1 to 20
	static const uint32_t LENGTH_MAX_COUNT = 6;						///< AI 30		var
	static const uint32_t LENGTH_MAX_APPLICATION_IDENTIFIER = 10;	///< AI 240		1 to 30
	static const uint32_t LENGTH_MAX_PRICE = 13;					///< AI 3922	var
	static const uint32_t LENGTH_MAX_GIAI = 34;						///< AI 8004	1 to 30
	static const uint32_t LENGTH_MAX_COMPANY_INTERNAL = 90;			///< AI 91-99	1 TO 90

	// Special characters
	static const char GROUP_SEPARATOR = 0x001D;	///< separator character (FNC1)
};
}

#endif
