// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_PAYLOADMETADATA_H
#define DMRC_DESSDK_PAYLOADMETADATA_H

#include "../Configuration/PerspectiveParams.h"

namespace DigimarcEmbeddedSystems {

/** This class carries additional information about a payload. */
class PayloadMetadata {
public:
	/** A unique (per frame) ID related to this symbol. Each distinct symbol within an image frame is given a unique ID. */
	int payloadId;

	/** The horizontal center of the symbol detected. */
	int centerX;

	/** The vertical center of the symbol detected. */
	int centerY;

	/** The horizontal "fine location" of the symbol detected. */
	int fineLocationX;

	/** The vertical "fine location" of the symbol detected. */
	int fineLocationY;

	/** The coarse scale of the symbol detected, if the symbol has a defined coarse scale. For symbols
	 * without a defined coarse scale, this value is always 1. */
	unsigned int coarseScale;

	/** The fine scale of the symbol detected, if the symbol has a defined fine scale. The total scale
	 * of the symbol is equal to coarseScale * fineScale. For symbols without a defined fine scale, this
	 * value is always 1. */
	float fineScale;

	/** The rotation of the symbol detected, if rotation can be determined. */
	float rotationDegrees;

	/** The perspective of the symbol, if known. */
	PerspectiveParams perspective;

	/** The time to read this symbol in microseconds. This value may be 0 if the host platform does not support high performance
	 * timing. */
	unsigned int timeToReadMicroseconds;

	/** @brief Relative strength of the detected Digimarc signal.
	 *
	 * @warning This value is an estimate of the relative strength of the detected Digimarc signal,
	 * with more positive values indicating stronger signals. It may be useful for diagnostic purposes
	 * but it is important to understand that the value is not a linear indicator of strength and can increase
	 * or decrease in an unpredictable way. For example, a small shift in the input image may change this metric.
	 * Digimarc reserves the right to change the algorithm that computes this value at any time.
	 */
	int relativeSignalStrength;

	/** @brief The message correlation with 10 bits of fraction precision. This value ranges from -1024 (perfect
	 * anti-correlation of message) to 1024 (perfect correlation of message). A measure of 0 means no correlation
	 * with the message. In practice, correlations of 0 or less will not be reported as no watermark signal
	 * could be decoded in that case.
	 * To save computation time for decoded results, the default is not to calculate message correlation.
	 * The default value of message correlation is 0. 
	 * See @ref DigimarcEmbeddedSystems::Configuration::enableMessageCorrelationCalculation "enableMessageCorrelationCalculation".
	 */
	int messageCorrelation;
};

}

#endif
