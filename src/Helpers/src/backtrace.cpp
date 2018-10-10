/*
 * backtrace.cpp
 */
#include "backtrace.h"
#include <iostream>
#include <execinfo.h>
#include <cxxabi.h>
#include <dlfcn.h>


static constexpr bool FULL_STACK = false;

int backtrace_lookup(void * address, Dl_info * info, char ** demangle_buffer, size_t * demangle_length)
{
	int r = dladdr(address, info);
	if (r == 0)
	{
		*info = { 0 };
		return r;
	}

	if (info->dli_sname)
	{
		char * p = abi::__cxa_demangle(info->dli_sname, *demangle_buffer, demangle_length, nullptr);
		if (p)
		{
			*demangle_buffer = p;
			info->dli_sname = p;
		}
	}
	return r;
}


void backtrace_format(void * address, Dl_info * info, char * buffer, size_t length)
{
#define PRINT(format, ...) \
	do { \
		size_t remaining = buffer + length - p; \
		n = snprintf(p, remaining, format, __VA_ARGS__); \
		if (n < 0) \
			return; \
		if (n + 1 >= remaining) \
			return; \
		p += n; \
	} while(0)

	int n;
	ptrdiff_t offset;

	if (length == 0)
		return;
	buffer[0] = '\0';
	if (length == 1)
		return;
	char * p = buffer;


	if (info->dli_fname)
	{
		PRINT("%s", info->dli_fname);

		if (info->dli_sname)
		{
			offset = (char *)address - (char *)(info->dli_saddr);
			if (offset != 0)
			{
				const char * sign = (offset > 0 ? "+" : "");
				PRINT("(%s%s%d) ", info->dli_sname, sign, offset);
			}
			else
			{
				PRINT("(%s) ", info->dli_sname);
			}
		}
		else
		{
			offset = (char *)address - (char *)(info->dli_fbase);
			if (offset != 0)
			{
				const char * sign = (offset > 0 ? "+" : "");
				PRINT("%s%d ", sign, offset);
			}
		}
	}

	PRINT("[%p]", address);
#undef PRINT
}

void backtrace_format(void * address, char * formatted_buffer, size_t formatted_length,
		           	   	     char ** demangle_buffer, size_t * demangle_length)
{
	Dl_info info;
	backtrace_lookup(address, &info, demangle_buffer, demangle_length);
	backtrace_format(address, &info, formatted_buffer, formatted_length);
}

void backtrace_format(void * address, char * formatted_buffer, size_t formatted_length)
{
	char * demangle_buffer = 0;
	size_t demangle_length = 0;

	backtrace_format(address, formatted_buffer, formatted_length, &demangle_buffer, &demangle_length);
	if (demangle_buffer)
		free(demangle_buffer);
}

void backtrace_print(void (*callback)(void * closure, char * string), void * closure, void ** array, size_t size)
{
	char * demangle_buffer = 0;
	size_t demangle_length = 0;
	char formatted[161];

	for(int i=0; i<size; i++)
	{
		backtrace_format(array[i], formatted, sizeof(formatted), &demangle_buffer, &demangle_length);
		callback(closure, formatted);
	}

	if (demangle_buffer)
		free(demangle_buffer);
}

static void callback_function(void * closure, char * string)
{
	auto callback = (const std::function<void (const std::string & msg)> *)closure;
	(*callback)(string);
}

void backtrace_print(const std::function<void (const std::string & msg)> & callback, void ** array, size_t size)
{
	void * closure = (void *)(&callback);
	backtrace_print(callback_function, closure, array, size);
}

static void callback_FILE(void * closure, char * string)
{
	FILE * fp = (FILE *) closure;
	fprintf(fp, "%s\n", string);
}

void backtrace_print(FILE * fp, void ** array, size_t size)
{
	void * closure = fp;
	backtrace_print(callback_FILE, closure, array, size);
}

void backtrace_print(void (*callback)(void * closure, char * string), void * closure,  size_t depth, size_t start)
{
	if (!FULL_STACK)
		start += 1;

	void * array[depth + start];
	size_t size;

	// get void*'s for all entries on the stack
	size = backtrace(array, start + depth);

	if (size <= start)
		return;

	// print out all the frames to stderr
	backtrace_print(callback, closure, array + start, size - start);
}

void backtrace_print(const std::function<void (const std::string & msg)> & callback, size_t depth, size_t start)
{
	void * closure = (void *)(&callback);
	backtrace_print( callback_function, closure,
			     depth, start + (FULL_STACK ? 0 : 1)   );
}

void backtrace_print(FILE * fp, size_t depth, size_t start)
{
	void * closure = fp;
	backtrace_print( callback_FILE, closure,
			     depth, start + (FULL_STACK ? 0 : 1)   );
}

