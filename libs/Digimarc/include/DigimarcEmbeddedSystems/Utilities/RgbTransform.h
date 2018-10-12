// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2017
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_RGBTRANSFORM_H
#define DMRC_RGBTRANSFORM_H

#include "../SDK/ApiDefs.h"
#include "../Configuration/ColorComponentOrder.h"
#include "../Configuration/ColorWeights.h"
#include "../Configuration/PixelFormat.h"
#include "../Configuration/StatusCode.h"
#include "../Configuration/WatermarkType.h"

namespace DigimarcEmbeddedSystems {

/**
 * @brief Performs color conversion of RGB images to signal space.
 * Supported pixel formats: @ref PixelFormat_RGB, @ref PixelFormat_RGBA, @ref PixelFormat_ARGB.
 *
 * The typical use of this class:
 *	1. Construct an instance of RgbTransform.
 *	2. Call SetupUsingWatermarkType() or SetupUsingArbitraryWeights() to set up the transform parameters.
 *	3. Allocate output image buffer based on output width and output height obtained in setup. (OutputStride x OutputHeight)
 *	4. Call Convert() to convert the given RGB image to signal space.
 *	5. Destroy the instance of RgbTransform when finished.
 *
 * @note RgbTransform supports arbitrary transform weights and all @ref WatermarkType.
 */
class RgbTransform {
public:
	/** Construct a RgbTransform instance. The instance is initialized with default values.
	 */
	DMRC_API RgbTransform();

	/** Setup RgbTransform parameters for a given @ref WatermarkType.
	 *  Supported pixel formats: @ref PixelFormat_RGB, @ref PixelFormat_RGBA, @ref PixelFormat_ARGB.
	 *  Supports all watermark types.
	 *
	 * @param[in] ImageType @ref PixelFormat of the Image.
	 * @param[in] CCOrder @ref ColorComponentOrder of the Image: RGB or BGR.
	 * @param[in] WMType @ref WatermarkType, used to choose the transform weights.
	 * @param[in] InputWidth Width of input image. (1 <= W < 65536)
	 * @param[in] InputHeight Height of input image. (1 <= H < 65536)
	 * @param[out] OutputWidth Receives the required width of the output image buffer for Convert().
	 * @param[out] OutputHeight Receives the required height of the output image buffer for Convert().
	 * @return @ref Success, or @ref Error_InvalidParameter, or @ref Error_Unsupported.
	 */
	DMRC_API StatusCode SetupUsingWatermarkType(PixelFormat ImageType
												, ColorComponentOrder CCOrder
												, WatermarkType WMType
												, unsigned int InputWidth
												, unsigned int InputHeight
												, unsigned int& OutputWidth
												, unsigned int& OutputHeight);

	/** Setup RgbTransform parameters with arbitrary transform weights.
	 *  Supported pixel formats: @ref PixelFormat_RGB, @ref PixelFormat_RGBA, @ref PixelFormat_ARGB.
	 *  Supported range: -1 <= TransformWeights < 1.
	 *
	 * @param[in] ImageType @ref PixelFormat of the Image.
	 * @param[in] CCOrder @ref ColorComponentOrder of the Image: RGB or BGR.
	 * @param[in] TransformWeight_R Transform weight of R component.
	 * @param[in] TransformWeight_G Transform weight of G component.
	 * @param[in] TransformWeight_B Transform weight of B component.
	 * @param[in] TransformOffset Transform offset.
	 * @param[in] InputWidth Width of input image. (1 <= W < 65536)
	 * @param[in] InputHeight Height of input image. (1 <= H < 65536)
	 * @param[out] OutputWidth Receives the required width of the output image buffer for Convert().
	 * @param[out] OutputHeight Receives the required height of the output image buffer for Convert().
	 * @return @ref Success, or @ref Error_InvalidParameter or @ref Error_Unsupported.
	 */
	DMRC_API StatusCode SetupUsingArbitraryWeights(PixelFormat ImageType
												   , ColorComponentOrder CCOrder
												   , float TransformWeight_R
												   , float TransformWeight_G
												   , float TransformWeight_B
												   , int TransformOffset
												   , unsigned int InputWidth
												   , unsigned int InputHeight
												   , unsigned int& OutputWidth
												   , unsigned int& OutputHeight);

	/** Convert RGB image to signal space (grayscale).
	 *  Must be used after one of the two setup functions.
	 *
	 * @param[in] InputImage Input image array.
	 * @param[in] InputStride Stride of the input image. Input stride for RGB, BGR cannot be less than 3 times input width,
	 *  input stride for ARGB, ABGR, RGBA, BGRA cannot be less than 4 times input width and negative stride is not supported.
	 * @param[out] OutputImage Buffer for the output image of size: OutputStride x OutputHeight.
	 * @param[in] OutputStride Stride of the output image. Output stride should be at least equal to the output width and negative stride is not supported.
	 * @return @ref Success, or @ref Error_InvalidParameter, or @ref Error_Unsupported, or @ref Error_NotInitialized.
	 */
	DMRC_API StatusCode Convert(const void* InputImage, int InputStride, void* OutputImage, int OutputStride);

private:
	PixelFormat cachedImageType;
	ColorWeights cachedTransformWeights;
	ColorComponentOrder cachedCCOrder;
	unsigned int cachedInputHeight;
	unsigned int cachedInputWidth;
	unsigned int cachedOutputHeight;
	unsigned int cachedOutputWidth;
};
}

#endif
