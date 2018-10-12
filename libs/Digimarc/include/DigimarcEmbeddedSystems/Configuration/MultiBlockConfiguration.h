// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_MULTIBLOCKCONFIGURATION_H
#define DMRC_DESSDK_MULTIBLOCKCONFIGURATION_H

#include "../SDK/ApiDefs.h"
#include "Block.h"
#include "Configuration.h"
#include "Handle.h"
#include "SimpleVector.h"

namespace DigimarcEmbeddedSystems {

class ConfigurationTarget;

/** @brief Configures the @ref DigimarcEmbeddedSystems::DigimarcProcessor "DigimarcProcessor" with specified blocks for detection.
 * See @ref blockConfigurationPage "Block Configuration Guidelines" for details.
 *
 * Describes a configuration of one or more fixed blocks.  You will specify the location of these blocks.
 *
 * Also see @ref DigimarcEmbeddedSystems::Configuration "Configuration" base class for additional parameters (i.e. width, height, color settings, etc.).
*/
class MultiBlockConfiguration : public Configuration {
public:
	DMRC_API static const int MAX_BLOCK_SCALE_GRAYSCALE = 6;
	DMRC_API static const int MAX_BLOCK_SCALE_RGB = 6;
	DMRC_API static const int MAX_BLOCK_SCALE_BAYER = 6;
	DMRC_API static const int MAX_BLOCK_SCALE_YUV = 9;

	/** Construct a MultiBlockConfiguration. The configuration has no blocks to start. */
	DMRC_API MultiBlockConfiguration();

	virtual Configuration* Clone() const;

	virtual StatusCode Configure(ConfigurationTarget &target) const;

	/** Validate that all of the Configure object's blocks are within bounds and that
	  * the coarseScale is acceptable for the current pixelFormat.
	  */
	DMRC_API virtual StatusCode Validate() const;

	/** Add a block to the configuration within which the detector will search for Digimarc Barcodes.
	  * @param[in] block The block to add.
	  * @return The handle to the added block, or INVALID_HANDLE if an error occurred.
	  */
	DMRC_API BlockHandle AddBlock(const Block& block);

	/** Get the number of blocks in the configuration.
	  * @return The number of blocks.
	  */
	DMRC_API virtual unsigned int GetNumBlocks() const;

	/** Get a pointer to a block in the config.
	  * @param[in] handle The handle of the block to retrieve.
	  * @return A pointer to the requested block, or NULL if the handle was invalid.
	  */
	DMRC_API Block* GetBlock(BlockHandle handle);

	/** Get a pointer to a block in the config. Const version.
	  * @param[in] handle The handle of the block to retrieve.
	  * @return A pointer to the requested block, or NULL if the handle was invalid.
	  */
	DMRC_API const Block* GetBlock(BlockHandle handle) const;

	/** Enable all blocks for processing (set each block's @ref DigimarcEmbeddedSystems::Block::enabled "enabled" field to true). Unlike other configuration changes,
	 * you do not have to call @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration "UpdateConfiguration" before
	 * the change will take effect. The change is immediate.
	 */
	DMRC_API StatusCode EnableAllBlocks();

	/** Disable all blocks for processing (set each block's @ref DigimarcEmbeddedSystems::Block::enabled "enabled" field to false). Unlike other configuration changes,
	 * you do not have to call @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration "UpdateConfiguration" before
	 * the change will take effect. The change is immediate.
	 */
	DMRC_API StatusCode DisableAllBlocks();

	/** Enable the block trigger on all blocks in the configuration. This is equivalent to setting useBlockTrigger to true for each block. */
	DMRC_API StatusCode SetBlockTriggerOnAllBlocks();

	/** Disable the block trigger on all blocks in the configuration. This is equivalent to setting useBlockTrigger to false for each block. */
	DMRC_API StatusCode ClearBlockTriggerOnAllBlocks();

	/** Set the maximum number of trigger blocks with content to attempt to read on each frame. A value of 0 means to attempt to read all trigger blocks with content. */
	DMRC_API StatusCode SetBlockTriggerMaxBlocksToRead(unsigned int maxBlocksToRead);

	/** Get the maximum number of trigger blocks with content to attempt to read on each frame. */
	DMRC_API unsigned int GetBlockTriggerMaxBlocksToRead() const;

private:
	Internal::SimpleVector<Block> blocks;
	unsigned int blockTriggerMaxBlocksToRead;
};

}

#endif
