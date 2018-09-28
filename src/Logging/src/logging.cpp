/*
 * logging.c
 *
 *  Created on: Jun 7, 2016
 *      Author: honeywell
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <sys/time.h>
#include <vector>

#include "logging.h"

static char *logFile = "server.log";
static unsigned int LOG_SIZE = 4096;
static unsigned char log_level = LOG_ERR;
static const char *log_tag = "";
static std::vector<std::function<void(const char *format, va_list ap)>> callbacks;


void log_save_local(const char *tag,char* log)
{
	FILE *file;

	char cDateTime[50];
	time_t tt;
	time( &tt );
	tt = tt + 8 * 3600; // transform the time zone
	tm* t = gmtime( &tt );

	sprintf(cDateTime, "%d-%02d-%02d %02d:%02d:%02d",
	        t->tm_year + 1900,t->tm_mon + 1,t->tm_mday,
	        t->tm_hour,t->tm_min,t->tm_sec);

	if ( (file = fopen(logFile, "a+")) != NULL)
	{
		fprintf(file, "%s  %s:  %s\n", cDateTime, tag, log);
		fclose(file);
	}

}
/**
 * \brief Check if a message should be filtered out.
 * \param level Log level (0 to disable all logs, 1 for errors only, ...
 * \param tag Tag identifier of the debug log message.
 * \return true if the message should not be output.
 *
 * If the setup tag list (DebugTags) is empty, all messages are allowed.
 * Else, the message tag should be in the '+' separated list.
 * The string comparison is case insensitive.
 */
bool messageIsFilteredOut(const unsigned char level, const char *tag)
{
	//Quick exit if level filtering applies.
	if (log_level <= level) return true;

	if (log_tag == NULL)
	{
		log_tag = "";
	}

	if (tag == NULL || ((tag != NULL) && (tag[0] == '\0')))
	{
		return false;
	}

#define TOKEN_SEPARATORS "+"
	const char *tagList = log_tag;
	int tagListLen = strlen(tagList);
	bool filteredOut = false; // Message is allowed by default
	if (tagListLen > 0) // Message is allowed if the list is empty
	{
		char *tags = (char *)malloc(tagListLen + 1);
		if (tags == NULL) filteredOut = true;
		else
		{
			filteredOut = true; // Message is blocked until the tag is found
			strcpy(tags, tagList);
			char *currentTag = strtok(tags, TOKEN_SEPARATORS);
			while (filteredOut && (currentTag != NULL))
			{
				if (strcasecmp(currentTag, tag) == 0) filteredOut = false;
				else currentTag = strtok(NULL, TOKEN_SEPARATORS);
			}
			free(tags);
		}
	}
	return filteredOut;
}

/**
 * If level is below or equal to LOG_ERR, log is sent to syslog.
 * If level is below or equal to *log_level*, log is sent to websockets
 * by default or to a file in a folder set by *set_log_destination()*.
 */
void log_print(unsigned char level, const char *tag, const char *format, ...) {
	va_list args_list;
	va_start(args_list, format);
	char buffer[LOG_SIZE];

	/*
	if (messageIsFilteredOut(level, tag)) {
		printf("%s\n","debug log2" );
		return;
	}
	*/
	std::string tag_format(tag);
	std::string new_format(format);

	if (tag_format != "") {
		tag_format += ": ";
		new_format = tag_format + new_format;
	}

	if (level <= log_level) {
		vsyslog(level, new_format.c_str(), args_list);
		for (auto callback : callbacks)
			callback(format, args_list);
	}
	else {
		vsnprintf(buffer, LOG_SIZE, format, args_list);
		log_save_local(tag, buffer);
	}

	va_end(args_list);
}

void log_print2(unsigned char level, const char *tag, const char *format, va_list args_list) {

	char buffer[LOG_SIZE];
	if (messageIsFilteredOut(level, tag)) {
		return;
	}

	std::string tag_format(tag);
	std::string new_format(format);

	if (tag_format != "") {
		tag_format += ": ";
		new_format = tag_format + new_format;
	}

	if (level <= log_level) {
		vsyslog(level, new_format.c_str(), args_list);
		for (auto callback : callbacks)
			callback(format, args_list);
	}
	else {
		vsnprintf(buffer, LOG_SIZE, format, args_list);
		log_save_local(tag, buffer);
	}
}


void log_set_level(unsigned char level) {
	log_level = level;
}

void log_set_tag(const char *tag) {
	log_tag = tag;
}

void log_register_callback(std::function<void(const char *format, va_list ap)> f)
{
	callbacks.push_back(f);
}

