// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_CONFIGURATION_H
#define DMRC_DESSDK_CONFIGURATION_H

#include "../SDK/ApiDefs.h"
#include "CancellationCallback.h"
#include "ColorComponentOrder.h"
#include "ColorWeights.h"
#include "Handle.h"
#include "Key.h"
#include "PixelFormat.h"
#include "StatusCode.h"
#include "WatermarkType.h"

namespace DigimarcEmbeddedSystems {

class ConfigurationTarget;

/** Base class of all configurations. */
class Configuration {
public:
	/** The maximum number of keys that can be added to any single configuration. */
	DMRC_API static const unsigned int MAX_NUM_KEYS = 10;

	/** The minimum fine scale. */
	DMRC_API static const float FINE_SCALE_LOWER_LIMIT;

	/** The maximum fine scale. */
	DMRC_API static const float FINE_SCALE_UPPER_LIMIT;

	DMRC_API virtual ~Configuration();

	/** Clone this configuration as a new object.
	  * @return Pointer to Configuration which is a clone of this one, or NULL if an error occurred (such as out of memory).
	  */
	virtual Configuration* Clone() const = 0;

	/** Pass the configuration to a ConfigurationTarget. This is done polymorphically to resolve the actual configuration
	  * type before passing it to the target.
	  */
	virtual StatusCode Configure(ConfigurationTarget& target) const = 0;

	/** Validate the configuration. */
	DMRC_API virtual StatusCode Validate() const;

	/** Get the total number of blocks in the configuration. */
	DMRC_API virtual unsigned int GetNumBlocks() const = 0;

	/** Add a key. */
	DMRC_API virtual KeyHandle AddKey(const Key& key);

	/** Get the number of keys. */
	DMRC_API virtual unsigned int GetNumKeys() const;

	/** Get a key. */
	DMRC_API virtual const Key& GetKey(KeyHandle handle) const;

	/** Set the details of the frames that are going to be processed.
	 *
	 * @note Correct for a majority of image formats and should be used unless advised otherwise.
	 *
	 * @param[in] format Pixel format (Grayscale, RGB, YUV, etc.).
	 * @param[in] ccOrder Ordering of the pixels, i.e. RGB or BGR.
	 * @param[in] wmType Which type of watermark should be in the image.
	 * @param[in] width Horizontal number of pixels
	 * @param[in] height Vertical number of pixels
	 * @param[in] rowStrideBytes number of bytes between rows. For example, 8-bit grayscale with a width of 4 likely has a stride of 4. 24-bit RGB with a width of 4 likely has a stride of 12.
	 *
	 * @returns StatusCode with Succcess if setup worked.
	 */
	DMRC_API virtual StatusCode SetupFrame(PixelFormat format, ColorComponentOrder ccOrder, WatermarkType wmType, unsigned int width, unsigned int height, int rowStrideBytes);

	/** Set the details of the frames that are going to be processed.
	 *
	 * @warning Should only be used in special cases. Check with your Digimarc representative for further details.
	 *
	 * @param[in] format Pixel format (Grayscale, RGB, YUV, etc.).
	 * @param[in] ccOrder Ordering of the pixels, i.e. RGB or BGR.
	 * @param[in] wmType Which type of watermark should be in the image.
	 * @param[in] width Horizontal number of pixels
	 * @param[in] height Vertical number of pixels
	 * @param[in] rowStrideBytes number of bytes between rows. For example, 8-bit grayscale with a width of 4 likely has a stride of 4. 24-bit RGB with a width of 4 likely has a stride of 12.
	 * @param[in] pixelStrideBytes Talk with Digimarc representative.
	 *
	 * @returns StatusCode with Succcess if setup worked.
	 */
	DMRC_API virtual StatusCode SetupFrame(PixelFormat format, ColorComponentOrder ccOrder, WatermarkType wmType, unsigned int width, unsigned int height, int rowStrideBytes, int pixelStrideBytes);

	/** Register a cancellation callback to be called periodically by the detector.
	 *
	 * @param[in] callback Pointer to a user function to be called periodically to check if detection should be canceled.
	 * @param[in] userData Pointer to user data to be passed to the cancellation callback.
	 * @param[in] cancellableInReadStage True if cancellation should be enabled even in the read stage. Default is false.
	 */
	DMRC_API virtual StatusCode RegisterCancellationCallback(CancellationCallback callback, void* userData, bool cancellableInReadStage=false);

	/** Get the default pixel stride to use for the given pixel format and watermark type. */
	DMRC_API static int GetDefaultPixelStride(PixelFormat format, WatermarkType wmType);

	unsigned int frameWidth;					///< The width of the image that will be processed using this configuration.
	unsigned int frameHeight;					///< The height of the image that will be processed using this configuration.
	int frameStride;							///< The stride of the image that will be processed using this configuration.
	int pixelStride;							///< The stride of each pixel of the image that will be processed using this configuration.
	PixelFormat pixelFormat;					///< The pixel format of the image that will be processed using this configuration.
	ColorWeights colorWeights;					///< The color weights that will be used to convert the image to watermark signal space.
	CancellationCallback cancellationCallback;	///< The cancellation callback. See RegisterCancellationCallback().
	void* cancellationUserData;					///< User data to be passed to the cancellation callback. See RegisterCancellationCallback().
	bool cancellableInReadStage;				///< Enable cancellation even during read stage.
	bool useFineScale;							///< Limit fine scale range?
	float fineScaleStart;						///< The starting point of the fine scale range.
	float fineScaleRange;						///< The size of the fine scale range.
	bool readAllBlocks;							///< Attempt to read all blocks, or just the first one to decode?
	bool enableMessageCorrelationCalculation;	///< Enable @ref DigimarcEmbeddedSystems::PayloadMetadata::messageCorrelation "message correlation" calculation.
												/// To save computation time for decoded results,
												///< the default is not to calculate message correlation.

protected:
	Configuration();

private:
	friend class Diagnostics;

	unsigned int numKeys;
	Key keys[MAX_NUM_KEYS];
	unsigned int special0;
};

}

#endif
