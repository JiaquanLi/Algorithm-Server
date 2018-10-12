//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

#ifndef MENU_FILES_UTILITIES_H
#define MENU_FILES_UTILITIES_H

// file names
#define	FLASH_MAX_CONFIGURATION_LENGTH   0x2000		// Maximum size of configuration area is 8K
#define FILENAME_PRODUCT_CONFIG     "/srv/scanning/settings/ProductConfig.txt"
#define FILENAME_WORKING_CONFIG     "/srv/scanning/settings/WorkingConfig.txt"  // cordless scanners have a single file
#define FILENAME_WORKING_CONFIG_0   "/srv/scanning/settings/WorkingConfig0.txt"
#define FILENAME_WORKING_CONFIG_1   "/srv/scanning/settings/WorkingConfig1.txt"
#define FILENAME_DEFAULT_CONFIG     "/srv/scanning/settings/DefaultConfig.txt"


int WriteAndCloseFile(const char *name, const unsigned char *data, int size);
int ReadAndCloseFile(const char *name,unsigned int maxsize,unsigned char **Data);
int GetFileLength(const char * FileName);
bool StoreFileToFlashIfChanged(const char *filename,
		unsigned char *new_content, int new_content_size);
int EraseFile(const char *name);
int RenameFile(const char *oldname,const char *newname);
int CopyFile(const char * destname,const char *sourcename);

#endif
