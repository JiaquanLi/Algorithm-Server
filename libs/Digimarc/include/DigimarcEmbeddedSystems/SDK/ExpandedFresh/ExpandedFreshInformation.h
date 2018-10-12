// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_EXPANDEDFRESHINFORMATION_H
#define DMRC_DESSDK_EXPANDEDFRESHINFORMATION_H

#include "../ApiDefs.h"
#include "../WatermarkInformation.h"
#include "ExpandedFreshDecodedValues.h"

namespace DigimarcEmbeddedSystems {

/**
* @brief The ExpandedFreshInformation class holds the decoded information from Expanded Fresh watermarks.
*		This class is passed to the registered @ref DigimarcEmbeddedSystems::ExpandedFreshCallback "ExpandedCallback"
*		and is used for accessing the relevent data.
*
* @note The individual getters for this class (i.e. GetPrice()) return ASCII string representations of the values.
*		The specific AI is not included and values are not padded. Please use @ref GetDataBar() to get a DataBar complient string.
*/
class ExpandedFreshInformation : public WatermarkInformation {
public:
	friend class ExpandedFreshHelper;
	DMRC_API ExpandedFreshInformation();

	/**
	 * @note There is an implied decimal two digits in from the right. For example, the string "12345" denotes a price of 123.45 (in local currency).
	 * @returns Price in [AI 3922 - Amount payable for variable measure trade item](https://www.gs1.org/docs/barcodes/GS1_General_Specifications.pdf#page=133)
	 */
	DMRC_API const char* GetPrice() const;

	/**
	 * @returns GTIN-14 in [AI 01 - Identification of a fixed measure trade item](https://www.gs1.org/docs/barcodes/GS1_General_Specifications.pdf#page=133)
	 */
	DMRC_API const char* GetGtin14() const;

	/**
	 * @deprecated This function has been replaced by @ref GetWeightInPoundsRange1, which provides the same formatting.
	 */
	DMRC_API const char* GetWeightInPounds() const;

	/**
	 * @deprecated This function has been replaced by @ref GetWeightInKiloGramsRange1, which provides the same formatting.
	 */
	DMRC_API const char* GetWeightInKiloGrams() const;

	/**
	 * @brief Get weight, range 0 to 22.767 lbs
	 * @note There is an implied decimal three digits in from the right. For example, the string "12345" denotes a weight of 12.345 lbs,
	 *      and the string "340" denotes a weight of 0.340 lbs.
	 * @returns Net Weight (lbs) in [AI 3203 Trade measures](https://www.gs1.org/docs/barcodes/GS1_General_Specifications.pdf#page=133)
	 */
	DMRC_API const char* GetWeightInPoundsRange1() const;

	/**
	 * @brief Get weight, range 0 to 22.767 kg
	 * @note There is an implied decimal three digits in from the right. For example, the string "12345" denotes a weight of 12.345 kg,
	 *      and the string "340" denotes  a weight of 0.340 kg.
	 * @returns Net Weight (kg) in [AI 3103 Trade measures](https://www.gs1.org/docs/barcodes/GS1_General_Specifications.pdf#page=133)
	 */
	DMRC_API const char* GetWeightInKiloGramsRange1() const;


	/**
	 * @brief Get weight, range 0 to 227.67 lbs.
	 *		In comparison to weight range 1, weight range 2 allows larger weights but with only 2 digits of fraction.
	 *		The weight range 2 values are formatted as 3202 with two digits of fraction.
	 *
	 * @note There is an implied decimal two digits in from the right. For example, the string "12345" denotes a weight of 123.45 lbs,
	 *      and the string "340" denotes a weight of 3.40 lbs.
	 * @returns Net Weight (lbs) in [AI 3202 Trade measures](https://www.gs1.org/docs/barcodes/GS1_General_Specifications.pdf#page=133)
	 */
	DMRC_API const char* GetWeightInPoundsRange2() const;

	/**
	 * @brief Get weight, range 0 to 227.67 kg
	 *		In comparison to weight range 1, weight range 2 allows larger weights but with only 2 digits of fraction.
	 *		The weight range 2 values are formatted as 3102 with two digits of fraction.
	 *
	 * @note There is an implied decimal two digits in from the right. For example, the string "12345" denotes a weight of 123.45 kg.
	 *      and the string "340" denotes a weight of 3.40 kg.
	 * @returns Net Weight (kg) in [AI 3102 Trade measures](https://www.gs1.org/docs/barcodes/GS1_General_Specifications.pdf#page=133)
	 */
	DMRC_API const char* GetWeightInKiloGramsRange2() const;

	/**
	 * @returns Count of items in [AI 30 Variable Count](https://www.gs1.org/docs/barcodes/GS1_General_Specifications.pdf#page=133)
	 */
	DMRC_API const char* GetCount() const;

	/**
	 * @returns Sell by date in [AI 16 - Sell by date](https://www.gs1.org/docs/barcodes/GS1_General_Specifications.pdf#page=133)
	 */
	DMRC_API const char* GetSellbyDate() const;

	/**
	 * @deprecated Please use @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString(ApplicationIdentifierFormatOptions) const "GetAppIdentifierElementString(...)"
	 *		in new code.
	 *
	 * @note This function returns an Application Identifier element string without the Digimarc Identifier.
	 */
	DMRC_API const char* GetDataBar() const;

	/**
	 * See @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString "GetAppIdentifierElementString" for details.
	 */
	DMRC_API const char* GetAppIdentifierElementString() const;

	/**
	 * See @ref DigimarcEmbeddedSystems::WatermarkInformation::GetAppIdentifierElementString(ApplicationIdentifierFormatOptions) const "GetAppIdentifierElementString(...)" for details.
	 */
	DMRC_API const char* GetAppIdentifierElementString(ApplicationIdentifierFormatOptions formatOptions) const;


private:
	ExpandedFreshDecodedValues decoded;	///< Copy of the decoded values provided during construction.

	static const unsigned int GTIN_14_LENGTH = 15;
	static const unsigned int SELLBY_DATE_LENGTH = 7;
	static const unsigned int MAX_PRICE_LENGTH = 8;
	static const unsigned int MAX_WEIGHT_LENGTH = 6;
	static const unsigned int MAX_COUNT_LENGTH = 3;

	mutable char sellbyDate[SELLBY_DATE_LENGTH];				///< AI 16
	mutable char price[MAX_PRICE_LENGTH];						///< AI 3922
	mutable char gtin[GTIN_14_LENGTH];							///< AI 01
	mutable char weightInPounds[MAX_WEIGHT_LENGTH];				///< AI 3203
	mutable char weightInKiloGrams[MAX_WEIGHT_LENGTH];			///< AI 3103
	mutable char weightInPoundsRange2[MAX_WEIGHT_LENGTH];		///< AI 3203
	mutable char weightInKiloGramsRange2[MAX_WEIGHT_LENGTH];	///< AI 3103
	mutable char count[MAX_COUNT_LENGTH];						///< AI 30

};

}

#endif
