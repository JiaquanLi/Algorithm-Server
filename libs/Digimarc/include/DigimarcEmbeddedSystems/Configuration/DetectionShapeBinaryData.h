#ifndef DMRC_DESSDK_DETECTIONSHAPEBINARYDATA_H
#define DMRC_DESSDK_DETECTIONSHAPEBINARYDATA_H

#include "../SDK/ApiDefs.h"
#include "StatusCode.h"

namespace DigimarcEmbeddedSystems {

/** This class is a container for DetectionShape binary data. It is used to retrieve, and set, the binary data
 * within a DetectionShape.
 *
 * When using the DetectionShape feature, the SDK must initialize certain internal tables according to the settings you have provided. This can be a
 * time consuming operation. The tables are initialized whenever you call @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration
 * "UpdateConfiguration."
 *
 * If you use the SDK by calling @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration "UpdateConfiguration" before every frame,
 * the DetectionShape initialization step can consume too much processing time. The SDK provides a way to obtain the internal tables that are
 * generated during initialization, so you can save them as constant data and pass them directly to the SDK to speed up the initialization step.
 *
 * To do this, first set up the configuration as desired, and call @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration "UpdateConfiguration".
 * Then, make calls to @ref DigimarcEmbeddedSystems::DigimarcProcessor::GetDetectionShapeBinaryData "GetDetectionShapeBinaryData" for each block
 * in the configuration that uses a DetectionShape. The data returned by @ref DigimarcEmbeddedSystems::DigimarcProcessor::GetDetectionShapeBinaryData "GetDetectionShapeBinaryData"
 * can be attached to the DetectionShape objects for future quick initialization.
 *
 * You can generate the tables at run time the first time you call @ref DigimarcEmbeddedSystems::DigimarcProcessor::UpdateConfiguration "UpdateConfiguration",
 * or alternatively you can generate the tables offline and include them in your product as static data.
 *
 * For a usage example, see @ref DetectionShapeQuickInit.cpp .
 *
 * For more assistance using this feature, contact Digimarc.
 *
 * @warning Please heed the note on 4-byte alignment when using SetData(). Failure to do so may result in
 * a runtime alignment exception!
 */
class DetectionShapeBinaryData {
public:
	/** Construct a DetectionShapeBinaryData with empty data (zero length) */
	DMRC_API DetectionShapeBinaryData();

	/** Construct a DetectionShapeBinaryData referring to the same data as binaryData. */
	DMRC_API DetectionShapeBinaryData(const DetectionShapeBinaryData &binaryData);

	DMRC_API ~DetectionShapeBinaryData();

	/** Copy a DetectionShapeBinaryData by referring to the same data as binaryData. */
	DMRC_API DetectionShapeBinaryData& operator=(const DetectionShapeBinaryData& binaryData);

	/** Set the data and data length. The data is pointed to directly -- no copy is made.
	 *
	 * @param[in] data Pointer to the data to use. The data must be at least 4-byte aligned.
	 * @param[in] dataLengthInBytes The length of the data being passed, in bytes.
	 * @warning The data must be at least 4-byte aligned. Failure to do so may result in a runtime alignment exception!
	 */
	DMRC_API void SetData(const void* data, unsigned int dataLengthInBytes);

	/** Get the data length, in bytes. If there is no data, a length of 0 is returned. */
	DMRC_API unsigned int GetDataLengthInBytes() const;

	/** Get a pointer to the data. */
	DMRC_API const unsigned char* GetData() const;

private:
	void SetAllocatedData(const unsigned char* data, unsigned int dataLengthInBytes);

	friend class DigimarcProcessorImpl;

	const unsigned char* data;
	unsigned int dataLengthInBytes;
	bool allocated;
};

}

#endif
