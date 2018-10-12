#ifndef TODO_H
#define TODO_H

#define CORDED
//managedbuffer/fifobase
#define DISABLE_INTERRUPTS()
#define RESTORE_INTERRUPTS()
#define DisableInterrupts(x)
#define RestoreInterrupts(x)


//SYN_FE_COMMAND_HANDLER
//#define xputchar


// FoundationAPP/menu/menu.h
#define NEW_MAJORTAG_CHAR  ';'
#define MAJOR_TAGSIZE   3
#define MINOR_TAGSIZE   3
#define TAG_SIZE        (MAJOR_TAGSIZE+MINOR_TAGSIZE)  //null terminator space added for CPP compile

//SynCommandParser.cpp
#define KCODE_MODE_TODO(a)//this is mainly called in menu.c, need to figure out what the purpose is here

// FoundationAPP/menu/Interface_Support_Functions.h
//#define USB_INTERFACE_CLASS 1

#endif

