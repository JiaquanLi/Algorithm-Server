//======================================================================================
// DecoderLibRevision.h
//======================================================================================
 
//---------------------------------------------------------------------------
//
//  Module Interface Description:
//      This file contains the revision information for the Gen 6 decoder lib project.
//      This information gets reported using REV_AD.
//
//---------------------------------------------------------------------------

/* Copyright 2017, Honeywell.  All Rights Reserved */

#ifndef DECODER_LIB_REVISION_H
#define DECODER_LIB_REVISION_H

#define _STR(x)  #x
#define STR(x)   _STR(x)

#define VERSION_MAJOR    2017
#define VERSION_MINOR    08
#define VERSION_BUILD    5084
#define VERSION_MODS     0

// For Windows resource file:
#define VERSION_STRING   STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_BUILD) "." STR(VERSION_MODS)


#if VERSION_MODS
#define VERSION_MODS_TXT     "Local Mods"
#else
#define VERSION_MODS_TXT     ""
#endif

#define VERSION_STRING_2     STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_BUILD) " " VERSION_MODS_TXT



#endif //DECODER_LIB_REVISION_H
