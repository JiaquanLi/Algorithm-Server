// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_BLOCK_H
#define DMRC_DESSDK_BLOCK_H

#include "../SDK/ApiDefs.h"
#include "PerspectiveParams.h"
#include "DetectionShape.h"
#include "StatusCode.h"

namespace DigimarcEmbeddedSystems {

/** Describes a single block within which the detector will search for Digimarc Barcodes. */
class Block {
public:
	/** Construct a default Block. The default block has position (0, 0), coarse scale 0, and no perspective. */
	DMRC_API Block();

	/** Construct a Block with the provided location and coarse scale with no perspective.
	  * @param[in] centerX The X coordinate of the block center (in image coordinates).
	  * @param[in] centerY The Y coordinate of the block center (in image coordinates).
	  * @param[in] coarseScale The coarse scale of the block.
	  * @param[in] mirrored (optional) Specifies if the image is mirrored.
	  */
	DMRC_API Block(int centerX, int centerY, unsigned int coarseScale, bool mirrored = false);

	/** Construct a Block with the provided location, coarse scale, and perspective.
	  * @param[in] centerX The X coordinate of the block center (in image coordinates).
	  * @param[in] centerY The Y coordinate of the block center (in image coordinates).
	  * @param[in] coarseScale The coarse scale of the block.
	  * @param[in] perspective The perspective parameters of the block.
	  * @param[in] mirrored (optional) Specifies if the image is mirrored.
	  */
	DMRC_API Block(int centerX, int centerY, unsigned int coarseScale, const PerspectiveParams& perspective, bool mirrored = false);

	/** Construct a Block with the provided location, coarse scale, and detection search shape.
	  * @param[in] centerX The X coordinate of the block center (in image coordinates).
	  * @param[in] centerY The Y coordinate of the block center (in image coordinates).
	  * @param[in] coarseScale The coarse scale of the block.
	  * @param[in] detectionShape The parameters that specify the geometry of detection for the block
	  * @param[in] mirrored (optional) Specifies if the image is mirrored.
	  */
	DMRC_API Block(int centerX, int centerY, unsigned int coarseScale, const DetectionShape& detectionShape, bool mirrored = false);

	int centerX;					///< The X coordinate of the block center (in image coordinates).
	int centerY;					///< The Y coordinate of the block center (in image coordinates).
	unsigned int coarseScale;		///< The coarse scale of the block.
	DetectionShape detectionShape;	///< The parameters that specify the geometry of detection for the block
	bool mirrored;					///< The image is mirrored, left <-> right or up <-> down.
	bool enabled;					///< Is the block enabled for processing?
	bool useBlockTrigger;			///< Should the @ref blockTriggerPage "Block Trigger" be used to process this block?
};

//! @cond
namespace Internal {
StatusCode Copy(const Block& src, Block& dst);
}
//! @endcond

}

#endif
