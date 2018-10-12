/*
 * exception-log.cpp
 *
 *  Created on: May 6, 2018
 *      Author: honeywell
 */

#include "exception-log.h"
#include <cxxabi.h>
#include <stdarg.h>
#include <logging.h>
#include <syslog.h>
#include <execinfo.h>
#include <thread>
#include "realtime.h"
#include "backtrace.h"
#include "templates.h"

static thread_local struct exception_trace exception_trace;

static void log(const char * format, ...)
{
	va_list args;
	va_start (args, format);
	log_print2(LOG_CRIT, "terminate", format, args);
	va_end (args);

	va_start (args, format);
	vfprintf (stderr, format, args);
	va_end (args);
}


typedef void (*cxa_throw_type)(void *, void *, void (*) (void *)) __attribute__((__noreturn__));
static cxa_throw_type orig_cxa_throw = 0;

static void load_orig_throw_code()
{
    orig_cxa_throw = (cxa_throw_type) dlsym(RTLD_NEXT, "__cxa_throw");
}


extern "C"
void __cxa_throw (void *thrown_exception, void *pvtinfo, void (*dest)(void *)) {
    if (orig_cxa_throw == 0)
        load_orig_throw_code();

	// get void*'s for all entries on the stack
	exception_trace.n_trace = backtrace(exception_trace.array, exception_trace.MAX_TRACE);

    orig_cxa_throw(thrown_exception, pvtinfo, dest);
}

static std::terminate_handler original_terminate_handler;

static void terminate_handler()
{
	char * demangle_buffer = nullptr;
	size_t demangle_length = 0;
	char line[161];

	log("terminate() called from thread %s %d\n", get_thread_name(), std::this_thread::get_id());

	std::type_info *t = abi::__cxa_current_exception_type();
	if (t)
	{
		const char * name = t->name();
		char * dname = abi::__cxa_demangle(name, demangle_buffer, &demangle_length, nullptr);
		if (dname)
		{
			demangle_buffer = dname;
			name = dname;
		}


		log("unhandled exception %s\n", name);

		for (size_t i = 0; i < exception_trace.n_trace; ++i)
		{
			backtrace_format(exception_trace.array[i], line, elementsof(line), &demangle_buffer, &demangle_length);
			log("%s\n", line);
		}
	}
	original_terminate_handler();
}


void install_terminate_handler()
{
	original_terminate_handler = std::set_terminate(terminate_handler);
}
