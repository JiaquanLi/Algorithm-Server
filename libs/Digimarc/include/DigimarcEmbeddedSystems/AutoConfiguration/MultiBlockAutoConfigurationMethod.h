// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2017
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_MULTIBLOCKAUTOCONFIGURATIONMETHOD_H
#define DMRC_DESSDK_MULTIBLOCKAUTOCONFIGURATIONMETHOD_H

#include "../SDK/ApiDefs.h"
#include "../Configuration/AdaptiveConfiguration.h"
#include "../Configuration/MultiBlockConfiguration.h"

namespace DigimarcEmbeddedSystems {

class Diagnostics;

/** This class implements the autoconfiguration algorithm for a multiblock configuration. */
class MultiBlockAutoConfigurationMethod {
public:
	DMRC_API MultiBlockAutoConfigurationMethod();
	DMRC_API ~MultiBlockAutoConfigurationMethod();

	/** Initialize the autoconfiguration method. You can request a maximum number of blocks to configure, as well as a time limit
	 * for the autoconfiguration process. Once you've called this, call Train() to actually train the blocks.
	 *
	 * @param[in] format The pixel format of the image.
	 * @param[in] ccOrder The color component order of the image.
	 * @param[in] wmType The watermark type of the image.
	 * @param[in] basePerspective The base perspective of the camera. Only the focal length and principal point must be filled in.
	 * @param[in] numBlocks The maximum number of blocks to select.
	 * @param[in] width The width of the image in pixels.
	 * @param[in] height The height of the image in pixels.
	 * @param[in] stride The stride of the image in bytes.
	 */
	DMRC_API StatusCode Initialize(PixelFormat format, ColorComponentOrder ccOrder, WatermarkType wmType, const PerspectiveParams& basePerspective, unsigned int numBlocks, unsigned int width, unsigned int height, int stride);

	/** Execute the training algorithm on the provided image data. After this, call GetTrainedMultiBlockConfiguration() or GetTrainedAdaptiveConfiguration()
	 * to get the resulting configuration.
	 */
	DMRC_API StatusCode Train(const void* frameData);

	/** Get the trained configuration as a MultiBlockConfiguration.
	 *
	 * @param[out] outConfig A MultiBlockConfiguration which will receive the blocks.
	 */
	DMRC_API StatusCode GetTrainedMultiBlockConfiguration(MultiBlockConfiguration& outConfig);

	/** Set the adaptive table and mean.
	 *
	 * @param[in] table Pointer to table of 32-bit integers
	 * @param[in] mean Mean value of table
	 */
	DMRC_API StatusCode SetAdaptiveTable(const void* table, int mean);

	/** Get the trained configuration as an AdaptiveConfiguration
	 *
	 * @param[out] outConfig An AdaptiveConfiguration which will receive the blocks.
	 */
	DMRC_API StatusCode GetTrainedAdaptiveConfiguration(AdaptiveConfiguration& outConfig);

private:
	friend class Diagnostics;

	void* impl;
};

}

#endif
