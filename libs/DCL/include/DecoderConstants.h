//======================================================================================
// DecoderConstants.h
//======================================================================================

//---------------------------------------------------------------------------
//
//  Module Interface Description:
//      This file contains any and all constant defines that can come from this interface.
//
//---------------------------------------------------------------------------

/* Copyright 2017, Honeywell.  All Rights Reserved */

#ifndef DECODER_CONSTANTS_H
#define DECODER_CONSTANTS_H


/** AIM Codeletters
 *   These defines have no bearing on the decoding capability of the decoder(s)
 *   included in the API. These defines are simply meant to provide a macro which 
 *   aligns with the current AIM specification. 
 *
 *   \defgroup aimID AIM IDs
 *   @{
 */

#define DEC_AIM_CODELETTER_CODE39      'A'
#define DEC_AIM_CODELETTER_TELEPEN     'B'
#define DEC_AIM_CODELETTER_CODE128     'C'
#define DEC_AIM_CODELETTER_GS1_128     'C'
#define DEC_AIM_CODELETTER_CODE1       'D'
#define DEC_AIM_CODELETTER_UPC         'E'   //includes EAN and Jan
#define DEC_AIM_CODELETTER_CODABAR     'F'
#define DEC_AIM_CODELETTER_CODE93      'G'
#define DEC_AIM_CODELETTER_CODE11      'H'
#define DEC_AIM_CODELETTER_I25         'I'
#define DEC_AIM_CODELETTER_DOTCODE     'J'
#define DEC_AIM_CODELETTER_CODE16K     'K'
#define DEC_AIM_CODELETTER_PDF417      'L' //include MicroPDF417
#define DEC_AIM_CODELETTER_TLC39       'L' //Not a typo. 'L' is defined in TLC39 spec, which is a PDF/Code 39 combo
#define DEC_AIM_CODELETTER_MSI         'M'
#define DEC_AIM_CODELETTER_ANKER       'N'
#define DEC_AIM_CODELETTER_CODABLOCK   'O' //includes both A and F
#define DEC_AIM_CODELETTER_PLESSEY     'P'
#define DEC_AIM_CODELETTER_QRCODE      'Q'
#define DEC_AIM_CODELETTER_S25_2BAR    'R' //Straight 2of5 with 2 bar start/stop (aka IATA 2of5)
#define DEC_AIM_CODELETTER_S25_3BAR    'S' //Straight 2of5 with 3 bar start/stop (aka Industrial 2of5)
#define DEC_AIM_CODELETTER_CODE49      'T'
#define DEC_AIM_CODELETTER_MAXICODE    'U'
//RESERVED                             'V'
//RESERVED                             'W'
#define DEC_AIM_CODELETTER_OTHER       'X'
#define DEC_AIM_CODELETTER_DIGIMARC    'X'
#define DEC_AIM_CODELETTER_EXPANSION   'Y'
#define DEC_AIM_CODELETTER_NONBARCODE  'Z'

//RESERVED                             'a'
//RESERVED                             'b'
#define DEC_AIM_CODELETTER_CHANNELCODE 'c'
#define DEC_AIM_CODELETTER_DATAMATRIX  'd'
#define DEC_AIM_CODELETTER_RSS         'e'
#define DEC_AIM_CODELETTER_GS1_DATABAR 'e'
#define DEC_AIM_CODELETTER_COMPOSITE   'e'
//RESERVED                             'f'
#define DEC_AIM_CODELETTER_GRID_MATRIX 'g'
//RESERVED                             'h'
//RESERVED                             'i'
//RESERVED                             'j'
//RESERVED                             'k'
//RESERVED                             'l'
//RESERVED                             'm'
//RESERVED                             'n'
#define DEC_AIM_CODELETTER_OCR         'o'
#define DEC_AIM_CODELETTER_POSICODE    'p'
//RESERVED                             'q'
//RESERVED                             'r'
#define DEC_AIM_CODELETTER_SUPERCODE   's'
//RESERVED                             't'
//RESERVED                             'u'
#define DEC_AIM_CODELETTER_ULTRACODE   'v'
//RESERVED                             'w'
//RESERVED                             'x'
//RESERVED                             'y'
#define DEC_AIM_CODELETTER_AZTEC_CODE  'z' //Including Mesas

/** @} */

/** Welch Allyn Codeletters or HHP Code ID
 *   These defines have no bearing on the decoding capability of the decoder(s)
 *   included in the API. These defines are simply meant to provide a macro which 
 *   aligns with the legacy Welch Allyn codeletters (called code IDs) and updated 
 *   when this decoder when Welch Allyn data collection became Hand Held Products.
 *
 *   \defgroup hhpID HHP Code IDs
 *   @{
 */

#define DEC_HHP_CODE_ID_DOTCODE         '.'
#define DEC_HHP_CODE_ID_CODE1           '1'
#define DEC_HHP_CODE_ID_MERGED_COUPON   ';'
#define DEC_HHP_CODE_ID_CODE39_BASE32   '<' //aka Code 32, Italian Pharmacode, PARAF
#define DEC_HHP_CODE_ID_LABELCODE_IV    '>'
#define DEC_HHP_CODE_ID_LABELCODE_V     '<'
#define DEC_HHP_CODE_ID_TRIOPTIC        '='
#define DEC_HHP_CODE_ID_KOREA_POST      '?'
#define DEC_HHP_CODE_ID_INFOMAIL        ','
#define DEC_HHP_CODE_ID_EAN13_ISBN      '`'
#define DEC_HHP_CODE_ID_SWEEDISH_POST   '['
#define DEC_HHP_CODE_ID_RM_MAILMARK     '|'
#define DEC_HHP_CODE_ID_BRAZIL_POST     ']'
#define DEC_HHP_CODE_ID_NO_READ         0x9C

#define DEC_HHP_CODE_ID_AUS_POST        'A'
#define DEC_HHP_CODE_ID_BRITISH_POST    'B'
#define DEC_HHP_CODE_ID_CANADIAN_POST   'C'
#define DEC_HHP_CODE_ID_EAN8            'D'
#define DEC_HHP_CODE_ID_UPCE            'E'
//#define DEC_HHP_CODE_ID_LABELCODE     'F'
#define DEC_HHP_CODE_ID_BC412           'G'
#define DEC_HHP_CODE_ID_HAN_XIN_CODE    'H'
#define DEC_HHP_CODE_ID_GS1_128         'I'
#define DEC_HHP_CODE_ID_JAPAN_POST      'J'
#define DEC_HHP_CODE_ID_KIX_CODE        'K'
#define DEC_HHP_CODE_ID_PLANET_CODE     'L'
#define DEC_HHP_CODE_ID_USPS_4_STATE    'M' //Intelligent Mail
#define DEC_HHP_CODE_ID_UPU_4_STATE     'N' //ID Tags
#define DEC_HHP_CODE_ID_OCR             'O'
#define DEC_HHP_CODE_ID_POSTNET         'P'
#define DEC_HHP_CODE_ID_HK25            'Q' //aka China Post
#define DEC_HHP_CODE_ID_MICROPDF        'R'
#define DEC_HHP_CODE_ID_SECURE_CODE     'S'
#define DEC_HHP_CODE_ID_TLC39           'T'
#define DEC_HHP_CODE_ID_ULTRACODE       'U'
#define DEC_HHP_CODE_ID_CODABLOCK_A     'V'
#define DEC_HHP_CODE_ID_POSICODE        'W'
#define DEC_HHP_CODE_ID_GRID_MATRIX     'X'
#define DEC_HHP_CODE_ID_NEC25           'Y'
#define DEC_HHP_CODE_ID_MESA            'Z'

#define DEC_HHP_CODE_ID_CODABAR         'a'
#define DEC_HHP_CODE_ID_CODE39          'b'
#define DEC_HHP_CODE_ID_UPCA            'c'
#define DEC_HHP_CODE_ID_EAN13           'd'
#define DEC_HHP_CODE_ID_I25             'e'
#define DEC_HHP_CODE_ID_S25             'f' //both 2bar and 3bar
#define DEC_HHP_CODE_ID_MSI             'g'
#define DEC_HHP_CODE_ID_CODE11          'h'
#define DEC_HHP_CODE_ID_CODE93          'i'
#define DEC_HHP_CODE_ID_CODE128         'j'
#define DEC_HHP_CODE_ID_UNUSED          'k'
#define DEC_HHP_CODE_ID_CODE49          'l'
#define DEC_HHP_CODE_ID_M25             'm'
#define DEC_HHP_CODE_ID_PLESSEY         'n'
#define DEC_HHP_CODE_ID_CODE16K         'o'
#define DEC_HHP_CODE_ID_CHANNELCODE     'p'
#define DEC_HHP_CODE_ID_CODABLOCK_F     'q'
#define DEC_HHP_CODE_ID_PDF417          'r'
#define DEC_HHP_CODE_ID_QRCODE          's'
#define DEC_HHP_CODE_ID_MICROQR_ALT     '-'
#define DEC_HHP_CODE_ID_TELEPEN         't'
#define DEC_HHP_CODE_ID_CODEZ           'u'
#define DEC_HHP_CODE_ID_VERICODE        'v'
#define DEC_HHP_CODE_ID_DATAMATRIX      'w'
#define DEC_HHP_CODE_ID_MAXICODE        'x'
#define DEC_HHP_CODE_ID_RSS             'y'
#define DEC_HHP_CODE_ID_GS1_DATABAR     'y'
#define DEC_HHP_CODE_ID_GS1_DATABAR_LIM '{'
#define DEC_HHP_CODE_ID_GS1_DATABAR_EXP '}'
#define DEC_HHP_CODE_ID_COMPOSITE       'y'
#define DEC_HHP_CODE_ID_AZTEC_CODE      'z'
#define DEC_HHP_CODE_ID_DIGIMARC        '|'

/** @} */


/** Swift Symbology Constants
 *   These defines have no bearing on the decoding capability of the decoder(s)
 *   included in the API. These defines are simply meant to provide a macro which 
 *   aligns with the legacy Swift Decoder symbology constants.
 *
 * \defgroup symbologyID Symbology IDs
 * @{
 */

//These settings apply to DecoderResult->Symbology
#define DEC_SYMBOLOGY_UPC                 (1 << 2) //includes UPC, EAN, and JAN
#define DEC_SYMBOLOGY_UPC_2_CHAR_SUPP     ((DEC_SYMBOLOGY_UPC) + 1) 
#define DEC_SYMBOLOGY_UPC_5_CHAR_SUPP     ((DEC_SYMBOLOGY_UPC) + 2) 
#define DEC_SYMBOLOGY_AUS_POST            (1 << 3)
#define DEC_SYMBOLOGY_CODE128             (1 << 4)
#define DEC_SYMBOLOGY_CODABLOCK_F         ((DEC_SYMBOLOGY_CODE128) + 1)
#define DEC_SYMBOLOGY_CODE39              (1 << 5)
#define DEC_SYMBOLOGY_CODABLOCK_A         ((DEC_SYMBOLOGY_CODE39) + 1)
#define DEC_SYMBOLOGY_CODABAR             (1 << 6)
#define DEC_SYMBOLOGY_PLANETCODE          (1 << 7)
#define DEC_SYMBOLOGY_DATAMATRIX          (1 << 8)
#define DEC_SYMBOLOGY_I25                 (1 << 9)
#define DEC_SYMBOLOGY_MAXICODE            (1 << 11)
#define DEC_SYMBOLOGY_PDF                 (1 << 12) //include MicroPDF
#define DEC_SYMBOLOGY_POSTNET             (1 << 13)
#define DEC_SYMBOLOGY_QRCODE              (1 << 14)
#define DEC_SYMBOLOGY_RSS                 (1 << 15)
#define DEC_SYMBOLOGY_RSS_EXP             ((DEC_SYMBOLOGY_RSS) + 1) //Expanded
#define DEC_SYMBOLOGY_RSS_EXP_ST          ((DEC_SYMBOLOGY_RSS) + 2) //Expanded Stacked
#define DEC_SYMBOLOGY_RSS_14_LIM          ((DEC_SYMBOLOGY_RSS) + 4) //Limited
#define DEC_SYMBOLOGY_RSS_14              ((DEC_SYMBOLOGY_RSS) + 8) 
#define DEC_SYMBOLOGY_RSS_14_ST           ((DEC_SYMBOLOGY_RSS) + 16) //Stacked
#define DEC_SYMBOLOGY_JAPAN_POST          (1 << 17)
#define DEC_SYMBOLOGY_CODE93              (1 << 18)
#define DEC_SYMBOLOGY_AZTEC_CODE          (1 << 19)
#define DEC_SYMBOLOGY_ROYAL_MAIL          (1 << 21) 
#define DEC_SYMBOLOGY_KIX                 ((DEC_SYMBOLOGY_ROYAL_MAIL) + 1)
#define DEC_SYMBOLOGY_S25                 (1 << 22)
#define DEC_SYMBOLOGY_S25_2BAR            ((DEC_SYMBOLOGY_S25))
#define DEC_SYMBOLOGY_S25_3BAR            ((DEC_SYMBOLOGY_S25) + 1)
#define DEC_SYMBOLOGY_MSI                 (1 << 23)
#define DEC_SYMBOLOGY_GO_CODE             (1 << 24)
#define DEC_SYMBOLOGY_PHARMACODE          (1 << 26)
#define DEC_SYMBOLOGY_UPU_4_STATE         (1 << 27)
#define DEC_SYMBOLOGY_CODE11              (1 << 28)
#define DEC_SYMBOLOGY_USPS_4_STATE        (1U << 31U)
 
/** @} */

/**
 *   \defgroup symbologyExID Extended Symbology IDs
 *   @{
 */
//These settings apply to DecoderResult->SymbologyEx
#define DEC_SYMBOLOGY_EX_M25              (1 << 0)
#define DEC_SYMBOLOGY_EX_TELEPEN          (1 << 1)
#define DEC_SYMBOLOGY_EX_NEC25            (1 << 2)
#define DEC_SYMBOLOGY_EX_TRIOPTIC         (1 << 3)
#define DEC_SYMBOLOGY_EX_OCR              (1 << 4)
#define DEC_SYMBOLOGY_EX_HK25             (1 << 6)
#define DEC_SYMBOLOGY_EX_INFOMAIL         (1 << 12)
#define DEC_SYMBOLOGY_EX_KOREA_POST       (1 << 14)
#define DEC_SYMBOLOGY_EX_HAN_XIN_CODE     (1 << 15)
#define DEC_SYMBOLOGY_EX_CANADIAN_POST    (1 << 16)
#define DEC_SYMBOLOGY_EX_CODE16K          (1 << 17)
#define DEC_SYMBOLOGY_EX_LABELCODE        (1 << 17) //Duplicate number, 16K not supported yet
#define DEC_SYMBOLOGY_EX_SWEEDISH_POST    (1 << 18)
#define DEC_SYMBOLOGY_EX_RM_MAILMARK      (1 << 19)
#define DEC_SYMBOLOGY_EX_BRAZIL_POST      (1 << 20)
#define DEC_SYMBOLOGY_EX_GRID_MATRIX      (1 << 22)
#define DEC_SYMBOLOGY_EX_DOTCODE          (1 << 23)

/** @} */

//Other constants
#define DEC_TRUE              1
#define DEC_FALSE             0

#define DEC_SKIP              4
#define DEC_HALT              2
#define DEC_SUCCESS           1
#define DEC_FAILURE           0

#define DEC_ENABLED           1
#define DEC_DISABLED          0
#define DEC_STRIPPED          2
#define DEC_INVERSE_ENABLED   2

/**
 *   \brief Revision Reporting types used with ReportDecoderVersion(). Add together to get multiple types. They will come out in order specified here.
 *   \defgroup revType Revision Types
 *   @{
 */
#define DEC_REVISION_CONTROL_LOGIC    0x01
#define DEC_REVISION_ID               0x02
#define DEC_REVISION_AD               0x04
#define DEC_REVISION_FLD              0x08
#define DEC_REVISION_ULD              0x10
#define DEC_REVISION_IN2D             0x20

/** @} */

//Array size restrictions, used for compiled memory footprint control
#define MAX_STORED_RESULTS          12         /// The maximum number of results that could be returned with a single Result Callback event.
#define MAX_DECODED_DATA_LENGTH     (8*1024)   /// The maximum number of characters that could be returned in a single result.
#define MAX_PREFERRED_CODES         4          /// The maximum number of codes that could be prioritized for returning a result.
#define MAX_OCR_TEMPLATE_LENGTH     1000       /// The maximum number of characters that can be in in a single OCR template.

/**
 *   \brief Composite link flags. Applies to LinkFlag in DecoderResult.
 *   \defgroup linkFlag Link Flags
 *   @{
 */
#define  DEC_NOT_LINKED    0
#define  DEC_LINKED_C128   11
#define  DEC_LINKED_RSS    12
#define  DEC_LINKED_C39    13
#define  DEC_LINKED_CC_A   21
#define  DEC_LINKED_CC_B   22
#define  DEC_LINKED_CC_C   23
#define  DEC_LINKED_UPDF   24

/** @} */

/**
 *   \brief Append identifiers. Applies to AppendType in DecoderResult and the ResultNotify callback (CB_RESULT_NOTIFY).
 *   \defgroup appendType Append Types
 *   @{
 */
#define CODE39_APPEND            (1 << 0)
#define COUPON_CODE_APPEND       (1 << 1)
#define CODE93_APPEND            (1 << 2)
#define MACROPDF_APPEND          (1 << 3)
#define CODE128_APPEND           (1 << 4)
#define AZTEC_APPEND             (1 << 5)
#define QRC_APPEND               (1 << 6)
#define DATAMATRIX_APPEND        (1 << 7)
#define GRIDMATRIX_APPEND        (1 << 8)
#define UCC_COMPOSITE_APPEND     (1 << 9)
#define CODABAR_APPEND           (1 << 10)
#define ISBT_APPEND              (1 << 11)
#define UPC_COMPOSITE_APPEND     (1 << 12)
#define OCR_APPEND               (1 << 13) //Passport Reading
#define OCR_USER_APPEND          (1 << 14) //Space separated template
#define KIX_REVERSE_CODE         (1 << 15) //KIX reverse code reading.
#define HIBC_APPEND              (1 << 16)

/** @} */

//These constants apply to the status flag of the Result Notify callback
#define APPEND_ERROR             (0)
#define PREFERRED_READ           (1<<20)

//Postal constants
#define DEC_B_AND_B_FIELDS       (1 << 0)
#define DEC_CEPNET               (1 << 1)
#define DEC_UNDECODABLE_POSTAL   (1 << 3)

#define POSTAL_OPTIONS           39

//These are the only combinations of postal codes allowed
//The value passed to DEC_POSTAL_ENABLED is the value at the beginning of each line.
//unsigned int PostalOptions[POSTAL_OPTIONS] = {
/* 0 */    //DEC_DISABLED,
/* 1 */    //DEC_SYMBOLOGY_AUS_POST,
/* 2 */    //DEC_SYMBOLOGY_EX_INFOMAIL,
/* 3 */    //DEC_SYMBOLOGY_JAPAN_POST,
/* 4 */    //DEC_SYMBOLOGY_KIX,
/* 5 */    //DEC_SYMBOLOGY_PLANETCODE,
/* 6 */    //DEC_SYMBOLOGY_POSTNET,
/* 7 */    //DEC_SYMBOLOGY_ROYAL_MAIL,
/* 8 */    //DEC_SYMBOLOGY_EX_INFOMAIL     + //DEC_SYMBOLOGY_ROYAL_MAIL,
/* 9 */    //DEC_SYMBOLOGY_UPU_4_STATE,
/* 10 */   //DEC_SYMBOLOGY_USPS_4_STATE,
/* 11 */   //DEC_SYMBOLOGY_POSTNET         + //DEC_B_AND_B_FIELDS,
/* 12 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_POSTNET,
/* 13 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_UPU_4_STATE,
/* 14 */   //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_UPU_4_STATE,
/* 15 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_USPS_4_STATE,
/* 16 */   //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_USPS_4_STATE,
/* 17 */   //DEC_SYMBOLOGY_UPU_4_STATE     + //DEC_SYMBOLOGY_USPS_4_STATE,
/* 18 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_POSTNET         + //DEC_B_AND_B_FIELDS,
/* 19 */   //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_UPU_4_STATE     + //DEC_B_AND_B_FIELDS,
/* 20 */   //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_USPS_4_STATE    + //DEC_B_AND_B_FIELDS,
/* 21 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_UPU_4_STATE,
/* 22 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_USPS_4_STATE,
/* 23 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_UPU_4_STATE     + //DEC_SYMBOLOGY_USPS_4_STATE,
/* 24 */   //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_UPU_4_STATE     + //DEC_SYMBOLOGY_USPS_4_STATE,
/* 25 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_UPU_4_STATE    + //DEC_B_AND_B_FIELDS,
/* 26 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_USPS_4_STATE   + //DEC_B_AND_B_FIELDS,
/* 27 */   //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_UPU_4_STATE     + //DEC_SYMBOLOGY_USPS_4_STATE   + //DEC_B_AND_B_FIELDS,
/* 28 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_UPU_4_STATE    + //DEC_SYMBOLOGY_USPS_4_STATE,
/* 29 */   //DEC_SYMBOLOGY_PLANETCODE      + //DEC_SYMBOLOGY_POSTNET         + //DEC_SYMBOLOGY_UPU_4_STATE    + //DEC_SYMBOLOGY_USPS_4_STATE  + //DEC_B_AND_B_FIELDS,
/* 30 */   //DEC_SYMBOLOGY_CANADIAN_POST,
/* 31 */   //DEC_SYMBOLOGY_POSTNET         + //DEC_CEPNET,
/* 32 */   //DEC_SYMBOLOGY_EX_SWEEDISH_POST,
/* 33 */   //DEC_SYMBOLOGY_EX_BRAZIL_POST,
/* 34 */   //DEC_SYMBOLOGY_EX_BRAZIL_POST  + //DEC_SYMBOLOGY_POSTNET         + //DEC_CEPNET,
/* 35 */   //DEC_SYMBOLOGY_EX_RM_MAILMARK,
/* 36 */   //DEC_SYMBOLOGY_EX_RM_MAILMARK  + //DEC_SYMBOLOGY_EX_INFOMAIL,
/* 37 */   //DEC_SYMBOLOGY_EX_RM_MAILMARK  + //DEC_SYMBOLOGY_ROYAL_MAIL,
/* 38 */   //DEC_SYMBOLOGY_EX_RM_MAILMARK  + //DEC_SYMBOLOGY_EX_INFOMAIL     + //DEC_SYMBOLOGY_ROYAL_MAIL
//};


/* Error Codes */
#define DEC_ERR_NONE                          0
#define DEC_ERR_INVALID_HANDLE                1001
#define DEC_ERR_READ_ONLY                     1002
#define DEC_ERR_UNKNOWN_PROPERTY              1003
#define DEC_ERR_TOO_MANY_OBJECTS              1004
#define DEC_ERR_PROPERTY_LIFETIME             1005
#define DEC_ERR_COMPONENT_ABSENT              1006
#define DEC_ERR_COMPONENT_UNAUTHORIZED        1007
#define DEC_ERR_COMPONENT_UNAUTHORISED        1007 /* alternate spelling */
#define DEC_ERR_PROPERTY_VALUE                1008
#define DEC_ERR_IMAGE_PROPERTY_VALUE          1009
#define DEC_ERR_INSUFFICIENT_MEMORY           1010
#define DEC_ERR_AGC_COMPONENT_UNREACHABLE     1011
#define DEC_ERR_ILLEGAL_FUNCTION              1012

/**
 *   \brief Group Disable Codes used with DEC_DISABLE_SYMBOLOGY_GROUP.
 */
#define ONE_DIMENSIONAL_CODES      0x1   /// All linear symbologies like UPC, Code 128, Code 39.
#define STACKED_LINEAR_CODES       0x2   /// All stacked linear symbologies like PDF417 and Codablock.
#define TWO_DIMENSIONAL_CODES      0x4   /// All 2D matrix symbologies like Aztec, Data Matrix, and QR.

/**
 *   \defgroup decType Decoder Types
 *   Decoder Types used with the Decode function.
 *   @{
 */
#define DEC_TYPE_NONE   0
#define DEC_TYPE_ID     1     /// Integrated Decoder. Also referred to as Gen 6.
#define DEC_TYPE_AD     2     /// Adaptus Decoder. Also referred to as Gen 5 or Gen 5.5.
#define DEC_TYPE_FLD    3     /// Fast Linear Decoder.
#define DEC_TYPE_ULD    4     /// Unified Linear Decoder.
#define DEC_TYPE_IN2D   5     /// IN2Dcode. From formerly Intermec.
/** @} */

// Decoder Data Types
#define DECODE_IMAGE_TYPE_PIXELS       0
#define DECODE_IMAGE_TYPE_RUNLENGTH    1
#define DECODE_IMAGE_TYPE_DMLDD        2
#define DECODE_IMAGE_TYPE_MLDD         3
#define DECODE_IMAGE_TYPE_TIMERCOUNTS  4

// Preferred Mode settings
#define DEC_PREFERRED                  1
#define DEC_NOT_PREFERRED              2

// Video reverse modes
#define DEC_VID_REVERSE_OFF            0
#define DEC_VID_REVERSE_ONLY           1
#define DEC_VID_REVERSE_BOTH           2

// Vesta activation
#define VESTA_ON ((int)-1)
#define VESTA_OFF ((int)0)

/* 
 *   Temperature -- measure of how far along decoder is, not sure how to make portable 
 */
#define COLD 2         // Just searching for symbols
#define LUKEWARM 5     // Evidence of a particular symbol has been found
#define WARM 8         // The type of symbol has been confirmed; Data is being collected
#define HOT 16         // Data capture has been successful at some level, with more to go
#define COOKED 48      //  A fully valid read has occurred; putting on finishing touches

#endif // DECODER_CONSTANTS_H
