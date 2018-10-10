/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./src/system/port/stosif.h,v $
 * Revision:    $Revision: 1.4 $
 * Date:        $Date: 2018/04/20 10:42:56 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_STOSIF_H
#define __BLUECODE_STOSIF_H

/** @file
 * OSIF interface of BlueCode+. Customer porting code should provide an implementation of the OSIF connector with platform-specific handlers. */

#include <stddef.h> // size_t

#if defined (__cplusplus)
extern "C" {
#endif

// External callback interface structure. Matching functions should be implemented in porting code

/** Can be called by BlueCode+ to request scheduling. */
typedef void (* TOsifReady) (void);

/** Can be called by BlueCode+ to initialize a critical section.
 * @return Context handle to identify the section in subsequent calls. Ownership is shared. */
typedef void *(* TInitCriticalSection) (void);

/** Can be called by BlueCode+ before entering a critical section. The call shall block indefinitely while another thread is operating within the critical section.
 * @param pParam [in,out] Context handle given to BlueCode+ on section initialization. Ownership is shared
 * @return historical return value, can be ignored. */
typedef unsigned long (* TEnterCriticalSection) (
        void * pParam);

/** Can be called by BlueCode+ after exiting a critical section.
 * @param pParam [in,out] Context handle given to BlueCode+ on section initialization. Ownership is shared
 * @param psw    [in] Historical argument, will be ignored */
typedef void (* TExitCriticalSection) (
        void * pParam,
        unsigned long psw);

/** Can be called by BlueCode+ to request allocation of a memory block.
 * @param size [in] Size of the requested memory block in octets
 * @return the memory allocated for usage by BlueCode+. Ownership is shared.
 * @retval NULL if allocation failed or @p size was 0. */
typedef void * (* TMemoryAllocate) (
        int size);

/** Can be called by BlueCode+ to release a previously allocated memory block.
 * @param pBlock [in,out] The memory previously provided to BlueCode+. Ownership is transferred */
typedef void (* TMemoryFree) (
        void * pBlock);

/** Can be called by BlueCode+ to initialize a block of non-volatile memory.
 * The contents of this memory shall be preserved after termination of BlueCode+.
 * BlueCode+ will not request more than one block, therefore all "NV*" calls refer to the same block.
 * If @p size is smaller than the size of a preserved block, the block shall be truncated.
 * Memory segments that have never been written to shall be filled with zeroes.
 * For more details (including the maximum size), see:
 * @llPortingGuide{1,5.2.2.5,Non-volatile Memory Access}
 * @param size [in] The size of the requested memory block */
typedef void (* TNVInit) (
        size_t size);

/** Can be called by BlueCode+ to read from a previously initialized block of non-volatile memory.
 * @param dest [out] Destination buffer to fill with the read data
 * @param size [in] The amount of data to read from the block, in octets */
typedef void (* TNVRead) (
        void * dest,
        size_t size);

/** Can be called by BlueCode+ to write data to a previously initialized block of non-volatile memory.
 * @param source [in] Source buffer containing the data to be written
 * @param size   [in] The amount of data to read from @p source, in octets */
typedef void (* TNVWrite) (
        void const * source,
        size_t size);

/** Can be called by BlueCode+ to output a debug trace message.
 * @param message [in] The message string. Not zero-terminated. Ownership shall be preserved
 * @param size    [in] Length of @p message */
typedef void (* TTrace) (
        char const * message,
        size_t size);

/** Can be called by OSIF to request termination of BlueCode+. */
typedef void (* TOsifShallExit) (void);

/** Can be called by BlueCode+ to signal that all previously acquired resources may be released. */
typedef void (* TOsifRelease) (void);

/** Can be called by OSIF to terminate BlueCode+ after its resources have been released. */
typedef void (* TOsifExit) (void);

/** Can be called by BlueCode+ to signal that a fatal error has occurred.
 * @param pFile [in] Name of the source file containing the signaling code
 * @param iLine [in] Line in the source file of the signaling code*/
typedef void (* TFatalError) (
        char * pFile,
        int iLine);

/** Can be called by OSIF to schedule BlueCode+.
 * @param TimeElapsedMSecond [in] Time passed since the last call to OsifActive, in milliseconds
 * @return the delay in milliseconds until BlueCode+ should be scheduled again.
 * @retval 0 if no rescheduling is required. */
typedef int (* TOsifActive) (
        int TimeElapsedMSecond);

/** BlueCode+ OSIF connector. Filled by the external OSIF layer and BlueCode+ before and during #stOsifInit.
 * Each member function must either be implemented by the stack ("internal") or by the external OSIF ("external").
 * Some external member function pointers may be set to NULL if no handling is required on the platform. */
typedef struct _TStOSIF
{
    TOsifReady                   OsifReady;            /**< (external) Called by BlueCode+ to request scheduling. May not be NULL */
    TInitCriticalSection         InitCriticalSection;  /**< (external) Called by BlueCode+ to initialize a critical section. May be NULL */
    TEnterCriticalSection        EnterCriticalSection; /**< (external) Called by BlueCode+ before entering a critical section. May be NULL */
    TExitCriticalSection         ExitCriticalSection;  /**< (external) Called by BlueCode+ after exiting a critical section. May be NULL */
    TMemoryAllocate              MemoryAllocate;       /**< (external) Called by BlueCode+ to request allocation of a memory block. May not be NULL */
    TMemoryFree                  MemoryFree;           /**< (external) Called by BlueCode+ to release a previously allocated memory block. May be NULL */
    TNVInit                      NVInit;               /**< (external) Called by BlueCode+ to initialize a block of non-volatile memory. May not be NULL */
    TNVRead                      NVRead;               /**< (external) Called by BlueCode+ to read from non-volatile memory. May not be NULL */
    TNVWrite                     NVWrite;              /**< (external) Called by BlueCode+ to write to non-volatile memory. May not be NULL */
    TTrace                       Trace;                /**< (external) Called by BlueCode+ to output a debug trace message. May be NULL */
    TOsifShallExit               OsifShallExit;        /**< (internal) Called by OSIF to request termination of BlueCode+ */
    TOsifRelease                 OsifRelease;          /**< (external) Called by BlueCode+ to signal that all previously acquired resources may be released. May not be NULL */
    TOsifExit                    OsifExit;             /**< (internal) Called by OSIF to terminate BlueCode+ after its resources have been released */
    TFatalError                  FatalError;           /**< (external) Called by BlueCode+ to signal that a fatal error has occurred. May not be NULL */
    TOsifActive                  OsifActive;           /**< (internal) Called by OSIF to schedule BlueCode+ */
} TStOSIF;
typedef TStOSIF * PStOSIF; /**< Pointer to #TStOSIF */

// External interface

/** Initializes and starts BlueCode+.
 * @retval !=0 if an error occurred during initialization. */
int stOsifInit(
    PStOSIF pStOSIF /**< [in,out] OSIF connector whose external callback members have been assigned. Internal callback members will be filled by this call */);

#if defined (__cplusplus)
}
#endif

#endif /* ndef __BLUECODE_STOSIF_H */
