/*
 * string-utilities.c
 *
 *  Created on: 4 janv. 2017
 *      Author: honeywell
 */
#include <string.h>
#include "string-utilities.h"

// Helper function to find the substring in a string. HSTRING->FindString doesn't work
// return the start position of the substring in the string
int strindex(const char *str,const char *substr)
{
	const char *p =strstr(str,substr);
	return (p)?p-str:-1;
}
