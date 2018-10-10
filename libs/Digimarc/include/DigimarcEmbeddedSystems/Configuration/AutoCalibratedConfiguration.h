// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_AUTOCALIBRATEDCONFIGURATION_H
#define DMRC_DESSDK_AUTOCALIBRATEDCONFIGURATION_H

#include "../SDK/ApiDefs.h"
#include "Configuration.h"

namespace DigimarcEmbeddedSystems {

/** @brief Configures the @ref DigimarcEmbeddedSystems::DigimarcProcessor "DigimarcProcessor" to run with an auto-calibrated configuration.
 * See @ref autoCalibrationPage "Autocalibration" for details.
 *
 * Specifies an auto-calibrating configuration.
 *
 * Also see @ref DigimarcEmbeddedSystems::Configuration "Configuration" base class for additional parameters (i.e. width, height, color settings, etc.).
*/
class AutoCalibratedConfiguration : public Configuration {
public:
	DMRC_API AutoCalibratedConfiguration();
	DMRC_API ~AutoCalibratedConfiguration();

	virtual Configuration *Clone() const;

	virtual StatusCode Configure(ConfigurationTarget& target) const;

	DMRC_API virtual StatusCode Validate() const;

	DMRC_API virtual unsigned int GetNumBlocks() const;

	DMRC_API virtual StatusCode GetBlockDetails(unsigned int index, unsigned int& scale, unsigned int& centerX, unsigned int& centerY, float& tilt, float& bearing) const;

	/** Serialize the auto-calibration data to a string format.
	 *
	 * @return A C-style string representing the auto-calibration data. The string must be deleted with the delete[] operator.
	 */
	DMRC_API char* SerializeToString();

	/** Deserialize the auto-calibration data from a string.
	 *
	 * @param[in] serializedData A string representing auto-calibration data, obtained by a prior call to SerializeToString.
	 * @return Success if deserialization was successful, otherwise an appropriate error.
	 */
	DMRC_API StatusCode DeserializeFromString(const char* serializedData);

	bool enableTrainingMode;					///< If true, train the configuration on subsequent frames.
	unsigned int maxBlocksPerFrame;				///< The maximum number of blocks to process per frame.
	unsigned int blockDistance;					///< Minimum distance between auto-configured blocks
	mutable void* autoCalibrationData;			///< Pointer to internal auto-calibration data. Do not touch.
};

}

#endif
