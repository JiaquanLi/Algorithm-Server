
// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2017
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_UVTRANSFORM_H
#define DMRC_UVTRANSFORM_H

#include "../SDK/ApiDefs.h"
#include "../Configuration/ColorComponentOrder.h"
#include "../Configuration/ColorWeights.h"
#include "../Configuration/PixelFormat.h"
#include "../Configuration/StatusCode.h"
#include "../Configuration/WatermarkType.h"

namespace DigimarcEmbeddedSystems {

/**
 * @brief Performs color conversion of semi-planar and planar YUV images to signal space.
 * Supported pixel formats: @ref PixelFormat_YUV420_SP and @ref PixelFormat_YUV420_P.
 *
 * The typical use of this class:
 *	1. Construct an instance of UvTransform.
 *	2. Call SetupUsingWatermarkType() or SetupUsingArbitraryWeights() to set up the transform parameters.
 *	3. Allocate output image buffer based on output width and output height obtained in setup. (OutputStride x OutputHeight)
 *	4. Call Convert() to convert the given semi-planar or planar YUV image to signal space.
 *	5. Destroy the instance of UvTransform when finished.
 *
 * @note @ref UvTransform supports @ref WatermarkType_Chroma_Mobile, @ref WatermarkType_Chroma_Package and arbitrary transform weights for a chroma watermark.
 */
class UvTransform {
public:
	/** Construct a UvTransform instance. The instance is initialized with default values.
	 */
	DMRC_API UvTransform();

	/** Setup UvTransform parameters for a given @ref WatermarkType.
	 *  Supported pixel formats: @ref PixelFormat_YUV420_SP and @ref PixelFormat_YUV420_P.
	 *  Supported watermark types: @ref WatermarkType_Chroma_Mobile, @ref WatermarkType_Chroma_Package.
	 *
	 * @param[in] ImageType @ref PixelFormat of the Image.
	 * @param[in] CCOrder @ref ColorComponentOrder of the Image: UV or VU.
	 * @param[in] WMType @ref WatermarkType, used to choose the transform weights.
	 * @param[in] InputWidth Width of input U or V image plane. (16 <= W < 65536)
	 * @param[in] InputHeight Height of input U or V image plane. (1 <= H < 65536)
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

	/** Setup UvTransform parameters with arbitrary transform weights.
	 *  Supported pixel formats: @ref PixelFormat_YUV420_SP and @ref PixelFormat_YUV420_P.
	 *  Supported range: -1 <= TransformWeights < 1,
	 *
	 * @param[in] ImageType @ref PixelFormat of the Image.
	 * @param[in] CCOrder @ref ColorComponentOrder of the Image: UV or VU.
	 * @param[in] TransformWeight_U Transform weight of U component.
	 * @param[in] TransformWeight_V Transform weight of V component.
	 * @param[in] TransformOffset Transform offset.
	 * @param[in] InputWidth Width of input U or V image plane. (16 <= W < 65536)
	 * @param[in] InputHeight Height of input U or V image plane. (1 <= H < 65536)
	 * @param[out] OutputWidth Receives the required width of the output image buffer for Convert().
	 * @param[out] OutputHeight Receives the required height of the output image buffer for Convert().
	 * @return @ref Success, or @ref Error_InvalidParameter, or @ref Error_Unsupported.
	 */
	DMRC_API StatusCode SetupUsingArbitraryWeights(PixelFormat ImageType
												  , ColorComponentOrder CCOrder
												  , float TransformWeight_U
												  , float TransformWeight_V
												  , int TransformOffset
												  , unsigned int InputWidth
												  , unsigned int InputHeight
												  , unsigned int& OutputWidth
												  , unsigned int& OutputHeight);

	/** Convert UV images to signal space (grayscale).
	 *  Must be used after one of the two setup functions.
	 *  Supported pixel format: @ref PixelFormat_YUV420_SP.
	 *
	 * @param[in] InputImage Input image array pointing to UV plane.
	 * @param[in] InputStride Stride of the input image. Input stride should be at least equal twice input width (U or V plane, min: 32) and negative stride is not supported.
	 * @param[out] OutputImage Buffer for the output image of size: OutputStride x OutputHeight.
	 * @param[in] OutputStride Stride of the output image. Output stride should be at least equal to the output width and negative stride is not supported.
	 * @return @ref Success, or @ref Error_InvalidParameter, or @ref Error_Unsupported, or @ref Error_NotInitialized.
	 */
	DMRC_API StatusCode Convert(const void* InputImage, int InputStride, void* OutputImage, int OutputStride);

	/** Convert Planar UV images to signal space (grayscale).
	 *  Must be used after one of the two setup functions.
	 *  Supported pixel format: @ref PixelFormat_YUV420_P.
	 *
	 * @param[in] UInput U component of input image array pointing to U plane.
	 * @param[in] VInput V component of input image array pointing to V plane.
	 * @param[in] InputStride Stride of the input image. U and V components should have equal stride, that must be at least equal to the input width (U and V plane, min: 16) and negative stride is not supported.
	 * @param[out] OutputImage Buffer for the output image of size: OutputStride x OutputHeight.
	 * @param[in] OutputStride Stride of the output image. Output stride should be at least equal to the output width and negative stride is not supported.
	 * @return @ref Success, or @ref Error_InvalidParameter, or @ref Error_Unsupported, or @ref Error_NotInitialized.
	 */
	DMRC_API StatusCode Convert(const void* UInput, const void* VInput, int InputStride, void* OutputImage, int OutputStride);

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
