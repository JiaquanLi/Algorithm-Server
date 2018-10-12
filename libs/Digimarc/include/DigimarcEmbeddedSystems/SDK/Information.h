// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -


#ifndef DMRC_DESSDK_INFORMATION_H
#define DMRC_DESSDK_INFORMATION_H

#include "ApiDefs.h"

namespace DigimarcEmbeddedSystems {

/**
 * @brief The Information class can be used to programmatically access details about this SDK. Package version, build number, venter, etc.
 */
class Information {
public:

	DMRC_API static const char* Vendor;			///< Digimarc: Name of the company or group who authored this software.
	DMRC_API static const char* ProductName;		///< GUM: Official name of software package.

	DMRC_API static const char* TargetPlatform;		///< iMX6UL: Name of the targeted system.
	DMRC_API static const char* TargetProcessor;		///< ARM: Name of the targeted processor type.
	DMRC_API static const char* TargetSystem;		///< Generic: Name of the targeted OS.
	DMRC_API static const char* BasicCompilerName;	///< Poky: Name of the compiler used (version not included).
	DMRC_API static const char* BuildType;			///< release:Debug or Release build.

	DMRC_API static const int VersionMajor;			///< 3: Major software version (X.y.z.b)
	DMRC_API static const int VersionMinor;			///< 5: Minor software version (x.Y.z.b)
	DMRC_API static const int VersionPatch;			///< 2: patch software version (x.y.Z.b)
	DMRC_API static const char* VersionBuild;		///< : Build number of software (x.y.z.B)
	DMRC_API static const char* VersionConstructed;	///< 3.5.2 - : Fully constructed version string useful for general printing.
};
}

#endif
