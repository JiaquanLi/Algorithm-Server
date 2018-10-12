//======================================================================================
// SwiftSettings.h
//======================================================================================

//---------------------------------------------------------------------------
//
//  Module Interface Description:
//      This file contains the configurable settings that apply only when the Swift decoder
//      is used. 
//
//---------------------------------------------------------------------------

/* Copyright 2017, Honeywell.  All Rights Reserved */

#ifndef SWIFT_SETTINGS_H
#define SWIFT_SETTINGS_H

/* Decoder Menu Types 
 *   These are the expected type for each command. They are embedded in the menu tag so 
 *   the user knows what type of information to pass into the menu function
 */
#define MENU_TYPE_INT        0x10000000
#define MENU_TYPE_STRING     0x20000000
#define MENU_TYPE_BITFIELD   0x40000000
#define MENU_TYPE_MASK       0xF0000000

/**
 *   \brief Specifies the minimum expected height of a 1D barcode.
 */
#define DEC_MIN_1D_HEIGHT                    (MENU_TYPE_INT + 0x0B003001)

/**
 *   \brief Specifies whether a Micro-QR symbolg will have its own HHP Code ID.
 *   \ingroup qr
 */
#define DEC_QR_USE_ALT_MICROQR_ID            (MENU_TYPE_INT + 0x0B02A003)

/**
 *   \brief Pharmacode enable.
 */
#define DEC_PHARMACODE_ENABLED               (MENU_TYPE_INT + 0x0B02E001)

/** @} */

/**
 *   \brief Go Code enable.
 *   \ingroup misctags
 */
#define DEC_GOCODE_ENABLED                   (MENU_TYPE_INT + 0x0B031001)


/**
 *   \brief Specifies which templates are active for decoding an OCR string.
 */
#define DEC_OCR_ACTIVE_TEMPLATES             (MENU_TYPE_INT + 0x0B02D003) 

/**
 *   \brief Specifies whether user templates that contain spaces and new lines are broken into individual templates.
 */
#define DEC_OCR_SEPARATE_TEMPLATE            (MENU_TYPE_INT + 0x0B02D004) 

/**
 *   \brief Specifies whether ICAO checksum calculations are preformed.
 */
#define DEC_OCR_PASSPORT_IGNORE_CHECKSUM     (MENU_TYPE_INT + 0x0B02D006)

/** @} */


// Properties that are managed directely by ID decoder (direct passthrough)
#define DEC_ID_PROP_USE_ROI                          0x40008015
#define DEC_SD_PROP_MC_MESSAGE_FORMAT                0x40010603
#define DEC_DPM_ENABLED                              0x40012903
#define DEC_MSIP_SHORT_MARGIN                        0x40011604
#define DEC_PROP_MSIP_OUT_OF_SPEC_SYMBOL             0x40011605

#define DEC_USE_DISTANCE_MAP                         0x40100002
#define DEC_AGC_EXPOSURE_QUALITY                     0x40002001
#define DEC_AGC_NEXT_GAIN                            0x40002002
#define DEC_AGC_SAMPLING_OPTIONS                     0x40002003
#define DEC_AUS_POST_INTERPRET_MODE                  0x40010818

#define DEC_AZTEC_SYMBOL_SIZE                        0x40011202
#define DEC_BLACK_LEVEL                              0x40005013
#define DEC_C128_IMPROVE_BOUNDS                      0x40010208
#define DEC_C128_PARTIAL                             0x40010207
#define DEC_C128_SHORT_MARGIN                        0x40010202

#define DEC_CODABAR_IMPROVE_BOUNDS                   0x40010104
#define DEC_CODABAR_SHORT_MARGIN                     0x40010103
#define DEC_CODE39_SHORT_MARGIN                      0x40010304
#define DEC_CODE39_SUPPRESS_CODABLOCK_CONFLICT       0x40010306
#define DEC_CODE93_IMPROVE_BOUNDS                    0x40011103

#define DEC_CODE93_SHORT_MARGIN                      0x40011102
#define DEC_CYCLING_FINDER                           0x40100006
#define DEC_DATAMATRIX_BINARY_IMPROVEMENTS           0x40010415
#define DEC_DATAMATRIX_SYMBOL_SIZE                   0x40010416
#define DEC_EDGE_DETECTOR                            0x40100003

#define DEC_GENERAL_IMPROVEMENTS                     0x40005011
#define DEC_I25_IMPROVE_BOUNDS                       0x40010506
#define DEC_I25_PARTIAL                              0x40010505
#define DEC_I25_SHORT_MARGIN                         0x40010504
#define DEC_IATA25_IMPROVE_BOUNDS                    0x40011505

#define DEC_IMAGE_MIRRORED                           0x40004003
#define DEC_ISSUE_IDENTICAL_SPACING                  0x40005019
#define DEC_ISSUE_IDENTICAL_SYMBOLS                  0x40005004
#define DEC_LINEAR_DAMAGE_IMPROVEMENTS               0x40005025
#define DEC_LOW_ASPECT_RATIO                         0x40005005

#define DEC_LOW_CONTRAST_IMPROVEMENTS                0x40005006
#define DEC_M25_CHECK_DIGIT_MODE                     0x40011902
#define DEC_PHARMACODE_COLOR_BARS                    0x40011708
#define DEC_PHARMACODE_MAX_BAR_COUNT                 0x40011703
#define DEC_PHARMACODE_MIN_VALUE                     0x40011704

#define DEC_PHARMACODE_MAX_VALUE                     0x40011705
#define DEC_PHARMACODE_MIN_BAR_COUNT                 0x40011702
#define DEC_PHARMACODE_ORIENTATION                   0x40011706
#define DEC_PHARMACODE_REVERSE                       0x40011707
#define DEC_QR_NON_SQUARE_MODULES                    0x40010902

#define DEC_QR_SYMBOL_SIZE                           0x40010904
#define DEC_POSTAL_MIN_BAR_COUNT                     0x40010802
#define DEC_POSTAL_MAX_BAR_COUNT                     0x40010804
#define DEC_POSTAL_ORIENTATIONS                      0x40010803
#define DEC_POSTAL_SUBREGION_HEIGHT                  0x40010812

#define DEC_POSTAL_SUBREGION_LEFT                    0x40010809
#define DEC_POSTAL_SUBREGION_TOP                     0x40010810
#define DEC_POSTAL_SUBREGION_WIDTH                   0x40010811
#define DEC_POSTAL_UNDECODABLE_HEIGHT                0x40010808
#define DEC_POSTAL_UNDECODABLE_LEFT                  0x40010805

#define DEC_POSTAL_UNDECODABLE_TOP                   0x40010806
#define DEC_POSTAL_UNDECODABLE_WIDTH                 0x40010807
#define DEC_ROYAL_MAIL_FORMAT_CHECK_MIN_LENGTH       0x40010815
#define DEC_AUS_POST_BAR_OUTPUT_ENABLED              0x40010817
#define DEC_AUS_POST_ZERO_FCC                        0x40010813

#define DEC_CAN_POST_BAR_OUTPUT                      0x40010819
#define DEC_DATAMATRIX_MIN_MODULE_COUNT              0x40010405
#define DEC_DATAMATRIX_MAX_MODULE_COUNT              0x40010403
#define DEC_DATAMATRIX_MIN_MODULE_SIZE               0x40010406
#define DEC_DATAMATRIX_MAX_MODULE_SIZE               0x40010404

#define DEC_DATAMATRIX_ORIENTATIONS                  0x40010407
#define DEC_DATAMATRIX_NON_SQUARE_MODULES            0x40010412
#define DEC_DATAMATRIX_SHIFTED_TILES                 0x40010413
#define DEC_DATAMATRIX_LOW_CONTRAST                  0x40010414
#define DEC_DATAMATRIX_RECTANGLE                     0x40010402

#define DEC_DATAMATRIX_SUBREGION_HEIGHT              0x40010411
#define DEC_DATAMATRIX_SUBREGION_LEFT                0x40010408
#define DEC_DATAMATRIX_SUBREGION_TOP                 0x40010409
#define DEC_DATAMATRIX_SUBREGION_WIDTH               0x40010410
#define DEC_HK25_IMPROVE_BOUNDS                      0x40012603

#define DEC_MAXICODE_SYMBOL_SIZE                     0x40010602
#define DEC_KOREA_POST_REVERSE                       0x40013503
#define DEC_PDF417_ENHANCED_DAMAGE_HANDLING          0x40010710
#define DEC_MICROPDF_IMPROVE_BOUNDS                  0x40010704
#define DEC_OCR_BUSY_BACKGROUND                      0x40012308

#define DEC_MSI_CHECK_DIGIT_MODE                     0x40011602
#define DEC_MSI_IMPROVE_BOUNDS                       0x40011603
#define DEC_TELEPEN_OLD_STYLE                        0x40012102
#define DEC_TELEPEN_IMPROVE_BOUNDS                   0x40012103
#define DEC_CODE11_CHECK_DIGIT_MODE                  0x40011802

#define DEC_CODE11_IMPROVE_BOUNDS                    0x40011803
#define DEC_NEC25_CHECK_DIGIT_MODE                   0x40012202
#define DEC_NEC25_IMPROVE_BOUNDS                     0x40012204
#define DEC_M25_IMPROVE_BOUNDS                       0x40011904
#define DEC_S25_IMPROVE_BOUNDS                       0x40011506

#define DEC_TRIOPTIC_SHORT_MARGIN                    0x40010308
#define DEC_UPC_IMPROVE_BOUNDS                       0x40011006
#define DEC_UPC_SHORT_MARGIN                         0x40011004
#define DEC_C128_SUPPRESS_CODABLOCK_CONFLICT         0x40010206
#define DEC_CODE39_IMPROVE_BOUNDS                    0x40010310

#define DEC_CODE39_PARTIAL                           0x40010309
#define DEC_SUBREGION_HEIGHT                         0x40012004
#define DEC_SUBREGION_LEFT                           0x40012001
#define DEC_SUBREGION_TOP                            0x40012002
#define DEC_SUBREGION_WIDTH                          0x40012003

#define DEC_SUBPIXEL_FINDER                          0x40100004
#define DEC_MISENCODED_SYMBOLS                       0x40005009
#define DEC_PASS_THROUGH                             0x40005016
#define DEC_UNDECODABLE_SYMBOLS                      0x40005008
#define DEC_CODE93_HIGH_DENSITY                      0x40011104

#define DEC_UNDECODABLE_SYMBOLS_EX                   0x40005014
#define DEC_SUBREGION_PROCESSING                     0x40005010
#define DEC_CELL_PHONE_IMPROVEMENTS                  0x40005020
#define DEC_OPERATING_MODE                           0x40005003
#define DEC_TYPICAL_IMAGE_DENSITY                    0x40004006

#define DEC_PDF417_HISTORY_MIN_MATCH_PERCENT         0x40010709
#define DEC_CLEAR_HISTORY                            0x40010705

#define DEC_DOTCODE_EXTENSIVE_SEARCH                 0x40016004

/** @} */
#endif //SWIFT_SETTINGS_H
