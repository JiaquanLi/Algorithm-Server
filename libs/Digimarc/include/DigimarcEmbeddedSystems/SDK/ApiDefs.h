// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -


#ifndef DMRC_DESSDK_APIDEFS_H
#define DMRC_DESSDK_APIDEFS_H


#if defined(_WIN32)
#	if defined(DMRC_SDK_BUILD)
#		define DMRC_API __declspec(dllexport)
#	else
#		define DMRC_API __declspec(dllimport)
#endif
#else
#	define DMRC_API
#endif

#endif
