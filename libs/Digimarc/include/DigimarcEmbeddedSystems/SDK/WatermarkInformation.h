// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_WATERMARKINFORMATION_H
#define DMRC_DESSDK_WATERMARKINFORMATION_H

#include "ApiDefs.h"
#include "../Configuration/StatusCode.h"
#include "PosIdentifierBuilder/InterfaceType.h"
#include "PosIdentifierBuilder/StringBuilderFactory.h"

#include <stdint.h>

namespace DigimarcEmbeddedSystems {

class SerialStringBuilder;
class ApplicationIdentifierStringBuilder;

/**
* @brief The WatermarkInformation class holds the decoded information from any watermark.
*		This class is passed to the registered @ref DigimarcEmbeddedSystems::WatermarkCallback "WatermarkCallback"
*		and is used for accessing the relevent data.
*/
class WatermarkInformation {
public:
	DMRC_API WatermarkInformation();
	DMRC_API ~WatermarkInformation();

	DMRC_API StatusCode Initialize(int payloadVersion, int payloadSubtype, const unsigned char* payloadBytes, unsigned int numPayloadBytes);
	DMRC_API int GetPayloadVersion() const;
	DMRC_API int GetPayloadSubtype() const;
	DMRC_API const unsigned char* GetPayloadBytes() const;
	DMRC_API unsigned int GetNumPayloadBytes() const;
	DMRC_API const char* GetPayloadPath() const;

	/**
	 * @brief Identifies this result as originating from a Digimarc Barcode
	 *
	 * @note The Symbology Identifier should be combined with the App Identifier Element String, but positioning depends on protocol
	 *			and is up to integrator to combine strings.
	 *
	 * @param[in] interfaceType denotes which interface the data will be sent out and is used to determin value of the returned string.
	 *
	 * @returns A string for the specified point-of-sale interface.
	 */
	DMRC_API virtual const char* GetSymbologyIdentifier(PosInterfaceType interfaceType) const;

	/**
	 * @brief Overloaded version of @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString(ApplicationIdentifierFormatOptions) const "GetAppIdentifierElementString(...)"
	 *  that uses default format options.
	 *
	 * @note Contents of the returned buffer are valid until the next time this function is called.
	 *
	 * @returns Concatenated set of element strings.
	 */
	DMRC_API virtual const char* GetAppIdentifierElementString() const;

	/**
	 * @brief Constructs a GS1 Application Identifier element string based on values decoded from the payload.
	 *			The element string consists of the AI and the related data field, per GS1 specification.
	 *			Fixed length elements come first, followed by any variable length elements.
	 *			If more than one variable length element string is present, they are separated by a Group Separator character \<GS\>,
	 *			a.k.a Function 1 Symbol Character (FNC1). This is character 29 of the [ISO/IEC 646 standard](https://en.wikipedia.org/wiki/ISO/IEC_646).
	 *
	 * @note Contents of the returned buffer are valid until the next time this function is called.
	 *
	 * @param[in] formatOptions allows @ref DigimarcEmbeddedSystems::ApplicationIdentifierFormatOptions "formatting adjustments".
	 * @returns Concatenated set of element strings.
	 */
	DMRC_API virtual const char* GetAppIdentifierElementString(ApplicationIdentifierFormatOptions formatOptions) const;

protected:
	static const unsigned int MAX_PAYLOAD_PATH_LENGTH = 256;
	static const unsigned int MAX_NUMBER_OF_PAYLOAD_BYTES = 256;

	int payloadVersion;
	int payloadSubtype;
	unsigned char payloadBytes[MAX_NUMBER_OF_PAYLOAD_BYTES];
	unsigned int numPayloadBytes;
	mutable char payloadPath[MAX_PAYLOAD_PATH_LENGTH];

	static const uint32_t MAX_LENGTH_ELEMENT_STRING = 100;
	mutable char elementString[MAX_LENGTH_ELEMENT_STRING];		///< Buffer for holding the element string. Used by subclasses.

	StringBuilderFactory builderFactory;	///< Used for getting the correct AI String Builder for getting the element string and symbology ID.

	/**
	 * @brief Provides a way of getting the correct App ID string builder based on the POS interface.
	 * @param[in] interfaceType specifies the POS interface to use (only matters when getting the symbology identifier).
	 * @returns a pointer to an AI String Builder class.
	 */
	ApplicationIdentifierStringBuilder* GetAppIdentifierBuilder(PosInterfaceType interfaceType) const;
};

}

#endif
