// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_ADAPTIVECONFIGURATION_H
#define DMRC_DESSDK_ADAPTIVECONFIGURATION_H

#include "../SDK/ApiDefs.h"
#include "AdaptiveRegion.h"
#include "Configuration.h"
#include "SimpleVector.h"

namespace DigimarcEmbeddedSystems {

class ConfigurationTarget;

/** @brief Configures the @ref DigimarcEmbeddedSystems::DigimarcProcessor "DigimarcProcessor" for automatic block placement and detection. See @ref adaptiveConfigurationPage for conceptual details.
 *
 * @note Adaptive configurations only works with Grayscale images currently.
 *
 * Describes regions of the frame, within which the detector will calculate block position. A frame can contain multiple regions,
 * each uniquely configured by creating and adding an @ref DigimarcEmbeddedSystems::AdaptiveRegion "AdaptiveRegion".
 *
 * Also see @ref DigimarcEmbeddedSystems::Configuration "Configuration" base class for additional parameters (i.e. width, height, color settings, etc.).
*/
class AdaptiveConfiguration : public Configuration {
public:
	/** Construct a default adaptive configuration. All fields will be zero and must be initialized before use. */
	DMRC_API AdaptiveConfiguration();

	virtual Configuration* Clone() const;

	virtual StatusCode Configure(ConfigurationTarget &target) const;

	DMRC_API virtual StatusCode Validate() const;

	DMRC_API virtual unsigned int GetNumBlocks() const;

	/** Add an adaptive region to the configuration. This is the larger area within which the detector will choose Block locations.
	  * @param[in] region The adaptive region to add.
	  * @return The handle to the added adaptive region, or INVALID_HANDLE if an error occurred.
	  */
	DMRC_API AdaptiveRegionHandle AddRegion(const AdaptiveRegion& region);

	/** Get the number of adaptive regions in the configuration.
	  * @return The number of adaptive regions.
	  */
	DMRC_API unsigned int GetNumRegions() const;

	/** Get a pointer to an adaptive region in the config.
	  * @param[in] handle The handle of the adaptive region to retrieve. The handle must be valid, or undefined behavior results.
	  * @return A pointer to the requested adaptive region.
	  */
	DMRC_API AdaptiveRegion* GetRegion(AdaptiveRegionHandle handle);

	/** Get a pointer to an adaptive region in the config, const version.
	  * @param[in] handle The handle of the adaptive region to retrieve. The handle must be valid, or undefined behavior results.
	  * @return A pointer to the requested adaptive region.
	  */
	DMRC_API const AdaptiveRegion* GetRegion(AdaptiveRegionHandle handle) const;

	/** Enable all static blocks in all regions for processing (set each block's enable field to true). Unlike other configuration changes,
	 * you do not have to call @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration "UpdateConfiguration" before
	 * the change will take effect. The change is immediate.
	 */
	DMRC_API StatusCode EnableAllStaticBlocks();

	/** Disable all static blocks in all regions for processing (set each block's enable field to false). Unlike other configuration changes,
	 * you do not have to call @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration "UpdateConfiguration" before
	 * the change will take effect. The change is immediate.
	 */
	DMRC_API StatusCode DisableAllStaticBlocks();


	float adaptiveThreshold;				///< Threshold for adaptive processing.

	/**
	 * @brief The maximum number of blocks processed per frame across all regions, and including both static and adaptive blocks.
	 *		The total number of blocks per frame is calculated in the following way:
	 *
	 *		@b maxBlocksPerFrame = sum of each (region * number of perspectives in that region) + number of static blocks
	 *
	 *	- By default, the value is zero (0), meaning run all blocks.
	 *	- Can be set to a value less than @ref GetNumBlocks() to reduce per-frame processing time.
	 *	- This value can be updated during run time. The new value will take effect after a call to @ref DigimarcProcessor::UpdateConfiguration().
	 */
	unsigned int maxBlocksPerFrame;

private:
	AdaptiveConfiguration(const AdaptiveConfiguration&);
	AdaptiveConfiguration& operator=(const AdaptiveConfiguration&);

	StatusCode ValidateRegion(const AdaptiveRegion& region) const;

	Internal::SimpleVector<AdaptiveRegion> regions;
};

}

#endif
