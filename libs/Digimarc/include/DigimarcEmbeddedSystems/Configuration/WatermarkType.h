// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2017
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_WATERMARKTYPE_H
#define DMRC_DESSDK_WATERMARKTYPE_H

namespace DigimarcEmbeddedSystems {

/** Describes the type of watermark being detected. */
enum WatermarkType {
	WatermarkType_Invalid = -1,				///< An invalid watermark
	WatermarkType_Luma,						///< A luminance watermark
	WatermarkType_Chroma_Mobile,			///< A chroma mobile watermark
	WatermarkType_Chroma_Package,			///< A chroma package watermark
	WatermarkType_RedOnly,					///< A watermark in the red channel
	WatermarkType_RedBlue_Luma,				///< A luminance watermark in the red/blue channels
	WatermarkType_RedBlue_Chroma_Mobile,	///< A chroma mobile watermark in the red/blue channels
	WatermarkType_RedBlue_Chroma_Package	///< A chroma package watermark in the red/blue channels
};

}

#endif
