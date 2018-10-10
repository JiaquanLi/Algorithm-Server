//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

#ifndef ERROR_DEFS_H_F3E1EF42_35D6_11D2_93BE_00805F2987D9
#define ERROR_DEFS_H_F3E1EF42_35D6_11D2_93BE_00805F2987D9


//! All the official error numbers.
/*! The error numbers are divided into several groups:
		- Legacy numbers
		- IoControl return values
		- A range for return an USHORT value
		- Error numbers
		- Warning numbers (not used right now)

*/
enum MatrixError_t : unsigned int
{
// legacy stuff
	ERR_FAIL	= 0,										//!< Legacy fail value
	ERR_PASS = 1,                             //!< Legacy pass value

 // return values for the IoControl command of the interface drivers
	IOCRET_DEFAULT,									//!< IoControl return: Use the default action.
	IOCRET_YES,											//!< IoControl return: Yes
	IOCRET_NO,											//!< IoControl return: No
	IOCRET_FAIL=ERR_FAIL,					   	//!< Deprecated, do not use anymore
	IOCRET_PASS=ERR_PASS,							//!< Deprecated, do not use anymore

// pass values back up to USHORT size
	OK_VAL_MIN	= 0x08000000,						//!< Lowest value of this group
	OK_VAL_BIT	= OK_VAL_MIN,						//!< This bit flags that MatrixError_t contains a return value
	OK_VAL_MASK = 0x0000FFFF,						//!< Mask to extract a return value out of a MatrixError_t
	OK_VAL_MAX	= 0x0800FFFF,						//!< Highest value of this group

// Errors
	ERR_MIN	= 0x20000000,                    //!< Lowest value of this error group
	ERR_BIT = ERR_MIN,								//!< This bit flags an error

 	// generic
	ERR_BADPARAM,										//!< An invalid Parameter was passed
	ERR_MEMORY_EXHAUSTED,							//!< We did run out of memory
	ERR_INSUFFIZIENT_BUFFER,						//!< Provided buffer was to small

	// interfaces
	ERR_NO_SUCH_INTERFACE,			         	//!< Term ID not found in if_table
	ERR_NO_SUCH_INTERFACE_TYPE,					//!< Menu glue does not know this interface type
	ERR_BAD_DELAY_PARAMS,							//!< DriverBase found bad InterX delay, (or did not find delays)
	ERR_BAD_ALIGNMENT,								//!< USB controller needs data aligned to ULONG
	ERR_CONNECT_TIMEOUT,								//!< USB (or other) driver did not get a connection with our host
	ERR_NOT_ALLOWED,									//!< Close not allowed for 4683
	ERR_COULD_NOT_SEND,								//!< Could not send the barcode
	ERR_COULD_NOT_PREPARE,							//!< Could not prepare data for sending
	ERR_NEED_RECONNECT,								//!< Returned by USB extract functions if the parameters require a USB re-connect

	// CBarcodeData and translations
	ERR_WRONG_DATA_TYPE,								//!< The object did not contain the requested data type
	ERR_UNKNOWN_CODEPAGE,							//!< The codepage is not supported
	ERR_BAD_TRANSLATION,								//!< Translation failed

	// Buffers
	ERR_BAD_GUARD,                         	//!< PANIC! Buffer overflow, guard area has been destroyed

	// bitbangers
	ERR_BB_ILLEGAL_CMD,								//!< Bitbang runtime found an illegal command
	ERR_BB_READ_NoData,								//!< The bitbang receiver did not find data (not really an error)
	ERR_BB_READ_Aborted,								//!< The bitbang receiver aborted the read, host might have aborted its tranmittion
	ERR_BB_READ_ERROR,								//!< Generic bitbang read error
	ERR_BB_READ_Parity,								//!< The bitbang receiver did find a bad parity
	ERR_BB_READ_NeedResend,							//!< Byte needs to be send again

	// Product config block
	ERR_CONFIG_INCOMPATIBLE,						//!< Not used anymore
	ERR_BAD_CONFIG_CHECKSUM,						//!< Not used anymore

	ERR_MAX	= 0x2FFFFFFF,							//!< Highest value of error group

// Warnings
	WARN_MIN	= 0x40000000,							//!< Lowest value of warning group
	WARN_BIT = WARN_MIN,								//!< This bit flags a warning

	WARN_MAX	= 0x4FFFFFFF,							//!< Highest value of warning group

	ERR_END_OF_TABLE = 0xffffffff		      	//!< Used to flag the end of an error table
};

///////////////////////////////////////////////////////////////////////////////
//! Checks whether the passed error number is an error or an OK.
/*!
 \param number Matrix error number.
 \return true if it is an error.
*/
inline bool IsError(MatrixError_t number)
{
	return (number & ERR_BIT) || (number == ERR_FAIL);
}

///////////////////////////////////////////////////////////////////////////////
//! Checks whether the passed error number is a warning or an OK.
/*!
 \param number Matrix error number.
 \return true if it is a warning.
*/
inline bool IsWarning(MatrixError_t number)
{
	return (number & WARN_BIT) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//! Checks whether the passed error number is an error or a warning or an OK.
/*!
 \param number Matrix error number.
 \return true if it is an error or a warning.
*/
inline bool IsErrorOrWarning(MatrixError_t number)
{
	return (number & (WARN_BIT|ERR_BIT)) || (number == ERR_FAIL);
}

///////////////////////////////////////////////////////////////////////////////
//! Checks whether the passed error number is the OK marker.
/*!
 \param number Matrix error number.
 \return true if it is the OK marker.
*/
inline bool IsOK(MatrixError_t number)
{
	return (number == ERR_PASS);
}

///////////////////////////////////////////////////////////////////////////////
//! Checks whether the passed error number is actually a return value.
/*!
 \param number Matrix error number.
 \return true if it is actually a return value.
*/
inline bool IsErrValue(MatrixError_t number)
{
	return (number & OK_VAL_BIT) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
//! Extracts the return value from the passed error number.
/*!
 \param number Matrix error number.
 \return Extracted return value.
*/
inline unsigned short GetErrValue(MatrixError_t number)
{
	return (unsigned short)(number & OK_VAL_MASK);
}

///////////////////////////////////////////////////////////////////////////////
//! Creates an error number from a return value.
/*!
 \param number Return value.
 \return Matrix error number.
*/
inline MatrixError_t MakeErrReturnValue(unsigned short val)
{
	return (MatrixError_t)(val | (unsigned int)OK_VAL_BIT);
}

#endif
