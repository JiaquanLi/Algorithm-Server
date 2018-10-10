/****************************************************************************
   SD_OP.H - Omniplanar ONLY !!! header file containing definitions and function prototypes
****************************************************************************/

/* Copyright 1998-2000, Omniplanar, Incorporated.  All Rights Reserved */

/* Preamble */
#ifndef SD_OP_H_INCLUDED
#define SD_OP_H_INCLUDED

#include "SD.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Definitions */
/* Definitions->Components and Symbologies */
#define  SD_CONST_GC       (1 << 24)
#define  SD_CONST_DEBUG    (1 << 29)
#define  SD_CONST_TIMING   (1 << 30)
#define  SD_CONST_LM4SB    (1U << 31U) /* U appeases integer overflow warning from ADS 6/23/2004 DGC */

/* Definitions->ComponentsEx and SymbologiesEx */
#define  SD_CONST_DPM      (1 << 8)
#define  SD_CONST_PATCH    (1 << 10)
#define  SD_CONST_CSC      (1 << 11)
#define  SD_CONST_HX       (1 << 15)
#define  SD_CONST_CODE_Z   (1 << 21)


/* Definitions->Symbologies */

/* Definitions->Linkage */

/* Definitions->Constants */

/* Definitions->Properties */
#define SD_PROP_C128_OUT_OF_SPEC_SYMBOL         0x40010203
#define SD_PROP_QR_OUT_OF_SPEC_SYMBOL           0x40010903
#define SD_PROP_MSIP_OUT_OF_SPEC_SYMBOL         0x40011605
#define SD_PROP_GC_ENABLED                      0x40012401
#define SD_PROP_CALLBACK_GET_BYTE               0x40003100
#define SD_PROP_CALLBACK_PUT_BYTE               0x40003101
#define SD_PROP_MISC_DEBUG_FLAGS                0x40005100
#define SD_PROP_MISC_EXPANDED_DEBUG_FLAGS       0x40005101
#define SD_PROP_TP_NUM_START                    0x40012102
#define SD_PROP_DPM_FILTERS                     0x50012901
#define SD_PROP_DPM_BUFFER                      0x40012902
#define SD_PROP_DPM_ENABLED                     0x40012903
#define SD_PROP_PDF_HANDLE_INVALID_SHIFT        0x40010703
#define SD_PROP_PDF_ENHANCED_DAMAGE_HANDLING    0x40010710
#define SD_PROP_IMAGE_SIGNATURE_KEY             0x40013001
#define SD_PROP_MISC_RESULT_FILE                0x40005015
#define SD_PROP_MISC_CURRENT_SETTINGS           0x40005017
#define SD_PROP_PATCH_ENABLED                   0x40013201
#define SD_PROP_IMAGE_FINAL_HEIGHT              0x40004009
#define SD_PROP_MISC_PASS_THROUGH               0x40005016
#define SD_PROP_POSTAL_SUPPRESS_FINDS           0x40010814
#define SD_PROP_POSTAL_RM_MISC                  0x40010815
#define SD_PROP_POSTAL_MISC                     0x40010816
#define SD_PROP_DM_HIGH_SAMPLE_DENSITY          0x40010417
#define SD_PROP_DM_ENHANCED_DAMAGE_MODE         0x40010418
#define SD_PROP_MISC_CELLPHONE_IMPROVEMENTS     0x40005020
#define SD_PROP_C39_INCREASE_AGGRESSIVENESS     0x40010311
#define SD_PROP_C39_MISC                        0x40010312
#define SD_PROP_PROGRESS_FINDER_LINE            0x40006002
#define SD_PROP_CSC_ENABLED                     0x40013301
#define SD_PROP_AGC_SPECULAR_DETECTED           0x40002004
#define SD_PROP_AGC_SPECULAR_BOUNDS             0x70002005
#define SD_PROP_AGC_CELLPHONE_OPTIONS           0x40002006
#define ID_PROP_MISC_CELLPH_IMPROVEMENTS_DONE   0x40002007
#define SD_PROP_CODE_Z_ENABLED                  0x40014101


#define SD_PROP_CB_MISC                         0x40010105
#define SD_PROP_OCR_MISC                        0x40012311
#define SD_PROP_HX_BINARY_REMOVE_FIRST_BYTE     0x40013602
#define SD_PROP_CIRCULAR_BUFFER_LAG_RECOVERY    0x40012803
#define SD_PROP_UPC_PARTIAL                     0x40011007

#define ID_PROP_USE_MLD                         0x40100001
#define ID_PROP_USE_DISTANCE_MAP                0x40100002
#define ID_PROP_EDGE_DETECTOR                   0x40100003
#define ID_PROP_SUBPIXEL_FINDER                 0x40100004
#define ID_PROP_CYCLING_FINDER                  0x40100006

#define ID_PROP_MONOCOLOR_CORRECTION_ENABLE     0x40100007
#define ID_PROP_MONOCOLOR_CORRECTION_OFFSETX    0x40100008
#define ID_PROP_MONOCOLOR_CORRECTION_OFFSETY    0x40100009
#define ID_PROP_MONOCOLOR_CORRECTION_SPACINGX   0x40100010
#define ID_PROP_MONOCOLOR_CORRECTION_SPACINGY   0x40100011
#define ID_PROP_USE_VESTA                       0x40100012
#define SD_PROP_GAMMA_CORRECTION                0x40100013
#define SD_PROP_ROI_INFOS                       0x50008013


/* Definitions->Constants->Symbology Groups */
#define OP_SD_CONST_SYMBOLOGIES_GROUP ((SD_CONST_SYMBOLOGIES_GROUP)     |  \
                                      ((SD_CONST_GC) * (COMPONENT_GC))  |  \
                                      ((SD_CONST_LM4SB) * (COMPONENT_LM4SB)))

#define OP_SD_CONST_POSTAL_SYMBOLOGIES_GROUP ((SD_CONST_POSTAL_SYMBOLOGIES_GROUP) | \
                                             ((SD_CONST_LM4SB) * (COMPONENT_LM4SB)))

#define OP_SD_CONST_SYMBOLOGIES_GROUP_EX ((SD_CONST_SYMBOLOGIES_GROUP_EX) | \
                                          (SD_CONST_CSC) * (COMPONENT_CSC)| \
                                          (SD_CONST_HX) * (COMPONENT_HX))

#define OP_SD_CONST_POSTAL_SYMBOLOGIES_GROUP_EX ((SD_CONST_POSTAL_SYMBOLOGIES_GROUP_EX))

/* Type Definitions */


/* Function Prototypes */
SD_API2 int SD_STDCALL2 SD_PrivateFunction1(int Handle);
SD_API2 int SD_STDCALL2 SD_DumpSettings(int Handle, void SettingFunc(int prop, void *value));


/* Error Codes */

/* Improve Bounds bit assignments */
#define SD_CONST_S25_3SS_BOUND            1
#define SD_CONST_MICROPDF_BOUND           2
#define SD_CONST_RSSLIM_BOUND            10
#define SD_CONST_RSSEXP_BOUND            16

/* Postamble */
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif /* !SD_OP_H_INCLUDED */

