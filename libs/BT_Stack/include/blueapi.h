/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/blueapi.h,v $
 * Revision:    $Revision: 1.48 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_BLUEAPI_H
#define __BLUECODE_BLUEAPI_H

/** @file
 * BlueAPI downstream interface of BlueCode+ (External function interface). BlueAPI application code that shall trigger BlueAPI operations via function calls should include this header.
 * Note: This interface is not thread-safe. If multi-threaded code accesses this interface, a locking mechanism shall be implemented to prevent concurrent calls. */

#ifndef V_BLUECODE_EXPORTED
#include "flags.h"         // Variant management
#endif
#include "blueapi_types.h" // BlueAPI data types
#include "gatt.h"          // GATT data types

#ifdef __cplusplus
extern "C" {
#endif

// BlueAPI access functions

/** Acquires a memory segment (buffer) allocated by BlueCode+, that can be used to send messages from the client application to the BlueAPI.
 * The BlueAPI implementation will use the buffer to store message parameters. In addition, the client application can add payload data to the buffer.
 * When using the function interface, this is required for messages carrying payload data that will be transmitted over links, such as [DataReq](@ref blueAPI_DataReq).
 * For messages not carrying payload data, the @p pBuffer parameter of the corresponding function may be set to NULL as the buffer can be allocated internally.
 * After acquiring a buffer, the client application should copy its payload data into the buffer, at the position specified by @p dsDataOffset.
 * Note that ownership of the buffer is shared between application and BlueCode+. BlueCode+ will store its own data in the buffer before @p dsDataOffset, so that segment
 * should not be overwritten by the application.
 * If the BlueAPI accepts a data-carrying message with a buffer reference, the applications' shared ownership of the buffer is released and it should discard the reference.
 * The application can also release its shared ownership by calling #blueAPI_BufferRelease.
 * The total amount of concurrently acquired buffers is limited. It is therefore recommended that the application calls #blueAPI_BufferRelease when a data-carrying message was not accepted.
 * Note that for BlueCode+ variants containing a reset feature, the application must release ownership of all buffers acquired via this function during its reset procedure.
 * @retval ::blueAPI_CauseSuccess if the buffer has been acquired successfully.
 * @retval ::blueAPI_CauseInvalidParameter if one of the parameters has been assigned an invalid value and the operation failed.
 * @retval ::blueAPI_CauseResourceError if the operation failed due to lack of available resources. */
TBlueAPI_Cause blueAPI_BufferGet(
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the link that the payload will be sent over, or 0 if the buffer will not be used for link payload */
        uint16_t dsPoolID,            /**< [in] Downstream buffer pool identifier. For payload data that will be sent over an active link, this value shall match the @p dsPoolID parameter of the
                                                [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) received during connection establishment.
                                                For small amounts of data that are not connection-related the value of the @p systemPoolID received via [ActInfo](@ref TBlueAPI_ActInfo) can be used.
                                                An example of this is the [GATTAttributeUpdateReq](@ref blueAPI_GATTAttributeUpdateReq) */
        uint16_t dsTPDUSize,          /**< [in] Length of the message payload that will be copied into the buffer.
                                                Maximum value is the @p dsTPDUSize parameter of the [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) received during connection establishment */
        uint16_t dsDataOffset,        /**< [in] Offset of the message payload in the buffer.
                                                Minimum value is the @p dsDataOffset parameter of the [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) received during connection establishment */
        void ** ppBuffer              /**< [out] Reference to the acquired buffer. If the return value is not ::blueAPI_CauseSuccess, the buffer reference is set to NULL.
                                                 Otherwise, the application now holds shared ownership of this buffer with the constraint that it may only write to octet indices
                                                 in the interval \[@p dsDataOffset, @p dsDataOffset + @p dsTPDUSize - 1]. The total length of the buffer is @p dsDataOffset + @p dsTPDUSize. */);

/** Releases shared ownership of a memory segment (buffer) previously acquired via #blueAPI_BufferGet.
 * Note that "manually" releasing the buffer is only required when the corresponding send operation could not be requested, or the application is performing the BlueCode+ reset procedure.
 * @retval ::blueAPI_CauseSuccess if the buffer has been released from the application successfully.
 * @retval ::blueAPI_CauseInvalidParameter if one of the parameters has been assigned an invalid value and the operation failed. */
TBlueAPI_Cause blueAPI_BufferRelease(
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        void * pBuffer                /**< [in,out] Reference to the buffer as returned from the @p ppBuffer parameter of #blueAPI_BufferGet.
                                                    The application should discard this reference once the release has completed successfully */);

// BlueAPI downstream function interface

#if (F_BLUE_API_GATT_SUPPORT)
/** @bookmark{ConnectGATTMDLReq} */
/** Requests the establishment of GATT connection to a remote GATT server. Instead of specifying a remote device, it can also be selected via the whitelist.
 * If the message is accepted, the application will receive a [ConnectMDLRsp](@ref TBlueAPI_ConnectMDLRsp) message.
 * The number of concurrent ACLs is limited to #BLUE_API_MAX_ACLS, and a new GATT connection consumes 1.
 * The number of concurrent BlueAPI links (independent of type) is limited to #BLUE_API_MAX_LINKS and a successful connection establishment consumes 1.
 * @attention MDEP IDs for Terminal I/O endpoints are no longer valid after GATT disconnection and need to be rediscovered via [SPPDiscoveryReq](@ref blueAPI_SPPDiscoveryReq) after GATT reconnection
 * @attention The attempt to setup concurrent BR/EDR and LE connections to the same peer device will be rejected with the resulting cause ::blueAPI_CauseNotSupported
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ConnectGATTMDLReq(
        void * pBuffer,                       /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,         /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,            /**< [in] Bluetooth device address of the remote device or all zeroes to connect to any device on the whitelist. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_RemoteBDType remote_BD_Type, /**< [in] Bluetooth device address type of @p remote_BD. Ignored if selecting via whitelist */
        uint8_t local_MDEP_ID,                /**< [in] Historical argument, shall be set to 0 */
        uint16_t scanInterval,                /**< [in] LE Scan Interval, in units of 0.625 ms. This value is a recommendation for the frequency of scanning.
                                                        Valid range is \[0x0004, 0x4000] (corresponds to \[2.5 ms, 10.24 s]).
                                                        Ignored for connections to Bluetooth Classic devices */
        uint16_t scanWindow,                  /**< [in] LE Scan Window, in units of 0.625 ms. This value is a recommendation for the duration of a single scan window, repeated at an interval of @p scanInterval.
                                                        Valid range is \[0x0004, @p scanInterval] (corresponds to \[2.5 ms, ...]).
                                                        Ignored for connections to Bluetooth Classic devices */
        uint16_t scanTimeout,                 /**< [in] Timeout after which BlueCode+ shall stop LE scanning if no matching remote device has been found, in units of 10 ms.
                                                        Valid range is \[0x000A, 0xFFFF] (corresponds to \[10 ms, 655 s]).
                                                        Ignored for connections to Bluetooth Classic devices */
        uint16_t connIntervalMin,             /**< [in] LE Minimum Connection Interval, in units of 1.25 ms. Valid range is \[0x0006, 0x0C80] (corresponds to \[7.5 ms, 4 s]).
                                                        Ignored for connections to Bluetooth Classic devices */
        uint16_t connIntervalMax,             /**< [in] LE Maximum Connection Interval, in units of 1.25 ms. Valid range is \[@p connIntervalMin, 0x0C80] (corresponds to \[..., 4 s]).
                                                        Ignored for connections to Bluetooth Classic devices */
        uint16_t connLatency,                 /**< [in] LE Slave Latency, i.e., the amount of connection events the slave may ignore. Valid range is \[0x0000, 0x01F3].
                                                        Ignored for connections to Bluetooth Classic devices */
        uint16_t supervisionTimeout           /**< [in] LE Connection Supervision Timeout, in units of 10 ms. Valid range is \[0x000A, 0x0C80] (corresponds to \[100 ms, 32 s]).
                                                        Ignored for connections to Bluetooth Classic devices */);
#endif /* (F_BLUE_API_GATT_SUPPORT) */

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing documentation here"
bool blueAPI_ConnectHDPMDLReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,
        uint8_t remote_MDEP_ID,
        uint8_t local_MDEP_ID,
        uint16_t remote_Control_PSM,
        uint16_t remote_Data_PSM,
        TBlueAPI_LinkConfigType linkConfigType);
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
/** @bookmark{ConnectSPPMDLReq} */
/** Requests the establishment of a either a new RFCOMM-based profile connection (such as SPP) or a new Terminal I/O connection to a remote endpoint.
 * The remote endpoint must have previously been discovered via an [SPPEndpointInd](@ref TBlueAPI_SPPEndpointInd), during a discovery procedure started via [SPPDiscoveryReq](@ref blueAPI_SPPDiscoveryReq).
 * If the remote endpoint has been discovered as a Terminal I/O endpoint, the serial connection will use the Terminal I/O profile based on a remote GATT service.
 * Therefore, a GATT connection that will be used as transport must have been established before issuing this message (<em>logical connection establishment</em>).
 * A new connection establishment may only be requested when there is no other pending connection setup (independent of the profiles).
 * The number of concurrent RFCOMM channels is limited to #BLUE_API_MAX_RFCOMM_CHANNELS, and a new SPP connection consumes 2 (data and control channel).
 * The number of concurrent outgoing Terminal I/O connections is limited to #BLUE_API_MAX_TIO_OUT.
 * The number of concurrent BlueAPI links (independent of type) is limited to #BLUE_API_MAX_LINKS, and a successful connection establishment consumes 1.
 * If the message is accepted, the application will receive a [ConnectMDLRsp](@ref TBlueAPI_ConnectMDLRsp) message.
 * @attention MDEP IDs for Terminal I/O endpoints are no longer valid after GATT disconnection and need to be rediscovered via [SPPDiscoveryReq](@ref blueAPI_SPPDiscoveryReq) after GATT reconnection
 * @attention The attempt to setup concurrent BR/EDR and LE connections to the same peer device will be rejected with the resulting cause ::blueAPI_CauseNotSupported
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ConnectSPPMDLReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,    /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        uint8_t remote_MDEP_ID,       /**< [in] Endpoint on the remote device, matching the @p remote_MDEP_ID parameter of the corresponding [SPPEndpointInd](@ref TBlueAPI_SPPEndpointInd) */
        uint8_t local_MDEP_ID         /**< [in] Historical argument, shall be set to 0 */);
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_APPLE_IAP)
#error "Missing documentation here"
bool blueAPI_ConnectIAPMDLReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,
        uint8_t remote_MDEP_ID,
        uint8_t local_MDEP_ID);
#endif /* (F_APPLE_IAP) */

#if (F_APPLE_IAP2)
#error "Missing documentation here"
bool blueAPI_ConnectIAP2MDLReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,
        uint8_t remote_MDEP_ID,
        uint8_t local_MDEP_ID);
#endif /* (F_APPLE_IAP2) */

#if (F_BLUE_API_HID_SUPPORT)
/** @bookmark{ConnectHIDMDLReq} */
/** Requests the establishment of an HID connection to a remote HID host.
 * A new connection establishment may only be requested when there is no other pending connection setup (independent of the profiles).
 * Only one HID link may exist at a time. The number of concurrent BlueAPI links (independent of type) is limited to #BLUE_API_MAX_LINKS and a successful connection establishment consumes 1.
 * If the message is accepted, the application will receive a [ConnectMDLRsp](@ref TBlueAPI_ConnectMDLRsp) message.
 * @attention This variant of BlueCode+ is limited to the HID device role functionality. Only connections to HID hosts, not to HID devices can be established
 * @attention The attempt to setup concurrent BR/EDR and LE connections to the same peer device will be rejected with the resulting cause ::blueAPI_CauseNotSupported
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ConnectHIDMDLReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,    /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        uint8_t remote_MDEP_ID,       /**< [in] Historical argument, shall be set to 0 */
        uint8_t local_MDEP_ID         /**< [in] Historical argument, shall be set to 0 */);
#endif /* (F_BLUE_API_HID_SUPPORT) */

#if (F_BLUE_API_L2CAP_SUPPORT)
#error "Missing documentation here"
bool blueAPI_ConnectL2CAPMDLReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,
        uint16_t remote_Data_PSM,
        uint8_t local_MDEP_ID,
        TBlueAPI_LinkConfigType linkConfigType);
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */

#if (F_BLUE_API_RECONNECT_SUPPORT)
/** @bookmark{ReconnectMDLReq} */
/** Requests a HDP reconnection of a formerly created but disconnected link. Only the Device that initially created the link (by use of Connect*MDLReq) can request a reconnect.
 * If the transaction succeeds, the complete configuration and setup that was used for the creation of the link will be reestablished.
 * If the message is accepted, the application will receive a [ReconnectMDLRsp](@ref TBlueAPI_ReconnectMDLRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ReconnectMDLReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the link to be reconnected */
        uint16_t remote_Control_PSM,  /**< [in] Control channel PSM of remote device. If 0, the rem_C_PSM value negotiated during the creation of the link will be used.
                                                Behavior is not HDP compliant: PSMs are defined to be dynamic and can change at any time.
                                                To gather actual PSM values, a new [HDPDiscoveryReq](@ref blueAPI_HDPDiscoveryReq) should be initiated. */
        uint16_t remote_Data_PSM      /**< [in] Data channel PSM of remote device. If 0, the rem_C_PSM value negotiated during the creation of the link will be used.
                                                Behavior is not HDP compliant: PSMs are defined to be dynamic and can change at any time.
                                                To gather actual PSM values, a new [HDPDiscoveryReq](@ref blueAPI_HDPDiscoveryReq) should be initiated. */);

/** @bookmark{ReconnectMDLConf} */
/** Responds to a [ReconnectMDLInd](@ref TBlueAPI_ReconnectMDLInd) by accepting/rejecting the link reconnection.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ReconnectMDLConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the link to be reconnected */
        TBlueAPI_Cause cause          /**< [in] <table><tr><td> ::blueAPI_CauseAccept           <td> Accept the link reconnection
                                                       <tr><td> ::blueAPI_CauseReject           <td> Reject the link reconnection (known link)
                                                       <tr><td> ::blueAPI_CauseInvalidParameter <td> Reject the link reconnection (unknown link)</table> */);
#endif /* (F_BLUE_API_RECONNECT_SUPPORT) */

/** @bookmark{DisconnectMDLReq} */
/** Requests the disconnection of an established link, or the release of a formerly created but then temporarily or unintentionally disconnected link.
 * Note that a Terminal I/O link can not be disconnected directly, the underlying GATT link shall be disconnected instead.
 * If the message is accepted, the application will receive a [DisconnectMDLRsp](@ref TBlueAPI_DisconnectMDLRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DisconnectMDLReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the link to be disconnected */
        TBlueAPI_Cause cause          /**< [in] <table><tr><td> ::blueAPI_CauseConnectionDisconnect <td> The link shall be disconnected permanently (if not idle) and released
                                                       <tr><td> ::blueAPI_CauseConnectionPaused     <td> The link shall be disconnected temporarily, but might be reconnected later.
                                                                                                         Only valid for a HDP-based link</table> */);

/** @bookmark{DisconnectMDLConf} */
/** Responds to a [DisconnectMDLInd](@ref TBlueAPI_DisconnectMDLInd).
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DisconnectMDLConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID         /**< [in] Local MDL ID of the link to be disconnected or terminated */);

/** @bookmark{CreateMDLConf} */
/** Responds to a [CreateMDLInd](@ref TBlueAPI_CreateMDLInd) by accepting/rejecting the link creation. Also defines upstream credits (flow control) and QoS configuration.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_CreateMDLConf(
        void * pBuffer,                         /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,           /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,                  /**< [in] Local MDL ID of the link to be created */
        TBlueAPI_LinkConfigType linkConfigType, /**< [in] Requested QoS configuration for the link */
        uint8_t maxTPDUusCredits,               /**< [in] Upstream credits: Maximum number of [DataInd](@ref TBlueAPI_DataInd) messages not confirmed by [DataConf](@ref blueAPI_DataConf) */
        TBlueAPI_Cause cause                    /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> Accept the link creation
                                                                 <tr><td> ::blueAPI_CauseReject <td> Reject the link creation</table> */);

/** @bookmark{RegisterReq} */
/** Registers a client application ("BlueAPI application") at BlueAPI. This version of BlueCode+ is limited to not more than application being registered at any time.
 * If the message is accepted, the application will receive a [RegisterRsp](@ref TBlueAPI_RegisterRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_RegisterReq(
        void * pBuffer,                        /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIAppHandle appHandle,           /**< [in,out] Application-provided context handle that the BlueAPI will include in message to address this application */
        BlueAPICallback MDHmsgHandlerCallback, /**< [in,out] BlueAPI message callback that BlueCode+ shall use to send messages to the application. NULL if using the queue system instead. */
        uint16_t MDHmsgHandlerQueueID          /**< [in] Queue ID for upstream messages if the queue system is used. The queue system is only available on platforms where a specific
                                                         implementation is documented. */);

/** @bookmark{ReleaseReq} */
/** Releases a client application ("BlueAPI application") from BlueAPI, that was previously registered with a [RegisterReq] (@ref blueAPI_RegisterReq).
 * If the message is accepted, the application will receive a [ReleaseRsp](@ref TBlueAPI_ReleaseRsp) message. After successfully sending a ReleaseReq, the application must discard all shared references,
 * including the BlueAPI handle, and not issue any further messages until the ReleaseRsp is received. After the ReleaseRsp is received, the application may register at BlueAPI again.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ReleaseReq(
        void * pBuffer,              /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle /**< [in,out] BlueAPI context handle */);

/** @bookmark{ReleaseConf} */
/** Responds to a [ReleaseInd](@ref TBlueAPI_ReleaseInd), releasing ownership of all shared resources. After successfully sending a ReleaseConf, the application must discard all shared references, including the BlueAPI handle,
 * and not issue any further messages until a [DeactInfo](@ref TBlueAPI_DeactInfo) is received. After the DeactInfo is received, the application may register at BlueAPI again.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ReleaseConf(
        void * pBuffer,              /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle /**< [in,out] BlueAPI context handle */);

/** @bookmark{DataReq} */
/** Requests the transmission of data to a remote device over a link. This can be a full unsegmented APDU or a start/continue/end segment of a segmented APDU.
 * If the message is accepted, the application will receive a [DataRsp](@ref TBlueAPI_DataRsp) message. BlueCode+ may delay the DataRsp to apply flow control.
 * Until the corresponding DataRsp is received, the operation is considered pending and flow control constraints (downstream credits) for the link apply.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DataReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer containing the payload data. If the message is accepted, application ownership of this buffer is released */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the link that the data shall be sent over */
        TBlueAPI_FrameType frameType, /**< [in] Segmentation status of the message. See #TBlueAPI_FrameType for possible values.
                                                For SPP and Terminal I/O connections, only ::blueAPI_FrameTypeUnsegmented is valid */
        uint16_t frameLength,         /**< [in] If this message contains the start segment of a segmented APDU (@p frameType is blueAPI_FrameTypeFirstSegment), defines the size of the complete APDU.
                                                If not, shall be set to 0 */
        uint16_t payloadLength,       /**< [in] Length of the payload data, in octets. Sum of this value and @p offset must not exceed the total length of the buffer */
        uint16_t offset               /**< [in] Offset of the data in @p pBuffer. Must be at least the value of @p dsDataOffset provided by [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) for the link */);

/** @bookmark{DataConf} */
/** Responds to a [DataInd](@ref TBlueAPI_DataInd), releasing shared ownership of the corresponding buffer.
 * After successfully sending this message, the application should discard the buffer reference. The application may delay this message to apply flow control.
 * Until the application sends this message, the DataInd is considered pending and flow control constraints (upstream credits) for the link apply.
 * Note that DataInds are always confirmed in the order they have been received in.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DataConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the link that the data was received on */
        TBlueAPI_Cause cause          /**< [in] Historical argument, shall always be ::blueAPI_CauseSuccess */);

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing documentation here"
bool blueAPI_RegHDPMDEPReq(
        void * pBuffer,                      /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,        /**< [in,out] BlueAPI context handle */
        uint8_t MDEP_ID,
        TBlueAPI_MDEPDataType MDEP_DataType,
        TBlueAPI_MDEPRole MDEP_Role,
        uint8_t const * MDEP_Description);
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
/** @bookmark{RegSPPMDEPReq} */
/** Requests the registration of a local SPP or Terminal I/O endpoint, or create a custom SDP record entry for a RFCOMM-based profile.
 * Up to #BLUE_API_MAX_LOCAL_SPP_ENDPPOINTS endpoints for SPP and RFCOMM-based profile may be registered.
 * Up to #BLUE_API_MAX_LOCAL_ENDPOINTS local endpoints may be registered, independent of type.
 * A Terminal I/O endpoint can only be registered in this manner if the variant of BlueCode+ includes a built-in Terminal I/O profile.
 * Telit's Terminal I/O is a proprietary GATT-based profile that enables efficient transport of serial data with Bluetooth Low Energy.
 * A successfully registered endpoint will be visible to remote peer devices that can now establish an SPP / Terminal I/O connection, which will then be signaled via a [CreateMDLInd](@ref TBlueAPI_CreateMDLInd).
 * For Terminal I/O, the endpoint will only be accessible by connected GATT clients that implement the Terminal I/O profile. Note that in order to make disconnected peer devices aware of the existence
 * of a Terminal I/O endpoint, the hosting device (the "Terminal I/O server") should include manufacturer-specific data in Low Energy advertisement packets. See the Terminal I/O documentation for more details.
 * Only one Terminal I/O endpoint may be registered.
 * If the message is accepted, the application will receive a [RegSPPMDEPRsp](@ref TBlueAPI_RegSPPMDEPRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_RegSPPMDEPReq(
        void * pBuffer,                      /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,        /**< [in,out] BlueAPI context handle */
        uint8_t MDEP_ID,                     /**< [in] MDEP ID of the requested endpoint.
                                                       To register an SPP endpoint, use an MDEP ID in the range \[1, 31\]. Note that each MDEP ID may only be registered once.
                                                       To register a Terminal I/O endpoint, use the MDEP ID 32. */
        TBlueAPI_MDEPDataType MDEP_DataType, /**< [in] 16-bit UUID of an RFCOMM-based profile or Terminal I/O.
                                                       To register an SPP endpoint, use ::blueAPI_MDEPUUIDSPPSerialPort.
                                                       To register a Terminal I/O endpoint, use ::blueAPI_MDEPUUIDTypeTIO.
                                                       To create a custom SDP record entry, see #TBlueAPI_MDEPDataType for possible values. */
        uint8_t const * MDEP_Description,    /**< [in] User-friendly name of this endpoint. UTF-8 formatted and zero-terminated. The maximum length of this string is #BLUE_API_MDEP_NAME_LENGTH. Ownership is preserved */
        bool RequireAuthenticationIn,        /**< [in] true if authentication shall be required for remote access to this endpoint */
        bool RequireAuthorizationIn,         /**< [in] true if authorization shall be required for remote access to this endpoint */
        bool RequireMITMIn,                  /**< [in] true if MITM protection shall be required for remote access to this endpoint. Only allowed if @p RequireAuthenticationIn is true */
        bool RequireEncryptionIn             /**< [in] true if encryption shall be required for remote access to this endpoint. Only allowed if @p RequireAuthenticationIn is true */);
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_BLUE_API_OBEX_SUPPORT)
#error "Missing documentation here"
bool blueAPI_RegOBEXMDEPReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t MDEP_ID,
        TBlueAPI_MDEPDataType MDEP_DataType,
        uint8_t const * MDEP_Description,
        uint16_t MDEP_OBEXDataMask, /**< see BLUE_API_OBEX_... for valid values */
        bool RequireAuthenticationIn,
        bool RequireAuthorizationIn,
        bool RequireMITMIn,
        bool RequireEncryptionIn);
#endif /* (F_BLUE_API_OBEX_SUPPORT) */

#if (F_BLUE_API_L2CAP_SUPPORT)
#error "Missing documentation here"
bool blueAPI_RegL2CAPMDEPReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t MDEP_PSM,
        uint16_t MDEP_Protocol,
        TBlueAPI_LinkConfigType MDEP_LinkConfigType,
        uint8_t const * MDEP_Description,
        bool RequireAuthorizationIn,
        bool RequireMITMIn);
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */

#if (F_BLUE_API_HID_SUPPORT)
/** @bookmark{RegHIDMDEPReq} */
/** Requests the registration of a local HID endpoint (device role). Only one HID endpoint may be registered.
 * Up to #BLUE_API_MAX_LOCAL_ENDPOINTS local endpoints may be registered, independent of type.
 * A successfully registered endpoint will be visible to remote peer devices that can now establish an HID connection, which will then be signaled via a [CreateMDLInd](@ref TBlueAPI_CreateMDLInd).
 * If the message is accepted, the application will receive a [RegHIDMDEPRsp](@ref TBlueAPI_RegHIDMDEPRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_RegHIDMDEPReq(
        void * pBuffer,                           /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,             /**< [in,out] BlueAPI context handle */
        uint8_t MDEP_ID,                          /**< [in] MDEP ID of the requested endpoint. Valid range is \[0x01, 0xFF\]. Note that each MDEP ID may only be registered once */
        uint8_t const * MDEP_Description,         /**< [in] User-friendly name of this endpoint. UTF-8 formatted and zero-terminated. The maximum length of this string is #BLUE_API_MDEP_NAME_LENGTH. Ownership is preserved */
        uint8_t MDEP_DeviceSubClass,              /**< [in] HID Device Subclass. See:
                                                            @usbhid{1.11,4.2,Subclass} */
        uint8_t MDEP_CountryCode,                 /**< [in] HID Device Country Code. See:
                                                            @usbhid{1.11,6.2.1,HID Descriptor} */
        uint8_t MDEP_ReconnectInitiate,           /**< [in] Boolean value, indicates that the application will initiate a reconnection process when data is available after unintentional disconnection.
                                                            This information will be exposed to remote devices. See:
                                                            @bthid{1.1,5.3.4.6,HIDReconnectInitiate} */
        bool RequireAuthenticationIn,             /**< [in] true if authentication shall be required for remote access to this endpoint */
        bool RequireAuthorizationIn,              /**< [in] true if authorization shall be required for remote access to this endpoint */
        bool RequireMITMIn,                       /**< [in] true if MITM protection shall be required for remote access to this endpoint. Only allowed if @p RequireAuthenticationIn is true */
        bool RequireEncryptionIn,                 /**< [in] true if encryption shall be required for remote access to this endpoint. Only allowed if @p RequireAuthenticationIn is true */
        TBlueAPI_HIDDescriptorID HIDDescriptorID, /**< [in] <table><tr><td> ::blueAPI_HIDDescriptorApplicationDefined <td> An application-defined HID device descriptor is used
                                                                   <tr><td> Any other value                           <td> A built-in HID device descriptor is used.
                                                                                                                           Note that this may not be available in each variant of BlueCode+.
                                                                                                                           The following parameters of this call are ignored</table> */
        uint16_t HIDDescriptorLength,             /**< [in] Length of @p pHIDDescriptor, in octets */
        uint8_t const * pHIDDescriptor            /**< [in] Application-defined Report Descriptor structure. See structure definition in:
                                                            @usbhid{1.11,6.2.2,Report Descriptor}*/);
#endif /* (F_BLUE_API_HID_SUPPORT) */

/** @bookmark{RelMDEPReq} */
/** Requests the release of a BlueAPI endpoint. This will erase a corresponding SDP record, if one exists.
 * Note that endpoints that represent built-in GATT services (such as Terminal I/O and HoGP) can only be registered, but not released.
 * The only available mechanism to undo the registration of such a mechanism is the BlueCode+ reset feature, if included in this variant of BlueCode+.
 * If the message is accepted, the application will receive a [RelMDEPRsp](@ref TBlueAPI_RelMDEPRsp) message. The corresponding MDEP ID can then be re-used to register a new endpoint.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_RelMDEPReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t MDEP_EntryHandle     /**< [in] BlueAPI endpoint entry handle that has been provided by BlueCode+ upon registration of the endpoint */);

/** @bookmark{RadioModeSetReq} */
/** Requests the configuration of controller functionality on the radio level.
 * If the message is accepted, the application will receive a [RadioModeSetRsp](@ref TBlueAPI_RadioModeSetRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_RadioModeSetReq(
        void * pBuffer,                    /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,      /**< [in,out] BlueAPI context handle */
        TBlueAPI_RadioMode localRadioMode, /**< [in] Requested Bluetooth radio mode. See #TBlueAPI_RadioMode for available configurations.
                                                     Default value corresponds to the #TBlueAPI_BRPageScanMode value specified in the configuration file (use macro definition #BPSM).
                                                     @attention The enumeration values of #TBlueAPI_RadioMode and #TBlueAPI_BRPageScanMode do not match! */
        bool limitedDiscoverable           /**< [in] true if the device shall respond to Limited Inquiry Requests */);

/** @bookmark{DeviceConfigDeviceSetReq} */
/** Requests the configuration of general device-specific parameters.
 * If the message is accepted, the application will receive a [DeviceConfigSetRsp](@ref TBlueAPI_DeviceConfigSetRsp) message with opCode ::blueAPI_DeviceConfigDevice.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DeviceConfigDeviceSetReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint32_t classOfDevice,       /**< [in] Class of Device identifier (CoD). The CoD consists of 24 bits. Bits 23 through 13 define service class, bits 12 through 8 define the major device class,
                                                and bits 7 through 2 define the minor device class. Bits 1 and 0 are reserved and must always be set to 0. For more details, see:
                                                @btasgn{baseband,Baseband,The Class of Device/Service Field}
                                                Default value is as specified in the configuration file (use macro definition #BCLASS).
                                                Please note that changing the CoD affects profile-specific requirements and may negatively affect interoperability.
                                                This value should only be changed after considering possible side effects. */
        uint8_t const * deviceName    /**< [in] User-friendly name of the device. UTF-8 formatted and zero-terminated. The maximum length of this string is #BLUE_API_LOCAL_DEVICE_NAME_LENGTH. Ownership is preserved.
                                                Default value is as specified in the configuration file (use macro definition #BNAME) */);

/** @bookmark{DeviceConfigDIDSetReq} */
/** Requests the configuration of DIP (Device ID Profile)-specific parameters.
 * If the message is accepted, the application will receive a [DeviceConfigSetRsp](@ref TBlueAPI_DeviceConfigSetRsp) message with opCode ::blueAPI_DeviceConfigDID.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DeviceConfigDIDSetReq(
        void * pBuffer,                /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,  /**< [in,out] BlueAPI context handle */
        uint16_t vendorID,             /**< [in] Vendor ID of the local device within the ID space defined by @p vendorIDSource. For more details, see:
                                                 @btasgn{company-identifiers,Company Identifiers}
                                                 Default value is as specified in the configuration file (use macro definition #VENDORID) */
        uint8_t vendorIDSource,        /**< [in] <table><tr><td> 0x01 <td> The vendor ID has been assigned by the Bluetooth SIG
                                                        <tr><td> 0x02 <td> The vendor ID has been assigned by the USB Implementer's Forum</table>
                                                 Default value is as specified in the configuration file (use macro definition #IDSOURCE) */
        uint16_t productID,            /**< [in] Vendor-specific Product ID of the local device.
                                                 Default value is as specified in the configuration file (use macro definition #PRODUCTID) */
        uint16_t productVersion        /**< [in] Vendor-specific Product Version of the local device.
                                                 Default value is as specified in the configuration file (use macro definition #PRODUCTVERS) */);

/** @bookmark{DeviceConfigSecuritySetReq} */
/** Requests the configuration of general security-related device-specific parameters.
 * If the message is accepted, the application will receive a [DeviceConfigSetRsp](@ref TBlueAPI_DeviceConfigSetRsp) message with opCode ::blueAPI_DeviceConfigSecurity.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DeviceConfigSecuritySetReq(
        void * pBuffer,                        /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,          /**< [in,out] BlueAPI context handle */
        TBlueAPI_StoreBondModes storeBondMode, /**< [in] Defines the storage method for bonding information. See #TBlueAPI_StoreBondModes for possible values.
                                                         Default value is as specified in the configuration file (use macro definition #BNDS) */
        uint8_t storeBondSize,                 /**< [in] Number of bonding information entries (authentication results) that BlueCode+ shall store. Maximum value is variant-specific.
                                                         Default value is as specified in the configuration file (use macro definition #BNDSIZE) */
        uint32_t leFixedDisplayValue           /**< [in] Fixed display value for SSP on a BLE link, "OR-ed" with #BLUE_API_USE_LE_FIXED_DISPLAY_VALUE, or 0 to specify that a random display value is used.
                                                         Valid range is \[0,999999] ("OR-ed" with the flag), default value is 0 (not fixed) */);

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing documentation here"
bool blueAPI_DeviceConfigHDPSetReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        bool reconnectEnable,
        uint16_t maxRxAPDUSize,
        bool secMITMout,
        bool secAUTHORout,
        bool secMITMin,
        bool secAUTHORin,
        uint8_t const * serviceName);
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
/** @bookmark{DeviceConfigSPPSetReq} */
/** Requests the configuration of SPP security-related device-specific parameters.
 * If the message is accepted, the application will receive a [DeviceConfigSetRsp](@ref TBlueAPI_DeviceConfigSetRsp) message with opCode ::blueAPI_DeviceConfigSPP.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DeviceConfigSPPSetReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        bool secAUTHENout,            /**< [in] If true, authentication shall be required for all outgoing SPP connections.
                                                For peer devices with Bluetooth version > 2.1, all connections are authenticated.
                                                Default value is as specified in the configuration file (use macro definition #SPPAUTHENOUT) */
        bool secENCRout,              /**< [in] If true, encryption shall be required for all outgoing SPP connections. Only allowed when @p secAUTHENout is true.
                                                For peer devices with Bluetooth version > 2.1, all connections are encrypted.
                                                Default value is as specified in the configuration file (use macro definition #SPPENCROUT) */
        bool secMITMout,              /**< [in] If true, MITM protection shall be required for all outgoing SPP connections. Only allowed when @p secAUTHENout is true.
                                                Default value is as specified in the configuration file (use macro definition #SPPMITMOUT) */
        bool secAUTHORout             /**< [in] If true, authorization shall be required for all outgoing SPP connections.
                                                Default value is as specified in the configuration file (use macro definition #SPPAUTHOROUT) */);
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_BLUE_API_L2CAP_SUPPORT)
#error "Missing documentation here"
bool blueAPI_DeviceConfigL2CAPSetReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        bool secMITMout,
        bool secAUTHORout);
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */

/** @bookmark{DeviceConfigPagescanSetReq} */
/** Requests the configuration of Classic Bluetooth Page Scan parameters.
 * If the message is accepted, the application will receive a [DeviceConfigSetRsp](@ref TBlueAPI_DeviceConfigSetRsp) message with opCode ::blueAPI_DeviceConfigPagescan.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DeviceConfigPagescanSetReq(
        void * pBuffer,                     /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,       /**< [in,out] BlueAPI context handle */
        TBlueAPI_BRPageScanType scanType,   /**< [in] Page Scan Type. See #TBlueAPI_BRPageScanType for possible values. Default value is ::blueAPI_BRPageScanTypeStandard */
        TBlueAPI_BRPageScanRepMode repMode, /**< [in] Page Repetition Mode. See #TBlueAPI_BRPageScanRepMode for possible values. Default value is ::blueAPI_BRPageScanRepMode_1_28s_Interval */
        uint16_t repInterval,               /**< [in] Page Repetition Interval, in units of 0.625 ms.
                                                      Valid range is \[0x0012, 0x1000] (corresponds to \[11.25 ms, 2.56 s]), default value is 0x0800 (corresponds to 1.28 s) */
        uint16_t repWindow,                 /**< [in] Page Scan Window, in units of 0.625 ms.
                                                      Valid range is \[0x0011, @p repInterval] (corresponds to \[10.625 ms, ...]), default value is 0x0012 (corresponds to 11.25 ms) */
        uint16_t pageTimeout                /**< [in] Page Timeout, in units of 0.625 ms. Valid range is \[0x0001, 0xFFFF] (corresponds to \[0.625 ms, 40.96 s]), default value is 0x2000 (corresponds to 5.12 s) */);

/** @bookmark{DeviceConfigInquiryScanSetReq} */
/** Requests the configuration of Classic Bluetooth Inquiry Scan parameters.
 * If the message is accepted, the application will receive a [DeviceConfigSetRsp](@ref TBlueAPI_DeviceConfigSetRsp) message with opCode ::blueAPI_DeviceConfigInquiryScan.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DeviceConfigInquiryScanSetReq(
        void * pBuffer,                      /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,        /**< [in,out] BlueAPI context handle */
        TBlueAPI_BRInquiryScanType scanType, /**< [in] Inquiry Scan Type. See #TBlueAPI_BRInquiryScanType for possible values. Default value is ::blueAPI_BRPageInquiryTypeStandard */
        uint16_t scanInterval,               /**< [in] Inquiry Scan Interval, in units of 0.625 ms.
                                                       Valid range is \[0x0012, 0x1000] (corresponds to \[11.25 ms, 2.56 s]), default value is 0x1000 (corresponds to 2.56 s) */
        uint16_t scanWindow                  /**< [in] Inquiry Scan Window, in units of 0.625 ms.
                                                       Valid range is \[0x0011, @p repInterval] (corresponds to \[10.625 ms, ...]), default value is 0x0012 (corresponds to 11.25 ms) */);

/** @bookmark{DeviceConfigLinkpolicySetReq} */
/** Requests the configuration of Classic Bluetooth connection parameters.
 * If the message is accepted, the application will receive a [DeviceConfigSetRsp](@ref TBlueAPI_DeviceConfigSetRsp) message with opCode ::blueAPI_DeviceConfigLinkpolicy.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DeviceConfigLinkpolicySetReq(
        void * pBuffer,                   /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,     /**< [in,out] BlueAPI context handle */
        TBlueAPI_BRLinkPolicy linkPolicy, /**< [in] Link policy for role switch and sniff mode. See #TBlueAPI_BRLinkPolicy for possible values.
                                                    Default value is as specified in the configuration file (use macro definition #BLINKP) */
        TBlueAPI_BRDeviceRole deviceRole, /**< [in] Desired device role for new connections. See #TBlueAPI_BRDeviceRole for possible values.
                                                    Default value is as specified in the configuration file (use macro definition #BROLE) */
        uint16_t supervisionTimeout       /**< [in] Supervision Timeout, in units of 0.625 ms.
                                                    Valid range is \[0x0001, 0xFFFF] (corresponds to \[0.625 ms, 40.96 s]).
                                                    Default value is as specified in the configuration file (use macro definition #BSUPTIM) */);

#if (BTEXT_RF_MAX_TX_PWR)
/** @bookmark{DeviceConfigMaxTxPowerSetReq} */
/** Requests the configuration of the maximum TX power of the Bluetooth controller.
 * The implementation is controller-specific and may not available for each controller model and in each variant of BlueCode+.
 * If the message is accepted, the application will receive a [DeviceConfigSetRsp](@ref TBlueAPI_DeviceConfigSetRsp) message with opCode ::blueAPI_DeviceConfigMaxTxPower.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DeviceConfigMaxTxPowerSetReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        int16_t txPower               /**< [in] Maximum TX power. The valid range and interpretation depends on the Bluetooth controller model.
                                                Default value is as specified in the configuration file (use macro definition #RFMAXTXPWR) */);
#endif /* (BTEXT_RF_MAX_TX_PWR) */

/** @bookmark{InquiryReq} */
/** Requests the start or cancellation of an inquiry procedure,
 * During an active inquiry procedure, BlueCode+ will indicate the discovery of remote devices via [InquiryDeviceInfo](@ref TBlueAPI_InquiryDeviceInfo).
 * If the message is accepted, the application will receive an [InquiryRsp](@ref TBlueAPI_InquiryRsp) message after the completion of the inquiry procedure.
 * No other operations shall be requested by the application during an active inquiry procedure, i.e., until InquiryRsp is received.
 * Note that negotiated QoS requirements for existing channels must be suspended for the duration of the inquiry process.
 * As a consequence, such channels might be disconnected by the remote device or the local Bluetooth implementation.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_InquiryReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        bool limitedInquiry,          /**< [in] <table><tr><td> true  <td> Remote devices operating in Limited Discoverable Mode will be indicated
                                                       <tr><td> false <td> Remote devices operating in Limited or General Discoverable Mode will be indicated</table> */
        bool cancelInquiry            /**< [in] <table><tr><td> true  <td> This message requests the cancellation of an active inquiry procedure and @p limitedInquiry is ignored
                                                       <tr><td> false <td> This message requests the start of a new inquiry procedure</table> */);

/** @bookmark{DeviceNameReq} */
/** Requests the user-friendly name of a remote device.
 * If the message is accepted, the application will receive a [DeviceNameRsp](@ref TBlueAPI_DeviceNameRsp).
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DeviceNameReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD     /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */);

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing documentation here"
bool blueAPI_HDPDiscoveryReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,
        TBlueAPI_MDEPRole remote_MDEP_Role,
        TBlueAPI_MDEPDataType remote_MDEP_DataType);
#endif /* (F_BLUE_API_HDP_SUPPORT) */

/** @bookmark{DIDDeviceConf} */
/** Responds to a [DIDDeviceInd](@ref TBlueAPI_DIDDeviceInd).
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_DIDDeviceConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint32_t serviceHandle,       /**< [in] Service handle provided in the corresponding [DIDDeviceInd](@ref TBlueAPI_DIDDeviceInd) */
        TBlueAPI_Cause cause          /**< [in] Historical argument, shall always be ::blueAPI_CauseSuccess */);

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing documentation here"
bool blueAPI_HDPServiceConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint32_t serviceHandle,
        TBlueAPI_Cause cause);

bool blueAPI_HDPEndpointConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint32_t serviceHandle,
        TBlueAPI_Cause cause);
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
/** @bookmark{SPPDiscoveryReq} */
/** Requests the start of an endpoint discovery procedure for SPP endpoints, Terminal I/O endpoints or custom RFCOMM-based profile endpoints on a specific remote device.
 * Unless a Terminal I/O discovery is requested, if the remote device supports SPP/RFCOMM, all SPP/RFCOMM and data-endpoint relevant information of the device will be indicated
 * with one or multiple [SPPEndpointInd](@ref TBlueAPI_SPPEndpointInd) messages.
 * If a Terminal I/O discovery is requested and Terminal I/O is a built-in profile in this variant of BlueCode+, all Terminal I/O and data-endpoint relevant information of the device will be indicated
 * with one or multiple SPPEndpointInd messages.
 * To perform a Terminal I/O discovery, the remote device must be GATT-connected.
 * If the message is accepted, the application will receive a [SPPDiscoveryRsp](@ref TBlueAPI_SPPDiscoveryRsp) message after the completion of the endpoint discovery procedure.
 * Note that negotiated QoS requirements for existing channels must be suspended for the duration of the inquiry process.
 * As a consequence, such channels might be disconnected by the remote device or the local Bluetooth implementation.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_SPPDiscoveryReq(
        void * pBuffer,                             /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,               /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,                  /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_MDEPDataType remote_MDEP_DataType, /**< [in] 16-bit UUID of an RFCOMM-based profile or Terminal I/O to discover endpoints for.
                                                              To discover SPP endpoints, use ::blueAPI_MDEPUUIDSPPSerialPort.
                                                              To discover Terminal I/O endpoints, use ::blueAPI_MDEPUUIDTypeTIO.
                                                              To discover custom SDP record entries, see #TBlueAPI_MDEPDataType for possible values. */
        bool remote_DID_Discovery                   /**< [in] If true, a DID Service discovery will be initiated, prior to the SPP/custom service discovery. For Terminal I/O discovery, ignored */);

/** @bookmark{SPPEndpointConf} */
/** Responds to an [SPPEndpointInd](@ref TBlueAPI_SPPEndpointInd).
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_SPPEndpointConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint32_t serviceHandle,       /**< [in] Service handle provided in the corresponding [SPPEndpointInd](@ref TBlueAPI_SPPEndpointInd) */
        TBlueAPI_Cause cause          /**< [in] Historical argument, shall always be ::blueAPI_CauseSuccess */);
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_BLUE_API_OBEX_SUPPORT)
#error "Missing documentation here"
bool blueAPI_OBEXDiscoveryReq(
        void * pBuffer,                              /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,                /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,
        TBlueAPI_MDEPDataType  remote_MDEP_DataType);

bool blueAPI_OBEXEndpointConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint32_t serviceHandle,
        TBlueAPI_Cause cause);
#endif /* (F_BLUE_API_OBEX_SUPPORT) */

#if (F_BLUE_API_GATT_SUPPORT)
#if (F_BT_GATT_SERVER)
/** @bookmark{GATTServiceRegisterReq} */
/** Requests the registration of one or more GATT-based services. A GATT service structure may either be defined by the application via the parameters of this message,
 * or be included with this variant of BlueCode+ ("built-in service"). A built-in service does not need to be constructed by the application and is only "activated" by this message.
 * BlueCode+ will delegate the operation of an application-defined service to the registering application via GATT-related BlueAPI messages. For built-in services, BlueCode+ may handle
 * the service operation internally and encapsulate the actual GATT state. For more details, see the documentation of the corresponding built-in service.
 * The GAP and GATT primary services are built-in and automatically registered/activated and not affected by this operation.
 * The application can perform a maximum of #BLUE_API_MAX_GATT_SRV_REGS service registrations until BlueCode+ is terminated / resetted. Note that a single service registration may contain multiple services,
 * which raises the effective limit on registered GATT services.
 * If the message is accepted, the application will receive a [GATTServiceRegisterRsp](@ref TBlueAPI_GATTServiceRegisterRsp) message.
 * @attention The attribute handles are assigned by BlueCode+ internally and not exposed to the application. For application-defined services, following messages will reference attributes via their indices
 * in @p pService.
 * @attention If the application submits more than one request, the internally assigned attribute handle ranges (exposed to peer devices) depend on the order of the calls.
 * It is therefore recommended to always register the services in the same order.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTServiceRegisterReq(
        void * pBuffer,                   /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,     /**< [in,out] BlueAPI context handle */
        TBlueAPI_GATTServiceID serviceID, /**< [in] <table><tr><td> ::blueAPI_ServiceApplicationDefined                <td> An application-defined GATT service is registered
                                                           <tr><td> Any other value defined in #TBlueAPI_GATTServiceID <td> The corresponding built-in service is activated.
                                                                                                                            Note that not all service may be available in each variant of BlueCode+.
                                                                                                                            The following parameters of this call are ignored</table> */
        uint16_t nbrOfAttrib,             /**< [in] Length of @p pService (number of GATT attributes in the application-defined service structure) */
        TAttribAppl * pService,           /**< [in] If @p serviceID is ::blueAPI_ServiceApplicationDefined, array of attribute descriptors. See #TAttribAppl for the inner structure of array elements.
                                                    The attribute descriptors shall form one or multiple valid GATT services as defined in:
                                                    @btspec{5.0,3,F,Attribute Protocol (ATT)}
                                                    and
                                                    @btspec{5.0,3,G,Generic Attribute Profile (GATT)}
                                                    Ownership is shared until termination / reset of BlueCode+.The application shall not modify the array to prevent synchronization issues */
        uint8_t serviceChanged            /**< [in] If true, indicates that the overall service structure changed permanently (i.e., this is not simply a re-initialization after device reset).
                                                    When a connection to a bonded device is established, it will receive an indication of the Service Changed characteristic.
                                                    When the service structure changed, only one request of this type shall set this parameter to true. Otherwise, bonded devices may be forced
                                                    to perform unnecessary discovery operations, which defeats an essential purpose of the bonding mechanism.
                                                    See also: @btspec{5.0,3,G,7.1,Service Changed} */);

#ifdef V_BLUECODE_MAYBE_OBSOLETE
#error "Missing documentation here"
bool blueAPI_GATTServiceReleaseReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        void * serviceHandle);
#endif

/** @bookmark{GATTAttributeUpdateReq} */
/** Requests an update of a local GATT attribute.
 * If an active connection to a GATT client exists and the Client Characteristic Configuration is set accordingly, a notification or indication will be generated.
 * See also: @btspec{5.0,3,G,3.3.3.3,Client Characteristic Configuration}
 * If no such connection exists, this will be reflected in the response @p cause and @p subCause parameters. An application might, for example, interpret this as a trigger to start advertising.
 * Once a client has established a connection, the application should repeat the update request to generate the notification/indication.
 * For attributes that are notified on ATT layer (with ATT Handle Value Notification), there is a limit to the maximum amount of pending update requests, which is specified by the @p maxTPDUdsCredits
 * parameter of the [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) for the GATT link.
 * If the message is accepted, the application will receive a [GATTAttributeUpdateRsp](@ref TBlueAPI_GATTAttributeUpdateRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTAttributeUpdateReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer containing the value data. If the message is accepted, application ownership of this buffer is released */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        void * serviceHandle,         /**< [in] Handle of the GATT service containing the attribute */
        void * requestHandle,         /**< [in] Application-defined request handle that can be used to track progress of specific update requests */
        uint16_t attribIndex,         /**< [in] Index of the attribute in the service descriptor array */
        uint16_t attribLength,        /**< [in] Length of new attribute value. For attributes with Flags bit VALUE_APPL=0, ignored */
        uint16_t offset               /**< [in] Offset of the value data in @p pBuffer.
                                                Must be at least the value of @p dsDataOffset provided by [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) for the GATT link */);

/** @bookmark{GATTAttributeUpdateStatusConf} */
/** Responds to a [GATTAttributeUpdateStatusInd](@ref TBlueAPI_GATTAttributeUpdateStatusInd).
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTAttributeUpdateStatusConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        void * serviceHandle,         /**< [in] Handle of the GATT service containing the attribute */
        void * requestHandle,         /**< [in] Request handle matching @p requestHandle in the corresponding [GATTAttributeUpdateStatusInd](@ref TBlueAPI_GATTAttributeUpdateStatusInd) */
        uint16_t attribIndex          /**< [in] Index of the attribute in the service descriptor array */);

/** @bookmark{GATTAttributeReadConf} */
/** Responds to a [GATTAttributeReadInd](@ref TBlueAPI_GATTAttributeReadInd) by providing an attribute value.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTAttributeReadConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer containing the value data. If the message is accepted, application ownership of this buffer is released */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the GATT link */
        void * serviceHandle,         /**< [in] Handle of the GATT service containing the attribute */
        TBlueAPI_Cause cause,         /**< [in] <table><tr><td> ::blueAPI_CauseSuccess         <td> The read operation completed successfully
                                                       <tr><td> ::blueAPI_CauseLowerLayerError <td> The read operation failed and an ATT protocol layer error code will be generated</table> */
        uint16_t subCause,            /**< [in] If @p cause is #blueAPI_CauseSuccess, ignored.
                                                If the value's MSB is ATT_ERR and LSB is <= ATT_ERR_INSUFFICIENT_RESOURCES or >= ATT_ERR_MIN_APPLIC_CODE, the value is forwarded as an ATT error code.
                                                Otherwise, the ATT error code ATT_ERR_UNLIKELY is generated. */
        uint16_t attribIndex,         /**< [in] Index of the attribute in the service descriptor array */
        uint16_t attribLength,        /**< [in] Length of new attribute value */
        uint16_t offset               /**< [in] Offset of the value data in @p pBuffer.
                                                Must be at least the value of @p dsDataOffset provided by [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) for the GATT link */);


/** @bookmark{GATTAttributeWriteConf} */
/** Responds to a [GATTAttributeWriteInd](@ref TBlueAPI_GATTAttributeWriteInd), indicating success or failure of the operation.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTAttributeWriteConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the GATT link */
        void * serviceHandle,         /**< [in] Handle of the GATT service containing the attribute */
        TBlueAPI_Cause cause,         /**< [in] <table><tr><td> ::blueAPI_CauseSuccess         <td> The write operation completed successfully
                                                       <tr><td> ::blueAPI_CauseLowerLayerError <td> The write operation failed and an ATT protocol layer error code will be generated</table> */
        uint16_t subCause,            /**< [in] If @p cause is #blueAPI_CauseSuccess, ignored.
                                                If the value's MSB is ATT_ERR and LSB is <= ATT_ERR_INSUFFICIENT_RESOURCES or >= ATT_ERR_MIN_APPLIC_CODE, the value is forwarded as an ATT error code.
                                                Otherwise, the ATT error code ATT_ERR_UNLIKELY is generated. */
        uint16_t attribIndex          /**< [in] Index of the attribute in the service descriptor array */);

#if (F_BT_ATT_PREP_EXEC_WRITE)
#error "Missing documentation here"
bool blueAPI_GATTAttributePrepareWriteConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,
        void * serviceHandle,
        TBlueAPI_Cause cause,
        uint16_t subCause,
        uint16_t attribIndex,
        uint16_t attribLength,
        uint16_t offset);

bool blueAPI_GATTExecuteWriteConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,
        TBlueAPI_Cause cause,
        uint16_t subCause);
#endif

/** @bookmark{GATTServerStoreConf} */
/** Responds to a [GATTServerStoreInd](@ref TBlueAPI_GATTServerStoreInd), indicating success or failure of the operation.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTServerStoreConf(
        void * pBuffer,                       /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,         /**< [in,out] BlueAPI context handle */
        TBlueAPI_GATTStoreOpCode opCode,      /**< [in] @p opCode parameter of the corresponding [GATTServerStoreInd](@ref TBlueAPI_GATTServerStoreInd) */
        uint8_t const * remote_BD,            /**< [in] Bluetooth device address of the peer device that persistent GATT information has been accessed for */
        TBlueAPI_RemoteBDType remote_BD_Type, /**< [in] Bluetooth device address type of @p remote_BD */
        uint16_t restartHandle,               /**< [in] If @p opCode is ::blueAPI_GATTStoreOpGetAllCCCBits and there is information for more peers available, assign a custom value that is not 0
                                                        to memorize the state of the partial operation (e.g., an array index). Otherwise, shall be set to 0 */
        uint8_t dataLength,                   /**< [in] If @p opCode indicates read access, length of @p data. Otherwise, shall be set to 0 */
        uint8_t const * data,                 /**< [in] If @p opCode indicates read access, the requested data. Ownership is preserved. Otherwise, ignored */
        TBlueAPI_Cause cause                  /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> Data has been read/stored/deleted
                                                               <tr><td> ::blueAPI_CauseReject <td> If @p opCode indicates read access, indicates that no data is available.
                                                                                                   If @p opCode indicates write access, indicates that the data could not be written</table> */);
#endif /* (F_BT_GATT_SERVER) */

#if (F_BT_GATT_CLIENT)
/** @bookmark{GATTDiscoveryReq} */
/** Requests the discovery of GATT structures on a connected GATT server. This implements all GATT sub-procedures listed in the documentation of #TBlueAPI_GATTDiscoveryType.
 * If the message is accepted, the application will receive a [GATTDiscoveryRsp](@ref TBlueAPI_GATTDiscoveryRsp) message.
 * If the discovery procedure has been started successfully, the application will receive one or multiple [GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd) messages describing the discovered GATT elements.
 * The application can control the discovery operation by changing the searched range, or terminating the discovery operation, after each returned result.
 * @attention The functionality of the GATT sub-procedure "Discover Characteristic by UUID" is not implemented here and is instead provided through [GATTAttributeReadReq](@ref blueAPI_GATTAttributeReadReq),
 * when the @p readType parameter is set to ::blueAPI_GATTReadTypeByUUID.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTDiscoveryReq(
        void * pBuffer,                           /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,             /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,                    /**< [in] Local MDL ID of the GATT link */
        TBlueAPI_GATTDiscoveryType discoveryType, /**< [in] Type of GATT discovery operation. See #TBlueAPI_GATTDiscoveryType for possible values */
        uint16_t startHandle,                     /**< [in] Start handle of the range to be searched */
        uint16_t endHandle,                       /**< [in] End handle of the range to be searched. Valid range is \[@p startHandle + 1, 0xFFFF] */
        uint16_t UUID16,                          /**< [in] If @p discoveryType is ::blueAPI_GATTDiscoveryServiceByUUID and this value is not 0, 16-bit UUID of the service to discover. Otherwise, ignored */
        uint8_t const * pUUID128                  /**< [in] If @p discoveryType is ::blueAPI_GATTDiscoveryServiceByUUID and @p UUID16 is 0, 128-bit UUID of the service to discover. Otherwise, ignored */);

/** @bookmark{GATTDiscoveryConf} */
/** Responds to a [GATTDiscoveryInd](@ref TBlueAPI_GATTDiscoveryInd), requesting continuation or termination of the discovery procedure.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTDiscoveryConf(
        void * pBuffer,                           /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,             /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,                    /**< [in] Local MDL ID of the GATT link */
        TBlueAPI_GATTDiscoveryType discoveryType, /**< [in] @p discoveryType of the corresponding GATTDiscoveryInd */
        uint16_t startHandle,                     /**< [in] If not 0, start handle of the range where the discovery should continue. If set to 0 and @p endHandle is not 0, the discovery continues after the
                                                            largest handle value received for a discovered element in the corresponding GATTDiscoveryInd */
        uint16_t endHandle                        /**< [in] End handle of the range where the discovery should continue. Valid range is \[@p startHandle, 0xFFFF].
                                                            If both @p startHandle and @p endHandle are set to 0, the discovery operation is terminated */);

/** @bookmark{GATTAttributeReadReq} */
/** Requests the reading of a GATT attribute value on a connected GATT server. This implements all GATT sub-procedures listed in the documentation of #TBlueAPI_GATTReadType.
 * If the message is accepted, the application will receive a [GATTAttributeReadRsp](@ref TBlueAPI_GATTAttributeReadRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTAttributeReadReq(
        void * pBuffer,                 /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,   /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,          /**< [in] Local MDL ID of the GATT link */
        TBlueAPI_GATTReadType readType, /**< [in] Type of GATT read operation. See #TBlueAPI_GATTReadType for possible values */
        uint16_t readOffset,            /**< [in] If @p readType is ::blueAPI_GATTReadTypeBasic and this value is not 0, the first @p readOffset octets of the attribute value are skipped.
                                                  This results in a "Read Blob Request" operation on the ATT layer, instead of a "Read Request". Otherwise, ignored */
        uint16_t startHandle,           /**< [in] If @p readType is:
                                                  <table><tr><td> ::blueAPI_GATTReadTypeBasic  <td> Handle of the attribute to be read
                                                         <tr><td> ::blueAPI_GATTReadTypeByUUID <td> Start handle of the range to search the attribute in</table> */
        uint16_t endHandle,             /**< [in] If @p readType is ::blueAPI_GATTReadTypeByUUID, end handle of the range to search the attribute in. Otherwise, ignored */
        uint16_t UUID16,                /**< [in] If @p readType is ::blueAPI_GATTReadTypeByUUID and this value is not 0, 16-bit UUID of the attribute to read. Otherwise, ignored */
        uint8_t const * pUUID128        /**< [in] If @p readType is ::blueAPI_GATTReadTypeByUUID and @p UUID16 is 0, 128-bit UUID of the attribute to read. Otherwise, ignored */);

/** @bookmark{GATTAttributeWriteReq} */
/** Requests the writing of a GATT attribute value on a connected GATT server. This implements all GATT sub-procedures listed in the documentation of #TBlueAPI_GATTWriteType.
 * If the message is accepted, the application will receive a [GATTAttributeWriteRsp](@ref TBlueAPI_GATTAttributeWriteRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTAttributeWriteReq(
        void * pBuffer,                   /**< [in,out] BlueAPI-provided buffer containing the value data. If the message is accepted, application ownership of this buffer is released */
        TBlueAPIHandle blueAPIHandle,     /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,            /**< [in] Local MDL ID of the GATT link */
        TBlueAPI_GATTWriteType writeType, /**< [in] Type of GATT write operation. See #TBlueAPI_GATTWriteType for possible values */
        uint16_t attribHandle,            /**< [in] Handle of the attribute to write to */
        uint16_t attribLength,            /**< [in] Length of the value data in @p pBuffer to write */
        uint16_t writeOffset,             /**< [in] Shall be set to 0 (reserved for future use) */
        uint16_t offset                   /**< [in] Offset of the value data in @p pBuffer.
                                                    Must be at least the value of @p dsDataOffset provided by [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) for the GATT link */);

#if (F_BT_ATT_PREP_EXEC_WRITE)
#error "Missing documentation here"
bool blueAPI_GATTExecuteWriteReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the GATT link */
        uint8_t flags);
#endif /* (F_BT_ATT_PREP_EXEC_WRITE) */

/** @bookmark{GATTAttributeConf} */
/** Responds to a [GATTAttributeInd](@ref TBlueAPI_GATTAttributeInd).
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTAttributeConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID         /**< [in] Local MDL ID of the GATT link */);

#if (F_BLUE_API_GATT_SDP_DIS_SUPPORT)
#error "Missing documentation here"
bool blueAPI_GATTSDPDiscoveryReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,
        uint16_t remote_GATT_UUID,
        bool remote_DID_Discovery);

bool blueAPI_GATTSDPDiscoveryConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint32_t serviceHandle,
        TBlueAPI_Cause cause);
#endif /* (F_BLUE_API_GATT_SDP_DIS_SUPPORT) */
#endif /* (F_BT_GATT_CLIENT) */

/** @bookmark{GATTSecurityReq} */
/** Requests the initiation of authentication on a GATT link.
 * If the message is accepted, the application will receive a [GATTSecurityRsp](@ref TBlueAPI_GATTSecurityRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_GATTSecurityReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the GATT link */
        uint16_t requirements,        /**< [in] Bitmask of security requirements, see #TBlueAPI_GATTSecurityRequirement for possible values */
        uint8_t minKeySize            /**< [in] Minimum required key size (Bluetooth Low Energy). Ignored for Bluetooth Classic links */);
#endif /* (F_BLUE_API_GATT_SUPPORT) */

/** @bookmark{PairableModeSetReq} */
/** Requests the configuration of security requirements for pairing.
 * If the message is accepted, the application will receive a [PairableModeSetRsp](@ref TBlueAPI_PairableModeSetRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_PairableModeSetReq(
        void * pBuffer,                             /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,               /**< [in,out] BlueAPI context handle */
        bool enablePairableMode,                    /**< [in] <table><tr><td> true  <td> The device shall be in pairable mode
                                                                     <tr><td> false <td> The device shall not be in pairable mode and reject incoming pairing requests. The following parameters are ignored</table>
                                                              Default value is as specified in the configuration file (use macro definition #BPAIRABLE) */
        TBlueAPI_BluetoothMode BluetoothMode,       /**< [in] Bluetooth pairing functionality that the device will utilize. See #TBlueAPI_BluetoothMode for possible values */
        TBlueAPI_AuthRequirements AuthRequirements, /**< [in] Authentication requirements for future pairing procedures. See #TBlueAPI_AuthRequirements for possible values.
                                                              Default value is as specified in the configuration file (use macro definition #BAUTHREQMTS) */
        TBlueAPI_IOCapabilities IOCapabilities,     /**< [in] Input/Output capabilities that can be used for authentication. See #TBlueAPI_IOCapabilities for possible values.
                                                              Default value is as specified in the configuration file (use macro definition #BIOCAP) */
        bool remoteOOBDataPresent                   /**< [in] If true, out-of-band (OOB) data is available and can be used for authentication */);

/** @bookmark{AuthReq} */
/** Requests the initiation of a Dedicated (Re-)Authentication procedure with a remote device.
 * If the message is accepted, the application will receive an [AuthRsp](@ref TBlueAPI_AuthRsp) message after the authentication procedure has completed.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_AuthReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD     /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */);

/** @bookmark{UserAuthorizationReqConf} */
/** Responds to a [UserAuthorizationReqInd](@ref TBlueAPI_UserAuthorizationReqInd) by accepting/rejecting the connection attempt on behalf of the user.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_UserAuthorizationReqConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,    /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_Cause cause          /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> The user accepts and authorizes the connection attempt
                                                       <tr><td> ::blueAPI_CauseReject <td> The user rejects the connection attempt</table> */);

/** @bookmark{UserAuthRequestConf} */
/** Responds to a [UserAuthRequestInd](@ref TBlueAPI_UserAuthRequestInd) by accepting/rejecting the authentication attempt on behalf of the user.
 * Also provides all additional information required to perform the user-level authentication.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_UserAuthRequestConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,    /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        uint8_t AuthCodeLength,       /**< [in] Length of @p AuthCode in octets */
        uint8_t const * AuthCode,     /**< [in] Binary authentication code provided by user interaction. Length must be smaller than or equal to #BLUEAPI_MAX_AUTHCODE_LENGTH. Ownership is preserved */
        TBlueAPI_Cause cause          /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> The user accepts the authentication attempt
                                                       <tr><td> ::blueAPI_CauseReject <td> The user rejects the authentication attempt. @p AuthCode and @p AuthCodeLength are ignored</table> */);

/** @bookmark{UserConfirmationReqConf} */
/** Responds to a [UserConfirmationReqInd](@ref TBlueAPI_UserConfirmationReqInd) by accepting/rejecting the authentication attempt on behalf of the user.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_UserConfirmationReqConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,    /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_Cause cause          /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> The user accepts the authentication attempt
                                                       <tr><td> ::blueAPI_CauseReject <td> The user rejects the authentication attempt</table> */);

/** @bookmark{UserPasskeyReqConf} */
/** Responds to a [UserPasskeyReqInd](@ref TBlueAPI_UserPasskeyReqInd) when user interaction is performed.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_UserPasskeyReqConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,    /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_Cause cause          /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> The user accepts the authentication attempt
                                                       <tr><td> ::blueAPI_CauseReject <td> The user rejects the authentication attempt</table> */);

/** @bookmark{UserPasskeyReqReplyReq} */
/** Requests the completion of an SSP procedure that required local keyboard and remote display functionality.
 * The application shall send this message after user input has been completed.
 * If the message is accepted, the application will receive a [UserPasskeyReqReplyRsp](@ref TBlueAPI_UserPasskeyReqReplyRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_UserPasskeyReqReplyReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,    /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        uint32_t passKey,             /**< [in] Result of user passkey input */
        TBlueAPI_Cause cause          /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> The user accepts the authentication attempt
                                                       <tr><td> ::blueAPI_CauseReject <td> The user rejects the authentication attempt. @p passKey is ignored</table> */);

/** @bookmark{KeypressNotificationReq} */
/** Indicates user interaction during SSP procedures that require local keyboard and remote display functionality.
 * If the message is accepted, the application will receive a [KeypressNotificationRsp](@ref TBlueAPI_KeypressNotificationRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_KeypressNotificationReq(
        void * pBuffer,                /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,  /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,     /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_SSPKeyEvent eventType /**< [in] Type of user interaction. See #TBlueAPI_SSPKeyEvent for possible values */);

/** @bookmark{RemoteOOBDataReqConf} */
/** Responds to a [RemoteOOBDataReqInd](@ref TBlueAPI_RemoteOOBDataReqInd) by accepting/rejecting the authentication attempt on behalf of the user.
 * Also provides the out-of-band (OOB) data required to perform the user-level authentication.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_RemoteOOBDataReqConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,    /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        uint8_t const * pC,           /**< [in] <table><tr><td> For Bluetooth Classic pairing    <td> Hash Value (C)
                                                       <tr><td> For Bluetooth Low Energy pairing <td> Temporary Key (TK)</table>
                                                Length is #BLUEAPI_AUTH_C_LENGTH. Ownership is preserved */
        uint8_t const * pR,           /**< [in] <table><tr><td> For Bluetooth Classic pairing    <td> Randomizer Value (R)
                                                       <tr><td> For Bluetooth Low Energy pairing <td> Ignored</table>
                                                Length is #BLUEAPI_AUTH_R_LENGTH. Ownership is preserved */
        TBlueAPI_Cause cause          /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> The user accepts the authentication attempt
                                                       <tr><td> ::blueAPI_CauseReject <td> The user rejects the authentication attempt. @p pC and @p pR are ignored</table> */);

/** @bookmark{LocalOOBDataReq} */
/** Requests the generation of local parameters for an out-of-band SSP procedure.
 * If the message is accepted, the application will receive a [LocalOOBDataRsp](@ref TBlueAPI_LocalOOBDataRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_LocalOOBDataReq(
        void * pBuffer,              /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle /**< [in,out] BlueAPI context handle */);

/** @bookmark{AuthResultConf} */
/** Responds to an [AuthResultInd](@ref TBlueAPI_AuthResultInd). If the authentication was successful, this message can be used to tag the resulting bond table entry with an application-defined value.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_AuthResultConf(
        void * pBuffer,                        /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,          /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,             /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_RemoteBDType remote_BD_Type,  /**< [in] Bluetooth device address type of @p remote_BD */
        uint32_t AppData,                      /**< [in] Custom value to assign to the new bond table entry. If the authentication was not successful, this parameter is ignored */
        TBlueAPI_Cause cause                   /**< [in] Shall be set to ::blueAPI_CauseSuccess */);

#ifdef V_BLUECODE_MAYBE_OBSOLETE
#error "Missing documentation here"
bool blueAPI_DevicePSKEYSetReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t pskeyID,
        uint16_t pskeyValueLength,      /* length of pskey value      */
        uint8_t const * pPskeyValue            /* pointer to value of pskey  */);

bool blueAPI_DevicePSKEYGetReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t pskeyID,
        uint16_t pskeyValueMaxLength,   /* max length of buffer for pskey value */
        uint8_t const * pPskeyValue            /* pointer to value of pskey            */);
#endif

/** @bookmark{AuthResultRequestConf} */
/** Responds to an [AuthResultRequestInd](@ref TBlueAPI_AuthResultRequestInd) by providing bonding information.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_AuthResultRequestConf(
        void * pBuffer,                       /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,         /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,            /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_RemoteBDType remote_BD_Type, /**< [in] Address type of @p remote_BD */
        uint8_t linkKeyLength,                /**< [in] Length of @p linkKey, in octets. Maximum value if #BLUEAPI_MAX_LINK_KEY_SIZE. If @p cause is ::blueAPI_CauseReject, ignored */
        uint8_t const * linkKey,              /**< [in] Link key stored during bonding. Ownership is preserved. If @p cause is ::blueAPI_CauseReject, ignored */
        TBlueAPI_LinkKeyType keyType,         /**< [in] Key type of @p linkKey. See #TBlueAPI_LinkKeyType for possible values. If @p cause is ::blueAPI_CauseReject, ignored */
        uint16_t restartHandle,               /**< [in] Application-defined handle to mark the current state when providing multiple entries. May not be 0 in that case */
        TBlueAPI_Cause cause                  /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> Bonding information is provided by the application
                                                               <tr><td> ::blueAPI_CauseReject <td> The application cannot provide the requested information</table> */);

/** @bookmark{AuthDeleteReq} */
/** Requests the deletion of an established trusted relation to a remote device (bond table entry).
 * Can also be used to delete all bond table entries, optionally filtering by address type or address.
 * If the message is accepted, the application will receive an [AuthDeleteRsp](@ref TBlueAPI_AuthDeleteRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_AuthDeleteReq(
        void * pBuffer,                      /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,        /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,           /**< [in] Bluetooth device address of the remote device, or all zeroes to delete entries without filtering by device address.
                                                       Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_RemoteBDType remote_BD_Type /**< [in] Address type of entries to be deleted, or ::blueAPI_RemoteBDTypeAny to delete entries without filtering by address type */);

/** @bookmark{AuthListReq} */
/** Requests a list of all established trusted relations to remote devices (bond table entries).
 * The list may optionally be filtered by address type and/or address. If there are any matching bond table entries, they will be provided via [AuthListInfo](@ref TBlueAPI_AuthListInfo).
 * If the message is accepted, the application will receive an [AuthListRsp](@ref TBlueAPI_AuthListRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_AuthListReq(
        void * pBuffer,                      /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,        /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,           /**< [in] Bluetooth device address to filter for, or all zeroes to not filter by device address. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_RemoteBDType remote_BD_Type /**< [in] Address type to filter for, or ::blueAPI_RemoteBDTypeAny to not filter by address type */);

#if (F_BLUE_API_HCI_TUNNEL_SUPPORT)
#error "Missing documentation here"
bool blueAPI_HCITunnelReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t length,
        uint8_t const * hciCommand);
#endif /* (F_BLUE_API_HCI_TUNNEL_SUPPORT) */

#if (F_BT_LOW_ENERGY)
/** @bookmark{LEAdvertiseReq} */
/** Requests enabling or disabling of Bluetooth Low Energy (LE) advertising.
 * For undirected advertising, the device will use the parameters (incl. PDU type) previously set via [LEAdvertiseParameterSetReq](@ref blueAPI_LEAdvertiseParameterSetReq).
 * For directed advertising, previously set parameters are ignored.
 * If the message is accepted, the application will receive a [LEAdvertiseRsp](@ref TBlueAPI_LEAdvertiseRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_LEAdvertiseReq(
        void * pBuffer,                      /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,        /**< [in,out] BlueAPI context handle */
        TBlueAPI_LEAdvMode advMode,          /**< [in] <table><tr><td> ::blueAPI_LEAdvModeDisabled   <td> Disable/stop LE advertising
                                                              <tr><td> ::blueAPI_LEAdvModeUndirected <td> Enable/start undirected advertising
                                                              <tr><td> ::blueAPI_LEAdvModeDirected   <td> Enable/start directed advertising</table> */
        uint8_t const * remote_BD,           /**< [in] Bluetooth device address of the remote device for directed advertising. Length is #BLUE_API_BD_SIZE. Ownership is preserved.
                                                       If @p advMode is not ::blueAPI_LEAdvModeDirected, ignored */
        TBlueAPI_RemoteBDType remote_BD_type /**< [in] Address type of @p remote_BD. If @p advMode is not ::blueAPI_LEAdvModeDirected, ignored */);

/** @bookmark{LEAdvertiseParameterSetReq} */
/** Requests setting the parameters for Bluetooth Low Energy (LE) undirected advertising.
 * If the message is accepted, the application will receive a [LEAdvertiseParameterSetRsp](@ref TBlueAPI_LEAdvertiseParameterSetRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_LEAdvertiseParameterSetReq(
        void * pBuffer,                           /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,             /**< [in,out] BlueAPI context handle */
        TBlueAPI_LEAdvType advType,               /**< [in] Advertising PDU type. Only ::blueAPI_LEAdvTypeUndirected, ::blueAPI_LEAdvTypeScannable and ::blueAPI_LEAdvTypeNonConnectable
                                                            are allowed for undirected advertising */
        TBlueAPI_LEFilterPolicy filterScanReq,    /**< [in] Filter policy for incoming scan requests. See #TBlueAPI_LEFilterPolicy for possible values */
        TBlueAPI_LEFilterPolicy filterConnectReq, /**< [in] Filter policy for incoming connection requests. See #TBlueAPI_LEFilterPolicy for possible values */
        uint16_t minAdvInterval,                  /**< [in] Minimum LE advertising interval, in units of 0.625 ms.
                                                            If @p advType is ::blueAPI_LEAdvTypeUndirected, the valid range is \[0x0020,0x4000] (corresponds to \[20 ms, 10.24 s]).
                                                            Otherwise, the valid range is \[0x00A0, 0x4000] (corresponds to \[100 ms, 10.24 s]) */
        uint16_t maxAdvInterval                   /**< [in] Maximum LE advertising interval, in units of 0.625 ms. Valid range is \[@p minAdvInterval, 0x4000] (corresponds to \[..., 10.24 s]).
                                                            It is recommended to set this value to a higher value than @p minAdvInterval, to enable the Bluetooth controller to determine
                                                            the best advertising interval, considering other Bluetooth activity. */);

/** @bookmark{LEAdvertiseDataSetReq} */
/** Requests setting of advertisement data or scan response data (payload) for Bluetooth Low Energy (LE) advertising.
 * If the message is accepted, the application will receive a [LEAdvertiseDataSetRsp](@ref TBlueAPI_LEAdvertiseDataSetRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_LEAdvertiseDataSetReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        TBlueAPI_LEDataType dataType, /**< [in] Type of data to be set. See #TBlueAPI_LEDataType for possible values */
        uint8_t dataLength,           /**< [in] Length of @p data, in octets. Valid range is \[0x00,0x1F] */
        uint8_t const * data          /**< [in] Application-defined payload data. Ownership is preserved */);

/** @bookmark{LEScanReq} */
/** Requests enabling or disabling of Bluetooth Low Energy (LE) scanning.
 * If the message is accepted, the application will receive a [LEScanRsp](@ref TBlueAPI_LEScanRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_LEScanReq(
        void * pBuffer,                       /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,         /**< [in,out] BlueAPI context handle */
        TBlueAPI_LEScanMode scanMode,         /**< [in] <table><tr><td> ::blueAPI_LEScanDisabled <td> Disable/stop LE scanning
                                                               <tr><td> ::blueAPI_LEScanPassive  <td> Enable/start passive scanning
                                                               <tr><td> ::blueAPI_LEScanActive   <td> Enable/start active scanning</table> */
        uint16_t scanInterval,                /**< [in] Scan Interval, in units of 0.625 ms. This value is a recommendation for the frequency of scanning.
                                                        Valid range is \[0x0004, 0x4000] (corresponds to \[2.5 ms, 10.24 s]) */
        uint16_t scanWindow,                  /**< [in] Scan Window, in units of 0.625 ms. This value is a recommendation for the duration of a single scan window, repeated at an interval of @p scanInterval.
                                                        Valid range is \[0x0004, @p scanInterval] (corresponds to \[2.5 ms, ...]) */
        TBlueAPI_LEFilterPolicy filterPolicy, /**< [in] Filter policy for incoming advertising events. See #TBlueAPI_LEFilterPolicy for possible values */
        uint8_t filterDuplicates              /**< [in] true if duplicate advertising events shall be filtered */);

/** @bookmark{LEModifyWhitelistReq} */
/** Requests a modification of the Bluetooth Low Energy device address whitelist.
 * Only allowed when the whitelist is not in use. The whitelist is in use in any of the following cases:
 * -# Advertising is enabled, and request filtering has been enabled via [LEAdvertiseParameterSetReq](@ref blueAPI_LEAdvertiseParameterSetReq)
 * -# Scanning is enabled, and advertising event filtering has been enabled via [LEScanReq](@ref blueAPI_LEScanReq)
 * -# If a GATT connection is being established as requested by [ConnectGATTMDLReq](@ref blueAPI_ConnectGATTMDLReq), and device selection by whitelist has been chosen
 * If the message is accepted, the application will receive a [LEModifyWhitelistRsp](@ref TBlueAPI_LEModifyWhitelistRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_LEModifyWhitelistReq(
        void * pBuffer,                       /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,         /**< [in,out] BlueAPI context handle */
        TBlueAPI_LEWhitelistOp operation,     /**< [in] Modification type.
                                                        <table><tr><td> ::blueAPI_LEWhitelistOpClear  <td> The whitelist shall be cleared
                                                               <tr><td> ::blueAPI_LEWhitelistOpAdd    <td> An entry shall be added to the whitelist
                                                               <tr><td> ::blueAPI_LEWhitelistOpRemove <td> An entry shall be removed from the whitelist</table> */
        uint8_t const * remote_BD,            /**< [in] Bluetooth device address of the remote device to add to / remove from the whitelist. Length is #BLUE_API_BD_SIZE. Ownership is preserved.
                                                        If @p operation is blueAPI_LEWhitelistOpClear, ignored */
        TBlueAPI_RemoteBDType remote_BD_type  /**< [in] Address type of @p remote_BD. If @p operation is blueAPI_LEWhitelistOpClear, ignored */);

/** @bookmark{LEConnectionUpdateReq} */
/** Request a Connection Parameter Update on an established Bluetooth Low Energy (LE) link.
 * If the local device operates as central/master, both devices will be informed of the new parameters via [LEConnectionParameterInfo](@ref TBlueAPI_LEConnectionParameterInfo).
 * If the local device operates as peripheral/slave, the central will be informed of the proposed parameters via [LEConnectionUpdateInd](@ref TBlueAPI_LEConnectionUpdateInd).
 * If the central accepts the parameters (cause set to ::blueAPI_CauseAccept in [LEConnectionUpdateConf](@ref blueAPI_LEConnectionUpdateConf)),
 * both devices will be informed of the new parameters via LEConnectionParameterInfo.
 * If the message is accepted, the application will receive a [LEConnectionUpdateRsp](@ref TBlueAPI_LEConnectionUpdateRsp) message.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_LEConnectionUpdateReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the LE link */
        uint16_t connIntervalMin,     /**< [in] Minimum Connection Interval, in units of 1.25 ms. Valid range is \[0x0006, 0x0C80] (corresponds to \[7.5 ms, 4 s]) */
        uint16_t connIntervalMax,     /**< [in] Maximum Connection Interval, in units of 1.25 ms. Valid range is \[@p connIntervalMin, 0x0C80] (corresponds to \[..., 4 s]) */
        uint16_t connLatency,         /**< [in] Slave Latency, i.e., the amount of connection events the slave may ignore. Valid range is \[0x0000, 0x01F3] */
        uint16_t supervisionTimeout   /**< [in] Connection Supervision Timeout, in units of 10 ms. Valid range is \[0x000A, 0x0C80] (corresponds to \[100 ms, 32 s]) */);

/** @bookmark{LEConnectionUpdateConf} */
/** Responds to an [LEConnectionUpdateInd](@ref TBlueAPI_LEConnectionUpdateInd) by accepting/rejecting the proposed parameters
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_LEConnectionUpdateConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,        /**< [in] Local MDL ID of the LE link */
        TBlueAPI_Cause cause          /**< [in] <table><tr><td> ::blueAPI_CauseAccept <td> Accept the Connection Parameter Update
                                                       <tr><td> ::blueAPI_CauseReject <td> Reject the Connection Parameter Update */);

#if (F_BT_LE_PRIVACY_MODE)
#error "Missing documentation here"
bool blueAPI_LEPrivacyModeReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        TBlueAPI_LEPrivacyMode privacyMode);

#endif /* (F_BT_LE_PRIVACY_MODE) */
#endif /* (F_BT_LOW_ENERGY) */

#if (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM)
#error "Missing documentation here"
bool blueAPI_TestmodeReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        TBlueAPI_Testmode testmode);
#endif /* (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM) */

/** @bookmark{ACLConfigLinkpolicyReq} */
/** Requests the configuration of link policy parameters for established connections.
 * If the message is accepted, the application will receive an [ACLConfigRsp](@ref TBlueAPI_ACLConfigRsp) message with opCode ::blueAPI_ACLConfigLinkpolicy.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ACLConfigLinkpolicyReq(
        void * pBuffer,                   /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,     /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,        /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_BRLinkPolicy linkPolicy, /**< [in] Link policy for role switch and sniff mode. See #TBlueAPI_BRLinkPolicy for possible values.
                                                    Default value is as configured for the device (see [DeviceConfigPolicySetReq](@ref blueAPI_DeviceConfigLinkpolicySetReq)) */
        TBlueAPI_BRDeviceRole deviceRole, /**< [in] Desired device role for the connections. See #TBlueAPI_BRDeviceRole for possible values.
                                                    Default value is as configured for the device (see [DeviceConfigPolicySetReq](@ref blueAPI_DeviceConfigLinkpolicySetReq)) */
        uint16_t supervisionTimeout       /**< [in] Supervision Timeout, in units of 0.625 ms.
                                                    Valid range is \[0x0001, 0xFFFF] (corresponds to \[0.625 ms, 40.96 s]), default value is 0x7D00 (corresponds to 20 s).
                                                    If the local device is not master of the piconet after the completion of the requested operations, this value has no effect */);

/** @bookmark{ACLConfigSniffmodeReq} */
/** Requests the configuration of sniff and sniff subrating parameters for established connections.
 * If the message is accepted, the application will receive an [ACLConfigRsp](@ref TBlueAPI_ACLConfigRsp) message with opCode ::blueAPI_ACLConfigSniffmode.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ACLConfigSniffmodeReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,    /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        uint16_t minInterval,         /**< [in] Minimum sniff interval, in units of 0.625 ms.
                                                Valid range is \[0x0002, 0xFFFE] (corresponds to \[0.625 ms, 40.96 s]).
                                                If @p maxInterval is 0, ignored */
        uint16_t maxInterval,         /**< [in] Maximum sniff interval, in units of 0.625 ms.
                                                May be set to 0, which disables active sniff.
                                                Valid range otherwise is \[@p minInterval, 0xFFFE] (corresponds to \[..., 40.96 s]) */
        uint16_t sniffAttempt,        /**< [in] Number of baseband receive slots for a sniff attempt. Each slot corresponds to 1.25 ms.
                                                Valid range is \[0x0001, 0x7FFF] (corresponds to \[0.625 ms, 40.96 s]) */
        uint16_t sniffTimeout,        /**< [in] Sniff timeout, in units of 1.25 ms.
                                                Valid range is \[0x0000, 0x7FFF] (corresponds to \[0, 40.96 s]) */
        uint16_t maxLatency,          /**< [in] Maximum subrate latency, in units of 0.625 ms.
                                                Valid range is \[0x0000, 0xFFFE] (corresponds to \[0, 40.96 s]) */
        uint16_t minRemoteTimeout,    /**< [in] Minimum base sniff subrate timeout of the remote device, in units of 0.625 ms.
                                                Valid range is \[0x0000, 0xFFFE] (corresponds to \[0, 40.96 s]) */
        uint16_t minLocalTimeout      /**< [in] Minimum base sniff subrate timeout of the local device, in units of 0.625 ms.
                                                Valid range is \[0x0000, 0xFFFE] (corresponds to \[0, 40.96 s]) */);

#if (F_BT_HCI_RADIO_STATUS_CONF)
/** @bookmark{ACLConfigLinkstatusReq} */
/** Requests enabling/disabling of periodic link status polling for established connections.
 * When polling is enabled, the application will receive periodic [ACLStatusInfo](@ref TBlueAPI_ACLStatusInfo) events where local_ACL_Status is ::blueAPI_ACLConnectedLinkStatus.
 * If the message is accepted, the application will receive an [ACLConfigRsp](@ref TBlueAPI_ACLConfigRsp) message with opCode ::blueAPI_ACLConfigLinkstatus.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_ACLConfigLinkstatusReq(
        void * pBuffer,                       /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,         /**< [in,out] BlueAPI context handle */
        uint8_t const * remote_BD,            /**< [in] Bluetooth device address of the remote device. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
        TBlueAPI_RemoteBDType remote_BD_Type, /**< [in] Address type of @p remote_BD */
        uint16_t pollInterval                 /**< [in] Polling interval, in units of 1 ms.
                                                        May be set to 0, which disables link status polling.
                                                        Valid range otherwise is \[0x000A, 0xFFFF] (corresponds to \[10 ms, 655 s]) */);
#endif /* (F_BT_HCI_RADIO_STATUS_CONF) */

#if (F_BLUE_API_HID_SUPPORT)
/** @bookmark{HIDMessageReq} */
/** Requests the transmission of an HID/HoGP message to a remote device over an HID link (for HID) or a GATT link (for HoGP).
 * If the message is accepted, the application will receive an [HIDMessageRsp](@ref TBlueAPI_HIDMessageRsp) message. BlueCode+ may delay the HIDMessageRsp to apply flow control.
 * Until the corresponding HIDMessageRsp is received, the operation is considered pending and flow control constraints (downstream credits) for the link apply.
 * Note that HoGP messages may only be sent over a GATT link if the built-in HoGP GATT service has been registered via [GATTServiceRegisterReq](@ref blueAPI_GATTServiceRegisterReq).
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_HIDMessageReq(
        void * pBuffer,                     /**< [in,out] BlueAPI-provided buffer containing the payload data. If the message is accepted, application ownership of this buffer is released */
        TBlueAPIHandle blueAPIHandle,       /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,              /**< [in] Local MDL ID of the HID link, or of the underlying GATT link for an HoGP message */
        TBlueAPI_HIDMsgHeader hidMsgHeader, /**< [in] HID message header identifying an HID operation */
        uint16_t payloadOffset,             /**< [in] Offset of the HID data in @p pBuffer. Must be at least the value of @p dsDataOffset provided by [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) for the HID link */
        uint16_t payloadLength              /**< [in] Length of the HID data in @p pBuffer */);

/** @bookmark{HIDMessageConf} */
/** Responds to a [HIDMessageInd](@ref TBlueAPI_HIDMessageInd), releasing shared ownership of the corresponding buffer.
 * After successfully sending this message, the application should discard the buffer reference. The application may delay this message to apply flow control.
 * Until the application sends this message, the HIDMessageInd is considered pending and flow control constraints (upstream credits) for the link apply.
 * Note that HIDMessageInds are always confirmed in the order they have been received in.
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_HIDMessageConf(
        void * pBuffer,                     /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle,       /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,              /**< [in] Local MDL ID of the HID link, or of the underlying GATT link for an HoGP message */
        TBlueAPI_HIDMsgHeader hidMsgHeader, /**< [in] HID message header identifying an HID operation */
        TBlueAPI_Cause cause                /**< [in] Historical argument, shall be set to ::blueAPI_CauseSuccess */);
#endif /* (F_BLUE_API_HID_SUPPORT) */

#if (F_APPLE_IAP2)
#error "Missing documentation here"
bool blueAPI_IAP2MessageReq(
        void * pBuffer,
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,
        uint8_t sessionID,
        uint16_t payloadOffset,
        uint16_t payloadLength);

bool blueAPI_IAP2MessageConf(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint16_t local_MDL_ID,
        uint8_t sessionID,
        TBlueAPI_Cause cause);
#endif /* (F_APPLE_IAP2) */

#if (F_BLUE_API_BAS_SUPPORT)
/** @bookmark{BatteryLevelSetReq} */
/** Requests setting the current battery level value of the built-in Battery Service (BAS).
 * May only be used after a built-in BAS GATT service has been registered.
 * If the message is accepted, the application will receive an [BatteryLevelSetRsp](@ref TBlueAPI_BatteryLevelSetRsp).
 * @retval false if the message could not be handled by BlueAPI. */
bool blueAPI_BatteryLevelSetReq(
        void * pBuffer,               /**< [in,out] BlueAPI-provided buffer that will be used to store message parameters. Can be set to NULL for this message */
        TBlueAPIHandle blueAPIHandle, /**< [in,out] BlueAPI context handle */
        uint8_t level                 /**< [in] New battery level value. Valid range is [0,100] */);
#endif /* (F_BLUE_API_BAS_SUPPORT) */

#ifdef __cplusplus
}
#endif

#endif /* ndef __BLUECODE_BLUEAPI_H */
