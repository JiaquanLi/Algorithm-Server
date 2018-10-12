// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_PERSPECTIVEPARAMS_H
#define DMRC_DESSDK_PERSPECTIVEPARAMS_H

#include "../SDK/ApiDefs.h"
#include "StatusCode.h"

namespace DigimarcEmbeddedSystems {

/** Describes the perspective correction parameters for a Block or Region. See @ref perspectiveCorrectionPage "Perspective Correction" for more details.*/
class PerspectiveParams {
public:
	/** Construct a default PerspectiveParams with no perspective (tilt 0). */
	DMRC_API PerspectiveParams();

	/** Construct a PerspectiveParams with the provided parameters. */
	DMRC_API PerspectiveParams(float tilt, float bearing, float focalLengthX, float focalLengthY, float cameraPrincipalPointX, float cameraPrincipalPointY);

	/** Validate the parameters. Valid tilts are between 0deg (inclusive) to 90deg (exclusive).
	 * Valid bearings are between -360deg (exclusive) and 360deg (exclusive).
	 * Valid focal lengths are positive.
	 * All values of camera principal point are valid.
	 */
	DMRC_API StatusCode Validate() const;

	float tilt;
	float bearing;
	float focalLengthX;
	float focalLengthY;
	float cameraPrincipalPointX;
	float cameraPrincipalPointY;
};

//! @cond
namespace Internal {
StatusCode Copy(const PerspectiveParams& src, PerspectiveParams& dst);
}
//! @endcond

}

#endif
