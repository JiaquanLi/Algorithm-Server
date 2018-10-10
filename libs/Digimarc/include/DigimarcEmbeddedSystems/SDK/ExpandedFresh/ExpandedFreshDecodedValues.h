// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_EXPANDEDFRESHDECODEDVALUES_H
#define DMRC_DESSDK_EXPANDEDFRESHDECODEDVALUES_H

#include <stdint.h>

namespace DigimarcEmbeddedSystems {

/**
 * @brief Holds the raw integer values that can be encoded in the KE 9.2 (ExpandedFresh) watermark.
 *
 * @note Gtin13
 *	- Allowable range: Any valid GTIN-13.
 *		- Other symbols that can be zero padded (UPC-A, GTIN-12, GTIN-8, etc.) are supported, but must be provided with padded zeros.
 *		- Value provided **Must include valid check digit**.
 *	- Use NULL or 0 to specify unused.

 * @note SellbyDate
 *	- Allowable range: **January 01, 2016** through **May 08, 2106**.
 *	- Value stored as days since January 01, 2016. Converted later to YYMMDD, See [GS1 General Specification: 3.4.6](https://www.gs1.org/docs/barcodes/GS1_General_Specifications.pdf#page=133)
 *	- Use NULL or 0 to specify unused.
 *
 * @note Price
 *	- Allowable range: 0.01 to 99999.99
 *	- Use NULL or 0 to specify unused.
 *	- Denotes local currency
 *	- Example:
 *		- 12345 = 123.45 (local currency).
 *
 * @note Weight
 *	- Allowable range: 1 to 22767
 *	- Use NULL or 0 to specify unused.
 *	- Numerical range is the same for pounds and kilograms.
 *	- Depending on the value of variation, either pounds or kilograms is used. If pounds and kilograms are provided, weights are not converted.
 *	- Input format:
 *		- 2345 = 2.345 (unit specified).
 *
 * @note Count
 *	- Allowable range: 1 to 99
 *	- Use NULL or 0 to specify unused.
 *	- Count is mutually exclusive with both weights. If count is provided with either weight, it is treated as an error and parsed output will not be valid.
 */
struct ExpandedFreshDecodedValues {
	uint32_t variation;
	uint32_t sellbyDate;
	uint32_t price;
	uint64_t gtin;
	uint32_t weightInPounds;
	uint32_t weightInKiloGrams;
	uint32_t weightInPoundsRange2;
	uint32_t weightInKiloGramsRange2;
	uint32_t count;
};
}
#endif
