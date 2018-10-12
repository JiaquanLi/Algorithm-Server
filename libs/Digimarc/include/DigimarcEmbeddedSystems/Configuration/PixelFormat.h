// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2017
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_PIXELFORMAT_H
#define DMRC_DESSDK_PIXELFORMAT_H

namespace DigimarcEmbeddedSystems {

const unsigned int MAX_NUM_PLANES = 3;

/** Describes the pixel format of an image. */
enum PixelFormat {
	PixelFormat_Invalid = -1,				///< Pixels format is invalid
	PixelFormat_Grayscale,					///< Pixels are 8-bit grayscale
	PixelFormat_RGB,						///< Pixels are 24-bit RGB (or BGR)
	PixelFormat_RGBA,						///< Pixels are 32-bit RGBA (or BGRA)
	PixelFormat_ARGB,						///< Pixels are 32-bit ARGB (or ABGR)
	PixelFormat_YUV420_SP,					///< Pixels are semi-planar 8-bit YUV (or YVU) 420 (luma plane followed by interleaved UV plane, UV plane at half sample rate)
	PixelFormat_Bayer_1,					///< Pixels are 8-bit RGB Bayer pattern with red (or blue) sample at upper left. For more information, see @ref bayerPixelFormatPage "Bayer Pixel Format"
	PixelFormat_Bayer_2,					///< Pixels are 8-bit RGB Bayer pattern with green sample at upper left. For more information, see @ref bayerPixelFormatPage "Bayer Pixel Format"
	PixelFormat_YUV420_P					///< Pixels are planar 8-bit YUV 420 (U and V planes at half sample rate)
};

}

#endif
