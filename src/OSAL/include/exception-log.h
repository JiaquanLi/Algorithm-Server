#include <stddef.h>

struct exception_trace
{
	static const unsigned MAX_TRACE = 32;
	void * array[MAX_TRACE];
	size_t n_trace;
};

exception_trace * get_exception_trace();
void install_terminate_handler();
