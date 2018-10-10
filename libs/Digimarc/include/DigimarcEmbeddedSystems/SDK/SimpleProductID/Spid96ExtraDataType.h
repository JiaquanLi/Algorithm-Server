// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMRC_DESSDK_SPID96EXTRADATATYPE_H
#define DMRC_DESSDK_SPID96EXTRADATATYPE_H

namespace DigimarcEmbeddedSystems {

/** Describes the data type of the Simple Product ID 96 extra data. */
enum Spid96ExtraDataType {
	  Spid96ExtraDataType_Numeric			///< SPID96 extra data is numeric
	, Spid96ExtraDataType_Alphanumeric		///< SPID96 extra data is alpha-numeric
	, ExtraDataType_Numeric					///< Plain extra data that is numeric
	, Spid96ExtraDataType_None = 1000		///< SPID96 extra data is not present
};

}

#endif
