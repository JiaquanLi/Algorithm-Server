//Main.cpp
/*
 * \brief Application revision information
 *
 * Versioning scheme:
 *     Major.Minor.Patch-PreRelease+BuildMetadata
 * where only Major, Minor and Patch are mandatory.
 * For instance:
 *     2.1.0-alpha.1+svn3456
 * Reference: http://semver.org/
 */


#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

#include "exception-log.h"
#include "AppRevision.h"
#include "GrpcServer.h"
#include "logging.h"

struct args {
	bool use_udmabuf;
	bool debugger_mode;
};

static struct args args = {
	.use_udmabuf = true,
	.debugger_mode = false,
};

static const char doc[] =
    APP_NAME " version " APP_VERSION
    " - barcode scanner app ";

static const char optionsstr[] =
    "-d  enable debugger mode\n"
    "      usb is not reinitialized\n"
    "-h  display help\n"
    "-u  disable use of udmabuf buffers (replaced by v4l2 ones)\n"
    "-v  display version\n";

static const char usage[] =
    "Usage: " APP_NAME "[-d] [-h] [-u] [-v]";

static int parse_opt(int argc, char * const argv[])
{
	int c;

	while ((c = getopt(argc, argv, "dhuv")) != -1) {
		switch (c) {
		case 'd':
			args.debugger_mode = true;
			break;
		case 'u':
			args.use_udmabuf = false;
			break;
		case 'v':
			printf("%s\n\n", doc);
			exit(EXIT_SUCCESS);
			break;
		case 'h':
			printf("%s\n\n", usage);
			printf("%s\n", optionsstr);
			exit(EXIT_SUCCESS);
			break;
		default:
			printf("%s\n\n", usage);
			printf("%s\n", optionsstr);
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}

static void sigsegv_handler(int sig)
{
	void *array[20];
	size_t size;

	// get void*'s for all entries on the stack
	size = backtrace(array, 20);

	// print out all the frames to stderr
	char **symbols = backtrace_symbols(array, size);
	if (symbols) {
		for (int i = 0; i < size; i++)
			syslog(LOG_EMERG, "SIGSEGV: %s", symbols[i]);
		free(symbols);
	}

	exit(1);
}

GrpcServer *g_Grpc = NULL ;

int main(int argc, char **argv)
{
	int err;

	install_terminate_handler();
	signal(SIGSEGV, sigsegv_handler);

	err = parse_opt(argc,argv);
	if(err) return err;
	
	openlog("algorithm-server", 0, LOG_LOCAL0);
	log_print(LOG_DEBUG, "MainAPP", "Server open");

	g_Grpc = new GrpcServer();
	g_Grpc->Start();

	delete g_Grpc;

	log_print(LOG_DEBUG, "Main", "Server Close");
	closelog();

	return true;
}
