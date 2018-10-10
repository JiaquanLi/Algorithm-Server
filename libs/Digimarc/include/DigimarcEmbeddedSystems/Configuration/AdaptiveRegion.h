// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -


#ifndef DMRC_DESSDK_ADAPTIVEREGION_H
#define DMRC_DESSDK_ADAPTIVEREGION_H

#include "../SDK/ApiDefs.h"
#include "Block.h"
#include "Handle.h"
#include "PerspectiveParams.h"
#include "StatusCode.h"

namespace DigimarcEmbeddedSystems {
class AdaptiveRegion;
//! @cond
namespace Internal {
StatusCode Copy(const AdaptiveRegion& src, AdaptiveRegion& dst);
}
//! @endcond
}

#include "SimpleVector.h"

namespace DigimarcEmbeddedSystems {

/** @brief A subsection of the frame that guides the @ref DigimarcEmbeddedSystems::DigimarcProcessor "DigimarcProcessor" for @ref adaptiveConfigurationPage.
 *
 * A region is a bounding box within a frame, where the @ref DigimarcEmbeddedSystems::DigimarcProcessor "DigimarcProcessor"
 * will calculate the most probable location to place a block for a successful detection. When creating a region, you can specify the minimum and maximum number of blocks
 * that will be placed within. For instance, a minimum of one and maximum of three will make sure that at least one adaptive block will be attempted
 * and up to three blocks may be attempted as long as they meet the @ref DigimarcEmbeddedSystems::AdaptiveConfiguration::adaptiveThreshold "probability threshold".
 *
 * @note A static block can be added and will take priority over any adaptive blocks. This can be helpful for creating a known fallback location, allowing you to set minimum adaptive blocks to zero.
 *
 * For more information about creating an adaptive block strategy, see @ref adaptiveConfigurationPage.
*/
class AdaptiveRegion {
public:
	/** Construct a default AdaptiveRegion. All values are initialized to 0/false. */
	DMRC_API AdaptiveRegion();

	/** Construct a AdaptiveRegion with the provided values.
	  * @param[in] upperLeftX The X coordinate of the upper left corner of the region (in image coordinates).
	  * @param[in] upperLeftY The Y coordinate of the upper left corner of the region (in image coordinates).
	  * @param[in] width The width of the region (in image coordinates).
	  * @param[in] height The height of the region (in image coordinates).
	  * @param[in] coarseScale The coarse scale of blocks in the region.
	  * @param[in] minAdaptiveBlocks Minimum number of adaptive blocks in the region.
	  * @param[in] maxAdaptiveBlocks Maximum number of adaptive blocks in the region.
	  */
	DMRC_API AdaptiveRegion(int upperLeftX, int upperLeftY, unsigned int width, unsigned int height, unsigned int coarseScale, unsigned int minAdaptiveBlocks, unsigned int maxAdaptiveBlocks);

	/** Add a static block to the configuration at the given location.
	  * @param[in] centerX The X coordinate of the block center (in image coordinates).
	  * @param[in] centerY The Y coordinate of the block center (in image coordinates).
	  * @return The handle to the added block, or INVALID_HANDLE if an error occurred.
	  */
	DMRC_API BlockHandle AddStaticBlock(int centerX, int centerY);

	/** Add a static block to the configuration at the given location.
	  * @param[in] centerX The X coordinate of the block center (in image coordinates).
	  * @param[in] centerY The Y coordinate of the block center (in image coordinates).
	  * @param[in] perspective The perspective parameters of the block.
	  */
	DMRC_API BlockHandle AddStaticBlock(int centerX, int centerY, const PerspectiveParams& perspective);

	/** Add a static block to the configuration at the given location.
	  * @param[in] centerX The X coordinate of the block center (in image coordinates).
	  * @param[in] centerY The Y coordinate of the block center (in image coordinates).
	  * @param[in] detectionShape The detection shape parameters of the block.
	  */
	DMRC_API BlockHandle AddStaticBlock(int centerX, int centerY, const DetectionShape& detectionShape);

	/** Get the number of static blocks. */
	DMRC_API unsigned int GetNumStaticBlocks() const;

	/** Get a pointer to a static block in the config.
	  * @param[in] handle The handle of the static block to retrieve.
	  * @return A pointer to the requested static block, or NULL if the handle was invalid.
	  */
	DMRC_API Block* GetStaticBlock(BlockHandle handle);

	/** Get a pointer to a static block in the config, const version.
	  * @param[in] handle The handle of the static block to retrieve.
	  * @return A pointer to the requested static block, or NULL if the handle was invalid.
	  */
	DMRC_API const Block* GetStaticBlock(BlockHandle handle) const;

	/** Enable non-perspective-corrected adaptive blocks in this region.
	  * @return The handle to the adaptive perspective, or INVALID_HANDLE if an error occurred.
	  */
	DMRC_API AdaptivePerspectiveHandle AddAdaptivePerspectiveUncorrected();

	/** Enable perspective correction of blocks in this region with the given perspective parameters.
	  * @param[in] perspective The perspective parameters.
	  * @return The handle to the adaptive perspective, or INVALID_HANDLE if an error occurred.
	  */
	DMRC_API AdaptivePerspectiveHandle AddAdaptivePerspective(const PerspectiveParams& perspective);

	/** Get the number of adaptive perspectives. */
	DMRC_API unsigned int GetNumAdaptivePerspectives() const;

	/** Get a pointer to the perspective parameters of the given adaptive perspective.
	  * @param[in] handle The handle of the adaptive perspective.
	  * @return A pointer to the PerspectiveParams of the requested adaptive perspective, or NULL if the handle was invalid.
	  */
	DMRC_API PerspectiveParams* GetAdaptivePerspective(AdaptivePerspectiveHandle handle);

	/** Get a pointer to the perspective parameters of the given adaptive perspective, const version.
	  * @param[in] handle The handle of the adaptive perspective.
	  * @return A pointer to the PerspectiveParams of the requested adaptive perspective, or NULL if the handle was invalid.
	  */
	DMRC_API const PerspectiveParams* GetAdaptivePerspective(AdaptivePerspectiveHandle handle) const;

	/** Enable detection search shape of blocks in this region with the given detection shape parameters.
	  * @param[in] detectionShape The detectionShape itself holds a PerspectiveParams, so this method also increments the
	  * number of PerspectiveParams, which means that calling this prior to calling GetNumAdaptivePerspectives() will increase
	  * the return value of that function by one.
	  * @return The handle to the adaptive detection shape, or INVALID_HANDLE if an error occurred. This handle can also be used
	  * to access the PerspectiveParams that is added implicitly along with the DetectionShape.
	  */
	DMRC_API AdaptivePerspectiveHandle AddAdaptiveDetectionShape(const DetectionShape& detectionShape);

	/** Get the number of adaptive detection shapes.*/
	DMRC_API unsigned int GetNumAdaptiveDetectionShapes() const;

	/** Get a pointer to the detection shape parameters of the given adaptive detection shape.
	  * @param[in] handle The handle of the adaptive detection shape.
	  * @return A pointer to the PerspectiveParams of the requested adaptive perspective, or NULL if the handle was invalid.
	  */
	DMRC_API DetectionShape* GetAdaptiveDetectionShape(AdaptivePerspectiveHandle handle);

	/** Get a pointer to the perspective parameters of the given adaptive perspective, const version.
	  * @param[in] handle The handle of the adaptive perspective.
	  * @return A pointer to the PerspectiveParams of the requested adaptive perspective, or NULL if the handle was invalid.
	  */
	DMRC_API const DetectionShape* GetAdaptiveDetectionShape(AdaptivePerspectiveHandle handle) const;

	/** Enable all static blocks in this region for processing (set each block's enable field to true). Unlike other configuration changes,
	 * you do not have to call @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration "UpdateConfiguration" before
	 * the change will take effect. The change is immediate.
	 */
	DMRC_API StatusCode EnableAllStaticBlocks();

	/** Disable all static blocks in this region for processing (set each block's enable field to false). Unlike other configuration changes,
	 * you do not have to call @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration "UpdateConfiguration" before
	 * the change will take effect. The change is immediate.
	 */
	DMRC_API StatusCode DisableAllStaticBlocks();


	//! @cond
	StatusCode CopyTo(AdaptiveRegion& dst) const;
	//! @endcond

	int upperLeftX;							///< The X coordinate of the upper left corner of the region (in image coordinates).
	int upperLeftY;							///< The Y coordinate of the upper left corner of the region (in image coordinates).
	unsigned int width;						///< The width of the region (in image coordinates).
	unsigned int height;					///< The height of the region (in image coordinates).
	unsigned int coarseScale;				///< The coarse scale of blocks in the region.
	bool mirrored;							///< Indicates that the region is a mirror image.
	unsigned int minAdaptiveBlocks;			///< Minimum number of adaptive blocks to process in the region.
	unsigned int maxAdaptiveBlocks;			///< Maximum number of adaptive blocks to process in the region.
	int logRegressMean;						///< The mean value of logistic regression table.
	const void* logRegressTable;			///< The logistic regression table.

private:
	AdaptiveRegion(const AdaptiveRegion&);
	AdaptiveRegion& operator=(const AdaptiveRegion&);

	Internal::SimpleVector<Block> staticBlocks;
	Internal::SimpleVector<DetectionShape> adaptiveBlockDetectionShapes;
};

//! @cond
namespace Internal {
StatusCode Copy(const AdaptiveRegion& src, AdaptiveRegion& dst);
}
//! @endcond

}

#endif
