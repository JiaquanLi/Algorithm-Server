// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_DIGIMARCPROCESSOR_H
#define DMRC_DESSDK_DIGIMARCPROCESSOR_H

#include "../Configuration/MultiBlockConfiguration.h"
#include "../Configuration/AdaptiveConfiguration.h"
#include "../Configuration/StatusCode.h"
#include "ExpandedFresh/ExpandedFreshCallback.h"
#include "ExpandedFresh/ExpandedFreshInformation.h"
#include "Giai/Giai17Callback.h"
#include "Giai/Giai17Information.h"
#include "Gtin/Gtin14Callback.h"
#include "Gtin/Gtin14Information.h"
#include "NegativeResultCallback.h"
#include "Upce/UpceCallback.h"
#include "Upce/UpceInformation.h"
#include "PayloadVersionFilter.h"
#include "WatermarkCallback.h"

namespace DigimarcEmbeddedSystems {

class Diagnostics;
class DigimarcProcessorImpl;
class DetectionShapeBinaryData;

/** @brief <b>Main interface to the Digimarc Embedded Systems SDK.</b>
 *
 * In order to configure the detector, the DigimarcProcessor interacts with either of two classes, MultiBlockConfiguration
 * and AdaptiveConfiguration.
 *
 * @internal
 * In order to setup the detector behavior in the case of a read, define callback functions that detail the
 * desired behavior and then register these functions with the DigimarcProcessor. You can assign different callback functions to
 * different types of Digimarc Bardcode reads by choosing from the available RegisterCallback functions. The detector, upon
 * reading a Digimarc Barcode, will call every callback function that has been registered as a type that that Digimarc Barcode
 * can be classified as.  For example, a Gtin14 type Digimarc Barcode can be classified as a Gtin14 and also as a Watermark.
 * If you've registered one function with RegisterGtin14Callback and a second with RegisterWatermarkCallback,
 * upon reading this type of mark the detector will call both functions.  If you've only registered one function with
 * RegisterGtin14Callback, than the detector will only call this one function.
 *
 * Furthermore, for a given Digimarc Barcode read, callback functions registered as Upce, Gtin14, or ExpandedFresh will always be
 * called before those registered as Watermark.
 * @endinternal
 *
 * The typical usage of this class is:
 *  1. Construct an instance of DigimarcProcessor.
 *  2. Call Initialize().
 *  3. Add one or more configurations by calling AddMultiBlockConfiguration() or AddAdaptiveConfiguration().
 *  4. Fine-tune the configurations you've added. For details, see MultiBlockConfiguration and AdaptiveConfiguration.
 *  5. Register callbacks of interest by calling one or more of:
 *		* RegisterUpceCallback()
 *		* RegisterExpandedFreshCallback()
 *		* RegisterGtin14Callback()
 *		* RegisterWatermarkCallback()
 *  6. Call UpdateConfiguration() to finalize your configuration data.
 *  7. Call ProcessFrame() repeatedly to look for watermarks in image frames. Handle any callbacks from detected watermarks.
 *  8. Destroy the instance of DigimarcProcessor when finished.
 *
 */
class DigimarcProcessor {
public:
	/** Construct a DigimarcProcessor instance. The instance is not yet initialized, and the Initialize() method
	 * must be called before it can be used.
	 */
	DMRC_API DigimarcProcessor();
	DMRC_API ~DigimarcProcessor();

	/** Initialize the DigimarcProcessor instance. This must be called before any other use of the instance.
	 *
	 * @return @ref Success, or @ref Error_OutOfMemory if not enough memory was available.
	 */
	DMRC_API StatusCode Initialize();

	/** Add a new MultiBlockConfiguration to the instance.
	 *
	 * @param[out] outConfig Receives a pointer to the new MultiBlockConfiguration.
	 * @return @ref Success if the configuration was added, or @ref Error_OutOfMemory if not enough memory was available.
	 */
	DMRC_API StatusCode AddMultiBlockConfiguration(MultiBlockConfiguration** outConfig);

	/** Add a new AdaptiveConfiguration to the instance.
	 *
	 * @param[out] outConfig Receives a pointer to the new AdaptiveConfiguration.
	 * @return @ref Success if the configuration was added, or @ref Error_OutOfMemory if not enough memory was available.
	 */
	DMRC_API StatusCode AddAdaptiveConfiguration(AdaptiveConfiguration** outConfig);

	/** Apply configuration updates. Call this after setting up your configuration(s), and whenever you change a configuration.
	 *
	 * @return @ref Success if the configuration(s) are valid, otherwise a specific error code.
	 */
	DMRC_API StatusCode UpdateConfiguration();

	/** Get the binary data associated with a DetectionShape, so it can be initialized more quickly in the future.
	 *
	 * @param[in] config The configuration to retrieve the binary data from.
	 * @param[in] handle The block handle of the block to retrieve the binary data from.
	 * @param[out] outBinaryData The binary data associated with the block.
	 * @return Success if there is binary data associated with the given config and block, else @ref Error_InvalidParameter.
	 */
	DMRC_API StatusCode GetDetectionShapeBinaryData(MultiBlockConfiguration* config, BlockHandle handle, DetectionShapeBinaryData& outBinaryData);

	/** Process a frame of image data with the current configuration and invoke callbacks for any detected watermarks.
	 *
	 * If you added more than one configuration via calls to AddMultiBlockConfiguration() or AddAdaptiveConfiguration(), the
	 * frames will be dispatched to them in round-robin fashion. For instance, if you've added a MultiBlockConfiguration 'A'
	 * and an AdaptiveConfiguration 'B', then the first call to ProcessFrame() will use configuration 'A', the second call will
	 * use configuration 'B', the third call will use 'A' again, etc.
	 *
	 * @param[in] frameData A pointer to image data.
	 * @param[out] outNumWatermarks Receives the number of watermarks detected in this frame.
	 * @return @ref Success, or @ref Error_OutOfMemory if not enough memory was available.
	 */
	DMRC_API StatusCode ProcessFrame(const void* frameData, unsigned int* outNumWatermarks);

	/** Process a frame of planar image data with the current configuration and invoke callbacks for any detected watermarks.
	 *
	 * If you added more than one configuration via calls to AddMultiBlockConfiguration() or AddAdaptiveConfiguration(), the
	 * frames will be dispatched to them in round-robin fashion. For instance, if you've added a MultiBlockConfiguration 'A'
	 * and an AdaptiveConfiguration 'B', then the first call to ProcessFrame() will use configuration 'A', the second call will
	 * use configuration 'B', the third call will use 'A' again, etc.
	 *
	 * @note: Currently supports planar UV image data (numPlanes = 2)
	 *
	 * @param[in] frameData Array of pointers to image data planes.
	 * @param[in] numPlanes Number of image data planes.
	 * @param[out] outNumWatermarks Receives the number of watermarks detected in this frame.
	 * @return @ref Success, or @ref Error_OutOfMemory if not enough memory was available.
	 */
	DMRC_API StatusCode ProcessFrame(const void** frameData, unsigned int numPlanes, unsigned int* outNumWatermarks);

	/** Invoke callbacks as if a watermark had been detected. The specific version and payload of the watermark is given
	 * in a specially formatted string argument.
	 *
	 * @param[in] payloadString A specially formatted string describing the watermark payload.
	 * @param[in] payloadMetadata Metadata associated with this payload that will be passed to the invoked callbacks.
	 * @return @ref Success, or an error code if payloadString is invalid.
	 */
	DMRC_API StatusCode DispatchPayload(const char* payloadString, const PayloadMetadata* payloadMetadata);

	/** Register a function to be called when UPC-E watermarks are detected.
	 *
	 * The callback function signature must be that of @ref UpceCallback. Three pieces of information will be passed to the
	 * callback:
	 *
	 *  * A const reference to a UpceInformation object which carries the UPC-E data. In the case of a SimpleProductID96 read,
	 *    this object will also hold either numeric or alphanumeric extraData
	 *  * A const pointer to a PayloadMetadata object which, if not NULL, carries additional information about the payload.
	 *  * An arbitrary user pointer, which you can use to pass your own data to the callback.
	 *
	 * To unregister a previously registered callback, pass NULL for both arguments.
	 *
	 * @note Only one callback of each type can be registered at a time. Calling RegisterUpceCallback() twice will replace the existing callback
	 * with the new callback.
	 *
	 * @param[in] callback Function pointer to the UPC-E callback function.
	 * @param[in] userData Pointer to user data to be passed to the callback function.
	 * @return Always returns @ref Success.
	 */
	DMRC_API StatusCode RegisterUpceCallback(UpceCallback callback, void* userData=0);

	/** Register a function to be called when Expanded Fresh watermarks are detected.
	 *
	 * The callback function signature must be that of @ref ExpandedFreshCallback. Three pieces of information will be passed to the
	 * callback:
	 *
	 *  * A const reference to a ExpandedFreshInformation object which carries the Expanded Fresh data.
	 *  * A const pointer to a PayloadMetadata object which, if not NULL, carries additional information about the payload.
	 *  * An arbitrary user pointer, which you can use to pass your own data to the callback.
	 *
	 * To unregister a previously registered callback, pass NULL for both arguments.
	 *
	 * @note Only one callback of each type can be registered at a time. Calling RegisterExpandedFreshCallback() twice will replace the existing callback
	 * with the new callback.
	 *
	 * @param[in] callback Function pointer to the Expanded Fresh callback function.
	 * @param[in] userData Pointer to user data to be passed to the callback function.
	 * @return Always returns @ref Success.
	 */
	DMRC_API StatusCode RegisterExpandedFreshCallback(ExpandedFreshCallback callback, void* userData=0);

	/** Register a function to be called when GIAI-17 watermarks are detected.
	 *
	 * The callback function signature must be that of @ref Giai17Callback. Three pieces of information will be passed to the
	 * callback:
	 *
	 *  * A const reference to a Giai17Information object which carries the GIAI-17 data. This object will hold the 17 digit
	 *  * numeric GIAI data.
	 *  * A const pointer to a PayloadMetadata object which, if not NULL, carries additional information about the payload.
	 *  * An arbitrary user pointer, which you can use to pass your own data to the callback.
	 *
	 * To unregister a previously registered callback, pass NULL for both arguments.
	 *
	 * @note Only one callback of each type can be registered at a time. Calling RegisterGiai17Callback() twice will replace the existing callback
	 * with the new callback.
	 *
	 * @param[in] callback Function pointer to the GIAI-17 callback function.
	 * @param[in] userData Pointer to user data to be passed to the callback function.
	 * @return Always returns @ref Success.
	 */
	DMRC_API StatusCode RegisterGiai17Callback(Giai17Callback callback, void* userData=0);

	/** Register a function to be called when GTIN-14 watermarks are detected.
	 *
	 * The callback function signature must be that of @ref Gtin14Callback. Three pieces of information will be passed to the
	 * callback:
	 *
	 *  * A const reference to a Gtin14Information object which carries the GTIN-14 data. In the case of a SimpleProductID96 read,
	 *    this object will also hold either numeric or alphanumeric extraData
	 *  * A const pointer to a PayloadMetadata object which, if not NULL, carries additional information about the payload.
	 *  * An arbitrary user pointer, which you can use to pass your own data to the callback.
	 *
	 * To unregister a previously registered callback, pass NULL for both arguments.
	 *
	 * @note Only one callback of each type can be registered at a time. Calling RegisterGtin14Callback() twice will replace the existing callback
	 * with the new callback.
	 *
	 * @param[in] callback Function pointer to the GTIN-14 callback function.
	 * @param[in] userData Pointer to user data to be passed to the callback function.
	 * @return Always returns @ref Success.
	 */
	DMRC_API StatusCode RegisterGtin14Callback(Gtin14Callback callback, void* userData=0);

	/** Register a function to be called when a watermark of any type/version is detected.
	 *
	 * The callback function signature must be that of @ref WatermarkCallback. Three pieces of information will be passed to the
	 * callback:
	 *
	 *  * A const reference to a WatermarkInformation object which carries the watermark data.
	 *  * A const pointer to a PayloadMetadata object which, if not NULL, carries additional information about the payload.
	 *  * An arbitrary user pointer, which you can use to pass your own data to the callback.
	 *
	 * To unregister a previously registered callback, pass NULL for both arguments.
	 *
	 * @note Only one callback of each type can be registered at a time. Calling RegisterWatermarkCallback() twice will replace the existing callback
	 * with the new callback.
	 *
	 * @param[in] callback Function pointer to the watermark callback function.
	 * @param[in] userData Pointer to user data to be passed to the callback function.
	 * @return Always returns @ref Success.
	 */
	DMRC_API StatusCode RegisterWatermarkCallback(WatermarkCallback callback, void* userData=0);

	/** Register a function to be called when a watermark matching the @ref PayloadVersionFilter is detected.
	 *
	 * The callback function signature must be that of @ref WatermarkCallback. Three pieces of information will be passed to the
	 * callback:
	 *
	 *  * A const reference to a WatermarkInformation object which carries the watermark data.
	 *  * A const pointer to a PayloadMetadata object which, if not NULL, carries additional information about the payload.
	 *  * An arbitrary user pointer, which you can use to pass your own data to the callback.
	 *
	 * @note Up to 10 unique callbacks can be registered. Callbacks are considered unique when both the filter and callback address are different
	 *			from any other entry in the current list.
	 *
	 * @param[in] callback Function pointer to callback function associated with this filter.
	 * @param[in] filter A filter that must match the detected watermark in order to be reported via callback.
	 * @param[in] userData Pointer to user data to be passed to the callback function.
	 * @return @ref StatusCode.
	 */
	DMRC_API StatusCode RegisterFilteredWatermarkCallback(WatermarkCallback callback, const PayloadVersionFilter& filter, void* userData=0);

	/** Register a function to be called when a watermark IS NOT detected.
	 *
	 * The callback function signature must be that of @ref NegativeResultCallback. Thwo pieces of information will be passed to the
	 * callback:
	 *
	 *  * A const pointer to a PayloadMetadata object which, if not NULL, carries additional information about the attempted decode block.
	 *  * An arbitrary user pointer, which you can use to pass your own data to the callback.
	 *
	 * To unregister a previously registered callback, pass NULL for both arguments.
	 *
	 * @note Only one callback of each type can be registered at a time. Calling RegisterWatermarkCallback() twice will replace the existing callback
	 * with the new callback.
	 *
	 * @warning If this callback is registered, a callback is triggered for every block that does not read in a frame. It is primarily used for off-line analysis
	 * and should not be registered in most situations. If you have any questions, please contact you Digimarc representative.
	 *
	 * @param[in] callback Function pointer to the negative result callback function.
	 * @param[in] userData Pointer to user data to be passed to the callback function.
	 * @return Always returns @ref Success.
	 */
	DMRC_API StatusCode RegisterNegativeResultCallback(NegativeResultCallback callback, void* userData=0);

private:
	DigimarcProcessor(const DigimarcProcessor&);
	DigimarcProcessor& operator=(const DigimarcProcessor&);

	DigimarcProcessorImpl* impl;

	friend class Diagnostics;
};

}

#endif
