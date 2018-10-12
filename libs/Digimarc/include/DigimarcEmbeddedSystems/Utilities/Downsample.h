// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DOWNSAMPLE_H
#define DMRC_DOWNSAMPLE_H

#include "../Configuration/StatusCode.h"
#include "../SDK/ApiDefs.h"
#include "../Configuration/PixelFormat.h"

namespace DigimarcEmbeddedSystems {

/**
 * @brief Downsamples an image by 2, 3, 4, 5 or 6 times
 *
 * The Downsample class supports grayscale pixel format and downsample factor 2, 3, 4, 5, and 6.
 *
 * The typical use of this class:
 *	1. Construct an instance of Downsample.
 *	2. Call DownsampleSetup() to setup the downsample parameters.
 *	3. Allocate output image buffer based on output of DownsampleSetup().
 *	4. Call DownsampleImage() to downsample the image by the downsample factor.
 *	5. Destroy the instance of Downsample when finished.
 */
class Downsample {
public:
	/** Construct a Downsample instance. The instance is initialized with default values.
	 */
	DMRC_API Downsample();

	/** Setup the downsample parameters. Call before DownsampleImage().
	 *
	 * @param[in] ImagePixelFormat Currently, only PixelFormat_Grayscale is supported.
	 * @param[in] InputWidth Width of input image.
	 * @param[in] InputHeight Height of input image.
	 * @param[in] DownsampleFactor Downsample factor. Only factors 2, 3, 4, 5 and 6 are supported.
	 * @param[out] OutputWidth Receives the required width of the output image buffer for DownsampleImage().
	 * @param[out] OutputHeight Receives the required height of the output image buffer for DownsampleImage().
	 * @return @ref Success if the setup is valid, or @ref Error_InvalidParameter if given invalid downsample parameters, or @ref Error_Unsupported if PixelFormat is not PixelFormat_Grayscale, or downsampleFactor is not in range 2-6.
	 */
	DMRC_API StatusCode DownsampleSetup(PixelFormat ImagePixelFormat
										, unsigned int InputWidth
										, unsigned int InputHeight
										, unsigned int DownsampleFactor
										, unsigned int& OutputWidth
										, unsigned int& OutputHeight);

	/** Downsamples the image by the downsample factor specified by DownsampleSetup(). Call after DownsampleSetup().
	*
	* @param[in] InputImage Input image array of size provided in DownsampleSetup().
	* @param[in] InputStride Stride of the input image. Input stride should be at least equal to the input width and negative stride is not supported.
	* @param[out] OutputImage Buffer for the output image of size obtained from DownsampleSetup().
	* @param[in] OutputStride Stride of the output image. Output stride should be at least equal to the output width and negative stride is not supported.
	* @return @ref Success, or @ref Error_NotInitialized when called before calling DownsampleSetup(), or @ref Error_Unsupported if stride is invalid.
	*/
	DMRC_API StatusCode DownsampleImage(const void* InputImage, int InputStride, void* OutputImage, int OutputStride);

private:
		unsigned int cachedDownsampleFactor;
		unsigned int cachedInputHeight;
		unsigned int cachedInputWidth;
		unsigned int cachedOutputHeight;
		unsigned int cachedOutputWidth;
		PixelFormat cachedImagePixelFormat;
};
}

#endif
