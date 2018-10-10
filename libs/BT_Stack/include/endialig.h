/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/endialig.h,v $
 * Revision:    $Revision: 1.5 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#if ! defined(__ENDIALIG_H)
#define __ENDIALIG_H

/* Get local WORD from external 2 BYTE, Big-Endian format STANDARD NETWORK BYTE ORDER */
#define BE_EXTRN2WORD(p) ((*((p)+1)) & 0xff) + ((*(p)) << 8)

/* Get local DWORD from external 4 BYTE, Big-Endian format STANDARD NETWORK BYTE ORDER */
#define BE_EXTRN2DWORD(p) ((DWORD)(*((p)+3)) & 0xff) + ((DWORD)(*((p)+2)) << 8) \
                      + ((DWORD)(*((p)+1)) << 16)  + ((DWORD)(*((p)+0)) << 24)

/* PUT external 2 CHARS from local SHORT, Big-Endian format STANDARD NETWORK BYTE ORDER */
#define BE_WORD2EXTRN(p,w)                 \
   {*((p)+1) = (BYTE)((w) & 0xff);         \
    *(p)     = /*lint -e(572,778)*/ (BYTE)(((w)>>8) & 0xff);}

/* PUT external 4 BYTE from local DWORD, Big-Endian format STANDARD NETWORK BYTE ORDER */
#define BE_DWORD2EXTRN(p,w)                   \
   {*((p)+3) = (BYTE)((w) & 0xff);          \
    *((p)+2) = /*lint -e(572,778)*/ (BYTE)(((w)>>8) & 0xff);     \
    *((p)+1) = /*lint -e(572,778)*/ (BYTE)(((w)>>16) & 0xff);    \
    *((p)+0) = /*lint -e(572,778)*/ (BYTE)(((w)>>24) & 0xff);}

/* Get local WORD from external 2 BYTE, Little-Endian format */
#define LE_EXTRN2WORD(p) (((*(p)) & 0xff) + ((*((p)+1)) << 8))

/* Get local DWORD from external 4 BYTE, Little-Endian format  */
#define LE_EXTRN2DWORD(p) (((DWORD)(*((p)+0)) & 0xff) + ((DWORD)(*((p)+1)) << 8) \
                   + ((DWORD)(*((p)+2)) << 16)  + ((DWORD)(*((p)+3)) << 24))

/* PUT external 2 BYTE from local WORD, Little-Endian Format */
#define LE_WORD2EXTRN(p,w)                 \
   {*((LPBYTE)p)     = (BYTE)((WORD)(w) & 0xff);      \
    *(((LPBYTE)p)+1) = /*lint -e(572,778)*/ (BYTE)(((WORD)(w)>>8) & 0xff);}

/* PUT external 4 BYTE from local DWORD, Little endian Format */
#define LE_DWORD2EXTRN(p,w)                      \
   {*((LPBYTE)p)     = (BYTE)((DWORD)(w) & 0xff);          \
    *(((LPBYTE)p)+1) = (BYTE)(((DWORD)(w)>>8) & 0xff);     \
    *(((LPBYTE)p)+2) = (BYTE)(((DWORD)(w)>>16) & 0xff);    \
    *(((LPBYTE)p)+3) = (BYTE)(((DWORD)(w)>>24) & 0xff);}

#endif
