/****************************************************************************
   SD.H - header file containing definitions and function prototypes
****************************************************************************/
/* Copyright 1998-2017, Honeywell International, Incorporated.  All Rights Reserved */

/* Preamble */
#ifndef SD_H_INCLUDED
#define SD_H_INCLUDED

/* Check if this is a DLL build */
#if defined(SD_API2_IS_DLL)
   #define SD_STDCALL2 __stdcall
   #ifndef SD_API2
      #define SD_API2 __declspec(dllimport)   /* customer applications import from DLL */
   #endif   /* !SD_API */
#elif __GNUC__ >= 4
   #define SD_STDCALL2
   #define SD_API2 __attribute__((visibility("default")))
#else
   #define SD_STDCALL2
   #define SD_API2 
#endif   /* SD_IS_DLL */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Definitions */


/* Status Codes */
#define  SD_STATUS_NO_COMPOSITE           0x001
#define  SD_STATUS_COARSE_FIND_COMPLETE   0x002
#define  SD_STATUS_DM_BEGIN               0x003
#define  SD_STATUS_DM_COMPLETE            0x004
#define  SD_STATUS_PDF_BEGIN              0x005
#define  SD_STATUS_PDF_COMPLETE           0x006
#define  SD_STATUS_NO_PACKAGE             0x007
#define  SD_STATUS_QR_BEGIN               0x008
#define  SD_STATUS_QR_COMPLETE            0x009
#define  SD_STATUS_SKIP_CHUNK             0x00A
#define  SD_STATUS_MC_BEGIN               0x00B
#define  SD_STATUS_MC_COMPLETE            0x00C
#define  SD_STATUS_AZ_BEGIN               0x00D
#define  SD_STATUS_AZ_COMPLETE            0x00E
#define  SD_STATUS_PROCESSING_CELLPHONE   0x00F
#define  SD_STATUS_DM_SEARCH_BEGIN        0x100
#define  SD_STATUS_DM_SEARCH_END          0x101



/* Definitions->Constants->Components and Symbologies */
#define  SD_CONST_CORE     (1 << 0)
#define  SD_CONST_AGC      (1 << 1)
#define  SD_CONST_UPC      (1 << 2)
#define  SD_CONST_AP       (1 << 3)
#define  SD_CONST_C128     (1 << 4)
#define  SD_CONST_C39      (1 << 5)
#define  SD_CONST_CB       (1 << 6)
#define  SD_CONST_PL       (1 << 7)
#define  SD_CONST_DM       (1 << 8)
#define  SD_CONST_I25      (1 << 9)
#define  SD_CONST_MANOP    (1 << 10)
#define  SD_CONST_MC       (1 << 11)
#define  SD_CONST_PDF      (1 << 12)
#define  SD_CONST_PN       (1 << 13)
#define  SD_CONST_QR       (1 << 14)
#define  SD_CONST_RSS      (1 << 15)
#define  SD_CONST_UNOP     (1 << 16)
#define  SD_CONST_JP       (1 << 17)
#define  SD_CONST_C93      (1 << 18)
#define  SD_CONST_AZ       (1 << 19)
#define  SD_CONST_PD       (1 << 20)
#define  SD_CONST_RM       (1 << 21)
#define  SD_CONST_S25      (1 << 22)
#define  SD_CONST_MSIP     (1 << 23)
#define  SD_CONST_DP       (1 << 25)
#define  SD_CONST_PHARMA   (1 << 26)
#define  SD_CONST_UPU      (1 << 27)
#define  SD_CONST_C11      (1 << 28)
#define  SD_CONST_USPS4CB  (1U << 31U)

/* The following definitions apply to EX Properties */
#define  SD_CONST_M25      (1 << 0)
#define  SD_CONST_TP       (1 << 1)
#define  SD_CONST_NEC25    (1 << 2)
#define  SD_CONST_TRIOPTIC (1 << 3)
#define  SD_CONST_OCR      (1 << 4)
#define  SD_CONST_VER1D    (1 << 5)
#define  SD_CONST_HK25     (1 << 6)
#define  SD_CONST_VERPN    (1 << 7)
#define  SD_CONST_VERPDF   (1 << 9)
#define  SD_CONST_INFOMAIL (1 << 12)
#define  SD_CONST_VER2D    (1 << 13)
#define  SD_CONST_KP       (1 << 14)
#define  SD_CONST_CP       (1 << 16)
#define  SD_CONST_LC       (1 << 17)
#define  SD_CONST_SP       (1 << 18)
#define  SD_CONST_EIB      (1 << 19)
#define  SD_CONST_BZ4      (1 << 20)
#define  SD_CONST_GM       (1 << 22)
#define  SD_CONST_DOTCODE  (1 << 23)

/* Definitions->Constants->Symbologies */
#define  SD_CONST_RSS_EXP            ((SD_CONST_RSS) + 1)
#define  SD_CONST_RSS_EXP_ST         ((SD_CONST_RSS) + 2)
#define  SD_CONST_RSS_14_LIM         ((SD_CONST_RSS) + 4)
#define  SD_CONST_RSS_14             ((SD_CONST_RSS) + 8)
#define  SD_CONST_RSS_14_ST          ((SD_CONST_RSS) + 16)
#define  SD_CONST_BF                 (1)
#define  SD_CONST_CEPNET             (2)
#define  SD_CONST_KIX                ((SD_CONST_RM) + 1)
#define  SD_CONST_UNDECODABLE_POSTAL (1 << 3)
#define  SD_CONST_S25_2SS            (SD_CONST_S25)
#define  SD_CONST_S25_3SS            ((SD_CONST_S25) + 1)
#define  SD_CONST_CODABLOCK_A        ((SD_CONST_C39) + 1)
#define  SD_CONST_CODABLOCK_F        ((SD_CONST_C128) + 1)

/* Definitions->Constants->Symbology Groups */
#define SD_CONST_SYMBOLOGIES_GROUP ((SD_CONST_UPC) | \
                                    (SD_CONST_AP) | \
                                    (SD_CONST_JP) | \
                                    (SD_CONST_PL) | \
                                    (SD_CONST_PN) | \
                                    (SD_CONST_C11) | \
                                    (SD_CONST_C128) | \
                                    (SD_CONST_C39) | \
                                    (SD_CONST_C93) | \
                                    (SD_CONST_CB) | \
                                    (SD_CONST_DM) | \
                                    (SD_CONST_I25) | \
                                    (SD_CONST_S25) | \
                                    (SD_CONST_MC) | \
                                    (SD_CONST_MSIP) | \
                                    (SD_CONST_PDF) | \
                                    (SD_CONST_QR) | \
                                    (SD_CONST_RSS) | \
                                    (SD_CONST_AZ) | \
                                    (SD_CONST_PHARMA) | \
                                    (SD_CONST_UPU) | \
                                    (SD_CONST_RM) | \
                                    (SD_CONST_USPS4CB))

#define SD_CONST_SYMBOLOGIES_GROUP_EX ((SD_CONST_M25)   | \
                                       (SD_CONST_TP)    | \
                                       (SD_CONST_NEC25) | \
                                       (SD_CONST_TRIOPTIC)  | \
                                       (SD_CONST_OCR)  | \
                                       (SD_CONST_HK25) | \
                                       (SD_CONST_INFOMAIL) | \
                                       (SD_CONST_KP) | \
                                       (SD_CONST_CP) | \
                                       (SD_CONST_LC) | \
                                       (SD_CONST_SP) | \
                                       (SD_CONST_EIB) | \
                                       (SD_CONST_BZ4) | \
                                       (SD_CONST_GM) | \
                                       (SD_CONST_DOTCODE))

#define SD_CONST_LINEAR_SYMBOLOGIES_GROUP ((SD_CONST_UPC) | \
                                           (SD_CONST_C11) | \
                                           (SD_CONST_C128) | \
                                           (SD_CONST_C39) | \
                                           (SD_CONST_C93) | \
                                           (SD_CONST_CB) | \
                                           (SD_CONST_I25) | \
                                           (SD_CONST_S25) | \
                                           (SD_CONST_MSIP) | \
                                           (SD_CONST_PDF) | \
                                           (SD_CONST_PHARMA) | \
                                           (SD_CONST_RSS))
  
#define SD_CONST_LINEAR_SYMBOLOGIES_GROUP_EX ((SD_CONST_M25)   | \
                                              (SD_CONST_TP)    | \
                                              (SD_CONST_NEC25) | \
                                              (SD_CONST_TRIOPTIC) | \
                                              (SD_CONST_HK25) | \
                                              (SD_CONST_KP) | \
                                              (SD_CONST_LC))

#define SD_CONST_POSTAL_SYMBOLOGIES_GROUP ((SD_CONST_AP) | \
                                           (SD_CONST_JP) | \
                                           (SD_CONST_PL) | \
                                           (SD_CONST_PN) | \
                                           (SD_CONST_UPU) | \
                                           (SD_CONST_RM) | \
                                           (SD_CONST_USPS4CB))

#define SD_CONST_POSTAL_SYMBOLOGIES_GROUP_EX  ((SD_CONST_INFOMAIL) | \
                                               (SD_CONST_CP) | \
                                               (SD_CONST_SP) | \
                                               (SD_CONST_EIB) | \
                                               (SD_CONST_BZ4))


/* Definitions->Constants->Linkage */
#define  SD_CONST_NOT_LINKED                 0
#define  SD_CONST_LINKED_C128                11
#define  SD_CONST_LINKED_RSS                 12
#define  SD_CONST_LINKED_C39                 13
#define  SD_CONST_LINKED_CC_A                21
#define  SD_CONST_LINKED_CC_B                22
#define  SD_CONST_LINKED_CC_C                23
#define  SD_CONST_LINKED_UPDF                24

/* Definitions->Constants->General */
#define  SD_CONST_FALSE                      0
#define  SD_CONST_TRUE                       1
#define  SD_CONST_DISABLED                   0
#define  SD_CONST_ENABLED                    1
#define  SD_CONST_STRIPPED                   2
#define  SD_CONST_INVERSE_ENABLED            2

/* Definitions->Constants->Data Matrix */
#define  SD_CONST_DM_AXIS_ALIGNED            0
#define  SD_CONST_DM_OMNIDIRECTIONAL         1

/* Definitions->Constants->Progressive Decode Phase */
#define  SD_CONST_ACQ_INCOMPLETE             0
#define  SD_CONST_ACQ_COMPLETE               1

/* Definitions->Constants->Progress */
#define  SD_CONST_PROGRESS_CONTINUE          0
#define  SD_CONST_PROGRESS_CANCEL            1
#define  SD_CONST_PROGRESS_PAUSE             2

/* Definitions->Constants->Status */
#define  SD_CONST_STATUS_NO_COMPOSITE           1
#define  SD_CONST_STATUS_COARSE_FIND_COMPLETE   2

/* Definitions->Constants->ECI */
#define SD_CONST_ECI                            1
#define SD_CONST_BCI                            2

/* Definitions->Constants->ROI */
#define  SD_CONST_ROI_DISABLED               0
#define  SD_CONST_ROI_STANDARD               1
#define  SD_CONST_ROI_CENTERED               2
#define  SD_CONST_ROI_DPM                    3
#define  SD_CONST_ROI_FIXED_POS              4

/* Definitions->Constants->Short Margins */
#define  SD_CONST_SHORT_MARGIN_ONE           1
#define  SD_CONST_SHORT_MARGIN_BOTH          2

/* Definitions->Constants->Result Output Mode */
#define SD_CONST_RESULT_OUTPUT_MODE_NORMAL     0
#define SD_CONST_RESULT_OUTPUT_MODE_CODEWORDS  1
#define SD_CONST_RESULT_OUTPUT_MODE_DETAILS    2

/* Definitions->Constants->Verification */
#define SD_CONST_VER_LINEAR_DECODE            (1 << 0)
#define SD_CONST_VER_LINEAR_SC                (1 << 1)
#define SD_CONST_VER_LINEAR_RMIN              (1 << 2)
#define SD_CONST_VER_LINEAR_ECMIN             (1 << 3)
#define SD_CONST_VER_LINEAR_MOD               (1 << 4)
#define SD_CONST_VER_LINEAR_DEFECTS           (1 << 5)
#define SD_CONST_VER_LINEAR_DECODABILITY      (1 << 6)
#define SD_CONST_VER_LINEAR_ISO               ( SD_CONST_VER_LINEAR_DECODE \
                                              | SD_CONST_VER_LINEAR_RMIN \
                                              | SD_CONST_VER_LINEAR_SC \
                                              | SD_CONST_VER_LINEAR_ECMIN \
                                              | SD_CONST_VER_LINEAR_MOD \
                                              | SD_CONST_VER_LINEAR_DEFECTS \
                                              | SD_CONST_VER_LINEAR_DECODABILITY)
#define SD_CONST_VER_LINEAR_HANDHELD         (  SD_CONST_VER_LINEAR_DECODE \
                                              | SD_CONST_VER_LINEAR_DECODABILITY)

/* Definitions->Constants->CircularBuffers */
#define SD_CONST_CIRC_BUFF_FRAME_START       0
#define SD_CONST_CIRC_BUFF_FRAME_END         1

/* Definitions->Constants->OCR->ModifierEx */
#define SD_CONST_OCR_TEMPLATE_USER                  0
#define SD_CONST_OCR_TEMPLATE_PASSPORT_LOWER        1
#define SD_CONST_OCR_TEMPLATE_PASSPORT_UPPER        2
#define SD_CONST_OCR_TEMPLATE_ISBN                  3
#define SD_CONST_OCR_TEMPLATE_PRICE_FIELD           4
#define SD_CONST_OCR_TEMPLATE_MICR13                5
#define SD_CONST_OCR_TEMPLATE_VISA_A_UPPER          6
#define SD_CONST_OCR_TEMPLATE_VISA_A_LOWER          7
#define SD_CONST_OCR_TEMPLATE_VISA_B_UPPER          8
#define SD_CONST_OCR_TEMPLATE_VISA_B_LOWER          9
#define SD_CONST_OCR_TEMPLATE_TD2_UPPER            10
#define SD_CONST_OCR_TEMPLATE_TD2_LOWER            11
#define SD_CONST_OCR_TEMPLATE_TD1_UPPER            12
#define SD_CONST_OCR_TEMPLATE_TD1_MIDDLE           13
#define SD_CONST_OCR_TEMPLATE_TD1_LOWER            14
#define SD_CONST_OCR_TEMPLATE_FRENCH_ID_UPPER      15
#define SD_CONST_OCR_TEMPLATE_FRENCH_ID_LOWER      16
#define SD_CONST_OCR_TEMPLATE_RUSSIAN_ID_UPPER     17
#define SD_CONST_OCR_TEMPLATE_RUSSIAN_ID_LOWER     18

/* Definitions->Properties */
#define SD_PROP_AGC_EXPOSURE_QUALITY             0x40002001
#define SD_PROP_AGC_NEXT_GAIN                    0x40002002
#define SD_PROP_AGC_SAMPLING_OPTIONS             0x40002003
#define SD_PROP_CALLBACK_RESULT                  0x40003001
#define SD_PROP_CALLBACK_PROGRESS                0x40003002
#define SD_PROP_CALLBACK_TIMER                   0x40003003
#define SD_PROP_CALLBACK_STATUS                  0x40003004
#define SD_PROP_IMAGE_HEIGHT                     0x40004001
#define SD_PROP_IMAGE_LINE_DELTA                 0x40004002
#define SD_PROP_IMAGE_MIRRORED                   0x40004003
#define SD_PROP_IMAGE_POINTER                    0x40004004
#define SD_PROP_IMAGE_RATIO_X                    0x40004007
#define SD_PROP_IMAGE_RATIO_Y                    0x40004008
#define SD_PROP_IMAGE_TYP_DENSITY                0x40004006
#define SD_PROP_IMAGE_WIDTH                      0x40004005
#define SD_PROP_IMAGE_SEARCH_CENTER_X            0x40004010
#define SD_PROP_IMAGE_SEARCH_CENTER_Y            0x40004011
#define SD_PROP_MISC_TAG                         0x40005001
#define SD_PROP_MISC_MIN_1D_HEIGHT               0x40005002
#define SD_PROP_MISC_OP_MODE                     0x40005003
#define SD_PROP_MISC_ISSUE_IDENTICAL_SYMBOLS     0x40005004
#define SD_PROP_MISC_LOW_ASPECT_RATIO            0x40005005
#define SD_PROP_MISC_LOW_CONTRAST_IMPROVEMENTS   0x40005006
#define SD_PROP_MISC_MAX_1D_LENGTH               0x40005007
#define SD_PROP_MISC_UNDECODABLE_SYMBOLS         0x40005008
/* SD_PROP_MISC_UNDECODABLE_SYMBOL is provided for backwards compatability with version 4.2.6.
   Its use is discouraged; use SD_PROP_MISC_UNDECODABLE_SYMBOLS as per the documentation. */
#define SD_PROP_MISC_UNDECODABLE_SYMBOL          (SD_PROP_MISC_UNDECODABLE_SYMBOLS)
#define SD_PROP_MISC_MISENCODED_SYMBOLS          0x40005009
#define SD_PROP_MISC_SUBREGION_PROCESSING        0x40005010
#define SD_PROP_MISC_IMPROVEMENTS                0x40005011
#define SD_PROP_MISC_DYNAMIC_PROCESSING          0x40005012
#define SD_PROP_MISC_BLACK_LEVEL                 0x40005013
#define SD_PROP_MISC_UNDECODABLE_SYMBOLS_EX      0x40005014
#define SD_PROP_MISC_ECI_HANDLING                0x40005018
#define SD_PROP_MISC_ISSUE_IDENTICAL_SPACING     0x40005019
#define SD_PROP_MISC_DECODE_LATENCY              0x40005021
#define SD_PROP_MISC_DYNAMIC_PROCESSING_REGIONS  0x40005022
#define SD_PROP_MISC_LINEAR_DAMAGE_IMPROVEMENTS  0x40005025
#define SD_PROP_MISC_LINEAR_BOUNDARY_CHECK       0x40005026
#define SD_PROP_MISC_LINEAR_DECODE_POLARITY      0x40005027
#define SD_PROP_PROGRESS_CANCEL                  0x40006001
#define SD_PROP_RESULT_BOUNDS                    0x70007001
#define SD_PROP_RESULT_CENTER                    0x70007002
#define SD_PROP_RESULT_SYMBOLOGY                 0x40007003
#define SD_PROP_RESULT_LENGTH                    0x40007004
#define SD_PROP_RESULT_LINKAGE                   0x40007005
#define SD_PROP_RESULT_MODIFIER                  0x40007006
#define SD_PROP_RESULT_STRING                    0x80007007
#define SD_PROP_RESULT_QRPOSITION                0x40007008
#define SD_PROP_RESULT_QRTOTAL                   0x40007009
#define SD_PROP_RESULT_QRPARITY                  0x40007010
#define SD_PROP_RESULT_QUALITY                   0x40007011
#define SD_PROP_RESULT_QUALITY2                  0x40007012
#define SD_PROP_RESULT_POSTAL_BARS_ANALYZED      0x40007013
#define SD_PROP_RESULT_POSTAL_BARS_ANALYSED      0x40007013  /* alternate spelling */
#define SD_PROP_RESULT_SYMBOLOGY_EX              0x40007014
#define SD_PROP_RESULT_CODABLOCK_CONFLICT        0x40007015
#define SD_PROP_RESULT_VERIFICATION_STRING       0x80007016
#define SD_PROP_RESULT_VERIFICATION_LENGTH       0x40007017
#define SD_PROP_RESULT_VERIFICATION_GRADE        0x40007018
#define SD_PROP_RESULT_MODIFIER_EX               0x40007019
#define SD_PROP_RESULT_2D_MODULESX               0x40007020
#define SD_PROP_RESULT_2D_MODULESY               0x40007021
#define SD_PROP_RESULT_FRAME_ID                  0x40007022
#define SD_PROP_AZ_ENABLED                       0x40011201
#define SD_PROP_AZ_SYMBOL_SIZE                   0x40011202
#define SD_PROP_AZ_PERMISSIVE_TEXT_HANDLING      0x40011203
#define SD_PROP_CB_ENABLED                       0x40010101
#define SD_PROP_CB_CHECKSUM                      0x40010102
#define SD_PROP_CB_SHORT_MARGIN                  0x40010103
#define SD_PROP_CB_IMPROVE_BOUNDS                0x40010104
#define SD_PROP_C128_ENABLED                     0x40010201
#define SD_PROP_C128_SHORT_MARGIN                0x40010202
#define SD_PROP_C128_PARITY_THRESHOLD            0x40010204
#define SD_PROP_CODABLOCK_F_ENABLED              0x40010205
#define SD_PROP_C128_SUPPRESS_CB_CONFLICT        0x40010206
#define SD_PROP_C128_PARTIAL                     0x40010207
#define SD_PROP_C128_IMPROVE_BOUNDS              0x40010208
#define SD_PROP_C128_SECURITY                    0x40010209
#define SD_PROP_C128_OUTPUT_MODE                 0x40010210
#define SD_PROP_C39_ENABLED                      0x40010301
#define SD_PROP_C39_CHECKSUM                     0x40010302
#define SD_PROP_C39_FULL_ASCII                   0x40010303
#define SD_PROP_C39_SHORT_MARGIN                 0x40010304
#define SD_PROP_CODABLOCK_A_ENABLED              0x40010305
#define SD_PROP_C39_SUPPRESS_CB_CONFLICT         0x40010306
#define SD_PROP_TRIOPTIC_ENABLED                 0x40010307
#define SD_PROP_TRIOPTIC_SHORT_MARGIN            0x40010308
#define SD_PROP_C39_PARTIAL                      0x40010309
#define SD_PROP_C39_IMPROVE_BOUNDS               0x40010310
#define SD_PROP_DM_ENABLED                       0x40010401
#define SD_PROP_DM_RECT                          0x40010402
#define SD_PROP_DM_MAX_MODULE_COUNT              0x40010403
#define SD_PROP_DM_MAX_MODULE_SIZE               0x40010404
#define SD_PROP_DM_MIN_MODULE_COUNT              0x40010405
#define SD_PROP_DM_MIN_MODULE_SIZE               0x40010406
#define SD_PROP_DM_ORIENTATIONS                  0x40010407
#define SD_PROP_DM_SUBREGION_LEFT                0x40010408
#define SD_PROP_DM_SUBREGION_TOP                 0x40010409
#define SD_PROP_DM_SUBREGION_WIDTH               0x40010410
#define SD_PROP_DM_SUBREGION_HEIGHT              0x40010411
#define SD_PROP_DM_NON_SQUARE_MODULES            0x40010412
#define SD_PROP_DM_SHIFTED_TILES                 0x40010413
#define SD_PROP_DM_LOW_CONTRAST                  0x40010414
#define SD_PROP_DM_BINARY_IMPROVEMENTS           0x40010415
#define SD_PROP_DM_SYMBOL_SIZE                   0x40010416
#define SD_PROP_DM_PERMISSIVE_TEXT_HANDLING      0x40010419
#define SD_PROP_I25_ENABLED                      0x40010501
#define SD_PROP_I25_CHECKSUM                     0x40010502
#define SD_PROP_I25_LENGTHS                      0x40010503
#define SD_PROP_I25_SHORT_MARGIN                 0x40010504
#define SD_PROP_I25_PARTIAL                      0x40010505
#define SD_PROP_I25_IMPROVE_BOUNDS               0x40010506
#define SD_PROP_LINEAR_SUBREGION_LEFT            0x40012001
#define SD_PROP_LINEAR_SUBREGION_TOP             0x40012002
#define SD_PROP_LINEAR_SUBREGION_WIDTH           0x40012003
#define SD_PROP_LINEAR_SUBREGION_HEIGHT          0x40012004
#define SD_PROP_MC_ENABLED                       0x40010601
#define SD_PROP_MC_SYMBOL_SIZE                   0x40010602
#define SD_PROP_MC_MESSAGE_FORMAT                0x40010603
#define SD_PROP_PDF_ENABLED                      0x40010701
#define SD_PROP_PDF_CLEAR_HISTORY                0x40010705
#define SD_PROP_PDF_HISTORY                      0x80010706
#define SD_PROP_PDF_HISTORY_SIZE                 0x40010707
#define SD_PROP_PDF_HISTORY_EXPIRE_COUNT         0x40010708
#define SD_PROP_PDF_HISTORY_MIN_MATCH_PERCENT    0x40010709
#define SD_PROP_MICROPDF_ENABLED                 0x40010702
#define SD_PROP_MICROPDF_IMPROVE_BOUNDS          0x40010704
#define SD_PROP_POSTAL_ENABLED                   0x40010801
#define SD_PROP_POSTAL_MIN_BAR_COUNT             0x40010802
#define SD_PROP_POSTAL_ORIENTATIONS              0x40010803
#define SD_PROP_POSTAL_MAX_BAR_COUNT             0x40010804
#define SD_PROP_POSTAL_UNDECODABLE_LEFT          0x40010805
#define SD_PROP_POSTAL_UNDECODABLE_TOP           0x40010806
#define SD_PROP_POSTAL_UNDECODABLE_WIDTH         0x40010807
#define SD_PROP_POSTAL_UNDECODABLE_HEIGHT        0x40010808
#define SD_PROP_POSTAL_SUBREGION_LEFT            0x40010809
#define SD_PROP_POSTAL_SUBREGION_TOP             0x40010810
#define SD_PROP_POSTAL_SUBREGION_WIDTH           0x40010811
#define SD_PROP_POSTAL_SUBREGION_HEIGHT          0x40010812
#define SD_PROP_POSTAL_AP_ZERO_FCC               0x40010813
#define SD_PROP_POSTAL_AP_BAR_OUTPUT             0x40010817
#define SD_PROP_POSTAL_AP_CUST_INTERPRET         0x40010818
#define SD_PROP_POSTAL_CP_BAR_OUTPUT             0x40010819
#define SD_PROP_POSTAL_AP_EC_OUTPUT              0x40010820
#define SD_PROP_QR_ENABLED                       0x40010901
#define SD_PROP_QR_NON_SQUARE_MODULES            0x40010902
#define SD_PROP_QR_SYMBOL_SIZE                   0x40010904
#define SD_PROP_UPC_ENABLED                      0x40011001
#define SD_PROP_UPC_EXPANSION                    0x40011002
#define SD_PROP_UPC_SUPPLEMENTALS                0x40011003
#define SD_PROP_UPC_SHORT_MARGIN                 0x40011004
#define SD_PROP_UPC_EXTRA_PROCESSING             0x40011005
#define SD_PROP_UPC_IMPROVE_BOUNDS               0x40011006
#define SD_PROP_UPC_SECURITY                     0x40011008
#define SD_PROP_C93_ENABLED                      0x40011101
#define SD_PROP_C93_SHORT_MARGIN                 0x40011102
#define SD_PROP_C93_IMPROVE_BOUNDS               0x40011103
#define SD_PROP_C93_HIGH_DENSITY                 0x40011104
#define SD_PROP_RSS_ENABLED                      0x40011301
#define SD_PROP_RSS14_IMPROVE_BOUNDS             0x40011302
#define SD_PROP_RSSLIM_IMPROVE_BOUNDS            0x40011303
#define SD_PROP_RSSEXP_IMPROVE_BOUNDS            0x40011304
#define SD_PROP_CC_ENABLED                       0x40011401
#define SD_PROP_S25_2SS_ENABLED                  0x40011501
#define SD_PROP_S25_2SS_LENGTHS                  0x40011502
#define SD_PROP_S25_3SS_ENABLED                  0x40011503
#define SD_PROP_S25_3SS_LENGTHS                  0x40011504
#define SD_PROP_S25_2SS_IMPROVE_BOUNDS           0x40011505
#define SD_PROP_S25_3SS_IMPROVE_BOUNDS           0x40011506
#define SD_PROP_MSIP_ENABLED                     0x40011601
#define SD_PROP_MSIP_CHECKSUM                    0x40011602
#define SD_PROP_MSIP_IMPROVE_BOUNDS              0x40011603
#define SD_PROP_MSIP_SHORT_MARGIN                0x40011604
#define SD_PROP_PHARMA_ENABLED                   0x40011701
#define SD_PROP_PHARMA_MIN_BAR_COUNT             0x40011702
#define SD_PROP_PHARMA_MAX_BAR_COUNT             0x40011703
#define SD_PROP_PHARMA_MIN_VALUE                 0x40011704
#define SD_PROP_PHARMA_MAX_VALUE                 0x40011705
#define SD_PROP_PHARMA_ORIENTATION               0x40011706
#define SD_PROP_PHARMA_REVERSE                   0x40011707
#define SD_PROP_PHARMA_COLOR_BARS                0x40011708
#define SD_PROP_C11_ENABLED                      0x40011801
#define SD_PROP_C11_CHECKSUM                     0x40011802
#define SD_PROP_C11_IMPROVE_BOUNDS               0x40011803
#define SD_PROP_M25_ENABLED                      0x40011901
#define SD_PROP_M25_CHECKSUM                     0x40011902
#define SD_PROP_M25_LENGTHS                      0x40011903
#define SD_PROP_M25_IMPROVE_BOUNDS               0x40011904
#define SD_PROP_TP_ENABLED                       0x40012101
#define SD_PROP_TP_IMPROVE_BOUNDS                0x40012103
#define SD_PROP_NEC25_ENABLED                    0x40012201
#define SD_PROP_NEC25_CHECKSUM                   0x40012202
#define SD_PROP_NEC25_LENGTHS                    0x40012203
#define SD_PROP_NEC25_IMPROVE_BOUNDS             0x40012204
#define SD_PROP_OCR_ENABLED                      0x40012301
#define SD_PROP_OCR_USER_TEMPLATES               0x50012302
#define SD_PROP_OCR_ACTIVE_TEMPLATES             0x40012303
#define SD_PROP_OCR_SINGLE_ROW                   0x40012304
#define SD_PROP_OCR_PREFERRED_ORIENTATION        0x40012305
#define SD_PROP_OCR_STRIP_CHECKSUMS              0x40012306
#define SD_PROP_OCR_CHAR_DISABLE                 0x40012307
#define SD_PROP_OCR_BUSY_BACKGROUND              0x40012308
#define SD_PROP_OCR_ISSUE_UNCERTAIN              0x40012309
#define SD_PROP_OCR_IGNORE_PASSPORT_CHECKSUMS    0x40012310
#define SD_PROP_VER_LINEAR_ENABLED               0x40012501
#define SD_PROP_VER_LINEAR_GRADE                 0x40012502
#define SD_PROP_VER_LINEAR_NUM_SCANS             0x40012503
#define SD_PROP_VER_LINEAR_REF_MIN               0x40012504
#define SD_PROP_VER_LINEAR_REF_MAX               0x40012505
#define SD_PROP_VER_LINEAR_DPI                   0x40012506
#define SD_PROP_VER_LINEAR_APERTURE              0x40012507
#define SD_PROP_HK25_ENABLED                     0x40012601
#define SD_PROP_HK25_LENGTHS                     0x40012602
#define SD_PROP_HK25_IMPROVE_BOUNDS              0x40012603
#define SD_PROP_VER_POSTAL_ENABLED               0x40012701
#define SD_PROP_VER_POSTAL_MAIL_TYPE             0x40012702
#define SD_PROP_CIRCULAR_BUFFER_HEIGHT           0x40012801
#define SD_PROP_CIRCULAR_BUFFER_STATE            0x40012802
#define SD_PROP_VER_PDF_ENABLED                  0x40013101
#define SD_PROP_VER_PDF_EXTRA_OUTPUT             0x40013102
#define SD_PROP_VER_PDF_APERTURE                 0x40013103
#define SD_PROP_VER_2D_ENABLED                   0x40013401
#define SD_PROP_KP_ENABLED                       0x40013501
#define SD_PROP_KP_CHECKSUM                      0x40013502
#define SD_PROP_KP_REVERSE                       0x40013503
#define SD_PROP_HX_ENABLED                       0x40013601
#define SD_PROP_LC_ENABLED                       0x40014001
#define SD_PROP_GM_ENABLED                       0x40015001
#define SD_PROP_GM_OUTPUT_MODE                   0x40015002
#define SD_PROP_DOTCODE_ENABLED                  0x40016001
#define SD_PROP_DOTCODE_EXTENSIVE_SEARCH         0x40016004
#define SD_PROP_DOTCODE_OUTPUT_MODE              0x40016005
#define SD_PROP_VERSION_BUILD                    0x40008001
#define SD_PROP_VERSION_COMPONENTS_AUTHORIZED    0x40008002
#define SD_PROP_VERSION_COMPONENTS_PRESENT       0x40008003
#define SD_PROP_VERSION_CONFIGURATION            0x50008004
#define SD_PROP_VERSION_COPYRIGHTS               0x60008005
#define SD_PROP_VERSION_MAJOR                    0x40008006
#define SD_PROP_VERSION_MINOR                    0x40008007
#define SD_PROP_VERSION_TRADEMARKS               0x60008008
#define SD_PROP_VERSION_COMMENTS                 0x60008009
#define SD_PROP_VERSION_COMPANY_NAME             0x50008010
#define SD_PROP_VERSION_PRODUCT_NAME             0x50008011
#define SD_PROP_VERSION_TIMESTAMP                0x50008012

#define SD_PROP_VERSION_COMPONENTS_AUTHORIZED_EX 0x40008013
#define SD_PROP_VERSION_COMPONENTS_PRESENT_EX    0x40008014
#define SD_PROP_ROI_MODE                         0x40008015

/* Type Definitions */
typedef struct tag_SD_STRUCT_POINT
{
   int X;
   int Y;
} SD_STRUCT_POINT;

typedef struct tag_SD_STRUCT_BOUNDS
{
   SD_STRUCT_POINT Point[4];
} SD_STRUCT_BOUNDS;

typedef struct tag_SD_STRUCT_CIRC_BUFFER_STATE
{
   int FrameID;
   int Line;
   int State;
} SD_STRUCT_CIRC_BUFFER_STATE;

/* Function Prototypes */
SD_API2 int SD_STDCALL2 SD_ComputeAGC(int Handle);
SD_API2 int SD_STDCALL2 SD_Create(void);
SD_API2 int SD_STDCALL2 SD_Decode(int Handle);
SD_API2 int SD_STDCALL2 SD_ProgressiveDecode(int Handle, int Phase);
SD_API2 int SD_STDCALL2 SD_Destroy(int Handle);
SD_API2 int SD_STDCALL2 SD_GetLastError(void);
SD_API2 int SD_STDCALL2 SD_Get(int Handle, int Property, void *Value);
SD_API2 int SD_STDCALL2 SD_Set(int Handle, int Property, void *Value);

/* Error Codes */
#define SD_ERR_INVALID_HANDLE                1001
#define SD_ERR_READ_ONLY                     1002
#define SD_ERR_UNKNOWN_PROPERTY              1003
#define SD_ERR_TOO_MANY_OBJECTS              1004
#define SD_ERR_PROPERTY_LIFETIME             1005
#define SD_ERR_COMPONENT_ABSENT              1006
#define SD_ERR_COMPONENT_UNAUTHORIZED        1007
#define SD_ERR_COMPONENT_UNAUTHORISED        1007 /* alternate spelling */
#define SD_ERR_PROPERTY_VALUE                1008
#define SD_ERR_IMAGE_PROPERTY_VALUE          1009
#define SD_ERR_INSUFFICIENT_MEMORY           1010
#define SD_ERR_AGC_COMPONENT_UNREACHABLE     1011
#define SD_ERR_ILLEGAL_FUNCTION              1012


/* Postamble */
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif /* SD_H_INCLUDED */
