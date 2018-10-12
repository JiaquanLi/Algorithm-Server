/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/gatt.h,v $
 * Revision:    $Revision: 1.22 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_GATT_H
#define __BLUECODE_GATT_H

#if !defined(V_BLUECODE_EXPORTED) || defined(V_BLUECODE_INTERNAL)
#include "flags.h" // Variant management
#endif

/** @file
 * GATT-related data types and useful constants for the BlueAPI interface of BlueCode+. BlueAPI application code that uses GATT should include this header.
 * This file also includes useful constants matching number assigned by the Bluetooth SIG. For their documentation, see:
 * @btasgn{Bluetooth Assigned Numbers} */

#ifdef __cplusplus
extern "C" {
#endif

#define UUID_16BIT_SIZE  ((size_t)  2)            /**< Size of a 16-bit UUID, in octets */
#define UUID_128BIT_SIZE ((size_t) 16)            /**< Size of a 128-bit UUID, in octets */
#define HI_WORD(x) ((uint8_t)((x & 0xFF00) >> 8)) /**< Most significant byte of a 16-bit integer */
#define LO_WORD(x) ((uint8_t) (x & 0x00FF)      ) /**< Least significant byte of a 16-bit integer */

/** @cond Doxygen_Ignored */
#if !defined(UUID_GATT)
#define UUID_GAP                        0x1800
#define UUID_GATT                       0x1801
#endif

#ifdef V_MAYBE_OBSOLETE
/* private codes for testing purposes: */
#define GATT_UUID_PRIVATE_SERVICE_1     0xF001
#define GATT_UUID_PRIVATE_SERVICE_2     0xF002
#define GATT_UUID_PRIVATE_SERVICE_3     0xF003
#define GATT_UUID_PRIVATE_SERVICE_4     0xF004

#define GATT_UUID_PRIVATE_CHAR_VALUE_1  0xF101
#define GATT_UUID_PRIVATE_CHAR_VALUE_2  0xF102
#define GATT_UUID_PRIVATE_CHAR_VALUE_3  0xF103
#define GATT_UUID_PRIVATE_CHAR_VALUE_4  0xF104
#define GATT_UUID_PRIVATE_CHAR_VALUE_5  0xF105
#define GATT_UUID_PRIVATE_CHAR_VALUE_6  0xF106
#define GATT_UUID_PRIVATE_CHAR_VALUE_7  0xF107
#define GATT_UUID_PRIVATE_CHAR_VALUE_8  0xF108
#define GATT_UUID_PRIVATE_CHAR_VALUE_9  0xF109
#endif

// GATT service and characteristic definition codes
#define GATT_UUID_PRIMARY_SERVICE       0x2800
#define GATT_UUID_SECONDARY_SERVICE     0x2801
#define GATT_UUID_INCLUDE               0x2802
#define GATT_UUID_CHARACTERISTIC        0x2803

// GATT characteristic descriptors
#define GATT_UUID_CHAR_EXTENDED_PROP    0x2900
#define GATT_UUID_CHAR_USER_DESCR       0x2901
#define GATT_UUID_CHAR_CLIENT_CONFIG    0x2902
#define GATT_UUID_CHAR_SERVER_CONFIG    0x2903
#define GATT_UUID_CHAR_FORMAT           0x2904
#define GATT_UUID_CHAR_AGGR_FORMAT      0x2905
#define GATT_UUID_CHAR_VALID_RANGE      0x2906

// GATT service/profile characteristics
#define GATT_UUID_CHAR_DEVICE_NAME          0x2A00
#define GATT_UUID_CHAR_APPEARANCE           0x2A01
#define GATT_UUID_CHAR_PER_PRIV_FLAG        0x2A02
#define GATT_UUID_CHAR_RECONN_ADDRESS       0x2A03
#define GATT_UUID_CHAR_PER_PREF_CONN_PARAM  0x2A04
#define GATT_UUID_CHAR_SERVICE_CHANGED      0x2A05

// GATT characteristic properties
#define GATT_CHAR_PROP_BROADCAST          0x01
#define GATT_CHAR_PROP_READ               0x02
#define GATT_CHAR_PROP_WRITE_NO_RSP       0x04
#define GATT_CHAR_PROP_WRITE              0x08
#define GATT_CHAR_PROP_NOTIFY             0x10
#define GATT_CHAR_PROP_INDICATE           0x20
#define GATT_CHAR_PROP_WRITE_AUTH_SIGNED  0x40
#define GATT_CHAR_PROP_EXT_PROP           0x80

// GATT client characteristic configuration bit field
#define GATT_CLIENT_CHAR_CONFIG_DEFAULT   0x0000
#define GATT_CLIENT_CHAR_CONFIG_NOTIFY    0x0001
#define GATT_CLIENT_CHAR_CONFIG_INDICATE  0x0002

// GATT server characteristic configuration bit field
#define GATT_SERVER_CHAR_CONFIG_BROADCAST 0x0001
// GATT appearance
#define GATT_APPEARANCE_UNKNOWN                   0x0000
#define GATT_APPEARANCE_HID_GENERIC               0x03C0
#define GATT_APPEARANCE_HID_SUBTYPE_KEYBOARD      0x03C1
#define GATT_APPEARANCE_HID_SUBTYPE_MOUSE         0x03C2

// Some service and characteristic UUIDs
#define GATT_UUID_DEVICE_INFORMATION_SERVICE      0x180A
#define GATT_UUID_CHAR_SYSTEM_ID                  0x2A23
#define GATT_UUID_CHAR_MODEL_NUMBER               0x2A24
#define GATT_UUID_CHAR_SERIAL_NUMBER              0x2A25
#define GATT_UUID_CHAR_FIRMWARE_REVISION          0x2A26
#define GATT_UUID_CHAR_HARDWARE_REVISION          0x2A27
#define GATT_UUID_CHAR_SOFTWARE_REVISION          0x2A28
#define GATT_UUID_CHAR_MANUFACTURER_NAME          0x2A29
#define GATT_UUID_CHAR_IEEE_CERTIF_DATA_LIST      0x2A2A
#define GATT_UUID_CHAR_PNP_ID                     0x2A50

#define GATT_UUID_BLOOD_PRESSURE                  0x1810
#define GATT_UUID_CHAR_BLS_MEASUREMENT            0x2A35
#define GATT_UUID_CHAR_BLS_INT_CUFF_PRESSURE      0x2A36
#define GATT_UUID_CHAR_BLS_FEATURE                0x2A49

#define GATT_UUID_HEART_RATE                      0x180D
#define GATT_UUID_CHAR_HRS_MEASUREMENT            0x2A37
#define GATT_UUID_CHAR_HRS_CONTROL_POINT          0x2A39

#define GATT_UUID_CHAR_RACP                       0x2A52

#define GATT_UUID_GLUCOSE                         0x1808
#define GATT_UUID_CHAR_GLS_MEASUREMENT            0x2A18
#define GATT_UUID_CHAR_GLS_MEASUREMENT_CTXT       0x2A34
#define GATT_UUID_CHAR_GLS_FEATURES               0x2A51
#define GATT_UUID_CHAR_GLS_RACP                   GATT_UUID_CHAR_RACP

#define GATT_UUID_CGM                             0x181F
#define GATT_UUID_CHAR_CGM_MEASUREMENT            0x2AA7
#define GATT_UUID_CHAR_CGM_FEATURE                0x2AA8
#define GATT_UUID_CHAR_CGM_STATUS                 0x2AA9
#define GATT_UUID_CHAR_CGM_SESSION_START_TIME     0x2AAA
#define GATT_UUID_CHAR_CGM_SESSION_RUN_TIME       0x2AAB
#define GATT_UUID_CHAR_CGM_RACP                   GATT_UUID_CHAR_RACP
#define GATT_UUID_CHAR_CGM_CGMCP                  0x2AAC

#define GATT_UUID_BATTERY                         0x180F
#define GATT_UUID_CHAR_BAS_LEVEL                  0x2A19

#define GATT_UUID_CURRENT_TIME                    0x1805
#define GATT_UUID_CHAR_CTS_CURRENT_TIME           0x2A2B
#define GATT_UUID_CHAR_CTS_LOCAL_TIME_INFO        0x2A0F
#define GATT_UUID_CHAR_CTS_REF_TIME_INFO          0x2A14

#define GATT_UUID_NEXT_DST_CHANGE                 0x1807
#define GATT_UUID_CHAR_NDCS_TIME_WITH_DST         0x2A11

#define GATT_UUID_REFERENCE_TIME_UPDATE           0x1806
#define GATT_UUID_CHAR_RTUS_CONTROL_POINT         0x2A16
#define GATT_UUID_CHAR_RTUS_STATE                 0x2A17

#define GATT_UUID_HEALTH_THERMOMETER              0x1809

#define GATT_UUID_HID                             0x1812
#define GATT_UUID_HID_BOOT_KEYBOARD_INPUT_REPORT  0x2A22
#define GATT_UUID_HID_BOOT_KEYBOARD_OUTPUT_REPORT 0x2A32
#define GATT_UUID_HID_INFORMATION                 0x2A4A
#define GATT_UUID_HID_REPORT_MAP                  0x2A4B
#define GATT_UUID_HID_CONTROl                     0x2A4C
#define GATT_UUID_HID_REPORT                      0x2A4D
#define GATT_UUID_HID_PROTOCOL_MODE               0x2A4E

#define GATT_UUID_HID_REPORT_REFERENCE            0x2908

#define GATT_UUID_CHAR_TEMP_MEASUREMENT           0x2A1C
#define GATT_UUID_CHAR_TEMP_TYPE                  0x2A1D
#define GATT_UUID_CHAR_INTERMEDIATE_TEMP          0x2A1E
#define GATT_UUID_CHAR_MEASUREMENT_INTERVAL       0x2A21
#define GATT_UUID_CHAR_BODY_SENSOR_LOCATION       0x2A38
/** @endcond */

#define GATT_PERM_NONE                  ((uint16_t)      0) /**< Attribute security flags value with no flag set */
/** @cond Doxygen_Ignored */
#define GATT_PERM_ALL                   ((uint16_t) 1 << 0)
#define GATT_PERM_AUTHEN_REQ            ((uint16_t) 2 << 0)
#define GATT_PERM_AUTHEN_MITM_REQ       ((uint16_t) 3 << 0)
#define GATT_PERM_AUTHOR_REQ            ((uint16_t) 1 << 2)
#define GATT_PERM_AUTHEN_GET(x, offset) ((uint8_t) ((x >> offset) & (3 << 0)))
#define GATT_PERM_AUTHOR_GET(x, offset) ((uint8_t) ((x >> offset) & (1 << 2)))
 /** @endcond */
#define GATT_PERM_OFFSET_READ      ((uint8_t)  0) /**< Offset of the "read" attribute security flags */
#define GATT_PERM_OFFSET_WRITE     ((uint8_t)  4) /**< Offset of the "write" attribute security flags */
#define GATT_PERM_OFFSET_NOTIF_IND ((uint8_t)  8) /**< Offset of the "notify/indicate" attribute security flags */
#define GATT_PERM_OFFSET_KEYSIZE   ((uint8_t) 12) /**< Offset of the key size in the attribute security flags */

/** @anchor GATT_attribute_security_flags
 * @name GATT attribute security flags */
/** @{ */
#define GATT_PERM_READ                      ((uint16_t) (GATT_PERM_ALL             << GATT_PERM_OFFSET_READ     )) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_READ_AUTHEN_GET),
                                                                                                                        indicates that attribute read operations are permitted without additional security requirements */
#define GATT_PERM_READ_AUTHEN_REQ           ((uint16_t) (GATT_PERM_AUTHEN_REQ      << GATT_PERM_OFFSET_READ     )) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_READ_AUTHEN_GET),
                                                                                                                        indicates that attribute read operations are permitted when authenticated */
#define GATT_PERM_READ_AUTHEN_MITM_REQ      ((uint16_t) (GATT_PERM_AUTHEN_MITM_REQ << GATT_PERM_OFFSET_READ     )) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_READ_AUTHEN_GET),
                                                                                                                        indicates that attribute read operations are permitted when authenticated with MITM protection */
#define GATT_PERM_READ_AUTHOR_REQ           ((uint16_t) (GATT_PERM_AUTHOR_REQ      << GATT_PERM_OFFSET_READ     )) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_READ_AUTHOR_GET),
                                                                                                                        indicates that attribute read operations are permitted when authorized */
#define GATT_PERM_WRITE                     ((uint16_t) (GATT_PERM_ALL             << GATT_PERM_OFFSET_WRITE    )) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_WRITE_AUTHEN_GET),
                                                                                                                        indicates that attribute write operations are permitted without additional security requirements */
#define GATT_PERM_WRITE_AUTHEN_REQ          ((uint16_t) (GATT_PERM_AUTHEN_REQ      << GATT_PERM_OFFSET_WRITE    )) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_WRITE_AUTHEN_GET),
                                                                                                                        indicates that attribute write operations are permitted when authenticated */
#define GATT_PERM_WRITE_AUTHEN_MITM_REQ     ((uint16_t) (GATT_PERM_AUTHEN_MITM_REQ << GATT_PERM_OFFSET_WRITE    )) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_WRITE_AUTHEN_GET),
                                                                                                                        indicates that attribute write operations are permitted when authenticated with MITM protection */
#define GATT_PERM_WRITE_AUTHOR_REQ          ((uint16_t) (GATT_PERM_AUTHOR_REQ      << GATT_PERM_OFFSET_WRITE    )) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_WRITE_AUTHOR_GET),
                                                                                                                        indicates that attribute write operations are permitted when authorized */
/** @cond Doxygen_Ignored */
#define GATT_PERM_NOTIF_IND                 ((uint16_t) (GATT_PERM_ALL             << GATT_PERM_OFFSET_NOTIF_IND))
/** @endcond */
#define GATT_PERM_NOTIF_IND_AUTHEN_REQ      ((uint16_t) (GATT_PERM_AUTHEN_REQ      << GATT_PERM_OFFSET_NOTIF_IND)) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_NOTIF_IND_AUTHEN_GET),
                                                                                                                        indicates that attribute notifications and indications are only transmitted when authenticated */
#define GATT_PERM_NOTIF_IND_AUTHEN_MITM_REQ ((uint16_t) (GATT_PERM_AUTHEN_MITM_REQ << GATT_PERM_OFFSET_NOTIF_IND)) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_NOTIF_IND_AUTHEN_GET),
                                                                                                                        indicates that attribute notifications and indications are only transmitted when authenticated with MITM protection */
#define GATT_PERM_NOTIF_IND_AUTHOR_REQ      ((uint16_t) (GATT_PERM_AUTHOR_REQ      << GATT_PERM_OFFSET_NOTIF_IND)) /**< If included in the attribute security flags (2 bits, test with #GATT_PERM_NOTIF_IND_AUTHOR_GET),
                                                                                                                        indicates that attribute notifications and indications are only transmitted when authorized */
#define GATT_PERM_KEYSIZE(size)             ((uint16_t) ((size - 1)                << GATT_PERM_OFFSET_KEYSIZE  )) /**< If included in the attribute security flags (4 bits, test with #GATT_PERM_KEYSIZE_GET),
                                                                                                                        indicates that an encryption key size of @p size octets is requested. If not included, a value of 16 is assumed */
/** @} */

#define GATT_PERM_READ_AUTHEN_GET(     x) (GATT_PERM_AUTHEN_GET(x, GATT_PERM_OFFSET_READ     )) /**< Can be used to test which attribute security flag for "read" authentication is included
                                                                                                     (<code>GATT_PERM_READ_AUTHEN_GET(wPermissions) << GATT_PERM_OFFSET_READ == flag)</code>) */
#define GATT_PERM_READ_AUTHOR_GET(     x) (GATT_PERM_AUTHOR_GET(x, GATT_PERM_OFFSET_READ     )) /**< Can be used to test which attribute security flag for "read" authorization is included
                                                                                                     (<code>GATT_PERM_READ_AUTHOR_GET(wPermissions) << GATT_PERM_OFFSET_READ == flag)</code>) */
#define GATT_PERM_WRITE_AUTHEN_GET(    x) (GATT_PERM_AUTHEN_GET(x, GATT_PERM_OFFSET_WRITE    )) /**< Can be used to test which attribute security flag for "write" authentication is included
                                                                                                     (<code>GATT_PERM_WRITE_AUTHEN_GET(wPermissions) << GATT_PERM_OFFSET_READ == flag)</code>) */
#define GATT_PERM_WRITE_AUTHOR_GET(    x) (GATT_PERM_AUTHOR_GET(x, GATT_PERM_OFFSET_WRITE    )) /**< Can be used to test which attribute security flag for "write" authorization is included
                                                                                                     (<code>GATT_PERM_WRITE_AUTHOR_GET(wPermissions) << GATT_PERM_OFFSET_READ == flag)</code>) */
#define GATT_PERM_NOTIF_IND_AUTHEN_GET(x) (GATT_PERM_AUTHEN_GET(x, GATT_PERM_OFFSET_NOTIF_IND)) /**< Can be used to test which attribute security flag for "notify/indicate" authentication is included
                                                                                                     (<code>GATT_PERM_NOTIF_IND_AUTHEN_GET(wPermissions) << GATT_PERM_OFFSET_READ == flag)</code>) */
#define GATT_PERM_NOTIF_IND_AUTHOR_GET(x) (GATT_PERM_AUTHOR_GET(x, GATT_PERM_OFFSET_NOTIF_IND)) /**< Can be used to test which attribute security flag for "notify/indicate" authorization is included
                                                                                                     (<code>GATT_PERM_NOTIF_IND_AUTHOR_GET(wPermissions) << GATT_PERM_OFFSET_READ == flag)</code>) */
#define GATT_PERM_KEYSIZE_GET(x) ((uint8_t) ((((x >> GATT_PERM_OFFSET_KEYSIZE) & 0x0F) == 0) ? 16 : ((x >> GATT_PERM_OFFSET_KEYSIZE) & 0x0F) + 1)) /**< Can be used to check the requested encryption key size
                                                                                                                                                        included in the attribute security flags */

#if (F_BT_GATT_SERVER_MIN)
#define ATTRIB_FLAG_VOID        ((uint16_t)         0) /**< Attribute descriptor flags value with no flag set */

/** @anchor GATT_attribute_descriptor_flags
 * @name GATT attribute descriptor flags */
/** @{ */
#define ATTRIB_FLAG_UUID_128BIT ((uint16_t) (1 <<  0)) /**< If included in the attribute descriptor flags, indicates that a 128-bit attribute UUID is stored in the descriptor.
                                                            Incompatible with #ATTRIB_FLAG_VALUE_INCL */
#define ATTRIB_FLAG_VALUE_INCL  ((uint16_t) (1 <<  1)) /**< If included in the attribute descriptor flags, indicates that the attribute value is stored in the descriptor.
                                                            Incompatible with #ATTRIB_FLAG_UUID_128BIT */
#define ATTRIB_FLAG_VALUE_APPL  ((uint16_t) (1 <<  2)) /**< If included in the attribute descriptor flags, indicates that the attribute value is managed by the application.
                                                            Incompatible with #ATTRIB_FLAG_VALUE_INCL */
#define ATTRIB_FLAG_ASCII_Z     ((uint16_t) (1 <<  3)) /**< If included in the attribute descriptor flags, indicates that the attribute value is a zero-terminated ASCII string */
#define ATTRIB_FLAG_CCCD_APPL   ((uint16_t) (1 <<  4)) /**< If included in the attribute descriptor flags and the attribute defines a Client Characteristic Configuration Descriptor (CCCD),
                                                            the application will receive a [GATTCCCDInfo](@ref TBlueAPI_GATTCCCDInfo) when the connection is established or the value changes.
                                                            Shall be set to 0 if not defining a CCCD */
#define ATTRIB_FLAG_BR_EDR      ((uint16_t) (1 << 10)) /**< If included in the attribute descriptor flags and the attribute defines a primary service, the service will be available over BR/EDR links.
                                                            Shall be set to 0 if not defining a primary service */
#define ATTRIB_FLAG_LE          ((uint16_t) (1 << 11)) /**< If included in the attribute descriptor flags and the attribute defines a primary service, the service will be available over LE links.
                                                            Shall be set to 0 if not defining a primary service */
/** @} */

/** Structure of an array element of an application-defined GATT service structure (attribute descriptor). One such element corresponds to a single attribute definition */
typedef struct _AttribAppl
{
  uint16_t wFlags;          /**< Attribute descriptor flags (bitmask). See [GATT attribute descriptor flags](@ref GATT_attribute_descriptor_flags).
                                 Bits that are not defined in any of the available constants are reserved for future use and shall be set to 0. */
  uint8_t bTypeValue[2+14]; /**< If @p wFlags contains:
                                 <table><tr><td> #ATTRIB_FLAG_UUID_128BIT <td> 128-bit UUID of the attribute (LSB first)
                                        <tr><td> #ATTRIB_FLAG_VALUE_INCL  <td> 16-bit UUID of the attribute (LSB first), followed by @p wValueLen bytes of attribute value (LSB first).
                                                                               If also #ATTRIB_FLAG_ASCII_Z is included, the string value must be zero-terminated
                                        <tr><td> None of the above        <td> At index 0, the 16-bit UUID of the attribute (LSB first), remaining 14 bytes will be ignored</table> */
  uint16_t wValueLen;       /**< If @p wFlags contains:
                                 <table><tr><td> #ATTRIB_FLAG_ASCII_Z     <td> Will be ignored; BlueCode+ will use <code>strlen()</code> to determine the length of the string value
                                        <tr><td> #ATTRIB_FLAG_VALUE_APPL  <td> Will be ignored
                                        <tr><td> None of the above        <td> Length of the attribute value stored in either @p bTypeValue or <code>*pValueContext</code></table> */
  void * pValueContext;     /**< If @p wFlags contains:
                                 <table><tr><td> #ATTRIB_FLAG_VALUE_INCL  <td> Shall be set to NULL
                                        <tr><td> #ATTRIB_FLAG_VALUE_APPL  <td> Context handle that can be used by the application to store additional information
                                        <tr><td> None of the above        <td> Pointer to the value data (LSB) first. If also #ATTRIB_FLAG_ASCII_Z is included, the string value must be zero-terminated.
                                                                               Ownership is shared until termination / reset of BlueCode+.
                                                                               The application shall not modify the value data to prevent synchronization issues</table> */
  uint16_t wPermissions;   /**< Attribute security flags (bitmask). See [GATT attribute security flags](@ref GATT_attribute_security_flags).
                               Bits that are not defined in any of the available constants are reserved for future use and shall be set to 0. */
} TAttribAppl, * PAttribAppl;
#endif /* (F_BT_GATT_SERVER_MIN) */

#ifdef __cplusplus
}
#endif

#endif /* ndef __BLUECODE_GATT_H */
