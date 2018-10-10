/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/blueapi_msg_upstream.h,v $
 * Revision:    $Revision: 2.1 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_BLUEAPI_MSG_UPSTREAM_H
#define __BLUECODE_BLUEAPI_MSG_UPSTREAM_H

/** @file
 * BlueAPI upstream interface of BlueCode+ (External message interface). BlueAPI application code that shall handle BlueAPI events received as messages should include this header. */

#ifndef V_BLUECODE_EXPORTED
#include "flags.h"             // Variant management
#endif
#include "blueapi_datatypes.h" // BlueAPI data types

#ifdef __cplusplus
extern "C" {
#endif

// BlueAPI upstream message interface

#define GATT_MDEP_ID ((uint8_t ) 0xFF) /**< Special remote MDEP ID indicating a GATT connection */

/** @bookmark{ConnectMDLRsp} */
/** Response to a previous Connect*MDLReq. */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< Bluetooth device address of the remote device that BlueCode+ tried to connect to. Length is #BLUE_API_BD_SIZE. Ownership is preserved */
    TBlueAPI_RemoteBDType remote_BD_type; /**< Bluetooth device address type of @p remote_BD */
    uint16_t local_MDL_ID;                /**< Local MDL ID of the link. Shall be ignored if cause is not ::blueAPI_CauseSuccess */
    uint8_t remote_MDEP_ID;               /**< Remote endpoint identifier of the endpoint the link connects to.
                                               For connection procedures that did not require the specification of a remote endpoint, this value shall be ignored.
                                               Shall be ignored if cause is not ::blueAPI_CauseSuccess */
    uint8_t local_MDEP_ID;                /**< @p local_MDEP_ID parameter of the corresponding request */
    TBlueAPI_Cause cause;                 /**< <table><tr><td> ::blueAPI_CauseSuccess              <td> The connection has been established successfully
                                                      <tr><td> ::blueAPI_CauseAuthenticationFailed <td> The required authentication failed
                                                      <tr><td> ::blueAPI_CauseReject               <td> The remote device rejected the connection attempt
                                                      <tr><td> ::blueAPI_CauseResourceError        <td> The connection could not be established due to resource constraints
                                                      <tr><td> ::blueAPI_CauseInvalidParameter     <td> The request contained an invalid parameter and has been ignored
                                                      <tr><td> ::blueAPI_CauseConnectionDisconnect <td> The remote device rejected the connection attempt
                                                      <tr><td> ::blueAPI_CauseConnectionLost       <td> The remote device is unresponsive or out of range
                                                      <tr><td> ::blueAPI_CauseAddressNotResolved   <td> The current resolvable private address of the remote device is not available</table> */
} TBlueAPI_ConnectMDLRsp, * PBlueAPI_ConnectMDLRsp;

/** @bookmark{CreateMDLInd} */
/** Message that indicates the creation of a new link. An link can be created due to an incoming or outgoing connection request.
 * The recipient BlueAPI application may still reject the creation of the link.
 * On reception of this message, the BlueAPI application shall respond with a matching [CreateMDLConf](@ref blueAPI_CreateMDLConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle;            /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];    /**< Bluetooth device address of the remote device */
    TBlueAPI_RemoteBDType remote_BD_type;   /**< Bluetooth device address type of @p remote_BD */
    uint16_t local_MDL_ID;                  /**< Local MDL ID of the link to be created. The ID is in the range [0x01,0xFE] and unique until the links's rejection / disconnection.
                                                 If the link creation is accepted, this value can now be used to identify the link in future messages */
    uint8_t remote_MDEP_ID;                 /**< Remote MDEP ID of the endpoint on the remote device that this link will be connected to.
                                                 If the link creation is caused by an incoming connection request, this value will be set to 0 */
    uint8_t local_MDEP_ID;                  /**< Local MDEP ID of the local endpoint that the link will be connected to */
    TBlueAPI_LinkConfigType linkConfigType; /**< Requested QoS configuration for the link */
}  TBlueAPI_CreateMDLInd, * PBlueAPI_CreateMDLInd;

/** @bookmark{DisconnectMDLInd} */
/** Message that indicates the disconnection of an existing link. An link can be disconnected due to an incoming or outgoing disconnection request, or due to unexpected errors / loss of connection.
 * The recipient BlueAPI application cannot reject the disconnection of the link.
 * On reception of this message, the BlueAPI application shall respond with a matching [DisconnectMDLConf](@ref blueAPI_DisconnectMDLConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the link to be disconnected.
                                      @attention This message does not indicate the deletion of the link; hence the MDL ID is not free for re-use yet. See [DeleteMDLInfo](@ref TBlueAPI_DeleteMDLInfo) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseConnectionDisconnect <td> The disconnection is caused by an intentional disconnection request
                                             <tr><td> ::blueAPI_CauseConnectionLost       <td> The disconnection is caused by an unintentional connection loss</table> */
}  TBlueAPI_DisconnectMDLInd, * PBlueAPI_DisconnectMDLInd;

/** @bookmark{DisconnectMDLRsp} */
/** Response to a previous [DisconnectMDLReq](@ref blueAPI_DisconnectMDLReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the link whose disconnection has been requested */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The request is valid and a disconnection procedure is in progress
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request has been ignored due to invalid parameters</table> */
}  TBlueAPI_DisconnectMDLRsp, * PBlueAPI_DisconnectMDLRsp;

#if (F_BLUE_API_RECONNECT_SUPPORT)
#error "Missing documentation here"
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;
    TBlueAPI_Cause cause;
}  TBlueAPI_ReconnectMDLRsp, * PBlueAPI_ReconnectMDLRsp;

typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;
}  TBlueAPI_ReconnectMDLInd, * PBlueAPI_ReconnectMDLInd;
#endif /* (F_BLUE_API_RECONNECT_SUPPORT) */

/** @bookmark{ConnectMDLInfo} */
/** Message that provides information about a newly connected link.
 * After this message has been received, data can be exchanged over the link. For GATT-based connections, the reception of this message allows the client application to use the functionality of all
 * built-in profiles that have previously been activated. For example, if the variant of BlueCode+ includes a built-in Terminal I/O profile, a serial channel can be opened by discovering a remote
 * endpoint using [SPPDiscoveryReq](@ref blueAPI_SPPDiscoveryReq) and then connecting to it via [ConnectSPPMDLReq](@ref blueAPI_ConnectSPPMDLReq). Note that from this point onwards, the serial
 * communication API for Terminal I/O is identical to the one for the Classic SPP profile. */
typedef struct
{
    TBlueAPIAppHandle appHandle;            /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;                  /**< Local MDL ID of the link */
    uint16_t dsPoolID;                      /**< Downstream buffer pool identifier for the link. The application can use this identifier to allocate buffers for data transfer with #blueAPI_BufferGet */
    uint16_t dsDataOffset;                  /**< Minimum offset of message payload in data buffers. See #blueAPI_BufferGet for more details */
    uint16_t maxAPDUSize;                   /**< Maximum size of logical application data packets transferred over the link. Note that packets larger than the maximum segment size must be segmented */
    uint16_t maxTPDUSize;                   /**< Maximum data packet segment size for the link. For RFCOMM-based connections, this value will not be larger than #BLUE_API_MAX_RFCOMM_SEGMENT.
                                                 For LE links, this value will not be larger than #BLUE_API_MAX_LE_SEGMENT.
                                                 For GATT-based connections, this parameter signals the MTU size on ATT protocol layer.
                                                 @attention The segment size for GATT-based connections is specific to the requested operation since the ATT header length varies.
                                                            See the documentation of individual GATT operations for more details */
    TBlueAPI_LinkConfigType linkConfigType; /**< Negotiated QoS configuration for the link */
    uint8_t maxTPDUusCredits;               /**< Maximum number of pending upstream data exchange messages for the link (<em>upstream credits</em>). Is smaller than or equal to the @p maxTPDUusCredits parameter
                                                 specified in the [CreateMDLConf](@ref blueAPI_CreateMDLConf) for the link. For GATT connections, this parameter is ignored.
                                                 @attention This means that a GATT server application can receive an arbitrary burst of messages that do not require acknowledgment (e.g., [GATTAttributeWriteCommandInfo](@ref TBlueAPI_GATTAttributeWriteCommandInfo) */
    uint8_t maxTPDUdsCredits;               /**< Maximum number of pending downstream data exchange messages for the link (<em>downstream credits</em>). The application must consider this value to not violate
                                                 the flow control constraints of the link. For GATT-based connections, this parameter is only applicable to:
                                                  - [GATTAttributeUpdateReq](@ref blueAPI_GATTAttributeUpdateReq)s that result in an ATT layer Handle Value Notification
                                                  - [GATTAttributeWriteReq](@ref blueAPI_GATTAttributeWriteReq)s that result in an ATT layer Write Command
                                                 For RFCOMM-based connections, this value will not be larger than #BLUE_API_MAX_RFCOMM_CREDITS */
} TBlueAPI_ConnectMDLInfo, * PBlueAPI_ConnectMDLInfo;

/** @bookmark{DeleteMDLInfo} */
/** Message that indicates the deletion of an existing link. An link may be deleted by BlueCode+ after it has been disconnected from its endpoints.
 * After reception of this message, the BlueAPI application may re-use the local MDL ID previously owned by the link. */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MCL ID of the deleted link that can now be re-used */
} TBlueAPI_DeleteMDLInfo, * PBlueAPI_DeleteMDLInfo;

/** @bookmark{MCLStatusInfo} */
/** Message that provides status information for a connection. This message always corresponds to the latest state transition of the connection. */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of the remote device */
    uint16_t local_MCL_ID;               /**< Local MCL ID of the connection */
    TBlueAPI_MCLStatus status;           /**< Current status of the connection. See #TBlueAPI_MCLStatus for possible values */
} TBlueAPI_MCLStatusInfo, * PBlueAPI_MCLStatusInfo;

/** @bookmark{ACLStatusInfo} */
/** Message that provides status information for a Bluetooth ACL. */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< Bluetooth device address of the remote device */
    TBlueAPI_RemoteBDType remote_BD_type; /**< Bluetooth device address type of @p remote_BD */
    TBlueAPI_ACLStatus status;            /**< Current status of the ACL. See #TBlueAPI_ACLStatus for possible values.
                                               Depending on the status, addition parameters are provided within @p p */
    TBlueAPI_ACLStatusParam p;            /**< Tagged union for ACL Status Info parameters. The corresponding tag is @p status */
} TBlueAPI_ACLStatusInfo, * PBlueAPI_ACLStatusInfo;

/** @bookmark{RegisterRsp} */
/** Response to a previous [RegisterReq](@ref blueAPI_RegisterReq).
 * If the registration has been successful, the application will receive an [ActInfo](@ref TBlueAPI_ActInfo) when BlueCode+ is ready for operation.
 * @attention The reception of this message does not indicate that BlueCode+ is ready for operation. See [ActInfo](@ref TBlueAPI_ActInfo). */
typedef struct
{
    TBlueAPIAppHandle appHandle;  /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPIHandle blueAPIHandle; /**< BlueCode+ context handle that the application shall provide in all following messages.
                                       Value shall be ignore if @p cause is not ::blueAPI_CauseSuccess */
    TBlueAPI_Cause cause;         /**< <table><tr><td> ::blueAPI_CauseSuccess       <td> The application has been registered at BlueAPI successfully
                                              <tr><td> ::blueAPI_CauseResourceError <td> The application could not be registered due to lack of resources
                                              <tr><td> ::blueAPI_CauseNotSupported  <td> The application could not be registered due to a mismatch of API versions</table> */
} TBlueAPI_RegisterRsp, * PBlueAPI_RegisterRsp;

/** @bookmark{ReleaseRsp} */
/** Response to a previous [ReleaseReq](@ref blueAPI_ReleaseReq).
 * If the release operation has been successful, a new application can be registered via [RegisterReq](@ref blueAPI_RegisterReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The request is valid and the application has been released from BlueAPI
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request has been ignored due to invalid parameters</table> */
} TBlueAPI_ReleaseRsp, * PBlueAPI_ReleaseRsp;

/** @bookmark{ReleaseInd} */
/** Message that indicates that the application will be released from BlueAPI. This release operation can be caused by the shutdown of a lower layer, or be part of the BlueCode+ reset feature.
 * On reception of this message, the BlueAPI application shall release shared ownership of all resources provide by BlueCode+
 * and then respond with a matching [ReleaseConf](@ref blueAPI_ReleaseConf).
 * After reception of this message, the application shall not send any message besides the [ReleaseConf](@ref blueAPI_ReleaseConf), until BlueCode+ has been deactivated ([DeactInfo](@ref TBlueAPI_DeactInfo))
 * and the application then registered itself again ([RegisterReq](@ref blueAPI_RegisterReq)).
 * @attention The application must discard all shared references before issuing a [ReleaseConf](@ref blueAPI_ReleaseConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
} TBlueAPI_ReleaseInd, * PBlueAPI_ReleaseInd;

/** @bookmark{ActInfo} */
/** Message that indicates the result of BlueCode+ activation.
 * After reception of this message with cause ::blueAPI_CauseSuccess, the application may consider BlueCode+ ready for operation and issue further BlueAPI messages. */
typedef struct
{
    TBlueAPIAppHandle appHandle;              /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t local_BD[BLUE_API_BD_SIZE];       /**< Own (local) Bluetooth device address */
    uint8_t version[BLUE_API_VERSION_LENGTH]; /**< User-friendly BlueCode+ version information string. Zero-terminated */
    uint16_t systemPoolID;                    /**< Downstream buffer pool identifier can be used which small amounts of data that are not connection-related. See #blueAPI_BufferGet */
    TBlueAPI_Cause cause;                     /**< <table><tr><td> ::blueAPI_CauseSuccess             <td> BlueCode+ has been activated successfully and is ready for operation
                                                          <tr><td> ::blueAPI_CauseInitTimeout         <td> BlueCode+ activation has failed due to a timeout of an external resource (such as the COMAPI)
                                                          <tr><td> ::blueAPI_CauseInitOutofSync       <td> BlueCode+ activation has failed due to communication problems with the Bluetooth controller
                                                          <tr><td> ::blueAPI_CauseInitHardwareFailure <td> BlueCode+ activation has failed due to a hardware error</table> */
} TBlueAPI_ActInfo, * PBlueAPI_ActInfo;

/** @bookmark{DeactInfo} */
/** Message that indicates the deactivation of BlueCode+. This indicates the completion of the BlueCode+ reset operation from the application's point of view.
 * The application may now register itself again by issuing a [RegisterReq](@ref blueAPI_RegisterReq).
 * This message also releases the application handle (@p appHandle) from BlueCode+ and it will not issue further messages with that handle */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
} TBlueAPI_DeactInfo, * PBlueAPI_DeactInfo;

/** @bookmark{InternalEventInfo} */
/** Message that indicates the reception of an illegal message from either the BlueAPI application or a Bluetooth peer.
 * This message will only be used for error signaling if there is no other planned message exchange that can be used for this purpose.
 * For example, there is no expected message to a downstream "confirmation" message, so the sending of an invalid confirmation message will result in the reception of this message. */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_InternalEventType eventType; /**< Type of illegal message reception. See #TBlueAPI_InternalEventType for possible values */
    uint32_t eventInfo;                   /**< Specific additional information for debug purposes */
    TBlueAPI_Cause cause;                 /**< <table><tr><td> ::blueAPI_CauseInvalidParameter     <td> The illegal message has been ignored since it contained invalid parameters
                                                      <tr><td> ::blueAPI_CauseResourceError        <td> The illegal message requested an operation that could be performed due to resource constraints
                                                      <tr><td> ::blueAPI_CauseInvalidState         <td> The illegal message has been received in a state where the requested operation is not permitted
                                                      <tr><td> ::blueAPI_CauseFlowcontrolViolation <td> The application has violated flow control constraints and the requested data has not been sent
                                                      <tr><td> ::blueAPI_CauseUnspecified          <td> The illegal message could not be handled due to an unspecified cause</table> */
} TBlueAPI_InternalEventInfo, * PBlueAPI_InternalEventInfo;

/** @bookmark{DataRsp} */
/** Response to a previous [DataReq](@ref blueAPI_DataReq).
 * If successful (and the link is still connected), the reception of this message returns a flow control credit for the link;
 * i.e., if the maximum amount of DataReq messages have been pending, the application may now send an additional DataReq. */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the link the data has been sent on. Matches the @p local_MDL_ID parameter of the corresponding request */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess              <td> The requested data has been transmitted successfully
                                             <tr><td> ::blueAPI_CauseInvalidParameter     <td> The request contained an invalid parameter and has been ignored
                                             <tr><td> ::blueAPI_CauseConnectionDisconnect <td> The link has been disconnected before the data could be sent
                                             <tr><td> ::blueAPI_CauseConnectionLost       <td> The connection has been lost before the data could be sent
                                             <tr><td> ::blueAPI_CauseFlowcontrolViolation <td> The application has violated flow control constraints and the requested data has not been sent</table> */
} TBlueAPI_DataRsp, * PBlueAPI_DataRsp;

/** @bookmark{DataInd} */
/** Message that indicates the reception of data from a remote peer. This message provides the complete received data avoid a copy operations.
 * The message structure is a variable-sized structure, where the @p data field serves as a placeholder for the complete payload (which is stored in memory following the structure after a gap of @p gap octets).
 * Therefore, individual data octets at index @em i can be accessed via <code>dataIndPointer->data[gap + i]</code>.
 * This memory is given into shared ownership with the application, which it must release via [DataConf](@ref blueAPI_DataConf).
 * Note that this message must always be communicated via reference, as a struct copy operation would discard the variable-sized data and data access via a copied structure may cause a memory access violation.
 * On reception of this message, the BlueAPI application shall respond with a matching [DataConf](@ref blueAPI_DataConf).
 * The application may delay the response to apply flow control. Until the application responds, the DataInd is considered pending and flow control constraints (upstream credits) for the link apply.
 * @attention Not sending a corresponding DataConf causes a loss of upstream credits and can lead to reduced performance or complete loss of communication
 * @attention Only the memory starting at <code>&data[gap]</code> with length @p payloadLength is shared with the application. For message itself, constraints of the reception mechanism still apply */
typedef struct
{
    TBlueAPIAppHandle appHandle;  /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;        /**< Local MDL ID of the link the data has been received on */
    TBlueAPI_FrameType frameType; /**< Segmentation status of the message. See #TBlueAPI_FrameType for possible values. For SPP and Terminal I/O connections, this is always ::blueAPI_FrameTypeUnsegmented */
    uint16_t frameLength;         /**< If this message contains the start segment of a segmented APDU (@p frameType is blueAPI_FrameTypeFirstSegment), the size of the complete APDU.
                                       If not, shall be ignored */
    uint16_t payloadLength;       /**< Size of the payload data starting at <code>&data[gap]</code> */
    uint16_t gap;                 /**< Index of the first octet of payload data in the variable-sized array @p data */
    uint8_t data[1];              /**< Placeholder for accessing the payload data stored in memory following the message structure */
} TBlueAPI_DataInd, * PBlueAPI_DataInd;

/** @bookmark{RadioModeSetRsp} */
/** Response to a previous [RadioModeSetReq](@ref blueAPI_RadioModeSetReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess      <td> The controller functionality has been configured successfully
                                             <tr><td> ::blueAPI_CauseReject       <td> The controller could not be configured as requested in its current state.
                                                                                       For example, "Deep Sleep" has been requested while an active connection existed
                                             <tr><td> ::blueAPI_CauseNotSupported <td> The requested functionality is not supported by the controller</table> */
} TBlueAPI_RadioModeSetRsp, * PBlueAPI_RadioModeSetRsp;

/** @bookmark{DeviceConfigSetRsp} */
/** Response to a previous DeviceConfig*Req. */
typedef struct
{
    TBlueAPIAppHandle appHandle;        /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_DeviceConfigOpcode opCode; /**< Type of device configuration request that this message responds to. See #TBlueAPI_DeviceConfigOpcode for possible values */
    TBlueAPI_Cause cause;               /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The configuration has been updated according to the request
                                                    <tr><td> ::blueAPI_CauseInvalidParameter <td> The configuration request contained an invalid parameter and has been ignored
                                                    <tr><td> ::blueAPI_CauseInvalidState     <td> The requested configuration was not applicable to the current state of BlueCode+ and has been ignored</table> */
} TBlueAPI_DeviceConfigSetRsp, * PBlueAPI_DeviceConfigSetRsp;

/** @bookmark{ACLConfigRsp} */
/** Response to a previous ACLConfig*Req. */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< Bluetooth device address of the remote device the configured ACL connects to */
    TBlueAPI_RemoteBDType remote_BD_Type; /**< Bluetooth device address type of @p remote_BD */
    TBlueAPI_ACLConfigOpcode opCode;      /**< Type of ACL configuration request that this message responds to. See #TBlueAPI_ACLConfigOpcode for possible values */
    TBlueAPI_Cause cause;                 /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The ACL configuration has been updated according to the request
                                                      <tr><td> ::blueAPI_CauseInvalidParameter <td> The ACL configuration request contained an invalid parameter and has been ignored
                                                      <tr><td> ::blueAPI_CauseInvalidState     <td> The requested ACL configuration was not applicable to the current state of BlueCode+ or the ACL and has been ignored</table> */
} TBlueAPI_ACLConfigRsp, * PBlueAPI_ACLConfigRsp;

/** @bookmark{PairableModeSetRsp} */
/** Response to a previous [PairableModeSetReq](@ref blueAPI_PairableModeSetReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The security requirements for pairing have been updated successfully
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                             <tr><td> ::blueAPI_CauseInvalidState     <td> The requested security configuration was not applicable to the current state of BlueCode+ and has been ignored</table> */
} TBlueAPI_PairableModeSetRsp, * PBlueAPI_PairableModeSetRsp;

/** @bookmark{AuthRsp} */
/** Response to a previous [AuthReq](@ref blueAPI_AuthReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of the remote device from the corresponding request */
    TBlueAPI_Cause cause;                /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The authentication procedure has been completed successfully
                                                     <tr><td> ::blueAPI_CauseReject           <td> The remote or local device has rejected the authentication attempt
                                                     <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored, or the authentication code was invalid
                                                     <tr><td> ::blueAPI_CauseConnectionLost   <td> The required connection attempt failed (e.g., the remote device is out of range)</table> */
} TBlueAPI_AuthRsp, * PBlueAPI_AuthRsp;

/** @bookmark{UserAuthorizationReqInd} */
/** Message that indicates the requirement of authorization for a connection attempt.
 * The recipient BlueAPI application may reject the authorization attempt.
 * On reception of this message, the BlueAPI application shall respond with a matching [UserAuthorizationReqConf](@ref blueAPI_UserAuthorizationReqConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of the remote device */
} TBlueAPI_UserAuthorizationReqInd, * PBlueAPI_UserAuthorizationReqInd;

/** @bookmark{UserAuthRequestInd} */
/** Message that indicates the requirement of non-SSP user level authentication via PIN entry (legacy pairing). The authentication could have been triggered by the local device or the remote device.
 * The recipient BlueAPI application may reject the authentication attempt. To accept the authentication attempt, it needs to perform the required user interaction.
 * On reception of this message, the BlueAPI application shall respond with a matching [UserAuthRequestConf](@ref blueAPI_UserAuthRequestConf) after waiting for user interaction. */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of the remote device */
} TBlueAPI_UserAuthRequestInd, * PBlueAPI_UserAuthRequestInd;

/** @bookmark{AuthResultRequestInd} */
/** Message that indicates a request for bonding information stored by the application. This message will only be issued when the current BlueCode+ configuration specifies that the application
 * is responsible for storing the bonding information (::blueAPI_StoreBondModeExtStore).
 * The bonding information may have been provided to application earlier via [AuthResultInd](@ref TBlueAPI_AuthResultInd).
 * On reception of this message, the BlueAPI application shall respond with a matching [AuthResultRequestConf](@ref blueAPI_AuthResultRequestConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< Bluetooth device address of the peer device that bonding information is requested for */
    TBlueAPI_RemoteBDType remote_BD_Type; /**< Bluetooth device address type of @p remote_BD */
    TBlueAPI_LinkKeyType keyType;         /**< Key type of the requested link key. See #TBlueAPI_LinkKeyType for possible values */
    uint16_t restartHandle;               /**< Application-defined handle to mark the current state when providing multiple entries. See the parameter @p restartHandle of [AuthResultRequestConf](@ref blueAPI_AuthResultRequestConf) */
} TBlueAPI_AuthResultRequestInd, * PBlueAPI_AuthResultRequestInd;

#define BLUEAPI_MAX_AUTHCODE_LENGTH ((uint8_t ) 16) /**< Maximum length of a non-SSP user-level authentication code in octets */

/** @bookmark{UserConfirmationReqInd} */
/** Message that indicates that an SSP procedure with "Display Yes/No" functionality is being performed and provides a 6-digit decimal value that shall be displayed to the user.
 * The recipient BlueAPI application may reject the authentication attempt. To accept the authentication attempt, it needs to perform the required user interaction.
 * On reception of this message, the BlueAPI application shall respond with a matching [UserConfirmationReqConf](@ref blueAPI_UserConfirmationReqConf) after waiting for user interaction. */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of the remote device */
    uint32_t displayValue;               /**< Value to be displayed to the user as a 6-digit decimal number. In range [0,999999] */
} TBlueAPI_UserConfirmationReqInd, * PBlueAPI_UserConfirmationReqInd;

/** @bookmark{UserPasskeyReqInd} */
/** Message that indicates that an SSP procedure with local keyboard and remote display functionality is being performed.
 * The recipient BlueAPI application may reject the authentication attempt. If it accepts the authentication attempt, it shall subsequently perform the required user interaction.
 * On reception of this message, the BlueAPI application shall respond with a matching [UserPasskeyReqConf](@ref blueAPI_UserPasskeyReqConf) after waiting for user interaction. */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of the remote device */
} TBlueAPI_UserPasskeyReqInd, * PBlueAPI_UserPasskeyReqInd;

/** @bookmark{UserPasskeyReqReplyRsp} */
/** Response to a previous [UserPasskeyReqReplyReq](@ref blueAPI_UserPasskeyReqReplyReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess      <td> The operation has been performed successfully
                                             <tr><td> ::blueAPI_CauseInvalidState <td> The operation is not applicable for the current state of BlueCode+</table> */
} TBlueAPI_UserPasskeyReqReplyRsp, * PBlueAPI_UserPasskeyReqReplyRsp;

/** @bookmark{UserPasskeyNotificationInfo} */
/** Message that indicates that an SSP procedure with local display and remote keyboard functionality has completed.
 * This message provides the application with the initial state of the display content. */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of the remote device */
    uint32_t displayValue;               /**< Value to be displayed to the user as a 6-digit decimal number. In range [0,999999] */
} TBlueAPI_UserPasskeyNotificationInfo, * PBlueAPI_UserPasskeyNotificationInfo;

/** @bookmark{KeypressNotificationRsp} */
/** Response to a previous [KeypressNotificationReq](@ref blueAPI_KeypressNotificationReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess      <td> The keypress event has been transmitted successfully
                                             <tr><td> ::blueAPI_CauseInvalidState <td> The operation is not applicable for the current state of BlueCode+</table> */
} TBlueAPI_KeypressNotificationRsp, * PBlueAPI_KeypressNotificationRsp;

/** @bookmark{KeypressNotificationInfo} */
/** Message that indicates that an SSP procedure with local display and remote keyboard functionality signals a user interaction event. */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of the remote device */
    TBlueAPI_SSPKeyEvent eventType;      /**< User interaction event. See #TBlueAPI_SSPKeyEvent for possible values */
} TBlueAPI_KeypressNotificationInfo, * PBlueAPI_KeypressNotificationInfo;

/** @bookmark{RemoteOOBDataReqInd} */
/** Message that indicates that an SSP procedure with Out-of-Band (OOB) functionality is being performed and requests OOB data received via a separate channel.
 * The recipient BlueAPI application may reject the authentication attempt. To accept the authentication attempt, it needs to perform the required user interaction.
 * On reception of this message, the BlueAPI application shall respond with a matching [RemoteOOBDataReqConf](@ref blueAPI_RemoteOOBDataReqConf) after waiting for user interaction. */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE]; /**< Bluetooth device address of the remote device */
} TBlueAPI_RemoteOOBDataReqInd, * PBlueAPI_RemoteOOBDataReqInd;

/** @bookmark{LocalOOBDataRsp} */
/** Response to a previous [LocalOOBDataReq](@ref blueAPI_LocalOOBDataReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;      /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t C[BLUEAPI_AUTH_C_LENGTH]; /**< Generated Hash Value (C). Shall be ignored if @p cause is not ::blueAPI_CauseSuccess */
    uint8_t R[BLUEAPI_AUTH_R_LENGTH]; /**< Generated Randomizer Value (R). Shall be ignored if @p cause is not ::blueAPI_CauseSuccess */
    TBlueAPI_Cause cause;             /**< <table><tr><td> ::blueAPI_CauseSuccess      <td> The Out-of-Band (OOB) data has been generated successfully
                                                  <tr><td> ::blueAPI_CauseNotSupported <td> The requested feature is not supported by this BlueCode+ variant / controller model</table> */
} TBlueAPI_LocalOOBDataRsp, * PBlueAPI_LocalOOBDataRsp;

/** @bookmark{AuthResultInd} */
/** Message that indicates that a bonding attempt has been performed.
 * The recipient BlueAPI application may append additional custom data to the bond table entry, if one is generated.
 * On reception of this message, the BlueAPI application shall respond with a matching [AuthResultConf](@ref blueAPI_AuthResultConf).
 * @attention This message will not be generated for an authentication procedure if the @p AuthRequirements were set to ::blueAPI_AuthNoMITMRequiredNoStore or ::blueAPI_AuthMITMRequiredNoStore.*/
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< Bluetooth device address of the remote device */
    TBlueAPI_RemoteBDType remote_BD_Type; /**< Bluetooth device address type of @p remote_BD */
    uint8_t linkKeyLength;                /**< Length of @p linkKey */
    uint8_t linkKey[28];                  /**< Negotiated link key */
    TBlueAPI_LinkKeyType keyType;         /**< Key type of @p linkKey. See #TBlueAPI_LinkKeyType for possible values */
    uint32_t AppData;                     /**< If a matching bond table entry already existed before the authentication,
                                               this value is the @p AppData parameter previously provided via [AuthResultConf](@ref blueAPI_AuthResultConf).
                                               Otherwise, the value is zero */
    TBlueAPI_Cause cause;                 /**< Historical parameter, always set to ::blueAPI_CauseSuccess */
} TBlueAPI_AuthResultInd, * PBlueAPI_AuthResultInd;

/** @bookmark{AuthDeleteRsp} */
/** Response to a previous [AuthDeleteReq](@ref blueAPI_AuthDeleteReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< @p remote_BD parameter of the corresponding request */
    TBlueAPI_RemoteBDType remote_BD_Type; /**< @p remote_BD_Type parameter of the corresponding request */
    TBlueAPI_Cause cause;                 /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The bond table entries have been deleted as requested
                                                      <tr><td> ::blueAPI_CauseInvalidParameter <td> No matching bond table entry exists, or the request contained an invalid parameter and has been ignored</table> */
} TBlueAPI_AuthDeleteRsp, * PBlueAPI_AuthDeleteRsp;

/** @bookmark{AuthListInfo} */
/** Message that provides information about a single established trusted relation (bond table entry) as requested via [AuthListReq](@ref blueAPI_AuthListReq).
 * It may be issued zero or multiple times, depending on the amount of bond table entries matching the request. */
typedef struct
{
    TBlueAPIAppHandle appHandle;                            /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];                    /**< Bluetooth device address of the peer device with the trusted relation */
    TBlueAPI_RemoteBDType remote_BD_Type;                   /**< Bluetooth device address type of @p remote_BD */
    TBlueAPI_LinkKeyType keyType;                           /**< Type of link key stored for this trusted relation */
    uint32_t AppData;                                       /**< The @p AppData parameter previously provided via [AuthResultConf](@ref blueAPI_AuthResultConf) */
    uint8_t Remote_DeviceName[BLUE_API_DEVICE_NAME_LENGTH]; /**< User-friendly name of the peer device. Zero-terminated. This field may be empty if no user-friendly name has been stored */
} TBlueAPI_AuthListInfo, * PBlueAPI_AuthListInfo;

/** @bookmark{AuthListRsp} */
/** Response to a previous [AuthListReq](@ref blueAPI_AuthListReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< @p remote_BD parameter of the corresponding request */
    TBlueAPI_RemoteBDType remote_BD_Type; /**< @p remote_BD_Type parameter of the corresponding request */
    TBlueAPI_Cause cause;                 /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> All matching bond table entries have been provided
                                                      <tr><td> ::blueAPI_CauseInvalidParameter <td> No matching bond table entry exists, or the request contained an invalid parameter and has been ignored</table> */

} TBlueAPI_AuthListRsp, * PBlueAPI_AuthListRsp;

#if (F_BLUE_API_HDP_SUPPORT)
/** @bookmark{RegHDPMDEPRsp} */
/** Response to a previous [RegHDPMDEPReq](@ref blueAPI_RegHDPMDEPReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t MDEP_ID;
    TBlueAPI_MDEPDataType  MDEP_DataType;
    uint16_t MDEP_EntryHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_RegHDPMDEPRsp, * PBlueAPI_RegHDPMDEPRsp;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
/** @bookmark{RegSPPMDEPRsp} */
/** Response to a previous [RegSPPMDEPReq](@ref blueAPI_RegSPPMDEPReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;         /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t MDEP_ID;                     /**< @p MDEP_ID parameter of the corresponding request. If successful, this MDEP ID can now be used to identify the endpoint in following messages */
    TBlueAPI_MDEPDataType MDEP_DataType; /**< @p MDEP_DataType parameter of the corresponding request */
    uint16_t MDEP_EntryHandle;           /**< Additional identifier for the generated endpoint (endpoint entry handle) that can be used to release it. Shall be ignored if @p cause is not ::blueAPI_CauseSuccess */
    TBlueAPI_Cause cause;                /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The requested endpoint has been registered successfully
                                                     <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                                     <tr><td> ::blueAPI_CauseResourceError    <td> The requested endpoint could not be registered due to lack of resources</table> */
} TBlueAPI_RegSPPMDEPRsp, * PBlueAPI_RegSPPMDEPRsp;
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_BLUE_API_HID_SUPPORT)
/** @bookmark{RegHIDMDEPRsp} */
/** Response to a previous [RegHIDMDEPReq](@ref blueAPI_RegHIDMDEPReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t MDEP_ID;             /**< @p MDEP_ID parameter of the corresponding request. If successful, this MDEP ID can now be used to identify the endpoint in following messages */
    uint16_t MDEP_EntryHandle;   /**< Additional identifier for the generated endpoint (endpoint entry handle) that can be used to release it. Shall be ignored if @p cause is not ::blueAPI_CauseSuccess */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The requested endpoint has been registered successfully
                                                     <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                                     <tr><td> ::blueAPI_CauseResourceError    <td> The requested endpoint could not be registered due to lack of resources</table> */
} TBlueAPI_RegHIDMDEPRsp, * PBlueAPI_RegHIDMDEPRsp;

/** @bookmark{HIDMessageRsp} */
/** Response to a previous [HIDMessageReq](@ref blueAPI_HIDMessageReq).
 * If successful (and the link is still connected), the reception of this message returns a flow control credit for the link;
 * i.e., if the maximum amount of DataReq messages have been pending, the application may now send an additional DataReq. */
typedef struct
{
    TBlueAPIAppHandle appHandle;        /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;              /**< Local MDL ID of the link the data has been sent on. Matches the @p local_MDL_ID parameter of the corresponding request */
    TBlueAPI_HIDMsgHeader hidMsgHeader; /**< @p hidMsgHeader parameter of the corresponding request */
    TBlueAPI_Cause cause;               /**< <table><tr><td> ::blueAPI_CauseSuccess              <td> The requested data has been transmitted successfully
                                                    <tr><td> ::blueAPI_CauseInvalidParameter     <td> The request contained an invalid parameter and has been ignored
                                                    <tr><td> ::blueAPI_CauseConnectionDisconnect <td> The link has been disconnected before the data could be sent
                                                    <tr><td> ::blueAPI_CauseConnectionLost       <td> The connection has been lost before the data could be sent
                                                    <tr><td> ::blueAPI_CauseFlowcontrolViolation <td> The application has violated flow control constraints and the requested data has not been sent</table> */
} TBlueAPI_HIDMessageRsp, * PBlueAPI_HIDMessageRsp;

/** @bookmark{HIDMessageInd} */
/** Message that indicates the reception of an HID message from a remote peer. This message provides the complete received data avoid a copy operations.
 * The message structure is a variable-sized structure, where the @p data field serves as a placeholder for the complete payload (which is stored in memory following the structure after a gap of @p gap octets).
 * Therefore, individual data octets at index @em i can be accessed via <code>hidMessageIndPointer->data[gap + i]</code>.
 * This memory is given into shared ownership with the application, which it must release via [HIDMessageConf](@ref blueAPI_HIDMessageConf).
 * Note that this message must always be communicated via reference, as a struct copy operation would discard the variable-sized data and data access via a copied structure may cause a memory access violation.
 * On reception of this message, the BlueAPI application shall respond with a matching [HIDMessageConf](@ref blueAPI_HIDMessageConf).
 * If the HID host command requests information (e.g., "GetReport"), the application shall provide that information in a following [HIDMessageReq](@ref blueAPI_HIDMessageReq), indicating the corresponding
 * command via the @p hidMsgHeader.
 * The application may delay the response to apply flow control. Until the application responds, the HIDMessageInd is considered pending and flow control constraints (upstream credits) for the link apply.
 * @attention Not sending a corresponding HIDMessageConf causes a loss of upstream credits and can lead to reduced performance or complete loss of communication
 * @attention Only the memory starting at <code>&data[gap]</code> with length @p payloadLength is shared with the application. For message itself, constraints of the reception mechanism still apply */
typedef struct
{
    TBlueAPIAppHandle appHandle;        /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;              /**< Local MDL ID of the HID/HoGP link the data has been received on */
    TBlueAPI_HIDMsgHeader hidMsgHeader; /**< HID message header identifying an HID operation */
    uint16_t payloadLength;             /**< Size of the payload data starting at <code>&data[gap]</code> */
    uint16_t gap;                       /**< Index of the first octet of payload data in the variable-sized array @p data */
    uint8_t data[1];                    /**< Placeholder for accessing the payload data stored in memory following the message structure */
} TBlueAPI_HIDMessageInd, * PBlueAPI_HIDMessageInd;
#endif /* (F_BLUE_API_HID_SUPPORT) */

#if (F_BLUE_API_OBEX_SUPPORT)
/** @bookmark{RegOBEXMDEPRsp} */
/** Response to a previous [RegOBEXMDEPReq](@ref blueAPI_RegOBEXMDEPReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t MDEP_ID;
    TBlueAPI_MDEPDataType  MDEP_DataType;
    uint16_t MDEP_EntryHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_RegOBEXMDEPRsp, * PBlueAPI_RegOBEXMDEPRsp;
#endif /* (F_BLUE_API_OBEX_SUPPORT) */

#if (F_BLUE_API_L2CAP_SUPPORT)
/** @bookmark{RegL2CAPMDEPRsp} */
/** Response to a previous [RegL2CAPMDEPReq](@ref blueAPI_RegL2CAPMDEPReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t MDEP_PSM;
    uint16_t MDEP_EntryHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_RegL2CAPMDEPRsp, * PBlueAPI_RegL2CAPMDEPRsp;
#endif/* (F_BLUE_API_L2CAP_SUPPORT) */

/** @bookmark{RelMDEPRsp} */
/** Response to a previous [RelMDEPReq](@ref blueAPI_RelMDEPReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t MDEP_EntryHandle;   /**< @p MDEP_EntryHandle parameter of the corresponding request */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The specified endpoint has been released successfully
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored</table> */
} TBlueAPI_RelMDEPRsp, * PBlueAPI_RelMDEPRsp;

#if (F_BLUE_API_GATT_SUPPORT)
#if (F_BT_GATT_SERVER)
/** @bookmark{GATTServiceRegisterRsp} */
/** Response to a previous [GATTServiceRegisterReq](@ref blueAPI_GATTServiceRegisterReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    void * serviceHandle;        /**< Handle for the GATT service that identifies it in following messages. Shall be ignored if @p cause is not ::blueAPI_CauseSuccess */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The service has been registered / activated successfully
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                             <tr><td> ::blueAPI_CauseResourceError    <td> The service could not be registered due to lack of resources</table> */
    uint16_t subCause;           /**< More detailed result information from lower protocol layers. Can be ignored unless stored in trace output */
    uint16_t startHandle;        /**< If @p cause is ::blueAPI_CauseSuccess, ATT layer handle assigned to the first attribute in the the service definition array referenced by
                                      the @p pService parameter of the corresponding request. The application may use this value to derive the real ATT layer handle of an attribute index as follows:
                                      <code>attHandle = startHandle + attribIndex</code>. Otherwise, shall be ignored */
} TBlueAPI_GATTServiceRegisterRsp, * PBlueAPI_GATTServiceRegisterRsp;

/** @bookmark{GATTAttributeUpdateRsp} */
/** Response to a previous [GATTAttributeUpdateReq](@ref blueAPI_GATTAttributeUpdateReq).
 * The message structure is a variable-sized structure, where the @p list field serves as a placeholder for a larger list structure (which is stored in memory following the structure after a gap of @p gap octets).
 * Therefore, individual list structure octets at index @em i can be accessed via <code>gattAttributeUpdateRspPointer->list[gap + i]</code>.
 * Note that this message must always be communicated via reference, as a struct copy operation would discard the variable-sized data and data access via a copied structure may cause a memory access violation.
 * @attention No additional memory ownership is given to the application. Constraints of the reception mechanism also apply for the list structure */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    void * serviceHandle;        /**< @p serviceHandle parameter of the corresponding request */
    void * requestHandle;        /**< @p requestHandle parameter of the corresponding request */
    uint16_t attribIndex;        /**< @p attribIndex parameter of the corresponding request */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The operation completed successfully and a notification has been transmitted
                                                                                           @attention ::blueAPI_CauseSuccess can only be returned when a connected GATT client has configured the CCCD for the
                                                                                                      attribute for notifications
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                             <tr><td> ::blueAPI_CauseInvalidState     <td> The current state of BlueCode+ does not permit this operation
                                             <tr><td> ::blueAPI_CauseResourceError    <td> The operation could not be performed due to lack of resources
                                             <tr><td> ::blueAPI_CauseReject           <td> Indicates that the requested characteristic value cannot be notified or indicated (e.g., the CCCD bits are not set)
                                             <tr><td> ::blueAPI_CauseAccept           <td> If @p subCause is:
                                                                                           <table><tr><td> ::blueAPI_GATT_ERR_NOTIF_IND_CONF_PD <td> An indication has been generated, and the peer devices confirmation is pending. The application
                                                                                                                                                     will receive a [GATTAttributeUpdateStatusInd](@ref TBlueAPI_GATTAttributeUpdateStatusInd) with the result
                                                                                                  <tr><td> ::blueAPI_GATT_ERR_NOTIF_IND_CFG     <td> No connection exists and the list structure contains a list of peer devices that have configured the CCCD
                                                                                                                                                     for notifications or indications. The application may decide to start LE advertising so that these clients
                                                                                                                                                     can connect. On connection, the application should send a new [GATTAttributeUpdateReq](@ref blueAPI_GATTAttributeUpdateReq) </table> */
    uint16_t subCause;           /**< More detailed status information from lower layers. May match values of #TBlueAPI_ATTSubcause or #TBlueAPI_GATTSubcause */
    uint16_t count;              /**< Number of Bluetooth address elements in @p list. Zero if an active connection exists. Shall be ignored if @p cause is not ::blueAPI_CauseSuccess */
    uint16_t gap;                /**< Index of the first octet of the list structure in the variable-sized array @p list */
    uint8_t list[1];             /**< Placeholder for accessing the list structure stored in memory following the message structure.
                                      The list structure is a gap-less sequence of entries, where each entry is a gap-less structure matching the following format:
                                      <table><tr><th> Type       <th> Name           <th> Description
                                             <tr><td> uint8_t[6] <td> remote_BD      <td> Bluetooth device address of a remote device
                                             <tr><td> uint8_t    <td> remote_BD_Type <td> Bluetooth device address type of @p remote_BD</table>
                                      Each entry identifies a peer device that has configured the corresponding Client Characteristic Configuration Descriptor attribute for notifications or indications,
                                      but is currently not connected */
} TBlueAPI_GATTAttributeUpdateRsp, * PBlueAPI_GATTAttributeUpdateRsp;

/** @bookmark{GATTAttributeUpdateStatusInd} */
/** Message that indicates the status of a GATT indication that BlueCode+ has attempted to transmit as a consequence of a previous [GATTAttributeUpdateReq](@ref blueAPI_GATTAttributeUpdateReq).
 * On reception of this message, the BlueAPI application shall respond with a matching GATTAttributeUpdateStatusConf](@ref blueAPI_GATTAttributeUpdateStatusConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    void * serviceHandle;                 /**< Handle of the GATT service containing the attribute */
    void * requestHandle;                 /**< @p requestHandle parameter of the corresponding [GATTAttributeUpdateReq](@ref blueAPI_GATTAttributeUpdateReq) */
    uint16_t attribIndex;                 /**< Index of the attribute in the service descriptor array */
    TBlueAPI_Cause cause;                 /**< <table><tr><td> ::blueAPI_CauseSuccess         <td> The operation completed successfully
                                                      <tr><td> ::blueAPI_CauseLowerLayerError <td> The operation failed due to a lower layer error specified by @p subCase </table> */
    uint16_t subCause;                    /**< More detailed status information from lower layers. May match values of #TBlueAPI_ATTSubcause or #TBlueAPI_GATTSubcause */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< Bluetooth device address of the peer device the indication is sent to */
    TBlueAPI_RemoteBDType remote_BD_Type; /**< Bluetooth device address type of @p remote_BD */
} TBlueAPI_GATTAttributeUpdateStatusInd, * PBlueAPI_GATTAttributeUpdateStatusInd;

/** @bookmark{GATTAttributeReadInd} */
/** Message that indicates an incoming read operation for a GATT attribute whose descriptor contains the Flags bit VALUE_APPL set to 1 (meaning that the application is responsible for providing all data).
 * On reception of this message, the BlueAPI application shall respond with a matching [GATTAttributeReadConf](@ref blueAPI_GATTAttributeReadConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the GATT link */
    void * serviceHandle;        /**< Handle of the GATT service containing the attribute */
    uint16_t attribIndex;        /**< Index of the attribute in the service descriptor array */
    uint16_t readOffset;         /**< Read offset within the attribute value */
} TBlueAPI_GATTAttributeReadInd, * PBlueAPI_GATTAttributeReadInd;

/** @bookmark{GATTAttributeWriteInd} */
/** Message that indicates an incoming write operation for a GATT attribute whose descriptor contains the Flags bit VALUE_APPL set to 1 (meaning that the application is responsible for storing all data).
 * The message structure is a variable-sized structure, where the @p data field serves as a placeholder for larger attribute write data (which is stored in memory following the structure after a gap of @p gap octets).
 * Therefore, individual attribute write data octets at index @em i can be accessed via <code>gattAttributeWriteIndPointer->data[gap + i]</code>.
 * Note that this message must always be communicated via reference, as a struct copy operation would discard the variable-sized data and data access via a copied structure may cause a memory access violation.
 * On reception of this message, the BlueAPI application shall respond with a matching [GATTAttributeWriteConf](@ref blueAPI_GATTAttributeWriteConf).
 * @attention No additional memory ownership is given to the application. Constraints of the reception mechanism also apply for the list structure */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the GATT link */
    void * serviceHandle;        /**< Handle of the GATT service containing the attribute */
    uint16_t attribIndex;        /**< Index of the attribute in the service descriptor array */
    uint16_t attribLength;       /**< Length of the attribute value in @p data */
    uint16_t writeOffset;        /**< Shall be ignored (reserved for future use) */
    uint16_t gap;                /**< Index of the first octet of attribute write data in the variable-sized array @p data */
    uint8_t data[1];             /**< Placeholder for accessing the attribute write data stored in memory following the message structure */
} TBlueAPI_GATTAttributeWriteInd, * PBlueAPI_GATTAttributeWriteInd;

/** Message identical to [GATTAttributeWriteInd](@ref TBlueAPI_GATTAttributeWriteInd), with the exception that the application shall not respond to the message. */
typedef TBlueAPI_GATTAttributeWriteInd TBlueAPI_GATTAttributeWriteCommandInfo, * PBlueAPI_GATTAttributeWriteCommandInfo;

#if (F_BT_ATT_PREP_EXEC_WRITE)
#error "Missing documentation here"
typedef TBlueAPI_GATTAttributeWriteInd TBlueAPI_GATTAttributePrepareWriteInd, * PBlueAPI_GATTAttributePrepareWriteInd;

typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;
    uint8_t flags;
} TBlueAPI_GATTExecuteWriteInd, * PBlueAPI_GATTExecuteWriteInd;
#endif /* (F_BT_ATT_PREP_EXEC_WRITE) */

/** @bookmark{GATTCCCDInfo} */
/** Message that provides information about the current value of one or more Client Characteristic Confirmation Descriptors (CCCDs) whose descriptors contain the Flags bit CCCD_APPL set to 1
 * (meaning that this message will be issued when the connection is established or whenever the value of such a CCCD changes during a connection).
 * It may be issued zero or multiple times, depending on the number of CCCDs affected. Note that each message comprises one or more CCCD attribute index-value pairs.
 * The message structure is a variable-sized structure, where the @p data field serves as a placeholder for a larger table structure (which is stored in memory following the structure after a gap of @p gap octets).
 * Therefore, individual table structure octets at index @em i can be accessed via <code>gattCCCDInfoPointer->data[gap + i]</code>.
 * Note that this message must always be communicated via reference, as a struct copy operation would discard the variable-sized data and data access via a copied structure may cause a memory access violation. */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the GATT link */
    void * serviceHandle;        /**< Handle of the GATT service containing the CCCDs */
    uint16_t count;              /**< Number of table rows in @p data */
    uint16_t gap;                /**< Index of the first octet of the table structure in the variable-sized array @p data */
    uint8_t data[1];             /**< Placeholder for accessing the table structure stored in memory following the message structure.
                                      The table structure is a gap-less sequence of table rows, where each row is a gap-less structure matching the following format:
                                      <table><tr><th> Type     <th> Name        <th> Description
                                             <tr><td> uint16_t <td> attribIndex <td> Index of the CCCD attribute in the service descriptor array
                                             <tr><td> uint16_t <td> cccBits     <td> The current CCCD value</table> */
} TBlueAPI_GATTCCCDInfo, * PBlueAPI_GATTCCCDInfo;

/** @bookmark{GATTServerStoreInd} */
/** Message that indicates a read or write access to persistent GATT information stored by the application. This message will only be issued when the current BlueCode+ configuration specifies
 * that the application is responsible for storing the bonding information (::blueAPI_StoreBondModeExtStore). There are two kinds of GATT information stored via this mechanism:
 * CCC Bit Blobs and Service Changed Handles/Flags.
 * On reception of this message, the BlueAPI application shall respond with a matching [GATTServerStoreConf](@ref blueAPI_GATTServerStoreConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_GATTStoreOpCode opCode;      /**< Type of storage access. See #TBlueAPI_GATTStoreOpCode for possible values */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< If @p opCode indicates individual access, Bluetooth device address of the peer device that persistent GATT information shall be accessed for.
                                               Otherwise, contents shall be ignored, only used for issuing a response */
    TBlueAPI_RemoteBDType remote_BD_Type; /**< If @p opCode indicates individual access, Bluetooth device address type of @p remote_BD. Otherwise, contents shall be ignored, only used for issuing a response */
    uint16_t restartHandle;               /**< If @p opCode is ::blueAPI_GATTStoreOpGetAllCCCBits, @p restartHandle parameter of the last [GATTServerStoreConf](@ref blueAPI_GATTServerStoreConf) that is part
                                               of the same operation, or 0 if this is the first message of the operation. Otherwise, shall be ignored */
    uint8_t dataLength;                   /**< If @p opCode indicates write access, length of @p data. Otherwise, shall be ignored */
    uint8_t data[32];                     /**< If @p opCode indicates write access, data to store. Otherwise, shall be ignored */
} TBlueAPI_GATTServerStoreInd, * PBlueAPI_GATTServerStoreInd;
#endif /* (F_BT_GATT_SERVER) */

#if (F_BT_GATT_CLIENT)
/** @bookmark{GATTDiscoveryRsp} */
/** Response to a previous [GATTDiscoveryReq](@ref blueAPI_GATTDiscoveryReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;              /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;                    /**< @p local_MDL_ID parameter of the corresponding request */
    TBlueAPI_GATTDiscoveryType discoveryType; /**< @p discoveryType parameter of the corresponding request */
    TBlueAPI_Cause cause;                     /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The discovery operation has been started successfully
                                                          <tr><td> ::blueAPI_CauseInvalidState     <td> The current state of BlueCode+ does not permit this operation (e.g., another discovery operation in progress)
                                                          <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                                          <tr><td> ::blueAPI_CauseResourceError    <td> The discovery operation could not be started due to resource constraints */
    uint16_t subCause;                        /**< More detailed status information from lower layers. May match values of #TBlueAPI_ATTSubcause or #TBlueAPI_GATTSubcause */
} TBlueAPI_GATTDiscoveryRsp, * PBlueAPI_GATTDiscoveryRsp;

/** @bookmark{GATTDiscoveryInd} */
/** Message that indicates a partial discovery result during any GATT discovery operation. The application can continue or terminate the discovery operation.
 * The message structure is a variable-sized structure, where the @p list field serves as a placeholder for larger table structure (which is stored in memory following the structure after a gap of @p gap octets).
 * Therefore, individual table structure octets at index @em i can be accessed via <code>gattDiscoveryIndPointer->list[gap + i]</code>.
 * Note that this message must always be communicated via reference, as a struct copy operation would discard the variable-sized data and data access via a copied structure may cause a memory access violation.
 * On reception of this message, the BlueAPI application shall respond with a matching [GATTDiscoveryConf](@ref blueAPI_GATTDiscoveryConf).
 * @attention No additional memory ownership is given to the application. Constraints of the reception mechanism also apply for the list structure */
typedef struct
{
    TBlueAPIAppHandle appHandle;              /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;                    /**< Local MDL ID of the GATT link */
    TBlueAPI_GATTDiscoveryType discoveryType; /**< Type of GATT discovery. See #TBlueAPI_GATTDiscoveryType for possible values */
    TBlueAPI_Cause cause;                     /**< <table><tr><td> ::blueAPI_CauseSuccess         <td> The discovery operation has been performed successfully
                                                          <tr><td> ::blueAPI_CauseLowerLayerError <td> The underlying ATT layer encountered an error, details can be derived from the value of @p subCause
                                                          <tr><td> ::blueAPI_CauseInitTimeout     <td> A timeout for an ATT transaction or GATT procedure expired</table> */
    uint16_t subCause;                        /**< More detailed status information from lower layers. May match values of #TBlueAPI_ATTSubcause or #TBlueAPI_GATTSubcause.
                                                   If ::blueAPI_ATT_ERR_ATTR_NOT_FOUND, indicates the completion of the discovery operation (no GATT structures in the remaining search range) */
    uint16_t elementCount;                    /**< Number of table rows in the table structure in @p list */
    uint16_t elementLength;                   /**< Size of a single table row in @p list, in octets.
                                                   Note that for some types of GATT discovery, multiple variants of table structures exist, which can be distinguished by this value */
    uint16_t gap;                             /**< Index of the first octet of the table structure in the variable-sized array @p list */
    uint8_t list[1];                          /**< Placeholder for accessing the table structure stored in memory following the message structure.
                                                   The table structure is a gap-less sequence of table rows, where each row is a gap-less structure matching one of the following formats,
                                                   according to the GATT discovery type:
<table><tr><th> @p discoveryType                         <th> Structure
       <tr><td> ::blueAPI_GATTDiscoveryServices          <td> <table><tr><th> Type     <th> Name           <th> Description
                                                                     <tr><td> uint16_t <td> attHandle      <td> Start handle of a discovered service
                                                                     <tr><td> uint16_t <td> endGroupHandle <td> End handle of the service
                                                                     <tr><td> uint16_t <td> UUID16         <td> 16-bit UUID of the service</table>
                                                              or
                                                              <table><tr><th> Type        <th> Name           <th> Description
                                                                     <tr><td> uint16_t    <td> attHandle      <td> Start handle of a discovered service
                                                                     <tr><td> uint16_t    <td> endGroupHandle <td> End handle of the service
                                                                     <tr><td> uint8_t[16] <td> UUID128        <td> 128-bit UUID of the service</table>
       <tr><td> ::blueAPI_GATTDiscoveryServiceByUUID     <td> <table><tr><th> Type     <th> Name           <th> Description
                                                                     <tr><td> uint16_t <td> attHandle      <td> Start handle of a discovered service
                                                                     <tr><td> uint16_t <td> endGroupHandle <td> End handle of the service</table>
       <tr><td> ::blueAPI_GATTDiscoveryCharacteristics   <td> <table><tr><th> Type     <th> Name        <th> Description
                                                                     <tr><td> uint16_t <td> declHandle  <td> Handle of a discovered characteristic's declaration
                                                                     <tr><td> uint16_t <td> properties  <td> Bits 0 to 7: The characteristic's properties, see:
                                                                                                             @btspec{5.0,3,G,3.3.1.1,Characteristic Properties}
                                                                                                             Other bits shall be ignored (reserved for future use)
                                                                     <tr><td> uint16_t <td> valueHandle <td> Handle of the value of the characteristic
                                                                     <tr><td> uint16_t <td> UUID16      <td> 16-bit UUID of the characteristic</table>
                                                              or
                                                              <table><tr><th> Type        <th> Name        <th> Description
                                                                     <tr><td> uint16_t    <td> declHandle  <td> Handle of a discovered characteristic's declaration
                                                                     <tr><td> uint16_t    <td> properties  <td> Bits 0 to 7: The characteristic's properties, see:
                                                                                                             @btspec{5.0,3,G,3.3.1.1,Characteristic Properties}
                                                                                                             Other bits shall be ignored (reserved for future use)
                                                                     <tr><td> uint16_t    <td> valueHandle <td> Handle of the value of the characteristic
                                                                     <tr><td> uint8_t[16] <td> UUID128     <td> 128-bit UUID of the characteristic</table>
       <tr><td> ::blueAPI_GATTDiscoveryCharacDescriptors <td> <table><tr><th> Type     <th> Name   <th> Description
                                                                     <tr><td> uint16_t <td> handle <td> Handle of a discovered characteristic descriptor
                                                                     <tr><td> uint16_t <td> UUID16 <td> 16-bit UUID of the characteristic descriptor</table>
                                                              or
                                                              <table><tr><th> Type        <th> Name    <th> Description
                                                                     <tr><td> uint16_t    <td> handle  <td> Handle of a discovered characteristic descriptor
                                                                     <tr><td> uint8_t[16] <td> UUID128 <td> 128-bit UUID of the characteristic descriptor</table>
       <tr><td> ::blueAPI_GATTDiscoveryRelationship      <td> <table><tr><th> Type     <th> Name           <th> Description
                                                                     <tr><td> uint16_t <td> declHandle     <td> Handle of an include declaration,see:
                                                                                                                @btspec{5.0,3,G,3.2,Include Definition}
                                                                     <tr><td> uint16_t <td> attHandle      <td> Start handle of the included service
                                                                     <tr><td> uint16_t <td> endGroupHandle <td> End handle of the included service
                                                                     <tr><td> uint16_t <td> UUID16         <td> 16-bit UUID of the included service</table>
                                                              or
                                                              <table><tr><th> Type     <th> Name           <th> Description
                                                                     <tr><td> uint16_t <td> declHandle     <td> Handle of an include declaration,see:
                                                                                                                @btspec{5.0,3,G,3.2,Include Definition}
                                                                     <tr><td> uint16_t <td> attHandle      <td> Start handle of the included service
                                                                     <tr><td> uint16_t <td> endGroupHandle <td> End handle of the included service
                                                                     <tr><td> uint16_t <td> UUID128        <td> Shall be ignored, see note below</table>
                                                              @attention The @p UUID128 element in the above table is currently not assigned to the 128-bit UUID of the included service,
                                                                         due to an ATT layer limitation. It is kept in for consistency and reserved for future use. The application can retrieve the actual
                                                                         128-bit UUID via a [GATTAttributeReadReq](@ref blueAPI_GATTAttributeReadReq) with the @p readType parameter set to
                                                                         ::blueAPI_GATTReadTypeBasic and the @p startHandle parameter set to the @p attHandle value from the above table.
                                                                         If successful, the returned attribute  will be the 128-bit UUID of the included service. </table> */
} TBlueAPI_GATTDiscoveryInd, * PBlueAPI_GATTDiscoveryInd;

/** @bookmark{GATTAttributeReadRsp} */
/** Response to a previous [GATTAttributeReadReq](@ref blueAPI_GATTAttributeReadReq).
 * The message structure is a variable-sized structure, where the @p handlesData field serves as a placeholder for larger table structure (which is stored in memory following the structure after a gap of @p gap octets).
 * Therefore, individual table structure octets at index @em i can be accessed via <code>gattAttributeReadRspPointer->handlesData[gap + i]</code>.
 * Note that this message must always be communicated via reference, as a struct copy operation would discard the variable-sized data and data access via a copied structure may cause a memory access violation.
 * @attention No additional memory ownership is given to the application. Constraints of the reception mechanism also apply for the list structure*/
typedef struct
{
    TBlueAPIAppHandle appHandle;    /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;          /**< @p local_MDL_ID parameter of the corresponding request */
    TBlueAPI_GATTReadType readType; /**< @p readType parameter of the corresponding request */
    TBlueAPI_Cause cause;           /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The read operation has been performed successfully
                                                <tr><td> ::blueAPI_CauseInvalidState     <td> The current state of BlueCode+ does not permit this operation
                                                <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                                <tr><td> ::blueAPI_CauseResourceError    <td> The read operation could not be performed due to resource constraints
                                                <tr><td> ::blueAPI_CauseLowerLayerError  <td> The underlying ATT layer encountered an error, details can be derived from the value of @p subCause
                                                <tr><td> ::blueAPI_CauseInitTimeout      <td> A timeout for an ATT transaction or GATT procedure expired
                                                <tr><td> ::blueAPI_CauseNotSupported     <td> The requested operation is not supported by the implementation</table> */
    uint16_t subCause;              /**< More detailed status information from lower layers. May match values of #TBlueAPI_ATTSubcause or #TBlueAPI_GATTSubcause */
    uint16_t readOffset;            /**< @p readOffset parameter of the corresponding request */
    uint16_t totalLength;           /**< Total size of the table structure in @p handlesData, in octets */
    uint16_t attribLength;          /**< Size of a single table row in @p handlesData */
    uint16_t nbrOfHandles;          /**< Number of table rows in @p handlesData, i.e., the number of attribute values read. If @p readType is ::blueAPI_GATTReadTypeBasic, the value is 1 */
    uint16_t gap;                   /**< Index of the first octet of the table structure in the variable-sized array @p handlesData */
    uint8_t handlesData[1];         /**< Placeholder for accessing the table structure stored in memory following the message structure.
                                         The table structure is a gap-less sequence of table rows, where each row is a gap-less structure matching the following format:
                                         <table><tr><th> Type                                        <th> Name   <th> Description
                                                <tr><td> uint16_t                                    <td> handle <td> Handle of the read attribute
                                                <tr><td> uint8_t[@p attribLength - sizeof(uint16_t)] <td> value  <td> Value of the attribute</table>
                                         Each row represents a single read attribute */
} TBlueAPI_GATTAttributeReadRsp, * PBlueAPI_GATTAttributeReadRsp;

/** @bookmark{GATTAttributeWriteRsp} */
/** Response to a previous [GATTAttributeWriteReq](@ref blueAPI_GATTAttributeWriteReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;      /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;            /**< @p local_MDL_ID parameter of the corresponding request */
    TBlueAPI_GATTWriteType writeType; /**< @p writeType parameter of the corresponding request */
    TBlueAPI_Cause cause;             /** <table><tr><td> ::blueAPI_CauseSuccess          <td> The write operation has been performed successfully
                                                 <tr><td> ::blueAPI_CauseInvalidState     <td> The current state of BlueCode+ does not permit this operation
                                                 <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                                 <tr><td> ::blueAPI_CauseLowerLayerError  <td> The underlying ATT layer encountered an error, details can be derived from the value of @p subCause
                                                 <tr><td> ::blueAPI_CauseInitTimeout      <td> A timeout for an ATT transaction or GATT procedure expired
                                                 <tr><td> ::blueAPI_CauseNotSupported     <td> The requested operation is not supported by the implementation</table> */
    uint16_t subCause;                /**< More detailed status information from lower layers. May match values of #TBlueAPI_ATTSubcause or #TBlueAPI_GATTSubcause */
    uint16_t attribLength;            /**< Shall be ignored (reserved for future use) */
    uint16_t gap;                     /**< Shall be ignored (reserved for future use) */
    uint8_t data[1];                  /**< Shall be ignored (reserved for future use) */
} TBlueAPI_GATTAttributeWriteRsp, * PBlueAPI_GATTAttributeWriteRsp;

#if (F_BT_ATT_PREP_EXEC_WRITE)
#error "Missing documentation here"
/** @bookmark{GATTExecuteWriteRsp} */
/** Response to a previous [GATTExecuteWriteReq](@ref blueAPI_GATTExecuteWriteReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;
    TBlueAPI_Cause cause;
    uint16_t subCause;
    /* XXXXMJMJ currently not used: */
    uint16_t attribHandle;
} TBlueAPI_GATTExecuteWriteRsp, * PBlueAPI_GATTExecuteWriteRsp;
#endif /* (F_BT_ATT_PREP_EXEC_WRITE) */

/** @bookmark{GATTAttributeInd} */
/** Message that indicates the reception of a GATT indication.
 * The message structure is a variable-sized structure, where the @p data field serves as a placeholder for a larger attribute value (which is stored in memory following the structure after a gap of @p gap octets).
 * Therefore, individual attribute value octets at index @em i can be accessed via <code>gattAttributeIndPointer->data[gap + i]</code>.
 * Note that this message must always be communicated via reference, as a struct copy operation would discard the variable-sized data and data access via a copied structure may cause a memory access violation.
 * On reception of this message, the BlueAPI application shall respond with a matching [GATTAttributeConf](@ref blueAPI_GATTAttributeConf).
 * @attention No additional memory ownership is given to the application. Constraints of the reception mechanism also apply for the list structure */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the GATT link */
    uint16_t attribHandle;       /**< Handle of the indicated attribute */
    uint16_t attribLength;       /**< Length of the attribute value in @p data */
    uint16_t gap;                /**< Index of the first octet of the attribute value in the variable-sized array @p list */
    uint8_t data[1];             /**< Placeholder for accessing the attribute value stored in memory following the message structure */
} TBlueAPI_GATTAttributeInd, * PBlueAPI_GATTAttributeInd;

/** Message identical to [GATTAttributeInd](@ref TBlueAPI_GATTAttributeInd), with the exception that the application shall not respond to the message.
 * Instead of a GATT indication, it represents a GATT notification */
typedef TBlueAPI_GATTAttributeInd TBlueAPI_GATTAttributeNotificationInfo, * PBlueAPI_GATTAttributeNotificationInfo;

#if (F_BLUE_API_GATT_SDP_DIS_SUPPORT)
#error "Missing documentation here"
/** Response to a previous [GATTSDPDiscoveryReq](@ref blueAPI_GATTSDPDiscoveryReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;
} TBlueAPI_GATTSDPDiscoveryRsp;
typedef TBlueAPI_GATTSDPDiscoveryRsp * PBlueAPI_GATTSDPDiscoveryRsp;

typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint32_t serviceHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    uint16_t remote_GATT_UUID;
    uint16_t remote_GATT_StartHandle;
    uint16_t remote_GATT_EndHandle;
} TBlueAPI_GATTSDPDiscoveryInd;
typedef TBlueAPI_GATTSDPDiscoveryInd * PBlueAPI_GATTSDPDiscoveryInd;
#endif /* (F_BLUE_API_GATT_SDP_DIS_SUPPORT) */
#endif /* (F_BT_GATT_CLIENT) */

/** Response to a previous [GATTSecurityReq](@ref blueAPI_GATTSecurityReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;   /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;         /**< @p local_MDL_ID parameter of the corresponding request */
    TBlueAPI_LinkKeyType keyType;  /**< If successful, key type of the generated link key. Otherwise, shall be ignored. See #TBlueAPI_LinkKeyType for possible values */
    uint8_t keySize;               /**< If successful, length of the generated link key. Otherwise, shall be ignored. In range \[7, 16] */
    TBlueAPI_Cause cause;          /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The security level has been updated successfully
                                               <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored, or the authentication code was invalid
                                               <tr><td> ::blueAPI_CauseReject           <td> The remote device rejected the authentication attempt
                                               <tr><td> ::blueAPI_CauseConnectionLost   <td> The required data exchange failed (e.g., the remote device is out of range)</table> */
} TBlueAPI_GATTSecurityRsp, * PBlueAPI_GATTSecurityRsp;

/** @bookmark{GATTMtuSizeInfo} */
/** Message that provides information about an MTU size change on a GATT link. The reception of this message indicates the application must adapt to the new segment size,
 * see the documentation of the @p maxTPDUSize parameter of [ConnectMDLInfo](@ref TBlueAPI_ConnectMDLInfo) */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the GATT link */
    uint16_t mtuSize;            /**< New ATT layer MTU size / link data segment size */
} TBlueAPI_GATTMtuSizeInfo, * PBlueAPI_GATTMtuSizeInfo;
#endif /* (F_BLUE_API_GATT_SUPPORT) */

/** @bookmark{InquiryRsp} */
/** Response to a previous [InquiryReq](@ref blueAPI_InquiryReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    bool cancelInquiry;          /**< @p cancelInquiry parameter of the corresponding request */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess      <td> The inquiry procedure has completed successfully
                                             <tr><td> ::blueAPI_CauseInvalidState <td> If @p cancelInquiry is true: There was no active inquiry procedure to cancel.
                                                                                       If @p cancelInquiry is false: The current state of BlueCode+ does not permit a new inquiry procedure (e.g., during discovery operations)</table> */
} TBlueAPI_InquiryRsp, * PBlueAPI_InquiryRsp;

/** @bookmark{InquiryDeviceInfo} */
/** Message that provides information about a single remote device found during an inquiry procedure started via [InquiryReq](@ref blueAPI_InquiryReq).
 * It may be issued zero or multiple times, depending on the amount of remote devices found. */
typedef struct
{
    TBlueAPIAppHandle appHandle;                             /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];                     /**< Bluetooth device address of the remote device */
    uint32_t remote_Device_Class;                            /**< Class of Device identifier (CoD) of the remote device.
                                                                  For more details, see the @p classOfDevice parameter of [DeviceConfigDeviceSetReq](@ref blueAPI_DeviceConfigDeviceSetReq) and:
                                                                  @btasgn{baseband,Baseband,The Class of Device/Service Field} */
    int8_t remote_RSSI;                                      /**< Current Received Signal Strength Indication (RSSI) value of the remote device. The range of indicated values will vary, usually a range of \[-100, 10] might be expected.
                                                                  @attention Bluetooth supports signal strength control mechanisms, so this indicator can not be seen as an absolute reference
                                                                  to the distance of a given remote device */
    uint8_t remote_Device_Name[BLUE_API_DEVICE_NAME_LENGTH]; /**< User-friendly name of the remote device. Zero-terminated. This field may be empty */
} TBlueAPI_InquiryDeviceInfo, * PBlueAPI_InquiryDeviceInfo;

/** @bookmark{DeviceNameRsp} */
/** Response to a previous [DeviceNameReq](@ref blueAPI_DeviceNameReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;                             /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];                     /**< Bluetooth device address of the remote device */
    uint8_t remote_Device_Name[BLUE_API_DEVICE_NAME_LENGTH]; /**< User-friendly name of the remote device. Zero-terminated. This field may be empty. Shall be ignored if @p cause is not ::blueAPI_CauseSuccess */
    TBlueAPI_Cause cause;                                    /**< <table><tr><td> ::blueAPI_CauseSuccess        <td> The operation has completed successfully
                                                                         <tr><td> ::blueAPI_CauseConnectionLost <td> The required data exchange failed (e.g., the remote device is out of range)
                                                                         <tr><td> ::blueAPI_CauseInvalidState   <td> The current state of BlueCode+ does not permit this operation (e.g., during discovery operations)</table> */
} TBlueAPI_DeviceNameRsp, * PBlueAPI_DeviceNameRsp;

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing documentation here"
/** @bookmark{HDPDiscoveryRsp} */
/** Response to a previous [HDPDiscoveryReq](@ref blueAPI_HDPDiscoveryReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;
} TBlueAPI_HDPDiscoveryRsp, * PBlueAPI_HDPDiscoveryRsp;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

/** @bookmark{DIDDeviceInd} */
/** Message that indicates the discovery of DIP (Device ID Profile) information on a Bluetooth Classic remote device, during a discovery procedure started via [SPPDiscoveryReq](@ref blueAPI_SPPDiscoveryReq)
 * with the @p remote_DID_Discovery parameter set to true.
 * On reception of this message, the BlueAPI application shall respond with a matching [DIDDeviceConf](@ref blueAPI_DIDDeviceConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle;                             /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint32_t serviceHandle;                                  /**< Service handle to identify the device service. Shall be used as a parameter of the matching confirmation message */
    uint8_t remote_BD[BLUE_API_BD_SIZE];                     /**< Bluetooth device address of the remote device */
    uint16_t remote_VendorID;                                /**< Vendor ID of the remote device within the ID space defined by @p remote_VendorID_Source. For more details, see:
                                                                  @btasgn{company-identifiers,Company Identifiers} */
    uint16_t remote_VendorID_Source;                         /**< <table><tr><td> 0x01 <td> The vendor ID has been assigned by the Bluetooth SIG
                                                                         <tr><td> 0x02 <td> The vendor ID has been assigned by the USB Implementer's Forum</table> */
    uint16_t remote_ProductID;                               /**< Vendor-specific Product ID of the remote device */
    uint16_t remote_Version;                                 /**< Vendor-specific Product Version of the remote device */
    uint8_t remote_Device_Name[BLUE_API_DEVICE_NAME_LENGTH]; /**< User-friendly name of the remote device. UTF-8 formatted and zero-terminated */
} TBlueAPI_DIDDeviceInd, * PBlueAPI_DIDDeviceInd;

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing documentation here"
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint32_t serviceHandle;
    uint16_t remote_Control_PSM;
    uint16_t remote_Data_PSM;
    uint8_t remote_Data_Format;
    uint8_t remote_MCAP_Features;
    uint8_t remote_Service_Name[BLUE_API_HDP_SERVICE_NAME_LENGTH];
} TBlueAPI_HDPServiceInd, * PBlueAPI_HDPServiceInd;

typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint32_t serviceHandle;
    uint8_t remote_MDEP_ID;
    TBlueAPI_MDEPRole     remote_MDEP_Role;
    TBlueAPI_MDEPDataType remote_MDEP_DataType;
    uint8_t remote_MDEP_Description[BLUE_API_MDEP_NAME_LENGTH];
} TBlueAPI_HDPEndpointInd, * PBlueAPI_HDPEndpointInd;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
/** @bookmark{SPPDiscoveryRsp} */
/** Response to a previous [SPPDiscoveryReq](@ref blueAPI_SPPDiscoveryReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess        <td> The SPP endpoint discovery has completed successfully
                                             <tr><td> ::blueAPI_CauseConnectionLost <td> The required data exchange failed (e.g., the remote device is out of range)
                                             <tr><td> ::blueAPI_CauseResourceError  <td> The SPP endpoint discovery failed due to lack of resources
                                             <tr><td> ::blueAPI_CauseInvalidState   <td> The current state of BlueCode+ does not permit this operation (e.g., during different operations)</table> */
} TBlueAPI_SPPDiscoveryRsp, * PBlueAPI_SPPDiscoveryRsp;

/** @bookmark{SPPEndpointInd} */
/** Message that indicates the discovery of a remote endpoint for an RFCOMM-based profile (such as SPP) or Terminal I/O, during a discovery procedure started via [SPPDiscoveryReq](@ref blueAPI_SPPDiscoveryReq).
 * On reception of this message, the BlueAPI application shall respond with a matching [SPPEndpointConf](@ref blueAPI_SPPEndpointConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle;                                /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint32_t serviceHandle;                                     /**< Service handle. Shall be used as a parameter of the matching confirmation message */
    uint8_t remote_BD[BLUE_API_BD_SIZE];                        /**< Bluetooth device address of the remote device */
    uint8_t remote_MDEP_ID;                                     /**< Endpoint identifier on the remote device. Can now be used to identify the endpoint in following messages */
    TBlueAPI_MDEPDataType remote_MDEP_DataType;                 /**< <table><tr><td> ::blueAPI_MDEPUUIDTypeTIO <td> This endpoint is a Terminal I/O endpoint
                                                                            <tr><td> any other value           <td> 16-bit UUID of the endpoint's RFCOMM-based profile.
                                                                                                                    See #TBlueAPI_MDEPDataType for possible values</table> */
    uint8_t remote_MDEP_Description[BLUE_API_MDEP_NAME_LENGTH]; /**< User-friendly name of the remote endpoint. Zero-terminated. This field may be empty */
} TBlueAPI_SPPEndpointInd, * PBlueAPI_SPPEndpointInd;
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_BLUE_API_OBEX_SUPPORT)
#error "Missing documentation here"
/** @bookmark{OBEXDiscoveryRsp} */
/** Response to a previous [OBEXDiscoveryReq](@ref blueAPI_OBEXDiscoveryReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;
} TBlueAPI_OBEXDiscoveryRsp, * PBlueAPI_OBEXDiscoveryRsp;

typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint32_t serviceHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    uint8_t remote_MDEP_ID;
    TBlueAPI_MDEPDataType   remote_MDEP_DataType;
    uint16_t remote_MDEP_OBEXDataMask;
    uint8_t remote_MDEP_Description[BLUE_API_MDEP_NAME_LENGTH];
} TBlueAPI_OBEXEndpointInd, * PBlueAPI_OBEXEndpointInd;
#endif /* (F_BLUE_API_OBEX_SUPPORT) */

#if (F_BLUE_API_HCI_TUNNEL_SUPPORT)
#error "Missing documentation here"
/** @bookmark{HCITunnelRsp} */
/** Response to a previous [HCITunnelReq](@ref blueAPI_HCITunnelReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t length;
    uint8_t hciEvent[BLUE_API_HCI_TUNNEL_DATA_LENGTH];   /* HCI event excluding H4 packet type field */
    TBlueAPI_Cause cause;
} TBlueAPI_HCITunnelRsp, * PBlueAPI_HCITunnelRsp;
#endif /* (F_BLUE_API_HCI_TUNNEL_SUPPORT) */

#if (F_BT_LOW_ENERGY)
/** @bookmark{LEAdvertiseRsp} */
/** Response to a previous [LEAdvertiseReq](@ref blueAPI_LEAdvertiseReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_LEAdvMode advMode;  /**< @p advMode parameter of the corresponding request */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess              <td> Advertising has been enabled / disabled successfully
                                             <tr><td> ::blueAPI_CauseInvalidParameter     <td> The request contained an invalid parameter and has been ignored
                                             <tr><td> ::blueAPI_CauseInvalidState         <td> The current state of BlueCode+ or the Bluetooth controller does not permit the requested mode
                                             <tr><td> ::blueAPI_CauseConnectionDisconnect <td> Only for directed advertising: Timeout expired without connection establishment
                                             <tr><td> ::blueAPI_CauseAddressNotResolved   <td> Only for directed advertising: The current resolvable private address of the remote device is not available</table> */
} TBlueAPI_LEAdvertiseRsp, * PBlueAPI_LEAdvertiseRsp;

/** @bookmark{LEAdvertiseParameterSetRsp} */
/** Response to a previous [LEAdvertiseParameterSetReq](@ref blueAPI_LEAdvertiseParameterSetReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> Advertising parameters have been updated successfully
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                             <tr><td> ::blueAPI_CauseInvalidState     <td> The current state of BlueCode+ or the Bluetooth controller does not permit this operation</table> */
} TBlueAPI_LEAdvertiseParameterSetRsp, * PBlueAPI_LEAdvertiseParameterSetRsp;

/** @bookmark{LEAdvertiseDataSetRsp} */
/** Response to a previous [LEAdvertiseDataSetReq](@ref blueAPI_LEAdvertiseDataSetReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;  /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_LEDataType dataType; /**< @p dataType of the corresponding request */
    TBlueAPI_Cause cause;         /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> Advertising data has been updated successfully
                                              <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                              <tr><td> ::blueAPI_CauseInvalidState     <td> The current state of BlueCode+ or the Bluetooth controller does not permit this operation</table> */
} TBlueAPI_LEAdvertiseDataSetRsp, * PBlueAPI_LEAdvertiseDataSetRsp;

/** @bookmark{LEScanRsp} */
/** Response to a previous [LEScanReq](@ref blueAPI_LEScanReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> Scanning has been enabled / disabled successfully
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored</table> */
} TBlueAPI_LEScanRsp, * PBlueAPI_LEScanRsp;

/** @bookmark{LEScanInfo} */
/** Message that provides information about a single advertising event, or Scan Response PDU for active scanning, received during an LE scan procedure started via [LEScanReq](@ref blueAPI_LEScanReq).
 * It may be issued zero or multiple times, depending on the amount of advertising PDUs received. */
typedef struct
{
    TBlueAPIAppHandle appHandle;          /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< Bluetooth device address of the remote device */
    TBlueAPI_RemoteBDType remote_BD_type; /**< Bluetooth device address type of @p remote_BD */
    TBlueAPI_LEAdvType advType;           /**< Type of advertising PDU that has been received. See #TBlueAPI_LEAdvType for possible values */
    int8_t rssi;                          /**< Current Received Signal Strength Indication (RSSI) value of the remote device. The range of indicated values will vary, usually a range of \[-100, 10] might be expected.
                                               @attention Bluetooth supports signal strength control mechanisms, so this indicator can not be seen as an absolute reference to the distance of a given remote device */
    uint8_t dataLength;                   /**< Length of @p data */
    uint8_t data[31];                     /**< Advertising Data / Scan Response Data contained in the PDU. The format is documented in:
                                               @btcss{7,A,"Data Types Specification} */
} TBlueAPI_LEScanInfo, * PBlueAPI_LEScanInfo;

/** @bookmark{LEModifyWhitelistRsp} */
/** Response to a previous [LEModifyWhitelistReq](@ref blueAPI_LEModifyWhitelistReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle;      /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_LEWhitelistOp operation; /**< @p operation of the corresponding request */
    TBlueAPI_Cause cause;             /**< <table><tr><td> ::blueAPI_CauseSuccess              <td> The whitelist has been modified successfully
                                                  <tr><td> ::blueAPI_CauseInvalidParameter     <td> The request contained an invalid parameter and has been ignored
                                                  <tr><td> ::blueAPI_CauseInvalidState         <td> The current state of BlueCode+ or the Bluetooth controller does not permit whitelist modification (e.g., whitelist is in use)
                                                  <tr><td> ::blueAPI_CauseAddressNotResolved   <td> The current resolvable private address of the remote device is not available</table> */
} TBlueAPI_LEModifyWhitelistRsp, * PBlueAPI_LEModifyWhitelistRsp;

/** @bookmark{LEConnectionUpdateRsp} */
/** Response to a previous [LEConnectionUpdateReq](@ref blueAPI_LEConnectionUpdateReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the LE link, matching the @p local_MDL_ID parameter of the corresponding request */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The Connection Parameter Update has been performed successfully
                                             <tr><td> ::blueAPI_CauseReject           <td> The Master has rejected the proposed connection parameters
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                             <tr><td> ::blueAPI_CauseConnectionLost   <td> The required data exchange failed (e.g., the remote device is out of range)</table> */
} TBlueAPI_LEConnectionUpdateRsp, * PBlueAPI_LEConnectionUpdateRsp;

/** @bookmark{LEConnectionUpdateInd} */
/** Message that indicates that the BLE Slave of a link where the local device is Master requested a Connection Parameter Update.
 * The recipient BlueAPI application may reject the proposed parameters
 * On reception of this message, the BlueAPI application shall respond with a matching [LEConnectionUpdateConf](@ref blueAPI_LEConnectionUpdateConf). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the LE link */
    uint16_t connIntervalMin;    /**< Proposed Minimum Connection Interval, in units of 1.25 ms. In range \[0x0006, 0x0C80] (corresponds to \[7.5 ms, 4 s]) */
    uint16_t connIntervalMax;    /**< Proposed Maximum Connection Interval, in units of 1.25 ms. In range \[@p connIntervalMin, 0x0C80] (corresponds to \[..., 4 s]) */
    uint16_t connLatency;        /**< Proposed Slave Latency, i.e., the amount of connection events the slave may ignore. In range \[0x0000, 0x01F3] */
    uint16_t supervisionTimeout; /**< Proposed Connection Supervision Timeout, in units of 10 ms. In range \[0x000A, 0x0C80] (corresponds to \[100 ms, 32 s]) */
} TBlueAPI_LEConnectionUpdateInd, * PBlueAPI_LEConnectionUpdateInd;

/** @bookmark{LEConnectionParameterInfo} */
/** Message that provides information about changed connection parameters on a BLE link. */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint16_t local_MDL_ID;       /**< Local MDL ID of the LE link */
    uint16_t connInterval;       /**< New Connection Interval, in units of 1.25 ms. In range \[0x0006, 0x0C80] (corresponds to \[7.5 ms, 4 s]) */
    uint16_t connLatency;        /**< New Slave Latency, i.e., the amount of connection events the slave may ignore. In range \[0x0000, 0x01F3] */
    uint16_t supervisionTimeout; /**< New Connection Supervision Timeout, in units of 10 ms. In range \[0x000A, 0x0C80] (corresponds to \[100 ms, 32 s]) */
} TBlueAPI_LEConnectionParameterInfo, * PBlueAPI_LEConnectionParameterInfo;

#if (F_BT_LE_PRIVACY_MODE)
#error "Missing documentation here"
/** @bookmark{LEPrivacyModeRsp} */
/** Response to a previous [LEPrivacyModeReq](@ref blueAPI_LEPrivacyModeReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    uint8_t local_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType local_BD_type;
    TBlueAPI_Cause cause;
} TBlueAPI_LEPrivacyModeRsp, * PBlueAPI_LEPrivacyModeRsp;

#endif /* (F_BT_LE_PRIVACY_MODE) */
#endif /* (F_BT_LOW_ENERGY) */

#if (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM)
#error "Missing documentation here"
/** @bookmark{TestmodeRsp} */
/** Response to a previous [TestmodeReq](@ref blueAPI_TestmodeReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Testmode       testmode;
    TBlueAPI_Cause cause;
} TBlueAPI_TestmodeRsp;
typedef TBlueAPI_TestmodeRsp * PBlueAPI_TestmodeRsp;
#endif /* (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM) */

#if (F_BLUE_API_BAS_SUPPORT)
/** @bookmark{BatteryLevelSetRsp} */
/** Response to a previous [BatteryLevelSetReq](@ref blueAPI_BatteryLevelSetReq). */
typedef struct
{
    TBlueAPIAppHandle appHandle; /**< BlueAPI application handle that the application provided through [RegisterReq](@ref blueAPI_RegisterReq) */
    TBlueAPI_Cause cause;        /**< <table><tr><td> ::blueAPI_CauseSuccess          <td> The battery level has been updated successfully
                                             <tr><td> ::blueAPI_CauseInvalidState     <td> The requested configuration was not applicable to the current state of BlueCode+ and has been ignored
                                                                                           (e.g., built-in Battery Service (BAS) not activated)
                                             <tr><td> ::blueAPI_CauseInvalidParameter <td> The request contained an invalid parameter and has been ignored
                                             <tr><td> ::blueAPI_CauseResourceError    <td> Sending of a generated notification failed</table> */
} TBlueAPI_BatteryLevelSetRsp, * PBlueAPI_BatteryLevelSetRsp;
#endif /* (F_BLUE_API_BAS_SUPPORT) */

#ifdef __cplusplus
}
#endif

#endif /* ndef __BLUECODE_BLUEAPI_MSG_UPSTREAM_H */
