/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/blueapi_helper.h,v $
 * Revision:    $Revision: 2.1 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_BLUEAPI_HELPER_H
#define __BLUECODE_BLUEAPI_HELPER_H

/** @file
 * Convenience macros, functions and structures, that are not part of BlueAPI, but are helpful when developing BlueAPI applications */

#include "blueapi_types.h" // BlueAPI data types

#ifdef __cplusplus
extern "C" {
#endif

/** Access to the entries of the list structure attached to [GATTAttributeUpdateRsp](@ref TBlueAPI_GATTAttributeUpdateRsp).
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct
{
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of a remote device */
    uint8_t remote_BD_Type;              /**< Bluetooth device address type of @p remote_BD */
} TBlueAPI_GATTAttributeUpdateListElement, * PBlueAPI_GATTAttributeUpdateListElement;

/** Access to a row of the table structure attached to [blueAPI_GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), when @p discoveryType is ::blueAPI_GATTDiscoveryServices
 * and @p elementLength equals the size of this type.
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct TBlueAPI_GATTServicesElement16
{
    uint16_t attHandle;      /**< Start handle of a discovered service */
    uint16_t endGroupHandle; /**< End handle of the service */
    uint16_t UUID16;         /**< 16-bit UUID of the service */
} TBlueAPI_GATTServicesElement16, * PBlueAPI_GATTServicesElement16;

/** Access to a row of the table structure attached to [blueAPI_GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), when @p discoveryType is ::blueAPI_GATTDiscoveryServices
 * and @p elementLength equals the size of this type.
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct TBlueAPI_GATTServicesElement128
{
    uint16_t attHandle;      /**< Start handle of a discovered service */
    uint16_t endGroupHandle; /**< End handle of the service */
    uint8_t UUID128[16];     /**< 128-bit UUID of the service */
} TBlueAPI_GATTServicesElement128, * PBlueAPI_GATTServicesElement128;

/** Access to a row of the table structure attached to [blueAPI_GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), when @p discoveryType is ::blueAPI_GATTDiscoveryServiceByUUID.
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct
{
    uint16_t attHandle;      /**< Start handle of a discovered service */
    uint16_t endGroupHandle; /**< End handle of the service */
} TBlueAPI_GATTServiceByUUIDElement, * PBlueAPI_GATTServiceByUUIDElement;

/** Access to a row of the table structure attached to [blueAPI_GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), when @p discoveryType is ::blueAPI_GATTDiscoveryCharacteristics
 * and @p elementLength equals the size of this type.
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct
{
    uint16_t declHandle;  /**< Handle of a discovered characteristic's declaration */
    uint16_t properties;  /**< Bits 0 to 7: The characteristic's properties, see:
                               @btspec{5.0,3,G,3.3.1.1,Characteristic Properties}
                               Other bits shall be ignored (reserved for future use) */
    uint16_t valueHandle; /**< Handle of the value of the characteristic */
    uint16_t UUID16;      /**< 16-bit UUID of the characteristic */
} TBlueAPI_GATTCharacteristicsElement16, * PBlueAPI_GATTCharacteristicsElement16;

/** Access to a row of the table structure attached to [blueAPI_GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), when @p discoveryType is ::blueAPI_GATTDiscoveryCharacteristics
 * and @p elementLength equals the size of this type.
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct
{
    uint16_t declHandle;  /**< Handle of a discovered characteristic's declaration */
    uint16_t properties;  /**< Bits 0 to 7: The characteristic's properties, see:
                               @btspec{5.0,3,G,3.3.1.1,Characteristic Properties}
                               Other bits shall be ignored (reserved for future use) */
    uint16_t valueHandle; /**< Handle of the value of the characteristic */
    uint8_t UUID128[16];  /**< 128-bit UUID of the characteristic */
} TBlueAPI_GATTCharacteristicsElement128, * PBlueAPI_GATTCharacteristicsElement128;

/** Access to a row of the table structure attached to [blueAPI_GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), when @p discoveryType is ::blueAPI_GATTDiscoveryCharacDescriptors
 * and @p elementLength equals the size of this type.
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct
{
    uint16_t handle; /**< Handle of a discovered characteristic descriptor */
    uint16_t UUID16; /**< 16-bit UUID of the characteristic descriptor */
} TBlueAPI_GATTCharacDescriptorsElement16, * PBlueAPI_GATTCharacDescriptorsElement16;

/** Access to a row of the table structure attached to [blueAPI_GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), when @p discoveryType is ::blueAPI_GATTDiscoveryCharacDescriptors
 * and @p elementLength equals the size of this type.
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct
{
    uint16_t handle;     /**< Handle of a discovered characteristic descriptor */
    uint8_t UUID128[16]; /**< 128-bit UUID of the characteristic descriptor */
} TBlueAPI_GATTCharacDescriptorsElement128, * PBlueAPI_GATTCharacDescriptorsElement128;

/** Access to a row of the table structure attached to [blueAPI_GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), when @p discoveryType is ::blueAPI_GATTDiscoveryRelationship
 * and @p elementLength equals the size of this type.
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct
{
    uint16_t declHandle;     /**< Handle of an include declaration,see:
                                  @btspec{5.0,3,G,3.2,Include Definition} */
    uint16_t attHandle;      /**< Start handle of the included service */
    uint16_t endGroupHandle; /**< End handle of the included service */
    uint16_t UUID16;         /**< 16-bit UUID of the included service */
} TBlueAPI_GATTRelationshipElement16, * PBlueAPI_GATTRelationshipElement16;

/** Access to a row of the table structure attached to [blueAPI_GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), when @p discoveryType is ::blueAPI_GATTDiscoveryRelationship
 * and @p elementLength equals the size of this type.
 * In an environment where the resulting structure is laid out gap-less (packed), each list structure element can be cast to this type to write more concise application code. */
typedef struct
{
    uint16_t declHandle;     /**< Handle of an include declaration,see:
                                  @btspec{5.0,3,G,3.2,Include Definition} */
    uint16_t attHandle;      /**< Start handle of the included service */
    uint16_t endGroupHandle; /**< End handle of the included service */
    uint8_t UUID128[16];     /**< 128-bit UUID of the included service */
} TBlueAPI_GATTRelationshipElement128, * PBlueAPI_GATTRelationshipElement128;

/** Bluetooth device address representation. This is not thread-safe and ownership of the returned buffer is shared, only until the next call to this function.
 * @return a human readable string representation of a Bluetooth device address (zero-terminated). */
const char * blueAPI_StringizeBd(
        const uint8_t * bd /**< [in] Bluetooth device address. Ownership is preserved */);

/** @return a human readable string representation of a BlueAPI operation result code. */
const char * blueAPI_CauseString(
        TBlueAPI_Cause cause /**< [in] Result code */);

/** @return a human readable string representation of a BlueAPI message command identifier. */
const char * blueAPI_CommandString(
        TBlueAPI_Command Command /**< [in] Command identifier */);

/** @return a human readable string representation of a BlueAPI Bluetooth radio mode configuration. */
const char * blueAPI_RadioModeString(
        TBlueAPI_RadioMode RadioMode /**< [in] Radio mode configuration */);

/** @return a human readable string representation of the status of a BlueAPI MCL. */
const char * blueAPI_MCLStatusString(
        TBlueAPI_MCLStatus status /**< [in] MCL status */);

/** @return a human readable string representation of the status of a BlueAPI ACL. */
const char * blueAPI_ACLStatusString(
        TBlueAPI_ACLStatus status /**< [in] ACL status */);

/** @return a human readable string representation of a BlueAPI link profile / QoS configuration. */
const char * blueAPI_LinkConfigString(
        TBlueAPI_LinkConfigType linkConfigType /**< [in] Link configuration */);

/** @return a human readable string representation of a BlueAPI endpoint role. */
const char * blueAPI_LinkRoleString(
        TBlueAPI_MDEPRole linkRole /**< [in] Endpoint role */);

/** @return a human readable string representation of a BlueAPI data segmentation status. */
const char * blueAPI_PacketTypeString(
        TBlueAPI_FrameType frameType /**< [in] Data segmentation status */);

/** @return a human readable string representation of the @p AuthCode parameter of [UserAuthRequestConf](@ref blueAPI_UserAuthRequestConf). */
const char * blueAPI_StringizeAuthCode(
        uint8_t AuthCodeLength,  /**< [in] Length of @p AuthCode */
        uint8_t const * AuthCode /**< [in] @p AuthCode parameter value. Ownership is preserved */);

/** @return a human readable string representation of a BlueAPI internal event identifier. */
const char * blueAPI_InternalEventTypeString(
        TBlueAPI_InternalEventType eventType /**< [in] Internal event identifier */);

/** @return a human readable string representation of a BlueAPI authentication requirement configuration. */
const char * blueAPI_AuthRequirementsString(
        TBlueAPI_AuthRequirements authReq /**< [in] Authentication requirement configuration */);

/** @return a human readable string representation of a BlueAPI configuration of available Input/Output (IO) capabilities for authentication. */
const char * blueAPI_IOCapabilitiesString(
        TBlueAPI_IOCapabilities ioCaps /**< [in] IO capability configuration */);

#ifdef __cplusplus
}
#endif

#endif /* ndef __BLUECODE_BLUEAPI_HELPER_H */
