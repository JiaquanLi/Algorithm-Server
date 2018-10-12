// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_STATUSCODE_H
#define DMRC_DESSDK_STATUSCODE_H

namespace DigimarcEmbeddedSystems {

/** Status codes. */
enum StatusCode {
	Success
	, Error_Internal
	, Error_NotInitialized
	, Error_AlreadyInitialized
	, Error_InvalidParameter
	, Error_InvalidKey
	, Error_OutOfBounds
	, Error_DetectionShapeRotationRange
	, Error_OutOfRangeFineScale
	, Error_OutOfRangeTilt				///< The tilt of a DetectionShape or PerspectiveParams is out of the legal range.
	, Error_OutOfRangeBearing			///< The bearing of a PerspectiveParams is out of the legal range.
	, Error_OutOfRangeFocalLength		///< The focal length of a PerspectiveParams is out of the legal range.
	, Error_OutOfMemory
	, Error_Unsupported
	, Error_Canceled
	, Error_AdaptiveRegionTooSmall
	, Error_TooManyDistinctPayloads		///< There were too many distinct payloads in a single frame during auto-calibration.
	, Error_NothingFound				///< No payload was found when one was expected.
};

}

#endif
