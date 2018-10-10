// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_COLORWEIGHTS_H
#define DMRC_DESSDK_COLORWEIGHTS_H

#include "../SDK/ApiDefs.h"
#include "ColorComponentOrder.h"
#include "PixelFormat.h"
#include "StatusCode.h"
#include "WatermarkType.h"

namespace DigimarcEmbeddedSystems {

/** Container for color weights. The primary public function in this class is SetStandardWeights().*/
class ColorWeights {
public:
	/** Describes the type of weights. */
	enum Type {
		Grayscale,			///< There is a single weight.
		RGB,				///< The weights are RGB weights.
		UV					///< The weights are UV weights.
	};

	DMRC_API ColorWeights();

	/** Calculate the proper weighting to give each color channel in order to maximize reading ability.
	  * %Information about the pixel format and the embedding type of the Digimarc Barcode are both used in the calculation.
	  * Out of the functions in this class, this is the one that is of primary interest to almost all users.
	  * Configuration::SetupFrame will call this function to set the color channel weightings.
	  * @param[in] format The pixel format of the image data
	  * @param[in] ccOrder The ordering within memory of the different colored pixels
	  * @param[in] wmType The expected embedding type used to embed the Digimarc Barcode
	  * @return Success or Error_InvalidParameter
	  */
	DMRC_API StatusCode SetStandardWeights(PixelFormat format, ColorComponentOrder ccOrder, WatermarkType wmType);

	/** Construct a ColorWeights for Grayscale with the given weight. */
	DMRC_API static ColorWeights ForGrayscale(int grayQ0_15, int offset);

	/** Construct a ColorWeights for RGB with the given weights. */
	DMRC_API static ColorWeights ForRGB(int redQ0_15, int greenQ0_15, int blueQ0_15, int offset);

	/** Construct a ColorWeights for UV with the given weights. */
	DMRC_API static ColorWeights ForUV(int uQ0_15, int vQ0_15, int offset);

	Type type;				///< The type of weights (RGB or UV)
	int weight[3];			///< The weights.
	int offset;				///< The offset to add after applying the weights.
};

}

#endif
