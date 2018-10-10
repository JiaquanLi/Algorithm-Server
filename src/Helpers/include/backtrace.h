/*
 * backtrace.h
 *
 *  Created on: Jan 20, 2018
 *      Author: honeywell
 */

#ifndef SRC_HELPERS_INCLUDE_BACKTRACE_H_
#define SRC_HELPERS_INCLUDE_BACKTRACE_H_

#include <functional>
#include <dlfcn.h>


int backtrace_lookup(void * address, Dl_info * info, char ** demangle_buffer, size_t * demangle_length);
void backtrace_format(void * address, Dl_info * info, char * buffer, size_t length);
void backtrace_format(void * address, char * formatted_buffer, size_t formatted_length,
		           	  char ** demangle_buffer, size_t * demangle_length);
void backtrace_format(void * address, char * formatted_buffer, size_t formatted_length);



void backtrace_print(const std::function<void (const std::string & msg)> & callback, void ** array, size_t size);
void backtrace_print(FILE * fp, void ** array, size_t size);

void backtrace_print(const std::function<void (const std::string & msg)> & callback, size_t depth = 20, size_t start = 0);
void backtrace_print(FILE * fp, size_t depth = 20, size_t start = 0);

#endif /* SRC_HELPERS_INCLUDE_BACKTRACE_H_ */
