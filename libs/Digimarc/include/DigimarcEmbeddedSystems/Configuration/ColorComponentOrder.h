// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2017
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_COLORCOMPONENTORDER_H
#define DMRC_DESSDK_COLORCOMPONENTORDER_H

namespace DigimarcEmbeddedSystems {

/** Describes the color component order of an image. */
enum ColorComponentOrder {
	ColorComponentOrder_Invalid = -1,				///< The color component order is invalid.
	ColorComponentOrder_SingleComponent,			///< The image has a single color component.
	ColorComponentOrder_RGB,						///< The RGB (or Bayer) image color components are in order R, G, B. For more information on how this applies to Bayer images, see @ref bayerPixelFormatPage "Bayer Pixel Format"
	ColorComponentOrder_BGR,						///< The RGB (or Bayer) image color components are in order B, G, R. For more information on how this applies to Bayer images, see @ref bayerPixelFormatPage "Bayer Pixel Format"
	ColorComponentOrder_UV,							///< The YUV image color components are in order U, V.
	ColorComponentOrder_VU							///< The YUV image color components are in order V, U.
};

}

#endif
