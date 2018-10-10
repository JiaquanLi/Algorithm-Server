//======================================================================================
// DecoderInterface.h
//======================================================================================
 
//---------------------------------------------------------------------------
//
//  Module Interface Description:
//      This file contains the interface definitions to create and interact with 
//      the decoder(s). This module will create separate decoder threads for each 
//      decoder it will interact with. 
//
//---------------------------------------------------------------------------

/* Copyright 2017, Honeywell.  All Rights Reserved */

#ifndef DECODER_INTERFACE_H
#define DECODER_INTERFACE_H

/* Check if this is a DLL build */
#ifdef DCL_IS_DLL
   #define DCL_STDCALL __stdcall
   #ifdef DCL_EXPORT
      #define DCL_API __declspec(dllexport)
   #endif
   #ifndef DCL_API
      #define DCL_API __declspec(dllimport)
   #endif   /* !DCL_API */
#else
   #if __GNUC__ >= 4
      #define DCL_API __attribute__ ((visibility ("default")))
   #else
      #define DCL_API 
   #endif
   #define DCL_STDCALL
#endif   /* DCL_IS_DLL */

/* Preamble */
#ifdef __cplusplus
extern "C" {
#endif

//Constants file
#include "DecoderConstants.h"

//Overall config file for the control logic
#include "DecoderConfig.h"
   
//Settings that apply to multiple decoders. Still may not apply to all decoders, so be wary for now...
#include "DecoderSettings.h"

//Include the settings that apply to decoders that are built in.
#if (SWIFT_BASE_DECODER)
#include "SwiftSettings.h"
#endif

#if (DECODER_AD)
#include "AdaptusSettings.h"
#endif

#if (DECODER_FLD)
//#include "FastLinearSettings.h" //not done yet, will have at least something in it
#endif

#if (DECODER_ULD)
#include "UnifiedLaserSettings.h"
#endif

/* Decoder Structures
 *  These are the structures by the decoder.
 */

/**
 *  \brief Callback tags used in InstallCallback.
 */
typedef enum {
   CB_PRINT,
   CB_TIMER,
   CB_RESULT,
   CB_RESULT_NOTIFY,
   CB_WATCHDOG,
   CB_STATUS,
   CB_PROGRESS
} CallbackTag;

/**
 *   \brief Defines a Point in the image coordinate system.
 */
typedef struct {
   int x;
   int y;
} Point_tag;

/**
 *   \brief The collection of points that defines the boundry of the barcode.
 */
typedef struct {
   Point_tag corners[4];
} Bounds;

/**
 *   \brief Information for IQ imaging functions with Image Core.
 */
typedef struct {
   Bounds bounds;
   int d_corner;
   int pdfRows;
   int pdfCols;
} IQImageInfo_t;

/**
 *   \brief Only used with Progressive Decoding.
 */
typedef struct {
   int frameID;
   int line;
   int state;
} CircluarBufferState;

/**
 * \brief Result structure that is passed through the Result Callback (CB_RESULT). Each result will have its own structure.
 */
typedef struct {
   unsigned char Data[MAX_DECODED_DATA_LENGTH]; /// Decoded data.
   int Length;                                  /// Number of characters in data. 
   Bounds MainBounds;                           /// Graphical boundry of barcode. 
   Point_tag GraphicalCenter;                   /// Graphical center of barcode.
   unsigned int Symbology;                      /// Symbology identifer. \see symbologyID
   unsigned int SymbologyEx;                    /// Extended symbology identifier. \see symbologyExID
   int Modifier;                                /// Modifier information of symbolody identifier.
   int ModifierEx;                              /// Extended mofifier information.
   char HHPCodeID;                              /// HHP Code identifier. \see hhpID
   char AIMCodeLetter;                          /// AIM identifier. \see aimID
   char AIMModifier;                            /// AIM modifier information.
   IQImageInfo_t IQImageInfo;                   /// IQ imaging information.
   int Parity;                                  /// Parity information. Applies to Data Matrix Append
   int AppendType;                              /// Append idenfifier. \see appendType
   int AppendIndex;                             /// Index of the result in the append sequence.
   int AppendTotal;                             /// Total number of results in the append sequence.
   int LinkFlag;                                /// Composite linking flag type.
   int ProgrammingCode;                         /// Reader programming code flag.
   int DecodeType;                              /// Decoder type that issued the result.
} DecoderResult;

/**
 *   \brief Image structure used with DEC_INJECT_MODE_IMAGE.
 */
typedef struct DecoderImage {
   int Height;
   int Width;
   int LineDelta;
   int Monocolor;
   int CenterX;
   int CenterY;
   void *pixels;
   struct DecoderImage *next;
} DecoderImage;

/**
 *  \defgroup apiFunctions Functions
 *  @{
 */

/** 
 *  InitDecoder:
 *  
 *  \brief Creates and initializes the Decoder Control Logic and all decoder libraries.
 *  
 *  \param [in] width The number of columns of the expected image data in pixels.
 *  \param [in] height The number of rows of the image data in pixels.
 *  \param [in] wrap The number of bytes a row of in memory.
 *  \return The combination of handles of the decoder libraries that are created and initialized.
 *  
 *  \details This must be called before using any other API function, aside from DestroyDecoder().
 */
DCL_API int DCL_STDCALL InitDecoder( int width, int height, int wrap );



/** 
 *  DestroyDecoder:
 *  
 *  \brief Destroys the DCL and any decoder libraries that were created and initialized with InitDecoder().
 *  
 *  \return Nothing.
 *  
 *  \details This function must be called when finished using any of the decoders.
 */
DCL_API void DCL_STDCALL DestroyDecoder( void );


/** 
 *  ReportDecoderVersion:
 * 
 *  \brief Copies the revision string of the type requested.
 *  
 *  \param [in] type Flag(s) of the revision string(s) being requested.
 *       DEC_REVISION_CONTROL_LOGIC   0x01
 *       DEC_REVISION_ID              0x02
 *       DEC_REVISION_FLD             0x08
 *  \param [out] reportString Memory space into which the revision string(s) will be copied.
 *  \return Nothing.
 *  
 *  \details The memory space must be long enough for the string(s) to be copied into. Since there is no length
 *       input to this function, the size of the memory cannot be checked. Each string is not more than 50 characters
 *       long, so if you are unsure of the length that will be returned, request one type at a time and copy the
 *       resulting string elsewhere.
 */
DCL_API void DCL_STDCALL ReportDecoderVersion( int type, char *reportString );


/** 
 *  InstallCallback:
 *  
 *  \brief Installs callback functions to the function tag to be used during decoding.
 *  
 *  \param [in] tag Function tag to tie the callback function to. 
 *  \param [in] function Function to be used for the callback.
 *  \return Non-zero if function succeeds. 
 *  
 *  \details The only reason for failure of this function is if the tag used is not part of the tag enum. If the
 *       function that is tied to a particular tag is incorrect, unexpected things will happen. 
 *       Callback functions prototypes:
 *          typedef  void (*fPrint_t)       (char *);
 *          typedef  int  (*fTimer_t)       (void);
 *          typedef  void (*fResult_t)      (int, DecoderResult *);
 *          typedef  void (*fResultNotify_t)(int);
 *          typedef  void (*fWatchDog_t)    (void);
 *          typedef  void (*fStatus_t)      (int, int);
 *          typedef  void (*fProgress_t)    (int);
 * 
 *  \see CallbackTag
 */
DCL_API int DCL_STDCALL InstallCallback( unsigned int tag, void *function );


/** 
 *  Decode:
 *  
 *  \brief Decodes the image data using the specified decoder library.
 *  
 *  \param [in] image Data to be decoded.
 *  \param [in] decodeType Decoder library to use.
 *  \return Depends on decoder library used to decode.
 *  
 *  \details The DCL can have many different decode libraries wrapped inside it. Each one has its own definitions of
 *       return values for their decode functions. There will be an attempt to harmonize the return values, or at 
 *       the very least document each one. 
 *
 *  \see decType
 */
DCL_API int DCL_STDCALL Decode( void *image, int decodeType );


/** 
 *  StopDecode:
 *  
 *  \brief Stops the decoder library.
 *  
 *  \return Non-zero if the decoder was told to stop. 
 *  
 *  \details Depending on the decoder library, this function might not be applicable. Also depending on the library,
 *       this function might only be available to be called at certain times. In general, this function will be responded 
 *       to during the execution of any of the callbacks installed.
 */
DCL_API int DCL_STDCALL StopDecode(void);


/** 
 *  ContinueDecode:
 *  
 *  \brief Continues the symbology that was processing when the Status callback was called. 
 *  
 *  \return Non-zero if the decoder was successfully told to continue. 
 *  
 *  \details Details
 */
DCL_API int DCL_STDCALL ContinueDecode(void);


/** 
 *  PauseDecode:
 *  
 *  \brief Stops the current symbology being processed.
 *  
 *  \return Non-zero if the decoder was successfully told to pause.
 *  
 *  \details Details
 */
DCL_API int DCL_STDCALL PauseDecode(void);


/** 
 *  DecodeGet:
 *  
 *  \brief Copies the value of the API tag to the memory space pointed to by data.
 *  
 *  \param [in] tag Decoder configuration tag.
 *  \param [out] data Memory space for value to be copied into.
 *  \return Non-zero if the data was retrieved successfully.
 *  
 *  \details Details
 */
DCL_API int DCL_STDCALL DecodeGet( unsigned int tag, void *data );


/** 
 *  DecodeSet:
 *  
 *  \brief Configures the API tag with the data.
 *  
 *  \param [in] tag Decoder configuration tag.
 *  \param [in] data Value to be set.
 *  \return Non-zero if the data was stored successfully.
 *  
 *  \details Details
 *  
 */
DCL_API int DCL_STDCALL DecodeSet( unsigned int tag, void *data );

/** 
 *  DecodeReset:
 *  
 *  \brief Sets the DCL and decoder library settings to their default values.
 *  
 *  \return Nothing
 *  
 *  \details Details
 */
DCL_API void DCL_STDCALL DecodeReset( void );


/** 
 *  GetLastDecoderError:
 *  
 *  \brief Returns the error code of the last error that occurred.
 *  
 *  \return Error code of the last error that occurred.
 *  
 *  \details Details
 */
DCL_API int DCL_STDCALL GetLastDecoderError(void);


/**
 *  ClearDecoderResults:
 *  
 *  \brief This function clears all stored partial results.
 *
 *  \return Nothing.
 *  
 *  \details Some append types in certain modes can store partial results so that a full result
 *    can be read across multiple images. For append types that are allowed to go across multiple
 *    images, but not across multiple trigger activations (assuming there are more than 1), it is
 *    important to clear these partial results. Clearing these partial results will avoid mixing 
 *    other pieces of the same append type and coming up with the wrong ultimate result.
 *  
 *    The only example so far of potential mixing of multiple symbols possible is Travel Document 1
 *    Passport reading, specifically mixing the 3rd row with rows 1 and 2 of another passport. Rows 1 and 2
 *    have a Composite Checksum calculation, but that calculation does not include row 3. Therefore, if rows 1
 *    and 2 are read in 1 trigger pull, and row 3 of another TD-1 is read in another trigger pull, inside the
 *    number of images specified by DEC_OCR_SECURITY, then all rows would be combined into a single result and 
 *    returned by the decoder. 
 *  
 *  \see Partial Result
 *  \see DEC_OCR_SECURITY
 */
DCL_API void DCL_STDCALL ClearDecoderResults(void);


/** @} */
/* Postamble */
#ifdef __cplusplus
}
#endif

#endif //DECODER_INTERFACE_H
