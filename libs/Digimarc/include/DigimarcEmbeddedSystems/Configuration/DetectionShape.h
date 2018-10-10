#ifndef DMRC_DESSDK_DETECTIONSHAPE_H
#define DMRC_DESSDK_DETECTIONSHAPE_H

#include "../SDK/ApiDefs.h"
#include "DetectionShapeBinaryData.h"
#include "PerspectiveParams.h"
#include "StatusCode.h"

namespace DigimarcEmbeddedSystems {

enum DetectionShapeIntensityLevel {
	MediumIntensity
	, HighIntensity
};

/** A geometric characterization of how the detector will search for a mark within the image. A detectionShape represents a "cone" of search parameter
 *  space whose axis is specified by a PerspectiveParams object. The member variables of the DetectionShape can be used to widen or narrow this cone,
 *  or to increase the density of perspective distortions attempted within. Please see @ref detectionShapePage "DetectionShape" for more information.
 */
class DetectionShape {
public:
	/** Constructs a detectionShape object with the provided PerspectiveParams and DetectionShapeIntensityLevel.
	 * @param[in] perspectiveParams With its tilt and bearing, the perspectiveParams object sets the base level perspective transformation, or the
	 * axis of the perspective "cone" defined by the detectionShape. It also sets the focalLength and principalPoint of the image, which will be used
	 * during the perspective correction process.
	 * @param[in] searchIntensity characterizes the properties of the search cone defined by the detectionShape. These include the ranges of tilt and
	 * fineScale used in the search, as well as the number of tilts, fineScales, bearings, and rotations. A higher level of searchIntensity results
	 * in a wider and/or denser cone, which will exhibit better decoding robustness but lower performance. All of these parameters can be fine-tuned
	 * individually as well. Please see @ref detectionShapePage "DetectionShape" for more information.
	 */
	DMRC_API DetectionShape(PerspectiveParams perspectiveParams, DetectionShapeIntensityLevel searchIntensity);

	/** Constructs a DetectionShape object whose members are all set to zero. After using this constructor, set every value manually, including
	 *  the values of the PerspectiveParams member object. Otherwise the detector will ignore DetectionShape when running.
	 */
	DMRC_API DetectionShape();

	/** This provides the DetectionShape with the axis of its transformation cone, the focalLength, and the principalPoint. */
	PerspectiveParams perspective;

	/** Maximum tilt at which the detector will search the image for a mark.
	  * Values are in degrees, and a tilt of zero corresponds to an image plane that is perpendicular to the optical axis.
	  */
	float tiltMax;

	/** Minimum tilt at which the detector will search the image for a mark.
	  * Values are in degrees, and a tilt of zero corresponds to an image plane that is perpendicular to the optical axis.
	  */
	float tiltMin;

	/** The detector will split the range of tilts defined by @ref DigimarcEmbeddedSystems::DetectionShape::tiltMin "tiltMin"
	  * and @ref DigimarcEmbeddedSystems::DetectionShape::tiltMax "tiltMax" into
	  * @ref DigimarcEmbeddedSystems::DetectionShape::numberOfTilts "numberOfTilts" equally spaced tilts,
	  * for every combination of bearing, scale, and rotation.
	  */
	unsigned int numberOfTilts;


	/** Maximum bearing at which the detector will search the image for a mark.
	  * Values are in degrees.
	  */
	float bearingMax;

	/** Minimum bearing at which the detector will search the image for a mark.
	  * Values are in degrees.
	  */
	float bearingMin;

	/** The detector will split the range of bearings defined by @ref DigimarcEmbeddedSystems::DetectionShape::bearingMin "bearingMin"
	  * and @ref DigimarcEmbeddedSystems::DetectionShape::bearingMax "bearingMax" into
	  * @ref DigimarcEmbeddedSystems::DetectionShape::numberOfBearings "numberOfBearings" equally spaced bearings,
	  * for every combination of tilt, scale, and rotation.
	  */
	unsigned int numberOfBearings;

	/** Maximum rotation at which the detector will search the image for a mark. This is an exclusive endpoint.
	  * Values are in degrees. The rotation range, or rotationMax - rotationMin, cannot be less than one.
	  * Note that because the detector takes advantage of a certain symmetry, it only needs 180 degrees of rotation
	  * to cover all possible rotations. Therefore, there is never any reason for the difference between
	  * @ref DigimarcEmbeddedSystems::DetectionShape::rotationMax "rotationMax" and
	  * @ref DigimarcEmbeddedSystems::DetectionShape::rotationMin "rotationMin" to be greater than 180 degrees.
	  */
	float rotationMax;

	/** Minimum rotation at which the detector will search the image for a mark.
	  * Values are in degrees. The rotation range, or rotationMax - rotationMin, cannot be less than one.
	  * Note that because the detector takes advantage of a certain symmetry, it only needs 180 degrees of rotation
	  * to cover all possible rotations. Therefore, there is never any reason for the difference between
	  * @ref DigimarcEmbeddedSystems::DetectionShape::rotationMax "rotationMax" and
	  * @ref DigimarcEmbeddedSystems::DetectionShape::rotationMax "rotationMin" to be greater than 180 degrees.
	  */
	float rotationMin;

	/** Number of rotations at which the detector will search the image for a mark.
	 *  The detector will split the range of rotations defined by @ref DigimarcEmbeddedSystems::DetectionShape::rotationMax "rotationMax"
	 *  and @ref DigimarcEmbeddedSystems::DetectionShape::rotationMin "rotationMin" into equally spaced rotations
	 *  for every combination of tilt, bearing, and scale.
	 */
	unsigned int numberOfRotations;

	/** Minimum finescale at which the detector will search the image for a mark. See @ref fineScalePage "Fine Scale Specification"
	  * for more information about fineScale. This variable is mutually exclusive with the member variable
	  * @ref DigimarcEmbeddedSystems::Configuration::fineScaleStart "fineScaleStart" in the class
	  * @ref DigimarcEmbeddedSystems::Configuration "Configuration". Conceptually they do the same thing, but when
	  * a detectionShape is added to a block, these finescale settings are used in place of the default ones in
	  * @ref DigimarcEmbeddedSystems::Configuration "Configuration", for that particular block. If, for a given block, a detectionShape is
	  * not used, that block will fall back to using the default @ref DigimarcEmbeddedSystems::Configuration::fineScaleStart "fineScaleStart".
	  */
	float finescaleStart;

	/** Minimum finescale at which the detector will search the image for a mark. See @ref fineScalePage "Fine Scale Specification"
	  * for more information about fineScale. This variable is mutually exclusive with the member variable
	  * @ref DigimarcEmbeddedSystems::Configuration::fineScaleStart "fineScaleStart" in the class
	  * @ref DigimarcEmbeddedSystems::Configuration "Configuration". Conceptually they do the same thing, but when
	  * a detectionShape is added to a block, these finescale settings are used in place of the default ones in
	  * @ref DigimarcEmbeddedSystems::Configuration "Configuration", for that particular block. If, for a given block, a detectionShape is
	  * not used, that block will fall back to using the default @ref DigimarcEmbeddedSystems::Configuration::fineScaleStart "fineScaleStart".
	  */
	float finescaleRange;

	/** The detector will split the range of finescales defined by @ref DigimarcEmbeddedSystems::DetectionShape::finescaleStart "finescaleStart"
	  * and @ref DigimarcEmbeddedSystems::DetectionShape::finescaleRange "finescaleRange" into
	  * @ref DigimarcEmbeddedSystems::DetectionShape::numberOfFinescales "numberOfFinescales" equally spaced finescales,
	  * for every combination of tilt, bearing, and rotation.
	  */
	unsigned int numberOfFinescales;

	/** An object for setting precomputed binary data to enable faster initialization. See @ref detectionShapeQuickInitialization
	 * "DetectionShape Quick Initialization" for more information.
	 */
	DetectionShapeBinaryData binaryData;
};

//! @cond
namespace Internal {
StatusCode Copy(const DetectionShape& src, DetectionShape& dst);
}
//! @endcond

}

#endif
