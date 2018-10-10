//---------------------------------------------------------------------------
//  Copyright (C) Honeywell International, Inc. 2017
//---------------------------------------------------------------------------

#include <cerrno>
#include <string>

#include <fcntl.h>
#include <libgen.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "makepath.h"

/*----------------------------------------------------------------------------------------
GetFileLength

  Gets the length of the file on the file system.

  Parameters:
		FileName[in]:  name of file

  Returns:  >=0 if file was found, < 0 if an error.
----------------------------------------------------------------------------------------*/
int GetFileLength(const char * FileName)
{
	struct stat st;
	int length = 0;
	if (stat(FileName, &st) == 0)
		length = st.st_size;
	return length;
}

//WriteAndCloseFile
//	Inputs
//		const char *name the name of the file to write
//		unsigned int size size of data to write
//	Returns
//		>=0 length of data written
//		others <0 file system error i.e no space etc
//If this function fails to rewrite data it should leave old file unmodified
int WriteAndCloseFile(const char *filename, const unsigned char *data, int size)
{
	std::string tmpname = std::string(filename) + ".tmp";
	const char *filedir = dirname(strdupa(filename));

	// Prepare folder hierarchy if necessary
	if(mkpath(filedir, 0755))
		return -1;

	// Write file content to tmp file and sync
	int fd = open(tmpname.c_str(), O_WRONLY | O_CREAT, 0644);
	ssize_t sz = write(fd, data, size);
	fsync(fd);
	if(close(fd))
		return -1;

	// Rename tmp file and sync folder
	rename(tmpname.c_str(), filename);
	fd = open(filedir, O_RDONLY, 0644);
	if(fd < 0)
		return -1;
	fsync(fd);
	if(close(fd))
		return -1;

	return sz;
}

int ReadAndCloseFile(const char *name,unsigned int maxsize,unsigned char **Data)
{
	int ReadStatus=-1;
	FILE *f =fopen(name,"r");
	if (f)				//open ok procede
	{
		ReadStatus=-2;	//assume alloc failure
		unsigned char *p=NULL;
		int size = GetFileLength(name);

		if (!maxsize)
		{
			p =(unsigned char *)realloc(*Data,size); // no max size specified allocate memory
		}
		else
		{
			if (size<=maxsize) // if enough room
			{
				p=*Data;	//no allocation make p point to the users buffer
			}
		}
		if (p)
		{
			ReadStatus = fread(p,1,size,f);
			*Data=p;
		}
		fclose(f);
	}
    return ReadStatus;
}

// return true on success
bool StoreFileToFlashIfChanged(const char *filename,
		unsigned char *new_content, int new_content_size)
{
	int	status = 0;		// Success so far.
	unsigned char *current_content = NULL;

	status = ReadAndCloseFile(filename, 0, &current_content);
	if(status != new_content_size
		|| memcmp(current_content, new_content, new_content_size)) {
		status = WriteAndCloseFile(filename, new_content, new_content_size);
	}

	if (current_content)
		free(current_content);

	return(status == new_content_size);
}

int EraseFile(const char *name)
{
    return 	remove(name);
}

int RenameFile(const char *oldname,const char *newname)
{
    return 	rename(oldname, newname);
}

// int CopyFile(const char * destname,const char *sourcename)
// copy file in file system from sourcename to destname
// file must fit in memmory
// returns size of file if sucsess
// <0 if fail -1 file cant be opened -2 if buffer cant be malloced
int CopyFile(const char * destname,const char *sourcename)
{

    unsigned char *p=NULL;
    int Ret=ReadAndCloseFile(sourcename,0,&p);
    if (Ret >=0)
    {
        Ret =WriteAndCloseFile(destname,p,Ret);
    }
    if (p)
    {
        free(p);
    }
    return Ret;
}
