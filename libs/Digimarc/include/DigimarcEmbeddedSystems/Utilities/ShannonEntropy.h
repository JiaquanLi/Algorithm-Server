// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2017
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_SHANNONENTROPY_H
#define DMRC_SHANNONENTROPY_H

#include "../SDK/ApiDefs.h"

namespace DigimarcEmbeddedSystems {

class ShannonEntropy {
public:

	/** Calculate the histogram for a frame.
	 *
	 * @param[in] frameData Pointer to image data.
	 * @param[in] width Width of frame in pixels.
	 * @param[in] height Height of frame in pixels.
	 * @param[in] stride Stride of frame (bytes between successive rows).
	 * @param[out] histogram Histogram of the grayscale image is accumulated into buffer of size 256. Must be initialized with zeros before calling.
	 *
	 * @return 0 for Success, or -1 if width or height is zero or if absolute value of stride is less than width.
	 */
	DMRC_API static int Histogram(const void* frameData, unsigned int width, unsigned int height, int stride, int histogram[256]);

	/** Calculate the value of the lighting metric for a frame.
	 *		return it as a fixed-point integer with 10 bits of fraction precision.
	 *
	 * @param[in] frameData Pointer to image data.
	 * @param[in] frameWidth Width of frame in pixels.
	 * @param[in] frameHeight Height of frame in pixels.
	 * @param[in] frameStride Stride of frame (bytes between successive rows).
	 *
	 * @return Lighting metric for the frame (avg bits per pixel) in fixed point, 10 bits of fraction precision, or -1 if invalid parameter.
	 */
	DMRC_API static int CalculateEntropyLightingMetric(const void* frameData, unsigned int frameWidth, unsigned int frameHeight, int frameStride);

private:
	ShannonEntropy();

};

}
#endif
