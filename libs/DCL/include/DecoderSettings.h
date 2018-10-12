//======================================================================================
// DecoderSettings.h
//======================================================================================
 
//---------------------------------------------------------------------------
//
//  Module Interface Description:
//      This file contains the settings / properties for the generic decoder 
//
//---------------------------------------------------------------------------

/* Copyright 2017, Honeywell.  All Rights Reserved */

#ifndef DECODER_SETTINGS_H
#define DECODER_SETTINGS_H

/* Decoder Menu Types 
 * These are the expected type for each command. They are embedded in the menu tag so 
 * the user knows what type of information to pass into the menu function
 */
#define MENU_TYPE_INT      0x10000000 //single integer
#define MENU_TYPE_CHAR     0x20000000 //single ASCII char
#define MENU_TYPE_ARRAY    0x80000000 //used in conjunction with INT or CHAR
#define MENU_TYPE_MASK     0xF0000000 //mask that can be used by software to determine types.


/* System Control Settings
 * These settings are general decoder control. 
 */
 

/**
 * \brief These configuration tags are used with DecodeSet() and DecodeGet().
 *
 *  \defgroup apiConfig Configuration
 *  @{
 */

/**
 * \brief All other tags that are not grouped.
 *
 * \defgroup misctags Misc
 * @{
 */

/**
 * \brief Algorithms for more vigorous searching decoding.
 */
#define DEC_DECODE_VIGOR                        (MENU_TYPE_INT + 0x0A001001)

/*
 * \brief N/A
 */
// deprecated
// #define DEC_IQ_FILTER_MODE                   (MENU_TYPE_INT + 0x0A001002)

/**
 * \brief Linear video reverse decoding. 
 */
#define DEC_VIDEO_REVERSE_ENABLED               (MENU_TYPE_INT + 0x0A001004)

/**
 * \brief N/A
 */
// deprecated
// #define DEC_SHOW_NO_READ_ENABLED             (MENU_TYPE_INT + 0x0A001005)

/**
 * \brief Debug verbosity.
 */
#define DEC_SHOW_DECODE_DEBUG                   (MENU_TYPE_INT + 0x0A001006)

/** @} */

/**
 * \brief Combine pieces of composite codes before issuing result.
 * \ingroup composite
 */
#define DEC_COMBINE_COMPOSITES                  (MENU_TYPE_INT + 0x0A001007)

/**
 * \brief All attributes of an image that is passed into Decode(). 
 * \defgroup image Image
 * @{
 */

/**
 * \brief Height of the image in pixels.
 */
#define DEC_IMAGE_HEIGHT                        (MENU_TYPE_INT + 0x0A001008)

/**
 * \brief Width of the image in pixels.
 */
#define DEC_IMAGE_WIDTH                         (MENU_TYPE_INT + 0x0A001009)

/**
 * \brief Length of the memory of each row of image in pixels.
 */
#define DEC_IMAGE_LINE_DELTA                    (MENU_TYPE_INT + 0x0A00100A)

/** @} */

/**
 * \defgroup windowing Windowing
 * @{
 */

/**
 * \brief Windowing or centering mode.
 */
#define DEC_WINDOW_MODE                         (MENU_TYPE_INT + 0x0A00100B)

/**
 * \brief Top border of window.
 */
#define DEC_WINDOW_TOP                          (MENU_TYPE_INT + 0x0A00100C)

/**
 * \brief Bottom border of window.
 */

#define DEC_WINDOW_BOTTOM                       (MENU_TYPE_INT + 0x0A00100D)

/**
 * \brief Left border of window.
 */
#define DEC_WINDOW_LEFT                         (MENU_TYPE_INT + 0x0A00100E)

/**
 * \brief Right border of window.
 */
#define DEC_WINDOW_RIGHT                        (MENU_TYPE_INT + 0x0A00100F)

/**
 * \brief Draws defined window in image.
 */
#define DEC_SHOW_DECODE_WINDOW                  (MENU_TYPE_INT + 0x0A001010)

/** @} */

/**
 * \brief Search start X coordinate.
 * \ingroup image
 */
#define DEC_IMAGE_CENTER_X                      (MENU_TYPE_INT + 0x0A001011)

/**
 * \brief Search start Y coordinate.
 * \ingroup image
 */
#define DEC_IMAGE_CENTER_Y                      (MENU_TYPE_INT + 0x0A001012)

/**
 * \brief Returns energy of image.
 * \ingroup misctags
 */
#define DEC_GET_ENERGY                          (MENU_TYPE_INT + 0x0A001013)

/**
 * \brief Sets the orientation of the image.
 * \ingroup image
 */
#define DEC_IMAGE_ROTATION                      (MENU_TYPE_INT + 0x0A001015)

/**
 * \brief Sets the type of image data.
 * \ingroup image
 */
// deprecated
// #define DEC_DATA_TYPE                        (MENU_TYPE_INT + 0x0A001016)

/**
 * \brief Offset of pixel data when reversing for linear video reverse.
 * \ingroup misctags
 */
#define DEC_VIDEO_REVERSE_SHIFT                 (MENU_TYPE_INT + 0x0A001017)

/**
 * \defgroup results Results
 * @{
 */

/**
 * \brief Gets the raw decoded data.
 */
#define DEC_RESULT_DATA                         (MENU_TYPE_INT + 0x0A001018)

/**
 * \brief Gets the lenght of the raw decoded data.
 */
#define DEC_RESULT_LENGTH                       (MENU_TYPE_INT + 0x0A001019)

/**
 * \brief Gets the graphical bounds of the result location in the image.
 */
#define DEC_RESULT_MAIN_BOUNDS                  (MENU_TYPE_INT + 0x0A00101A)

/**
 * \brief Gets the graphical center point of the result location in the image.
 */
#define DEC_RESULT_GRAPHICAL_CENTER             (MENU_TYPE_INT + 0x0A00101B)

/**
 * \brief Gets the Symbology identifier of the result.
 */
#define DEC_RESULT_SYMBOLOGY                    (MENU_TYPE_INT + 0x0A00101C)

/**
 * \brief Gets the extended Symbology identifier of the result.
 */
#define DEC_RESULT_SYMBOLOGY_EX                 (MENU_TYPE_INT + 0x0A00101D)

/**
 * \brief Gets the Modifier identifier of the result.
 */
#define DEC_RESULT_MODIFIER                     (MENU_TYPE_INT + 0x0A00101E)

/**
 * \brief Gets the extended Modifier indentifier of the result.
 */
#define DEC_RESULT_MODIFIER_EX                  (MENU_TYPE_INT + 0x0A00101F)

/**
 * \brief Gets the HHP Code ID of the result.
 */
#define DEC_RESULT_HHP_CODE_ID                  (MENU_TYPE_INT + 0x0A001020)

/**
 * \brief Gets the AIM Codeletter of the result.
 */
#define DEC_RESULT_AIM_CODE_LETTER              (MENU_TYPE_INT + 0x0A001021)

/**
 * \brief Gets the AIM Modifier of the result.
 */
#define DEC_RESULT_AIM_MODIFIER                 (MENU_TYPE_INT + 0x0A001022)

/**
 * \brief Gets the IQ Image information of the result.
 */
#define DEC_RESULT_IQ_IMAGE_INFO                (MENU_TYPE_INT + 0x0A001023)

/**
 * \brief Gets the parity of the result.
 */
#define DEC_RESULT_PARITY                       (MENU_TYPE_INT + 0x0A001024)

/**
 * \brief Gets the Append type of the result.
 */
#define DEC_RESULT_APPEND_TYPE                  (MENU_TYPE_INT + 0x0A001025)

/**
 * \brief Gets the Append index of the result. Set to change the result index less than the total number of results.
 */
#define DEC_RESULT_APPEND_INDEX                 (MENU_TYPE_INT + 0x0A001026)

/**
 * \brief Gets the total number of results.
 */
#define DEC_RESULT_APPEND_TOTAL                 (MENU_TYPE_INT + 0x0A001027)

/**
 * \brief Gets the Link flag of the result.
 */
#define DEC_RESULT_LINK_FLAG                    (MENU_TYPE_INT + 0x0A001028)

/**
 * \brief Gets whether the result is a reader programming code.
 */
#define DEC_RESULT_PROGRAMMING_CODE             (MENU_TYPE_INT + 0x0A001029)

/**
 * \brief Gets the Decoder library that returned the result.
 */
#define DEC_RESULT_DECODE_TYPE                  (MENU_TYPE_INT + 0x0A00102A)

/** @} */

/**
 * \addtogroup misctags
 * @{
 */

/**
 * \brief Maximum Likelihood Decoding algorithms.
 */
#define DEC_USE_MLD                             (MENU_TYPE_INT + 0x0A002001) 

/**
 * \brief The aggressiveness of decoding algorithms.
 */
#define DEC_SECURITY_LEVEL                      (MENU_TYPE_INT + 0x0A002002) 

/**
 * \brief ECI codeword handling in result data.
 */
#define DEC_ECI_HANDLING                        (MENU_TYPE_INT + 0x0A002003)

/**
 * \brief Reads all symbols in an image in the time allowed.
 */
#define DEC_MULTIREAD_ENABLED                   (MENU_TYPE_INT + 0x0A002004)

/**
 * \brief Prioritizes a specific symbology when returning results from multiple codes in an image.
 */
#define DEC_PREFERRED_ENABLED                   (MENU_TYPE_INT + 0x0A002005)

/**
 * \brief List of HHP Code IDs of preferred codes.
 */
#define DEC_PREFERRED_CODE_IDS                  (MENU_TYPE_INT + 0x0A002006)

/**
 * \brief List of HHP Code IDs of non-preferred codes.
 */
#define DEC_NONPREFERRED_CODE_IDS               (MENU_TYPE_INT + 0x0A002007)

/**
 * \brief Windowing control for preferred mode only.
 */
#define DEC_NONPREFERRED_WINDOW_ENABLED         (MENU_TYPE_INT + 0x0A002008)

/**
 * \brief HIBC append enable.
 */
#define DEC_HIBC_APPEND_ENABLED                 (MENU_TYPE_INT + 0x0A002009)

/**
 * \brief HIBC append mode.
 */
#define DEC_HIBC_APPEND_TYPE                    (MENU_TYPE_INT + 0x0A00200A)

/**
 * \brief HIBC check digit transmit.
 */
#define DEC_HIBC_CHECK_DIGIT_TRANSMIT           (MENU_TYPE_INT + 0x0A00200B)

/**
 * \brief Vesta algorithms.
 */
#define DEC_USE_VESTA                           (MENU_TYPE_INT + 0x0A00200C)

/**
 * \brief N/A
 */
// deprecated
// #define DEC_DECODE_TIMING_CONTROL            (MENU_TYPE_INT + 0x0A003001)

/**
 * \brief Maximum amount of time allowed for an image in linear video reverse. 
 */
#define DEC_DECODE_TIME                         (MENU_TYPE_INT + 0x0A003002)

/**
 * \brief N/A
 */
// deprecated
// #define DEC_SEARCH_TIME                      (MENU_TYPE_INT + 0x0A003003)

/**
 * \brief Minimum additional time to decode a UPC addenda.
 */
#define DEC_ADD_SEARCH_TIME_ADDENDA             (MENU_TYPE_INT + 0x0A003004) 

/**
 * \brief Minimum additional time to decode certain appends.
 */
#define DEC_ADD_SEARCH_TIME_CONCAT              (MENU_TYPE_INT + 0x0A003005) 

/** @} */

/**
 * \brief Minimum additional time to decode the composite piece after reading a UPC.
 * \ingroup composite
 */
#define DEC_ADD_SEARCH_TIME_UPC_COMPOSITE       (MENU_TYPE_INT + 0x0A003006) 

/**
 * \brief Forces enough space in the image for a UPC addenda. 
 * \ingroup upca
 * \see upce ean8 ean13
 */
#define DEC_ADDENDA_SPACING_ENABLED             (MENU_TYPE_INT + 0x0A003007)

/**
 * \brief Defines the minimum size of a 1D bar in the image in 1/10 of pixel
 */
#define DEC_MIN_PPM_1D                          (MENU_TYPE_INT + 0x0A003008)

/**
 * \brief Defines the minimum size of a 2D module in the image in 1/10 of pixel
 */
#define DEC_MIN_PPM_2D                          (MENU_TYPE_INT + 0x0A003009)

/**
 * \addtogroup misctags
 * @{
 */

/**
 * \brief Prints result structure for each result prior to issuing them.
 */
#define DEC_PRINT_RESULTS                       (MENU_TYPE_INT + 0x0A005001) 

/**
 * \brief Prints all settings and values.
 */
#define DEC_DUMP_SETTINGS                       (MENU_TYPE_INT + 0x0A005002)

/**
 * \brief N/A
 */
// deprecated
// #define DEC_DISPLAY_DATA                        (MENU_TYPE_INT + 0x0A005003)

/**
 * \brief Resets settings to default values.
 */
#define DEC_RESET_DECODER                       (MENU_TYPE_INT + 0x0A005004)

/**
 * \brief Fast decoder decoding control. 
 */
#define DEC_FAST_DECODER_ENABLED                (MENU_TYPE_INT + 0x0A005005) 

/**
 * \brief Full decoder decoding control.
 */
#define DEC_FULL_DECODER_ENABLED                (MENU_TYPE_INT + 0x0A005006)

/**
 * \brief Controls enables for groups of symbologies.
 */
#define DEC_DISABLE_SYMBOLOGY_GROUP             (MENU_TYPE_INT + 0x0A005007)

/** @} */

/**
 * \brief Use injected image set for decoding.
 * \ingroup image
 */
#define DEC_INJECT_MODE_ENABLED                 (MENU_TYPE_INT + 0x0A005008)

/**
 * \brief Pointer to the first image of an Inject Mode image set.
 * \ingroup image
 */
#define DEC_INJECT_MODE_IMAGE                   (MENU_TYPE_INT + 0x0A005009)

/**
 * \addtogroup misctags
 * @{
 */

/**
 * \brief Flag for trigger pull event.
 */
#define DEC_TRIGGERED                           (MENU_TYPE_INT + 0x0A00500A)

/**
 * \brief Force API Decode Type
 */
#define DEC_FORCE_API_DECODE_TYPE               (MENU_TYPE_INT + 0x0A00500E)

/**
 * \brief Coupon Code decoding mode.
 */
#define DEC_COUPON_CODE_MODE                    (MENU_TYPE_INT + 0x0A006001) 

/**
 * \brief EAN/UCC emulation mode.
 */
#define DEC_EANUCC_EMULATION_MODE               (MENU_TYPE_INT + 0x0A006002)

/**
 * \brief Output of GS1-Databar Extended control for coupon codes.
 */
#define DEC_COUPON_SECONDARY_OUTPUT             (MENU_TYPE_INT + 0x0A006003)

/**
 * \brief Combines coupon code pieces prior to issuing a result.
 */
#define DEC_COMBINE_COUPON_CODES                (MENU_TYPE_INT + 0x0A006004) 

/** @} */

/**
 * \addtogroup image
 * @{
 */

/**
 * \brief Monocolor interpolation enable.
 */
#define DEC_MONOCOLOR_ENABLED                   (MENU_TYPE_INT + 0x0A007001)

/**
 * \brief Monocolor interpolation X coordinate offset.
 */
#define DEC_MONOCOLOR_OFFSET_X                  (MENU_TYPE_INT + 0x0A007002) 

/**
 * \brief Monocolor interpolation Y coordinate offset.
 */
#define DEC_MONOCOLOR_OFFSET_Y                  (MENU_TYPE_INT + 0x0A007003) 

/**
 * \brief Monocolor interpolation spacing between X coordinates.
 */
#define DEC_MONOCOLOR_SPACING_X                 (MENU_TYPE_INT + 0x0A007004) 

/**
 * \brief Monocolor interpolation spacing between Y coordinates.
 */
#define DEC_MONOCOLOR_SPACING_Y                 (MENU_TYPE_INT + 0x0A007005) 

/** @} */

/**
 * \defgroup upca UPC-A
 * @{
 */

/**
 * \brief UPC-A enable.
 */
#define DEC_UPCA_ENABLE                         (MENU_TYPE_INT + 0x0A010011)

/**
 * \brief Translate UPC-A to EAN-13. This is legacy behavior
 */
#define DEC_UPCA_ENABLED                        (MENU_TYPE_INT + 0x0A010001) //deprecated: kept to help transition to new tag
#define DEC_UPCA_TRANSLATE_TO_EAN13             (MENU_TYPE_INT + 0x0A010001) 

/**
 * \brief UPC-A check digit transmit enable.
 */
#define DEC_UPCA_CHECK_DIGIT_TRANSMIT           (MENU_TYPE_INT + 0x0A010002) 

/**
 * \brief UPC-A number system transmit enable.
 */
#define DEC_UPCA_NUMBER_SYSTEM_TRANSMIT         (MENU_TYPE_INT + 0x0A010003) 

/**
 * \brief UPC-A 2-character addenda enable.
 */
#define DEC_UPCA_2CHAR_ADDENDA_ENABLED          (MENU_TYPE_INT + 0x0A010004) 

/**
 * \brief UPC-A 5-character addenda enable. 
 */
#define DEC_UPCA_5CHAR_ADDENDA_ENABLED          (MENU_TYPE_INT + 0x0A010005) 

/**
 * \brief Requires reading an addenda for UPC-A to issue a result.
 */
#define DEC_UPCA_ADDENDA_REQUIRED               (MENU_TYPE_INT + 0x0A010006) 

/**
 * \brief Added a space between main code and addenda for UPC-A.
 */
#define DEC_UPCA_ADDENDA_SEPARATOR              (MENU_TYPE_INT + 0x0A010007)

/** @} */

/**
 * \defgroup upce UPC-E
 * @{
 */

/**
 * \brief UPC-E0 enable.
 */
#define DEC_UPCE0_ENABLED                       (MENU_TYPE_INT + 0x0A011001) 

/**
 * \brief UPC-E1 enable.
 */
#define DEC_UPCE1_ENABLED                       (MENU_TYPE_INT + 0x0A011002) 

/**
 * \brief UPC-E expand enable.
 */
#define DEC_UPCE_EXPAND                         (MENU_TYPE_INT + 0x0A011003) 

/**
 * \brief UPC-E check digit transmit enable.
 */
#define DEC_UPCE_CHECK_DIGIT_TRANSMIT           (MENU_TYPE_INT + 0x0A011004) 

/**
 * \brief UPC-E number system transmit enable.
 */
#define DEC_UPCE_NUMBER_SYSTEM_TRANSMIT         (MENU_TYPE_INT + 0x0A011005) 

/**
 * \brief UPC-E 2-character addenda enable.
 */
#define DEC_UPCE_2CHAR_ADDENDA_ENABLED          (MENU_TYPE_INT + 0x0A011006) 

/**
 * \brief UPC-E 5-character addenda enable.
 */
#define DEC_UPCE_5CHAR_ADDENDA_ENABLED          (MENU_TYPE_INT + 0x0A011007) 

/**
 * \brief Requires reading an addenda for UPC-E to issue a result.
 */
#define DEC_UPCE_ADDENDA_REQUIRED               (MENU_TYPE_INT + 0x0A011008) 

/**
 * \brief Adds a space between main code and addenda for UPC-E.
 */
#define DEC_UPCE_ADDENDA_SEPARATOR              (MENU_TYPE_INT + 0x0A011009) 

/** @} */

/**
 * \defgroup ean8 EAN-8
 * @{
 */

/**
 * \brief EAN-8 enable.
 */
#define DEC_EAN8_ENABLED                        (MENU_TYPE_INT + 0x0A012001) 

/**
 * \brief EAN-8 check digit transmit enable.
 */
#define DEC_EAN8_CHECK_DIGIT_TRANSMIT           (MENU_TYPE_INT + 0x0A012002) 

/**
 * \brief EAN-8 2-character addenda enable.
 */
#define DEC_EAN8_2CHAR_ADDENDA_ENABLED          (MENU_TYPE_INT + 0x0A012003) 

/**
 * \brief EAN-8 5-character addenda enable.
 */
#define DEC_EAN8_5CHAR_ADDENDA_ENABLED          (MENU_TYPE_INT + 0x0A012004) 

/**
 * \brief Requires reading an addenda for EAN-8 to issue a result.
 */
#define DEC_EAN8_ADDENDA_REQUIRED               (MENU_TYPE_INT + 0x0A012005) 

/**
 * \brief Adds a space between main code and addenda for EAN-8.
 */
#define DEC_EAN8_ADDENDA_SEPARATOR              (MENU_TYPE_INT + 0x0A012006) 

/** @} */

/**
 * \defgroup ean13 EAN-13
 * @{
 */

/**
 * \brief EAN-13 enable.
 */
#define DEC_EAN13_ENABLED                       (MENU_TYPE_INT + 0x0A013001) 

/**
 * \brief EAN-13 check digit transmit enable.
 */
#define DEC_EAN13_CHECK_DIGIT_TRANSMIT          (MENU_TYPE_INT + 0x0A013002) 

/**
 * \brief EAN-13 2-character addenda enable.
 */
#define DEC_EAN13_2CHAR_ADDENDA_ENABLED         (MENU_TYPE_INT + 0x0A013003) 

/**
 * \brief EAN-13 5-character addenda enable.
 */
#define DEC_EAN13_5CHAR_ADDENDA_ENABLED         (MENU_TYPE_INT + 0x0A013004) 

/**
 * \brief Requires reading an addenda for EAN-13 to issue a result.
 */
#define DEC_EAN13_ADDENDA_REQUIRED              (MENU_TYPE_INT + 0x0A013005) 

/**
 * \brief Adds a space between main code and addenda for EAN-13.
 */
#define DEC_EAN13_ADDENDA_SEPARATOR             (MENU_TYPE_INT + 0x0A013006) 

/**
 * \brief EAN-13 ISBN format handling enable.
 */
#define DEC_EAN13_ISBN_ENABLED                  (MENU_TYPE_INT + 0x0A013007)

/**
 * \brief Changes EAN-13 ISBN HHP Code ID, AIM ID, and AIM Modifier.
 */
#define DEC_EAN13_ISBN_IDS_ENABLED              (MENU_TYPE_INT + 0x0A013008)

/**
 * \brief Requires 5 chars addenda for EAN13 starting with 290 to issue a result
 */
#define DEC_EAN13_290_ADDENDA_REQUIRED          (MENU_TYPE_INT + 0x0A013009)

/**
 * \brief Requires addenda (can be 2 chars, 5 chars or both) for EAN13 starting with 378 or 379 to issue a result
 */
#define DEC_EAN13_378_ADDENDA_REQUIRED          (MENU_TYPE_INT + 0x0A01300A)

/**
 * \brief Requires addenda (can be 2 chars, 5 chars or both) for EAN13 starting with 414 or 419 to issue a result
 */
#define DEC_EAN13_414_ADDENDA_REQUIRED          (MENU_TYPE_INT + 0x0A01300B)

/**
 * \brief Requires addenda (can be 2 chars, 5 chars or both) for EAN13 starting with 434 or 439 to issue a result
 */
#define DEC_EAN13_434_ADDENDA_REQUIRED          (MENU_TYPE_INT + 0x0A01300C)
/**
 * \brief Requires 2 chars addenda for EAN13 starting with 977 to issue a result
 */
#define DEC_EAN13_977_ADDENDA_REQUIRED          (MENU_TYPE_INT + 0x0A01300D)

/**
 * \brief Requires 5 chars addenda for EAN13 starting with 978 to issue a result
 */
#define DEC_EAN13_978_ADDENDA_REQUIRED          (MENU_TYPE_INT + 0x0A01300E)

/**
 * \brief Requires 5 chars addenda for EAN13 starting with 979 to issue a result
 */
#define DEC_EAN13_979_ADDENDA_REQUIRED          (MENU_TYPE_INT + 0x0A01300F)

/**
 * \brief Requires addenda (can be 2 chars, 5 chars or both) for EAN13 starting with 491 to issue a result (Japan)
 */
#define DEC_EAN13_491_ADDENDA_REQUIRED          (MENU_TYPE_INT + 0x0A013010)

/** @} */

/**
 * \defgroup code128 Code 128
 * @{
 */

/**
 * \brief Code 128 enable.
 */
#define DEC_CODE128_ENABLED                     (MENU_TYPE_INT + 0x0A014001) 

/**
 * \brief Minimum data length to issue a result for Code 128.
 */
#define DEC_CODE128_MIN_LENGTH                  (MENU_TYPE_INT + 0x0A014002) 

/**
 * \brief Maximum data length to issue a result for Code 128.
 */
#define DEC_CODE128_MAX_LENGTH                  (MENU_TYPE_INT + 0x0A014003)

/**
 * \brief Code 128 append enable.
 */
#define DEC_CODE128_APPEND_ENABLED              (MENU_TYPE_INT + 0x0A014004) 

/** @} */

/**
 * \defgroup gs1128 GS1-128
 * @{
 */

/**
 * \brief GS1-128 enable.
 */
#define DEC_GS1_128_ENABLED                     (MENU_TYPE_INT + 0x0A015001) 

/**
 * \brief Minimum data length to issue a result for GS1-128.
 */
#define DEC_GS1_128_MIN_LENGTH                  (MENU_TYPE_INT + 0x0A015002)

/**
 * \brief Maximum data length to issue a result for GS1-128.
 */
#define DEC_GS1_128_MAX_LENGTH                  (MENU_TYPE_INT + 0x0A015003) 

/** @} */

/**
 * \addtogroup code128
 * @{
 */

/**
 * \brief Code 128 ISBT concatenation enable.
 */
#define DEC_C128_ISBT_ENABLED                   (MENU_TYPE_INT + 0x0A014005) 

/**
 * \brief N/A
 */
#define DEC_C128_FNC1_SUBSTITUTE                (MENU_TYPE_INT + 0x0A014006)

/**
 * \brief Replaces function codes for Code 128.
 */
#define DEC_C128_FNC_TRANSMIT                   (MENU_TYPE_INT + 0x0A014007)

/**
 * \brief Enables FNC4 for Code 128.
 */
#define DEC_C128_FNC4_ENABLED                   (MENU_TYPE_INT + 0x0A014008)

/** @} */

/**
 * \defgroup code39 Code 39
 * @{
 */

/**
 * \brief Code 39 enable.
 */
#define DEC_CODE39_ENABLED                      (MENU_TYPE_INT + 0x0A016001) 

/**
 * \brief Minimum data length to issue a result for Code 39.
 */
#define DEC_CODE39_MIN_LENGTH                   (MENU_TYPE_INT + 0x0A016002) 

/**
 * \brief Maximum data length to issue a result for Code 39.
 */
#define DEC_CODE39_MAX_LENGTH                   (MENU_TYPE_INT + 0x0A016003) 

/**
 * \brief Code 39 check digit mode.
 */
#define DEC_CODE39_CHECK_DIGIT_MODE             (MENU_TYPE_INT + 0x0A016004)

/**
 * \brief Code 39 append enable.
 */
#define DEC_CODE39_APPEND_ENABLED               (MENU_TYPE_INT + 0x0A016005) 

/**
 * \brief Code 39 Full ASCII translation enable.
 */
#define DEC_CODE39_FULL_ASCII_ENABLED           (MENU_TYPE_INT + 0x0A016006)

/**
 * \brief Code 39 Start/Stop character transmite enable.
 */
#define DEC_CODE39_START_STOP_TRANSMIT          (MENU_TYPE_INT + 0x0A016007)

/**
 * \brief Code 39 Base 32 conversion enable.
 */
#define DEC_CODE39_BASE32_ENABLED               (MENU_TYPE_INT + 0x0A016008)

/** @} */

/**
 * \brief TLC 39 Composite enable.
 * \ingroup composite
 */
#define DEC_TLC39_ENABLED                       (MENU_TYPE_INT + 0x0A017001) 

/**
 * \defgroup trioptic Trioptic
 * @{
 */

/**
 * \brief Trioptic Code enable.
 */
#define DEC_TRIOPTIC_ENABLED                    (MENU_TYPE_INT + 0x0A018001) 

/** @} */

/**
 * \defgroup i2of5 Interleaved 2 of 5
 * @{
 */

/**
 * \brief Interleaved 2 of 5 Code enable.
 */
#define DEC_I25_ENABLED                         (MENU_TYPE_INT + 0x0A019001) 

/**
 * \brief Minimum data length to issue a result for Interleaved 2 of 5.
 */
#define DEC_I25_MIN_LENGTH                      (MENU_TYPE_INT + 0x0A019002) 

/**
 * \brief Maximum data length to issue a result for Interleaved 2 of 5.
 */
#define DEC_I25_MAX_LENGTH                      (MENU_TYPE_INT + 0x0A019003) 

/**
 * \brief Interleaved 2 of 5 check digit mode.
 */
#define DEC_I25_CHECK_DIGIT_MODE                (MENU_TYPE_INT + 0x0A019004) 

/** @} */

/**
 * \defgroup s2of5 Straight 2 of 5
 * @{
 */

/**
 * \brief Straight 2 of 5 enable. Also called Industrial 2 of 5.
 */
#define DEC_S25_ENABLED                         (MENU_TYPE_INT + 0x0A01A001) 

/**
 * \brief Minimum data length to issue a result for Straight 2 of 5. 
 */
#define DEC_S25_MIN_LENGTH                      (MENU_TYPE_INT + 0x0A01A002) 

/**
 * \brief Maximum data length to issue a result for Straight 2 of 5.
 */
#define DEC_S25_MAX_LENGTH                      (MENU_TYPE_INT + 0x0A01A003) 

/** @} */

/**
 * \defgroup iata2of5 IATA 2 of 5
 * @{
 */

/**
 * \brief IATA 2 of 5 enable. Also called Airline 2 of 5.
 */
#define DEC_IATA25_ENABLED                      (MENU_TYPE_INT + 0x0A01B001) 

/**
 * \brief Minimum data length to issue a result for IATA 2 of 5.
 */
#define DEC_IATA25_MIN_LENGTH                   (MENU_TYPE_INT + 0x0A01B002) 

/**
 * \brief Maximum data length to issue a result for IATA 2 of 5.
 */
#define DEC_IATA25_MAX_LENGTH                   (MENU_TYPE_INT + 0x0A01B003) 

/** @} */

/**
 * \defgroup matrix2of5 Matrix 2 of 5
 * @{
 */

/**
 * \brief Matrix 2 of 5 enable.
 */
#define DEC_M25_ENABLED                         (MENU_TYPE_INT + 0x0A01C001) 

/**
 * \brief Minimum data length to issue a result for Matrix 2 of 5.
 */
#define DEC_M25_MIN_LENGTH                      (MENU_TYPE_INT + 0x0A01C002) 

/**
 * \brief Maximum data length to issue a result for Matrix 2 of 5.
 */
#define DEC_M25_MAX_LENGTH                      (MENU_TYPE_INT + 0x0A01C003) 

/** @} */

/**
 * \defgroup nec2of5 NEC 2 of 5
 * @{
 */

/**
 * \brief NEC 2 of 5 enable.
 */
#define DEC_NEC25_ENABLED                       (MENU_TYPE_INT + 0x0A02F001)

/**
 * \brief Minimum data length to issue a result for NEC 2 of 5.
 */
#define DEC_NEC25_MIN_LENGTH                    (MENU_TYPE_INT + 0x0A02F002)

/**
 * \brief Maximum data length to issue a result for NEC 2 of 5.
 */
#define DEC_NEC25_MAX_LENGTH                    (MENU_TYPE_INT + 0x0A02F003)

/** @} */

/**
 * \defgroup code93 Code 93
 * @{
 */

/**
 * \brief Code 93 enable.
 */
#define DEC_CODE93_ENABLED                      (MENU_TYPE_INT + 0x0A01D001) 

/**
 * \brief Minimum data length to issue a result for Code 93.
 */
#define DEC_CODE93_MIN_LENGTH                   (MENU_TYPE_INT + 0x0A01D002)

/**
 * \brief Maximum data length to issue a result for Code 93.
 */
#define DEC_CODE93_MAX_LENGTH                   (MENU_TYPE_INT + 0x0A01D003) 

/**
 * \brief Code 93 append enable.
 */
#define DEC_CODE93_APPEND_ENABLED               (MENU_TYPE_INT + 0x0A01D004)

/** @} */

/**
 * \defgroup code11 Code 11
 * @{
 */

/**
 * \brief Code 11 enable.
 */
#define DEC_CODE11_ENABLED                      (MENU_TYPE_INT + 0x0A01E001) 

/**
 * \brief Minimum data length to issue a result for Code 11.
 */
#define DEC_CODE11_MIN_LENGTH                   (MENU_TYPE_INT + 0x0A01E002) 

/**
 * \brief Maximum data length to issue a result for Code 11.
 */
#define DEC_CODE11_MAX_LENGTH                   (MENU_TYPE_INT + 0x0A01E003) 

/** @} */

/**
 * \defgroup codabar Codabar
 * @{
 */

/**
 * \brief Codabar enable.
 */
#define DEC_CODABAR_ENABLED                     (MENU_TYPE_INT + 0x0A01F001) 

/**
 * \brief Minimum data length to issue a result for Codabar.
 */
#define DEC_CODABAR_MIN_LENGTH                  (MENU_TYPE_INT + 0x0A01F002) 

/**
 * \brief Maximum data length to issue a result for Codabar.
 */
#define DEC_CODABAR_MAX_LENGTH                  (MENU_TYPE_INT + 0x0A01F003) 

/**
 * \brief Codabar Start/Stop character transmit enable.
 */
#define DEC_CODABAR_START_STOP_TRANSMIT         (MENU_TYPE_INT + 0x0A01F004) 

/**
 * \brief Codabar check digit mode.
 */
#define DEC_CODABAR_CHECK_DIGIT_MODE            (MENU_TYPE_INT + 0x0A01F005) 

/**
 * \brief Codabar concatenation enable.
 */
#define DEC_CODABAR_CONCAT_ENABLED              (MENU_TYPE_INT + 0x0A01F007) 

/**
 * \brief Specifies the expected number of pieces to issue a concatenated result for Codabar.
 */
#define DEC_CODABAR_CONCAT_TARGET               (MENU_TYPE_INT + 0x0A01F008) 

/** @} */

/**
 * \defgroup telepen Telepen
 * @{
 */

/**
 * \brief Telepen enable.
 */
#define DEC_TELEPEN_ENABLED                     (MENU_TYPE_INT + 0x0A020001) 

/**
 * \brief Minimum data length to issue a result for Telepen.
 */
#define DEC_TELEPEN_MIN_LENGTH                  (MENU_TYPE_INT + 0x0A020002) 

/**
 * \brief Maximum data length to issue a result for Telepen.
 */
#define DEC_TELEPEN_MAX_LENGTH                  (MENU_TYPE_INT + 0x0A020003) 

/** @} */

/**
 * \defgroup msi MSI
 * @{
 */ 

/**
 * \brief MSI enable.
 */
#define DEC_MSI_ENABLED                         (MENU_TYPE_INT + 0x0A021001) 

/**
 * \brief Minimum data length to issue a result for MSI.
 */
#define DEC_MSI_MIN_LENGTH                      (MENU_TYPE_INT + 0x0A021002) 

/**
 * \brief Maximum data length to issue a result for MSI.
 */
#define DEC_MSI_MAX_LENGTH                      (MENU_TYPE_INT + 0x0A021003) 

/** @} */

/**
 * \defgroup gs1databar GS1-Databar
 * @{
 */ 

/**
 * \brief GS1-Databar enable.
 */
#define DEC_RSS_14_ENABLED                      (MENU_TYPE_INT + 0x0A022001) 

/**
 * \brief GS1-Databar Limited enable.
 */
#define DEC_RSS_LIMITED_ENABLED                 (MENU_TYPE_INT + 0x0A022002) 

/**
 * \brief GS1-Databar Expanded enable.
 */
#define DEC_RSS_EXPANDED_ENABLED                (MENU_TYPE_INT + 0x0A022003) 

/**
 * \brief Minimum data length to issue a result for GS1-Databar Expanded.
 */
#define DEC_RSS_EXPANDED_MIN_LENGTH             (MENU_TYPE_INT + 0x0A022004) 

/**
 * \brief Maximum data length to issue a result for GS1-Databar Expanded.
 */
#define DEC_RSS_EXPANDED_MAX_LENGTH             (MENU_TYPE_INT + 0x0A022005) 

/** @} */

/**
 * \defgroup codablock Codablock
 * @{
 */

/**
 * \brief Codablock A enable.
 */
#define DEC_CODABLOCK_A_ENABLED                 (MENU_TYPE_INT + 0x0A030001)

/**
 * \brief Minimum data length to issue a result for Codablock A.
 */
#define DEC_CODABLOCK_A_MIN_LENGTH              (MENU_TYPE_INT + 0x0A030002)

/**
 * \brief Maximum data length to issue a result for Codablock A.
 */
#define DEC_CODABLOCK_A_MAX_LENGTH              (MENU_TYPE_INT + 0x0A030003)

/**
 * \brief Codablock F enable.
 */
#define DEC_CODABLOCK_F_ENABLED                 (MENU_TYPE_INT + 0x0A023001) 

/**
 * \brief Minimum data length to issue a result for Codablock F.
 */
#define DEC_CODABLOCK_F_MIN_LENGTH              (MENU_TYPE_INT + 0x0A023002) 

/**
 * \brief Maximum data length to issue a result for Codablock F.
 */
#define DEC_CODABLOCK_F_MAX_LENGTH              (MENU_TYPE_INT + 0x0A023003) 

/** @} */

/**
 * \defgroup pdf417 PDF417
 * @{
 */

/**
 * \brief PDF417 enable.
 */
#define DEC_PDF417_ENABLED                      (MENU_TYPE_INT + 0x0A024001) 

/**
 * \brief Minimum data length to issue a result for PDF417.
 */
#define DEC_PDF417_MIN_LENGTH                   (MENU_TYPE_INT + 0x0A024002) 

/**
 * \brief Maximum data length to issue a result for PDF417.
 */
#define DEC_PDF417_MAX_LENGTH                   (MENU_TYPE_INT + 0x0A024003) 

/**
 * \brief N/A
 */
#define DEC_PDF417_SHOW_GLI                     (MENU_TYPE_INT + 0x0A024004)

/**
 * \brief Macro PDF417 append enable.
 */
#define DEC_PDF417_MACRO_ENABLED                (MENU_TYPE_INT + 0x0A024005)

/**
 * \brief Issues the Macro PDF417 data to the end of the result.
 */
// deprecated
// #define DEC_PDF417_SHOW_MACRO                   (MENU_TYPE_INT + 0x0A024006)

/**
 * \brief Controls the number of images the decoder will hold partially decoded PDF417 info.
 */
#define DEC_PDF417_HISTORY_EXPIRE_COUNT         (MENU_TYPE_INT + 0x0A024007)

/** @} */

/**
 * \defgroup micropdf MicroPDF 417
 * @{
 */

/**
 * \brief MicroPDF417 enable.
 */
#define DEC_MICROPDF_ENABLED                    (MENU_TYPE_INT + 0x0A025001) 

/**
 * \brief Minimum data length to issue a result for MicroPDF417.
 */
#define DEC_MICROPDF_MIN_LENGTH                 (MENU_TYPE_INT + 0x0A025002) 

/**
 * \brief Maximum data length to issue a result for MicroPDF417.
 */
#define DEC_MICROPDF_MAX_LENGTH                 (MENU_TYPE_INT + 0x0A025003) 

/** @} */

/**
 * \defgroup composite Composite
 * @{
 */

/**
 * \brief Composite code enable.
 */
#define DEC_COMPOSITE_ENABLED                   (MENU_TYPE_INT + 0x0A026001) 

/**
 * \brief Minimum data length to issue a result for a composite code.
 */
#define DEC_COMPOSITE_MIN_LENGTH                (MENU_TYPE_INT + 0x0A026002) 

/**
 * \brief Maximum data length to issue a result for a composite code.
 */
#define DEC_COMPOSITE_MAX_LENGTH                (MENU_TYPE_INT + 0x0A026003) 

/**
 * \brief Allows UPC codes to be read with PDF417 or MicroPDF417 composite.
 */
#define DEC_COMPOSITE_WITH_UPC_ENABLED          (MENU_TYPE_INT + 0x0A026004)

/** @} */

/**
 * \defgroup aztec Aztec
 * @{
 */

/**
 * \brief Aztec Code enable.
 */
#define DEC_AZTEC_ENABLED                       (MENU_TYPE_INT + 0x0A027001) 

/**
 * \brief Minimum data length to issue a result for Aztec Code.
 */
#define DEC_AZTEC_MIN_LENGTH                    (MENU_TYPE_INT + 0x0A027002) 

/**
 * \brief Maximum data length to issue a result for Aztec Code.
 */
#define DEC_AZTEC_MAX_LENGTH                    (MENU_TYPE_INT + 0x0A027003) 

/**
 * \brief Aztec Code append enable.
 */
#define DEC_AZTEC_APPEND_ENABLED                (MENU_TYPE_INT + 0x0A027004) 

/**
 * \brief Removes append information before issuing a result for Aztec Code.
 */
#define DEC_AZTEC_APPEND_STRIP_INFO             (MENU_TYPE_INT + 0x0A027005)

/** @} */

/**
 * \defgroup maxicode Maxicode
 * @{
 */

/**
 * \brief Maxicode enable.
 */
#define DEC_MAXICODE_ENABLED                    (MENU_TYPE_INT + 0x0A028001) 

/**
 * \brief Minimum data length to issue a result for Maxicode.
 */
#define DEC_MAXICODE_MIN_LENGTH                 (MENU_TYPE_INT + 0x0A028002) 

/**
 * \brief Maximum data length to issue a result for Maxicode.
 */
#define DEC_MAXICODE_MAX_LENGTH                 (MENU_TYPE_INT + 0x0A028003) 

/** @} */

/**
 * \defgroup datamatrix Data Matrix
 * @{
 */

/**
 * \brief Data Matrix enable.
 */
#define DEC_DATAMATRIX_ENABLED                  (MENU_TYPE_INT + 0x0A029001) 

/**
 * \brief Minimum data length to issue a result for Data Matrix.
 */
#define DEC_DATAMATRIX_MIN_LENGTH               (MENU_TYPE_INT + 0x0A029002) 

/**
 * \brief Maximum data length to issue a result for Data Matrix.
 */
#define DEC_DATAMATRIX_MAX_LENGTH               (MENU_TYPE_INT + 0x0A029003) 

/** @} */

/**
 * \defgroup qr QR Code
 * @{
 */

/**
 * \brief QR Code enable.
 */
#define DEC_QR_ENABLED                          (MENU_TYPE_INT + 0x0A02A001) 

/**
 * \brief Minimum data length to issue a result for QR Code.
 */
#define DEC_QR_MIN_LENGTH                       (MENU_TYPE_INT + 0x0A02A002) 

/**
 * \brief Maximum data length to issue a result for QR Code.
 */
#define DEC_QR_MAX_LENGTH                       (MENU_TYPE_INT + 0x0A02A003) 

/**
 * \brief QR Code append enable.
 */
#define DEC_QR_APPEND_ENABLED                   (MENU_TYPE_INT + 0x0A02A004) 

/** @} */

/**
 * \defgroup hanxin Han Xin Code
 * @{
 */

/**
 * \brief Han Xin Code enable.
 */
#define DEC_HANXIN_ENABLED                      (MENU_TYPE_INT + 0x0A02B001) 

/**
 * \brief Minimum data length to issue a result for Han Xin Code.
 */
#define DEC_HANXIN_MIN_LENGTH                   (MENU_TYPE_INT + 0x0A02B002) 

/**
 * \brief Maximum data length to issue a result for Han Xin Code.
 */
#define DEC_HANXIN_MAX_LENGTH                   (MENU_TYPE_INT + 0x0A02B003)  

/**
 * \defgroup gridmatrix Grid Matrix Code
 * @{
 */

/**
 * \brief Grid Matrix Code enable.
 */
#define DEC_GRIDMATRIX_ENABLED                  (MENU_TYPE_INT + 0x0A160001) 

/**
 * \brief Minimum data length to issue a result for Grid Matrix Code.
 */
#define DEC_GRIDMATRIX_MIN_LENGTH               (MENU_TYPE_INT + 0x0A160002) 

/**
 * \brief Maximum data length to issue a result for Grid Matrix Code.
 */
#define DEC_GRIDMATRIX_MAX_LENGTH               (MENU_TYPE_INT + 0x0A160003)  

/**
 * \defgroup dotcode DotCode
 * @{
 */

/**
 * \brief DotCode enable.
 */
#define DEC_DOTCODE_ENABLED                     (MENU_TYPE_INT + 0x0A161001) 

/**
 * \brief Minimum data length to issue a result for DotCode.
 */
#define DEC_DOTCODE_MIN_LENGTH                  (MENU_TYPE_INT + 0x0A161002) 

/**
 * \brief Maximum data length to issue a result for DotCode.
 */
#define DEC_DOTCODE_MAX_LENGTH                  (MENU_TYPE_INT + 0x0A161003)  



/** @} */

/**
 * \defgroup ocr OCR
 * @{
 */

/**
 * \brief Optical Character Recognition mode.
 */
#define DEC_OCR_MODE                            (MENU_TYPE_INT + 0x0A02D001)

/**
 * \brief Template for reading Optical Characters. 
 */
#define DEC_OCR_TEMPLATE                        (MENU_TYPE_INT + MENU_TYPE_ARRAY + 0x0A02D002)

/** \brief Number of images allowed between the reading of rows for Passports, Travel Documents, and Visas.
 * 
 * Passports are read row-by-row, so each row is considered a Partial Result until all rows
 * for the particular passport type are read. Each call to Decode() is considered a new image.
 * This setting allows the user to specify how many images are allowed before partial results
 * are cleared.
 * 
 * \see Partial Result
 * \see ClearDecoderResults
 */
#define DEC_OCR_SECURITY                        (MENU_TYPE_INT + 0x0A02D003) 

/** @} */

/**
 * \defgroup hk2of5 Hong Kong 2 of 5
 * @{
 */ 

/**
 * \brief Hong Kong 2 of 5 enable. Also called China Post.
 */
#define DEC_HK25_ENABLED                        (MENU_TYPE_INT + 0x0A02C001) 

/**
 * \brief Minimum data length to issue a result for Hong Kong 2 of 5.
 */
#define DEC_HK25_MIN_LENGTH                     (MENU_TYPE_INT + 0x0A02C002) 

/**
 * \brief Maximum data length to issue a result for Hong Kong 2 of 5.
 */
#define DEC_HK25_MAX_LENGTH                     (MENU_TYPE_INT + 0x0A02C003)  

/** @} */

/**
 * \defgroup koreapost Korea Post
 * @{
 */

/**
 * \brief Korea Post enable.
 */
#define DEC_KOREA_POST_ENABLED                  (MENU_TYPE_INT + 0x0A100001)

/**
 * \brief Minimum data length to issue a result for Korea Post.
 */
#define DEC_KOREA_POST_MIN_LENGTH               (MENU_TYPE_INT + 0x0A100002)

/**
 * \brief Maximum data length to issue a result for Korea Post.
 */
#define DEC_KOREA_POST_MAX_LENGTH               (MENU_TYPE_INT + 0x0A100003)

/**
 * \brief Korea Post check digit transmit enable.
 */
#define DEC_KOREA_POST_CHECK_DIGIT_TRANSMIT     (MENU_TYPE_INT + 0x0A100004)

/** @} */

/**
 * \defgroup labelcode Label Code
 * @{
 */

/**
 * \brief Label Code enable.
 */
#define DEC_LABELCODE_ENABLED                   (MENU_TYPE_INT + 0x0A101001) 

/** @} */

/**
 * \defgroup postal Postal Codes
 * @{
 */

/**
 * \brief Postal Symbologies enable.
 */
#define DEC_POSTAL_ENABLED                      (MENU_TYPE_INT + 0x0A110001)

/**
 * \brief Direct configuration of Postal Symbologies.
 */
#define DEC_POSTAL_ENABLED_DIRECT               (MENU_TYPE_INT + 0x0A110002)

/**
 * \brief Postnet check digit transmit enable.
 */
#define DEC_POSTNET_CHECK_DIGIT_TRANSMIT        (MENU_TYPE_INT + 0x0A120001)

/**
 * \brief Planetcode check digit transmit enable.
 */
#define DEC_PLANETCODE_CHECK_DIGIT_TRANSMIT     (MENU_TYPE_INT + 0x0A130001)

/** @} */

/**
 * \defgroup FLDmisc FLD Misc
 * @{
 */
 
/**
 * \brief Defines the search area for FLD (0:centre only or 1:full image).
 */
#define DEC_FLD_SEARCH_AREA                     0xFD012002

/**
 * \brief Defines the amount of summing for FLD (from 0:no summing to 2:5 pixels).
 */
#define DEC_FLD_SUMMING                         0xFD012003

/**
 * \brief Defines if all FLD decode filters are applied on the same image (0) or on several images (1).
 */
#define DEC_FLD_ROLLING_FILTERS                 0xFD012004

 /**
 * \brief Allows FLD to decode Code 39 barcodes with unconventional inter characters.
 */
#define DEC_FLD_CODE39_UNCONV_INTER_CHAR        0xFD004009

/** @} */

/** @} */
#endif //DECODER_SETTINGS_H
