//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Helpers to fix tchar_t, unsigned char (signed unsigned char) problems.
//---------------------------------------------------------------------------

#ifndef UCHAR_HELPER_H
#define UCHAR_HELPER_H

#include <stdio.h>

inline size_t strlen(const unsigned char *pStr)
{
	return strlen((const char*)pStr);
}

inline unsigned char *strcpy( unsigned char *strDestination, const unsigned char *strSource )
{
	return (unsigned char *)strcpy( (char *)strDestination, (const char *)strSource );
}

inline unsigned char *strcpy( unsigned char *strDestination, const char *strSource )
{
	return (unsigned char *)strcpy( (char *)strDestination, (const char *)strSource );
}

inline unsigned char *strncpy( unsigned char *strDestination, const unsigned char *strSource, size_t count  )
{
	return (unsigned char *)strncpy( (char *)strDestination, (const char *)strSource, count );
}

inline unsigned char *strncpy( unsigned char *strDestination, const char *strSource, size_t count  )
{
	return (unsigned char *)strncpy( (char *)strDestination, (const char *)strSource, count );
}

inline unsigned char *strcat( unsigned char *strDestination, const unsigned char *strSource )
{
	return (unsigned char *)strcat( (char *)strDestination, (const char *)strSource );
}

inline unsigned char *strncat( unsigned char *strDestination, const unsigned char *strSource, size_t count  )
{
	return (unsigned char *)strncat( (char *)strDestination, (const char *)strSource, count );
}

inline unsigned char *strchr( const unsigned char *string, int c )
{
	return (unsigned char *)strchr( (const char *)string, c );
}

inline unsigned char *strrchr( const unsigned char *string, int c )
{
	return (unsigned char *)strrchr( (const char *)string, c );
}

inline unsigned char *strstr( const unsigned char *string, const unsigned char *strCharSet )
{
	return (unsigned char *)strstr( (const char *)string, (const char *)strCharSet );
}

inline unsigned char *strstr( const unsigned char *string, const char *strCharSet )
{
	return (unsigned char *)strstr( (const char *)string, (const char *)strCharSet );
}

inline unsigned char *strstr( const char *string, const unsigned char *strCharSet )
{
	return (unsigned char *)strstr( (const char *)string, (const char *)strCharSet );
}

inline int strcmp( const unsigned char *string1, const unsigned char *string2 )
{
	return strcmp( (const char *)string1, (const char *)string2 );
}

inline int strcmp( const unsigned char *string1, const char *string2 )
{
	return strcmp( (const char *)string1, (const char *)string2 );
}

inline int strcmp( const char *string1, const unsigned char *string2 )
{
	return strcmp( (const char *)string1, (const char *)string2 );
}

inline int strncmp( const unsigned char *string1, const unsigned char *string2, size_t count )
{
	return strncmp( (const char *)string1, (const char *)string2, count );
}

/*
inline int stricmp( const unsigned char *string1, const unsigned char *string2 )
{
	return stricmp( (const char *)string1, (const char *)string2 );
}

inline int strnicmp( const unsigned char *string1, const unsigned char *string2, size_t count )
{
	return strnicmp( (const char *)string1, (const char *)string2, count );
}
*/

inline int atoi(const unsigned char *pStr)
{
	return atoi((const char*)pStr);
}

inline long atol(const unsigned char *pStr)
{
	return atol((const char*)pStr);
}

inline double atof(const unsigned char *pStr)
{
	return atof((const char*)pStr);
}

size_t sprintf(unsigned char *pBuffer,const unsigned char *pFormat, ...);
size_t _snprintf(unsigned char *pBuffer, size_t n, const unsigned char *pFormat, ...);

#endif
