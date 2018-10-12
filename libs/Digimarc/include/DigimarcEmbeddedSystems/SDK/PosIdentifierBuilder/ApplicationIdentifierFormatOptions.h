// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2017
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_APPLICATIONIDENTIFIERFORMATOPTIONS_H
#define DMRC_DESSDK_APPLICATIONIDENTIFIERFORMATOPTIONS_H

#include "../../Configuration/StatusCode.h"
#include "../ApiDefs.h"

#include <stdint.h>

namespace DigimarcEmbeddedSystems {

/**
 * @brief Provides a way of setting up and validating a collection of formatting options when calling
 *			@ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString(ApplicationIdentifierFormatOptions) const "GetAppIdentifierElementString(...)".
 *
 *	An example of turning off the default option to include the Digimarc Identifier:
 * @code
ApplicationIdentifierFormatOptions formatOptions;
if(Success == formatOptions.Initialize(formatOptions.COMPATIBILITY_MODE)) {
	watermarkInfo.GetAppIdentifierElementString(formatOptions);
}
 * @endcode
 *
 * @note If the StatusCode returned from @ref ApplicationIdentifierFormatOptions::Initialize "Initialize" is not Success,
 *			then the @ref ApplicationIdentifierFormatOptions::DEFAULT_OPTIONS "DEFAULT_OPTIONS" will be set and the format object is still valid to use.
 */
class ApplicationIdentifierFormatOptions {
public:
	static const uint32_t COMPATIBILITY_MODE = 0;			///< Formats element strings without (240)DWCODEDmnn, to be compatible with standard DataBars.
	static const uint32_t INCLUDE_DIGIMARC_IDENTIFIER = 1 << 0;	///< Append the AI (240)DWCODEDmnn at the end of element strings

	static const uint32_t DEFAULT_OPTIONS = INCLUDE_DIGIMARC_IDENTIFIER;

	/**
	 * @brief Default format options are automatically used for newly created objects.
	 */
	DMRC_API ApplicationIdentifierFormatOptions();

	/**
	 * @brief After creating, the options can be set by constructing a custom set of options.
	 * @param[in] options that you would like to apply
	 * @returns Success if the options pass validation.
	 */
	DMRC_API StatusCode Initialize(uint32_t options);

	/**
	 * @returns the current option bit field.
	 */
	DMRC_API uint32_t GetOptions();

private:
	uint32_t selectedOptions;	///< currently set options
};

}

#endif
