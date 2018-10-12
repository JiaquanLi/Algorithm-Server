/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/blueapi_datatypes.h,v $
 * Revision:    $Revision: 2.1 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_BLUEAPI_DATATYPES_H
#define __BLUECODE_BLUEAPI_DATATYPES_H

/** @file
 * Data types for the BlueAPI interface of BlueCode+. BlueAPI application code should include this header. */

#ifndef V_BLUECODE_EXPORTED
#include "flags.h"   // Variant management
#endif
#ifdef V_MAYBE_OBSOLETE
#if defined(_MSC_VER) && (_MSC_VER < 1700)
/*--- if your compiler does not provide the files below you have to provide ---*/
/*--- definitions for the C99 types uint8_t, uint16_t, uint32_t and bool:   ---*/
#if !defined (__cplusplus)
typedef  BYTE   bool;
#endif
typedef  CHAR   int8_t;
typedef  BYTE   uint8_t;
typedef  WORD   uint16_t;
typedef  SHORT  int16_t;
typedef  DWORD  uint32_t;
#else
#include <stdint.h>
#include <stdbool.h>
#endif
#endif
#include <stdint.h>  // uint*_t
#include <stdbool.h> // bool

#if defined (__cplusplus)
extern "C" {
#endif

#ifdef V_BLUECODE_DEV_NOTES
/* the following defaults are intended to assure compatibility with Windows  */
/* tool BTTRACE which does NOT include <target.h>. for targets that should   */
/* generate BLUE_API trace output (via UART) that can be decoded with BTTRACE   */
/* the values defined in <target.h> must match the defaults defined below or */
/* must not be defined there:                                                */
#endif

#define BLUE_API_VERSION_LENGTH           ((size_t )  6) /**< Length of the BlueAPI version information string, in characters */
#define BLUE_API_DEVICE_NAME_LENGTH       ((size_t ) 20) /**< Maximum length of the user-friendly name of a remote device, in characters */
#define BLUE_API_MDEP_NAME_LENGTH         (          24) /**< Maximum length of the user-friendly name of an endpoint, in characters */
#if (F_BLUE_API_HDP_SUPPORT) || defined(V_BLUECODE_INTERNAL)
#define BLUE_API_MDEP_NAME_LENGTH_HDP_SDP (          10)
#define BLUE_API_HDP_SERVICE_NAME_LENGTH  (          24)
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_HCI_TUNNEL_SUPPORT)
#error "Missing documentation here"
#define BLUE_API_HCI_TUNNEL_DATA_LENGTH   ((size_t ) 48)
#endif /* (F_BLUE_API_HCI_TUNNEL_SUPPORT) */
#define BLUE_API_BD_SIZE                  ((size_t )  6) /**< Size of a Bluetooth device address, in octets */
#define BLUEAPI_MAX_LINK_KEY_SIZE         ((size_t ) 28) /**< Maximum size of a link key, in octets */
#define BLUEAPI_MIN_GENERATED_KEY_SIZE    ((uint8_t)  7) /**< Minimum length of a generated link key, in octets */
#define BLUEAPI_MAX_GENERATED_KEY_SIZE    ((uint8_t) 16) /**< Maximum length of a generated link key, in octets */
#define BLUEAPI_AUTH_C_LENGTH             ((uint8_t) 16) /**< Length of the "C" parameter for out-of-band authentication, in octets */
#define BLUEAPI_AUTH_R_LENGTH             ((uint8_t) 16) /**< Length of the "R" parameter for out-of-band authentication, in octets */
#define BLUEAPI_GATTSTORE_SRVCHG_OFFSET   ((size_t )  2) /**< Offset of the "Service Changed Flag" in Service Changed Handle/Flag data, when stored by the application */
#define BLUEAPI_API_VERSION                  0x20180313  /**< BlueAPI version */

#ifndef V_BLUECODE_EXPORTED
/** @cond Doxygen_Ignored */
#if defined(BLUE_API_LOCAL_DEVICE_NAME_COUNT) && (BLUE_API_LOCAL_DEVICE_NAME_COUNT > 0)
#define __EXPORT_BLUE_API_LOCAL_DEVICE_NAME_COUNT         BLUE_API_LOCAL_DEVICE_NAME_COUNT
#else
#define __EXPORT_BLUE_API_LOCAL_DEVICE_NAME_COUNT         BLUE_API_DEVICE_NAME_LENGTH
#endif
#if defined(BLUE_API_HID_USB_DESCRIPTOR_LENGTH_COUNT) && (BLUE_API_HID_USB_DESCRIPTOR_LENGTH_COUNT > 0)
#define __EXPORT_BLUE_API_HID_USB_DESCRIPTOR_LENGTH_COUNT BLUE_API_HID_USB_DESCRIPTOR_LENGTH_COUNT
#endif
#define __EXPORT_BLUE_API_MDEP_COUNT                      BLUE_API_MDEP_COUNT
#define __EXPORT_BLUE_API_SPP_ENDPOINT_COUNT              BLUE_API_SPP_ENDPOINT_COUNT
#define __EXPORT_BT_GATT_SERVER_MAX_SERVICES_COUNT        BT_GATT_SERVER_MAX_SERVICES_COUNT
#define __EXPORT_BT_MAX_ACL_CONNECTION_COUNT              BT_MAX_ACL_CONNECTION_COUNT
#define __EXPORT_BLUE_API_MDL_COUNT                       BLUE_API_MDL_COUNT
#define __EXPORT_BT_RFCOMM_MAX_CHANNELS_COUNT             BT_RFCOMM_MAX_CHANNELS_COUNT
#define __EXPORT_BLUE_API_TIO_CLIENT_COUNT                BLUE_API_TIO_CLIENT_COUNT
#define __EXPORT_BT_RFCOMM_CREDIT_COUNT                   BT_RFCOMM_CREDIT_COUNT
#define __EXPORT_BT_RFCOMM_MTU_COUNT                      BT_RFCOMM_MTU_COUNT
#define __EXPORT_BT_ATT_MTU_SIZE_LE_COUNT                 BT_ATT_MTU_SIZE_LE_COUNT
/** @endcond */
#endif

/** Maximum length of the user-friendly name of the local device, in characters */
#define BLUE_API_LOCAL_DEVICE_NAME_LENGTH  ((size_t) __EXPORT_BLUE_API_LOCAL_DEVICE_NAME_COUNT        )
/** Maximum length of a local HID descriptor, in characters */
#define BLUE_API_HID_USB_DESCRIPTOR_LENGTH ((size_t) __EXPORT_BLUE_API_HID_USB_DESCRIPTOR_LENGTH_COUNT)
/** Maximum number of local BlueAPI endpoints */
#define BLUE_API_MAX_LOCAL_ENDPOINTS       ((size_t) __EXPORT_BLUE_API_MDEP_COUNT                     )
/** Maximum number of local SPP / RFCOMM-based profile endpoints */
#define BLUE_API_MAX_LOCAL_SPP_ENDPPOINTS  ((size_t) __EXPORT_BLUE_API_SPP_ENDPOINT_COUNT             )
/** Maximum number of GATT service registrations that the application can request */
#define BLUE_API_MAX_GATT_SRV_REGS         ((size_t) __EXPORT_BT_GATT_SERVER_MAX_SERVICES_COUNT       )
/** Maximum number of concurrent ACL connections */
#define BLUE_API_MAX_ACLS                  ((size_t) __EXPORT_BT_MAX_ACL_CONNECTION_COUNT             )
/** Maximum number of concurrent BlueAPI links */
#define BLUE_API_MAX_LINKS                 ((size_t) __EXPORT_BLUE_API_MDL_COUNT                      )
/** Maximum number of concurrent RFCOMM channels */
#define BLUE_API_MAX_RFCOMM_CHANNELS       ((size_t) __EXPORT_BT_RFCOMM_MAX_CHANNELS_COUNT            )
/** Maximum number of outgoing Terminal I/O connections */
#define BLUE_API_MAX_TIO_OUT               ((size_t) __EXPORT_BLUE_API_TIO_CLIENT_COUNT               )
/** Maximum number of available RFCOMM credits */
#define BLUE_API_MAX_RFCOMM_CREDITS        ((size_t) __EXPORT_BT_RFCOMM_CREDIT_COUNT                  )
/** Maximum size of an RFCOMM data segment */
#define BLUE_API_MAX_RFCOMM_SEGMENT        ((size_t) __EXPORT_BT_RFCOMM_MTU_COUNT                     )
/** Maximum size of a data segment on an LE link */
#define BLUE_API_MAX_LE_SEGMENT            ((size_t) __EXPORT_BT_ATT_MTU_SIZE_LE_COUNT                )

#ifdef V_BLUECODE_INTERNAL
#define BLUE_API_ENABLE_ACL_INFO_CONNECTED_ACTIVE         0x0001
#define BLUE_API_ENABLE_ACL_INFO_CONNECTED_SNIFF          0x0002
#define BLUE_API_ENABLE_ACL_INFO_AUTH_STARTED             0x0004
#define BLUE_API_ENABLE_ACL_INFO_AUTH_SUCCESS             0x0008
#define BLUE_API_ENABLE_ACL_INFO_AUTH_FAILED              0x0010
#define BLUE_API_ENABLE_ACL_INFO_CONNECTION_ENCRYPTED     0x0020
#define BLUE_API_ENABLE_ACL_INFO_CONNECTION_DISCONNECTED  0x0040
#define BLUE_API_ENABLE_ACL_INFO_ADDRESS_RESOLVED         0x0080
#define BLUE_API_ENABLE_ACL_INFO_DEVICE_ROLE              0x0100

#define BLUE_API_ENABLE_ACL_INFO_ALL                      0x01FF

#define BLUE_API_ENABLE_MCL_INFO_IDLE                     0x0001
#define BLUE_API_ENABLE_MCL_INFO_CTRL_CONNECTING          0x0002
#define BLUE_API_ENABLE_MCL_INFO_CTRL_CONNECTED           0x0004
#define BLUE_API_ENABLE_MCL_INFO_CTRL_DISCONNECTING       0x0008
#define BLUE_API_ENABLE_MCL_INFO_CTRL_LISTEN              0x0010
#define BLUE_API_ENABLE_MCL_INFO_DATA_CONNECTING          0x0020
#define BLUE_API_ENABLE_MCL_INFO_DATA_CONNECTED           0x0040
#define BLUE_API_ENABLE_MCL_INFO_DATA_DISCONNECTING       0x0080
#define BLUE_API_ENABLE_MCL_INFO_DATA_LISTEN              0x0100
#define BLUE_API_ENABLE_MCL_INFO_CTRL_WAIT_FOR_RSP        0x0200
#define BLUE_API_ENABLE_MCL_INFO_WAIT_FOR_RSP             0x0400

#define BLUE_API_ENABLE_MCL_INFO_ALL                      0x07FF
#endif

/** BlueAPI message command identifier. See #TBlueAPI_Message. */
typedef enum TBlueAPI_Command
{
    /** @name Message command identifiers */
    /** @{ */
    blueAPI_EventConnectMDLReq                 = 0x01, /**< BlueAPI message command identifier */
    blueAPI_EventConnectMDLRsp                 = 0x02,
    blueAPI_EventReconnectMDLReq               = 0x03,
    blueAPI_EventReconnectMDLRsp               = 0x04,
    blueAPI_EventReconnectMDLInd               = 0x05,
    blueAPI_EventReconnectMDLConf              = 0x06,
    blueAPI_EventDisconnectMDLReq              = 0x07,
    blueAPI_EventDisconnectMDLRsp              = 0x08,
    blueAPI_EventDisconnectMDLInd              = 0x09,
    blueAPI_EventDisconnectMDLConf             = 0x0A,
    blueAPI_EventCreateMDLInd                  = 0x0B,
    blueAPI_EventCreateMDLConf                 = 0x0C,
    blueAPI_EventConnectMDLInfo                = 0x0D,
    blueAPI_EventDeleteMDLInfo                 = 0x0E,
    blueAPI_EventMCLStatusInfo                 = 0x0F,
    blueAPI_EventACLStatusInfo                 = 0x10,
    blueAPI_EventRegisterReq                   = 0x11,
    blueAPI_EventRegisterRsp                   = 0x12,
    blueAPI_EventReleaseReq                    = 0x13,
    blueAPI_EventReleaseRsp                    = 0x14,
    blueAPI_EventReleaseInd                    = 0x15,
    blueAPI_EventReleaseConf                   = 0x16,
    blueAPI_EventActInfo                       = 0x17,
    blueAPI_EventDeactInfo                     = 0x18,
    blueAPI_EventInternalEventInfo             = 0x19,
    blueAPI_EventDataReq                       = 0x1A,
    blueAPI_EventDataRsp                       = 0x1B,
    blueAPI_EventDataInd                       = 0x1C,
    blueAPI_EventDataConf                      = 0x1D,
#if (F_BLUE_API_HDP_SUPPORT)
    blueAPI_EventRegHDPMDEPReq                 = 0x1E,
    blueAPI_EventRegHDPMDEPRsp                 = 0x1F,
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT)
    blueAPI_EventRegSPPMDEPReq                 = 0x20,
    blueAPI_EventRegSPPMDEPRsp                 = 0x21,
#endif /* (F_BLUE_API_SPP_SUPPORT) */
#if (F_BLUE_API_OBEX_SUPPORT)
    blueAPI_EventRegOBEXMDEPReq                = 0x22,
    blueAPI_EventRegOBEXMDEPRsp                = 0x23,
#endif /* (F_BLUE_API_OBEX_SUPPORT) */
#if (F_BLUE_API_L2CAP_SUPPORT)
    blueAPI_EventRegL2CAPMDEPReq               = 0x24,
    blueAPI_EventRegL2CAPMDEPRsp               = 0x25,
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */
#if (F_BLUE_API_HID_SUPPORT)
    blueAPI_EventRegHIDMDEPReq                 = 0x26,
    blueAPI_EventRegHIDMDEPRsp                 = 0x27,
#endif /* (F_BLUE_API_HID_SUPPORT) */
    blueAPI_EventRelMDEPReq                    = 0x28,
    blueAPI_EventRelMDEPRsp                    = 0x29,
    blueAPI_EventRadioModeSetReq               = 0x2A,
    blueAPI_EventRadioModeSetRsp               = 0x2B,
    blueAPI_EventDeviceConfigSetReq            = 0x2C,
    blueAPI_EventDeviceConfigSetRsp            = 0x2D,
    blueAPI_EventInquiryReq                    = 0x30,
    blueAPI_EventInquiryRsp                    = 0x31,
    blueAPI_EventInquiryDeviceInfo             = 0x32,
    blueAPI_EventDeviceNameReq                 = 0x33,
    blueAPI_EventDeviceNameRsp                 = 0x34,
#if (F_BLUE_API_HDP_SUPPORT)
    blueAPI_EventHDPDiscoveryReq               = 0x35,
    blueAPI_EventHDPDiscoveryRsp               = 0x36,
#endif /* (F_BLUE_API_HDP_SUPPORT) */
    blueAPI_EventDIDDeviceInd                  = 0x37,
    blueAPI_EventDIDDeviceConf                 = 0x38,
#if (F_BLUE_API_HDP_SUPPORT)
    blueAPI_EventHDPServiceInd                 = 0x39,
    blueAPI_EventHDPServiceConf                = 0x3A,
    blueAPI_EventHDPEndpointInd                = 0x3B,
    blueAPI_EventHDPEndpointConf               = 0x3C,
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT)
    blueAPI_EventSPPDiscoveryReq               = 0x3D,
    blueAPI_EventSPPDiscoveryRsp               = 0x3E,
    blueAPI_EventSPPEndpointInd                = 0x3F,
    blueAPI_EventSPPEndpointConf               = 0x40,
#endif /* (F_BLUE_API_SPP_SUPPORT) */
#if (F_BLUE_API_OBEX_SUPPORT)
    blueAPI_EventOBEXDiscoveryReq              = 0x41,
    blueAPI_EventOBEXDiscoveryRsp              = 0x42,
    blueAPI_EventOBEXEndpointInd               = 0x43,
    blueAPI_EventOBEXEndpointConf              = 0x44,
#endif /* (F_BLUE_API_OBEX_SUPPORT) */
#if (F_BLUE_API_GATT_SUPPORT)
#if (F_BT_GATT_SERVER)
    blueAPI_EventGATTServiceRegisterReq        = 0x45,
    blueAPI_EventGATTServiceRegisterRsp        = 0x46,
    blueAPI_EventGATTServiceReleaseReq         = 0x47,
    blueAPI_EventGATTServiceReleaseRsp         = 0x48,
    blueAPI_EventGATTAttributeUpdateReq        = 0x49,
    blueAPI_EventGATTAttributeUpdateRsp        = 0x4A,
    blueAPI_EventGATTAttributeUpdateStatusInd  = 0x4B,
    blueAPI_EventGATTAttributeUpdateStatusConf = 0x4C,
    blueAPI_EventGATTAttributeReadInd          = 0x4D,
    blueAPI_EventGATTAttributeReadConf         = 0x4E,
    blueAPI_EventGATTAttributeWriteInd         = 0x4F,
    blueAPI_EventGATTAttributeWriteConf        = 0x50,
    blueAPI_EventGATTAttributeWriteCommandInfo = 0x51,
#if (F_BT_ATT_PREP_EXEC_WRITE)
    blueAPI_EventGATTAttributePrepareWriteInd  = 0x52,
    blueAPI_EventGATTAttributePrepareWriteConf = 0x53,
    blueAPI_EventGATTExecuteWriteInd           = 0x54,
    blueAPI_EventGATTExecuteWriteConf          = 0x55,
#endif /* (F_BT_ATT_PREP_EXEC_WRITE) */
    blueAPI_EventGATTCCCDInfo                  = 0x56,
#endif /* (F_BT_GATT_SERVER) */
#if (F_BT_GATT_CLIENT)
    blueAPI_EventGATTDiscoveryReq              = 0x57,
    blueAPI_EventGATTDiscoveryRsp              = 0x58,
    blueAPI_EventGATTDiscoveryInd              = 0x59,
    blueAPI_EventGATTDiscoveryConf             = 0x5A,
    blueAPI_EventGATTAttributeReadReq          = 0x5B,
    blueAPI_EventGATTAttributeReadRsp          = 0x5C,
    blueAPI_EventGATTAttributeWriteReq         = 0x5D,
    blueAPI_EventGATTAttributeWriteRsp         = 0x5E,
#if (F_BT_ATT_PREP_EXEC_WRITE)
    blueAPI_EventGATTExecuteWriteReq           = 0x5F,
    blueAPI_EventGATTExecuteWriteRsp           = 0x60,
#endif /* (F_BT_ATT_PREP_EXEC_WRITE) */
    blueAPI_EventGATTAttributeInd              = 0x61,
    blueAPI_EventGATTAttributeConf             = 0x62,
    blueAPI_EventGATTAttributeNotificationInfo = 0x63,
#if (F_BLUE_API_GATT_SDP_DIS_SUPPORT)
    blueAPI_EventGATTSDPDiscoveryReq           = 0x64,
    blueAPI_EventGATTSDPDiscoveryRsp           = 0x65,
    blueAPI_EventGATTSDPDiscoveryInd           = 0x66,
    blueAPI_EventGATTSDPDiscoveryConf          = 0x67,
#endif /* (F_BLUE_API_GATT_SDP_DIS_SUPPORT) */
#endif /* (F_BT_GATT_CLIENT) */
    blueAPI_EventGATTSecurityReq               = 0x68,
    blueAPI_EventGATTSecurityRsp               = 0x69,
    blueAPI_EventGATTServerStoreInd            = 0x6A,
    blueAPI_EventGATTServerStoreConf           = 0x6B,
    blueAPI_EventGATTMtuSizeInfo               = 0x6C,
#endif /* (F_BLUE_API_GATT_SUPPORT) */
    blueAPI_EventPairableModeSetReq            = 0x6D,
    blueAPI_EventPairableModeSetRsp            = 0x6E,
    blueAPI_EventAuthReq                       = 0x6F,
    blueAPI_EventAuthRsp                       = 0x70,
    blueAPI_EventUserAuthorizationReqInd       = 0x71,
    blueAPI_EventUserAuthorizationReqConf      = 0x72,
    blueAPI_EventUserAuthRequestInd            = 0x73,
    blueAPI_EventUserAuthRequestConf           = 0x74,
    blueAPI_EventUserConfirmationReqInd        = 0x75,
    blueAPI_EventUserConfirmationReqConf       = 0x76,
    blueAPI_EventUserPasskeyReqInd             = 0x77,
    blueAPI_EventUserPasskeyReqConf            = 0x78,
    blueAPI_EventUserPasskeyReqReplyReq        = 0x79,
    blueAPI_EventUserPasskeyReqReplyRsp        = 0x7A,
    blueAPI_EventUserPasskeyNotificationInfo   = 0x7B,
    blueAPI_EventKeypressNotificationReq       = 0x7C,
    blueAPI_EventKeypressNotificationRsp       = 0x7D,
    blueAPI_EventKeypressNotificationInfo      = 0x7E,
    blueAPI_EventRemoteOOBDataReqInd           = 0x7F,
    blueAPI_EventRemoteOOBDataReqConf          = 0x80,
    blueAPI_EventLocalOOBDataReq               = 0x81,
    blueAPI_EventLocalOOBDataRsp               = 0x82,
    blueAPI_EventAuthResultInd                 = 0x83,
    blueAPI_EventAuthResultConf                = 0x84,
    blueAPI_EventAuthResultRequestInd          = 0x85,
    blueAPI_EventAuthResultRequestConf         = 0x86,
    blueAPI_EventAuthDeleteReq                 = 0x87,
    blueAPI_EventAuthDeleteRsp                 = 0x88,
    blueAPI_EventAuthListReq                   = 0x89,
    blueAPI_EventAuthListInfo                  = 0x8A,
    blueAPI_EventAuthListRsp                   = 0x8B,
#if (F_BLUE_API_HCI_TUNNEL_SUPPORT)
    blueAPI_EventHCITunnelReq                  = 0x8C,
    blueAPI_EventHCITunnelRsp                  = 0x8D,
#endif /* (F_BLUE_API_HCI_TUNNEL_SUPPORT) */
#if (F_BT_LOW_ENERGY)
    blueAPI_EventLEAdvertiseReq                = 0x8E,
    blueAPI_EventLEAdvertiseRsp                = 0x8F,
    blueAPI_EventLEAdvertiseParameterSetReq    = 0x90,
    blueAPI_EventLEAdvertiseParameterSetRsp    = 0x91,
    blueAPI_EventLEAdvertiseDataSetReq         = 0x92,
    blueAPI_EventLEAdvertiseDataSetRsp         = 0x93,
    blueAPI_EventLEScanReq                     = 0x94,
    blueAPI_EventLEScanRsp                     = 0x95,
    blueAPI_EventLEScanInfo                    = 0x96,
    blueAPI_EventLEModifyWhitelistReq          = 0x97,
    blueAPI_EventLEModifyWhitelistRsp          = 0x98,
    blueAPI_EventLEConnectionUpdateReq         = 0x99,
    blueAPI_EventLEConnectionUpdateRsp         = 0x9A,
    blueAPI_EventLEConnectionUpdateInd         = 0x9B,
    blueAPI_EventLEConnectionUpdateConf        = 0x9C,
    blueAPI_EventLEConnectionParameterInfo     = 0x9D,
#if (F_BT_LE_PRIVACY_MODE)
    blueAPI_EventLEPrivacyModeReq              = 0x9E,
    blueAPI_EventLEPrivacyModeRsp              = 0x9F,
#endif /* (F_BT_LE_PRIVACY_MODE) */
#endif /* (F_BT_LOW_ENERGY) */
#if (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM)
    blueAPI_EventTestmodeReq                   = 0xA0,
    blueAPI_EventTestmodeRsp                   = 0xA1,
#endif /* (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM) */
    blueAPI_EventACLConfigReq                  = 0xA2,
    blueAPI_EventACLConfigRsp                  = 0xA3,
#if (F_BLUE_API_HID_SUPPORT)
    blueAPI_EventHIDMessageReq                 = 0xA4,
    blueAPI_EventHIDMessageConf                = 0xA5,
    blueAPI_EventHIDMessageInd                 = 0xA6,
    blueAPI_EventHIDMessageRsp                 = 0xA7,
#endif /* (F_BLUE_API_HID_SUPPORT) */
#if (F_APPLE_IAP2)
    blueAPI_EventIAP2MessageReq                = 0xA8,
    blueAPI_EventIAP2MessageConf               = 0xA9,
    blueAPI_EventIAP2MessageInd                = 0xAA,
    blueAPI_EventIAP2MessageRsp                = 0xAB,
#endif /* (F_APPLE_IAP2) */
#if (F_BLUE_API_BAS_SUPPORT)
    blueAPI_EventBatteryLevelSetReq            = 0xAC,
    blueAPI_EventBatteryLevelSetRsp            = 0xAD,
#endif /* (F_BLUE_API_BAS_SUPPORT) */
    blueAPI_EventIdle                          = 0xFF,
    /** @} */
} TBlueAPI_Command, * PBlueAPI_Command;

/** BlueAPI operation result code. */
typedef enum TBlueAPI_Cause
{
    blueAPI_CauseSuccess              = 0x00, /**< Indicates that an operation has completed successfully */
    blueAPI_CauseAccept               = 0x01, /**< Indicates that an operation has been accepted */
    blueAPI_CauseReject               = 0x02, /**< Indicates that an operation has been rejected */
    blueAPI_CauseResourceError        = 0x03, /**< Indicates that an operation could not be completed due to resource constraints */
    blueAPI_CauseInvalidParameter     = 0x04, /**< Indicates that at least one parameter of a request is invalid, the operation has not been performed */
    blueAPI_CauseInvalidState         = 0x05, /**< Indicates that a requested operation cannot be processed because the connection is not in the required state */
    blueAPI_CauseConnectionDisconnect = 0x06, /**< Indicates that a connection has been terminated intentionally */
    blueAPI_CauseConnectionPaused     = 0x07, /**< Indicates that a connection is terminated temporarily */
    blueAPI_CauseConnectionLost       = 0x08, /**< Indicates that a connection is terminated due to RF link loss */
    blueAPI_CauseAuthenticationFailed = 0x09, /**< Indicates that an authentication attempt has failed */
    blueAPI_CauseFlowcontrolViolation = 0x0A, /**< Indicates that flow control conditions have been violated by the client application and the data has not been transmitted */
    blueAPI_CauseInitTimeout          = 0x0B, /**< Indicates that the initialization of BlueCode+ could not be completed within a given time limit (e.g., due to HCI controller communication timeout). The BlueAPI+ interface is not operational */
    blueAPI_CauseInitOutofSync        = 0x0C, /**< Indicates that BlueCode+ failed to communicate with the HCI controller. The BlueAPI+ interface is not operational */
    blueAPI_CauseInitHardwareFailure  = 0x0D, /**< Indicates that BlueCode+ detected a hardware failure during startup. The BlueAPI+ interface is not operational */
    blueAPI_CauseLowerLayerError      = 0x0E, /**< Indicates that a lower layer module (L2CAP, ATT, HCI ..) detected a problem */
#if (F_BT_LE_PRIVACY_RESOLVING)
    blueAPI_CauseAddressNotResolved   = 0x0F, /**< Indicates that the Bluetooth protocol stack is not able to map a blueAPI_RemoteBDTypeLEResolved address */
#endif /* (F_BT_LE_PRIVACY_RESOLVING) */
    blueAPI_CauseUnspecified          = 0xFD, /**< Indicates that an unspecified error occurred */
    blueAPI_CauseNotSupported         = 0xFE, /**< Indicated that the requested operation is not supported by the BlueAPI+ implementation */
} TBlueAPI_Cause, * PBlueAPI_Cause;

typedef uint16_t TBlueAPI_SubCause; /**< BlueAPI operation result code describing operation-specific results not covered by #TBlueAPI_Cause */
typedef TBlueAPI_SubCause * PBlueAPI_SubCause;

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing documentation here"
typedef uint8_t TBlueAPI_TimeStamp[8];
typedef TBlueAPI_TimeStamp * PBlueAPI_TimeStamp;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

/** Bluetooth device address type identifier. */
typedef enum TBlueAPI_RemoteBDType
{
    blueAPI_RemoteBDTypeClassic    = 0x00, /**< Classic BR/EDR Bluetooth device address */
    blueAPI_RemoteBDTypeLEPublic   = 0x02, /**< Bluetooth Low Energy Public address */
    blueAPI_RemoteBDTypeLERandom   = 0x03, /**< Bluetooth Low Energy Random address */
    blueAPI_RemoteBDTypeAny        = 0x04, /**< Any type of Bluetooth device address */
#if (F_BT_LE_PRIVACY_RESOLVING)
    blueAPI_RemoteBDTypeLEResolved = 0x0A, /**< Bluetooth low energy peer with resolvable private address that distributed its IRK */
#endif /* (F_BT_LE_PRIVACY_RESOLVING) */
} TBlueAPI_RemoteBDType, * PBlueAPI_RemoteBDType;

/** Segmentation status of a BlueAPI data message (DataReq, DataInd). */
typedef enum TBlueAPI_FrameType
{
    blueAPI_FrameTypeUnsegmented     = 0x00, /**< Unsegmented application data packet (APDU). The complete APDU is included within the data message */
    blueAPI_FrameTypeFirstSegment    = 0x01, /**< Identifies a segmented application data packet (APDU). The data message contains the first segment of the APDU */
    blueAPI_FrameTypeLastSegment     = 0x02, /**< Identifies a segmented application data packet (APDU). The data message contains the last segment of the APDU */
    blueAPI_FrameTypeContinueSegment = 0x03, /**< Identifies a segmented application data packet (APDU). The data message contains an intermediate segment of the APDU */
} TBlueAPI_FrameType, * PBlueAPI_FrameType;

/** Requested/mandated role for BlueAPI endpoint. */
typedef enum TBlueAPI_MDEPRole
{
#if (F_BLUE_API_HDP_SUPPORT)
    blueAPI_MDEPRoleSource    = 0x00, /**< The endpoint provides the MCAP/IEEE Source/Agent Role functionality */
    blueAPI_MDEPRoleSink      = 0x01, /**< The endpoint provides the MCAP/IEEE Sink/Manager Role functionality */
    blueAPI_MDEPRoleMCAP      = 0x02, /**< When registering an endpoint, the endpoint provides vendor specific functionality on MCAP level not covered by the HDP specification. When searching for HDP endpoints, a search for all MCAP/IEEE roles shall be performed */
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT) || (F_BLUE_API_OBEX_SUPPORT)
    blueAPI_MDEPRoleRFCOMM    = 0x03, /**< internal use only: SPP/RFCOMM endpoint */
#endif /* (F_BLUE_API_SPP_SUPPORT) || (F_BLUE_API_OBEX_SUPPORT) */
#if (F_BLUE_API_GATT_SUPPORT)
    blueAPI_MDEPRoleGATT      = 0x04, /**< internal use only: GATT endpoint */
#endif /* (F_BLUE_API_GATT_SUPPORT) */
#if (F_BLUE_API_L2CAP_SUPPORT)
    blueAPI_MDEPRoleL2CAP     = 0x05, /**< internal use only: L2CAP endpoint */
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */
#if (F_BLUE_API_HID_SUPPORT)
    blueAPI_MDEPRoleHID       = 0x06, /**< internal use only: HID endpoint */
#endif /* (F_BLUE_API_HID_SUPPORT) */
#if (F_BLUE_API_HDP_SUPPORT)
    blueAPI_MDEPRoleDontCare  = 0x63, /**< internal use only */
#endif /* (F_BLUE_API_HDP_SUPPORT) */
} TBlueAPI_MDEPRole, * PBlueAPI_MDEPRole;

/** Profile / QoS configuration for a new BlueAPI link. */
typedef enum _TBlueAPI_LinkConfigType
{
#if (F_BLUE_API_HDP_SUPPORT)
    blueAPI_LinkConfigHDPDontCare                   = 0x00, /**< HDP: no QoS preference */
    blueAPI_LinkConfigHDPReliable                   = 0x01, /**< HDP: reliable (lossless) channel */
    blueAPI_LinkConfigHDPStreaming                  = 0x02, /**< HDP: streaming (lossy) channel */
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT) || (F_BLUE_API_TIO_SUPPORT)
    blueAPI_LinkConfigSPPBasic                      = 0x03, /**< SPP/RFCOMM channel */
#endif /* (F_BLUE_API_SPP_SUPPORT) || (F_BLUE_API_TIO_SUPPORT) */
#if (F_BLUE_API_GATT_SUPPORT)
    blueAPI_LinkConfigGATT                          = 0x04, /**< GATT channel */
#endif /* (F_BLUE_API_GATT_SUPPORT) */
    blueAPI_LinkConfigSDP                           = 0x05, /**< internal use only: SDP channel */
#if (F_APPLE_IAP)
    blueAPI_LinkConfigAppleIAP                      = 0x06, /**< Apple iAP/RFCOMM channel, General Lingo subset */
#endif /* (F_APPLE_IAP) */
#if (F_BLUE_API_L2CAP_SUPPORT)
    blueAPI_LinkConfigL2CapBasic                    = 0x07, /**< L2CAP: basic mode */
    blueAPI_LinkConfigL2CapReliable                 = 0x08, /**< L2CAP: reliable mode  */
    blueAPI_LinkConfigL2CapStreaming                = 0x09, /**< L2CAP: streaming mode */
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */
#if (F_APPLE_IAP_ADD_LINGO_SUPPORT)
    blueAPI_LinkConfigAppleIAPSimpleRemote          = 0x0A, /**< Apple iAP/RFCOMM channel, Simple Remote Lingo */
#endif /* (F_APPLE_IAP_ADD_LINGO_SUPPORT) */
#if (F_BLUE_API_HID_SUPPORT)
    blueAPI_LinkConfigHID                           = 0x0B, /**< HID channel */
#endif /* (F_BLUE_API_HID_SUPPORT) */
#if (F_APPLE_IAP_ADD_LINGO_SUPPORT)
    blueAPI_LinkConfigAppleIAPSimpleRemoteVoiceOver = 0x0C, /**< Simple Remote Lingo / VoiceOver enabled */
#endif /* (F_APPLE_IAP_ADD_LINGO_SUPPORT) */
#if (F_APPLE_IAP2)
    blueAPI_LinkConfigAppleIAP2                     = 0x0D, /**< Apple iAP2/RFCOMM channel */
#endif /* (F_APPLE_IAP2) */
#if (F_BLUE_API_TIO_SUPPORT)
    blueAPI_LinkConfigTIO                           = 0x0E, /**< Telit proprietary Terminal I/O channel */
#endif /* (F_BLUE_API_TIO_SUPPORT) */
#if (F_BLUE_API_HOGP_SUPPORT)
    blueAPI_LinkConfigHOGP                          = 0x0F, /**< HoGP channel */
#endif /* (F_BLUE_API_HOGP_SUPPORT) */
} TBlueAPI_LinkConfigType, * PBlueAPI_LinkConfigType;

/** 16-bit UUID referring to the profile implemented by a BlueAPI MDEP. */
typedef enum TBlueAPI_MDEPDataType
{
#if (F_BLUE_API_HID_SUPPORT)
    blueAPI_MDEPUUIDHID                 = 0x0011, /**< HID (Human Interface Device Profile) */
#endif /* (F_BLUE_API_HID_SUPPORT) */
#if (F_BLUE_API_HDP_SUPPORT)
    blueAPI_MDEPUUIDPulseOximeter       = 0x1004,
    blueAPI_MDEPUUIDBasicECGHeartRate   = 0x1006,
    blueAPI_MDEPUUIDBloodPressure       = 0x1007,
    blueAPI_MDEPUUIDBodyTemperature     = 0x1008,
    blueAPI_MDEPUUIDWeight              = 0x100F,
    blueAPI_MDEPUUIDGlucose             = 0x1011,
    blueAPI_MDEPUUIDINRMonitor          = 0x1012,
    blueAPI_MDEPUUIDBodyComposition     = 0x1014,
    blueAPI_MDEPUUIDPeakFlowMonitor     = 0x1015,
    blueAPI_MDEPUUIDCardiocasFandAMon   = 0x1029,
    blueAPI_MDEPUUIDStrengthFitness     = 0x102A,
    blueAPI_MDEPUUIDLivingActivityHub   = 0x1047,
    blueAPI_MDEPUUIDStepCounter         = 0x1068,
    blueAPI_MDEPUUIDFallSensor          = 0x1075,
    blueAPI_MDEPUUIDPersEmergancyRsp    = 0x1076,
    blueAPI_MDEPUUIDSmokeSensor         = 0x1077,
    blueAPI_MDEPUUIDCOSensor            = 0x1078,
    blueAPI_MDEPUUIDWaterSensor         = 0x1079,
    blueAPI_MDEPUUIDGasSensor           = 0x107A,
    blueAPI_MDEPUUIDMotionSensor        = 0x107B,
    blueAPI_MDEPUUIDPropertyExit        = 0x107C,
    blueAPI_MDEPUUIDEnuresisSensor      = 0x107D,
    blueAPI_MDEPUUIDContactClosure      = 0x107E,
    blueAPI_MDEPUUIDUsageSensor         = 0x107F,
    blueAPI_MDEPUUIDSwitchSensor        = 0x1080,
    blueAPI_MDEPUUIDMedicationDosing    = 0x1081,
    blueAPI_MDEPUUIDTemperature         = 0x1082,
    blueAPI_MDEPUUIDMedicationMonitor   = 0x1082,
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT)
    blueAPI_MDEPUUIDSPPSerialPort       = 0x1101, /**< SPP (Serial Port Profile) */
#ifdef V_BLUECODE_MAYBE_OBSOLETE
    blueAPI_MDEPUUIDSPPDialupNetworking = 0x1103,
#endif
#endif /* (F_BLUE_API_SPP_SUPPORT) */
#if (F_BLUE_API_OBEX_SUPPORT)
    blueAPI_MDEPUUIDOBEXSynch           = 0x1104,
    blueAPI_MDEPUUIDOBEXObjectPush      = 0x1105,
    blueAPI_MDEPUUIDOBEXFileTransfer    = 0x1106,
    blueAPI_MDEPUUIDOBEXSynchCommand    = 0x1107,
#endif /* (F_BLUE_API_OBEX_SUPPORT) */
    blueAPI_MDEPUUIDAppleIAP            = 0xFA01, /**< Apple iPod Accessory Protocol (iAP) */
    blueAPI_MDEPUUIDAppleIAP2           = 0xFA02, /**< Apple iPod Accessory Protocol (iAP2) */
#if (F_BLUE_API_TIO_SUPPORT)
    blueAPI_MDEPUUIDTypeTIO             = 0xFEFB, /**< Terminal I/O (Telit proprietary SPP replacement for Bluetooth Low Energy) */
#endif /* (F_BLUE_API_TIO_SUPPORT) */
#ifdef V_BLUECODE_MAYBE_OBSOLETE
    /* Special */
    blueAPI_MDEPUUIDTypeSpecial         = 0xFFFE,
    blueAPI_MDEPUUIDTypeEcho            = 0xFFFF,
#endif
} TBlueAPI_MDEPDataType, * PBlueAPI_MDEPDataType;

/** Status of a BlueAPI MCL. */
typedef enum TBlueAPI_MCLStatus
{
    blueAPI_MCLIdle                            = 0x01, /**< The MCL is allocated and idle */
    blueAPI_MCLControlConnecting               = 0x02, /**< The MCL has a control channel setup pending */
    blueAPI_MCLControlConnected                = 0x03, /**< The MCL has a connected control channel, but no data channels */
    blueAPI_MCLControlDisconnecting            = 0x04, /**< The MCL has a pending control channel disconnect */
    blueAPI_MCLControlListening                = 0x05, /**< The MCL is waiting for an incoming control channel */
    blueAPI_MCLDataConnecting                  = 0x06, /**< The MCL has a data channel setup pending */
    blueAPI_MCLDataConnected                   = 0x07, /**< The MCL has at least one data channel connected */
    blueAPI_MCLDataDisconnecting               = 0x08, /**< The MCL has a data channel disconnect pending */
    blueAPI_MCLDataListening                   = 0x09, /**< The MCL is waiting for an incoming data channel */
    blueAPI_MCLControlWaitForResponse          = 0x0A, /**< The MCL is waiting for an MCAP response */
    blueAPI_MCLComWaitForResponse              = 0x0B, /**< The MCL is waiting for an application response */
    blueAPI_MCLReleased                        = 0x0C, /**< The MCL is not allocated */
    blueAPI_MCLControlConnectingDataListening  = 0x0D, /**< The MCL has a control channel setup pending, and is waiting for an incoming data channel */
    blueAPI_MCLControlConnectingDataConnecting = 0x0E, /**< The MCL has a control channel setup and a data channel setup pending */
    blueAPI_MCLControlConnectedDataConnecting  = 0x0F, /**< The MCL has a connected control channel, and a data channel setup pending */
} TBlueAPI_MCLStatus, * PBlueAPI_MCLStatus;

/** Status of a BlueAPI ACL. */
typedef enum TBlueAPI_ACLStatus
{
    blueAPI_ACLConnectedActive        = 0x01, /**< The ACL is established and in active mode */
    blueAPI_ACLConnectedSniff         = 0x02, /**< The ACL is in sniff mode */
    blueAPI_ACLAuthenticationStarted  = 0x03, /**< Authentication for this ACL has been started */
    blueAPI_ACLAuthenticationSuccess  = 0x04, /**< Authentication for this ACL has been successful */
    blueAPI_ACLAuthenticationFailure  = 0x05, /**< Authentication for this ACL has failed */
    blueAPI_ACLConnectionEncrypted    = 0x06, /**< The ACL data traffic is encrypted */
    blueAPI_ACLConnectionDisconnected = 0x07, /**< The ACL is no longer connected */
    blueAPI_ACLConnectionNotEncrypted = 0x08, /**< The ACL data traffic is no longer encrypted */
#if (F_BT_LE_PRIVACY_RESOLVING)
    blueAPI_ACLAddressResolved        = 0x09, /**< The ACL BLE address has been resolved */
#endif /* (F_BT_LE_PRIVACY_RESOLVING) */
    blueAPI_ACLDeviceRoleMaster       = 0x0A, /**< The local device role is now Master (Classic only) */
    blueAPI_ACLDeviceRoleSlave        = 0x0B, /**< The local device role is now Slave (Classic only)  */
    blueAPI_ACLConnectedSniffSubrate  = 0x0C, /**< The sniff subrate has been negotiated (Classic only) */
    blueAPI_ACLConnectedLinkStatus    = 0x0D, /**< Link status information is available */
} TBlueAPI_ACLStatus, * PBlueAPI_ACLStatus;

/** Link key type */
typedef enum TBlueAPI_LinkKeyType
{
    blueAPI_LinkKeyTypeCombination      = 0x00, /**< Bluetooth 2.0 link key */
    blueAPI_LinkKeyTypeUnauthenticated  = 0x04, /**< SSP generated link key without MITM protection */
    blueAPI_LinkKeyTypeAuthenticated    = 0x05, /**< SSP generated link key with MITM protection */
    blueAPI_LinkKeyTypeLELocalLTK       = 0x11, /**< Bluetooth Low Energy Long Term Key Blob (Local) */
    blueAPI_LinkKeyTypeLERemoteLTK      = 0x12, /**< Bluetooth Low Energy Long Term Key Blob (Remote) */
    blueAPI_LinkKeyTypeLELocalIRK       = 0x13, /**< Bluetooth Low Energy Identity Resolving Key (Local) */
    blueAPI_LinkKeyTypeLERemoteIRK      = 0x14, /**< Bluetooth Low Energy Identity Resolving Key (Remote) */
    blueAPI_LinkKeyTypeRequestBR        = 0x80, /**< Used to request any Classic link key */
    blueAPI_LinkKeyTypeDeleted          = 0xFF, /**< Link key is no longer valid and has been deleted */
} TBlueAPI_LinkKeyType;

typedef void * TBlueAPIAppHandle; /**< Custom context handle for BlueAPI messages that identifies the recipient client application. */
typedef void * TBlueAPIHandle;    /**< Context handle for BlueAPI messages that identifies the recipient BlueCode+ state. */

/** ACL Status Info parameter for ::blueAPI_ACLAuthenticationStarted, ::blueAPI_ACLAuthenticationSuccess, ::blueAPI_ACLAuthenticationFailure, ::blueAPI_ACLConnectionEncrypted and ::blueAPI_ACLConnectionNotEncrypted. */
typedef struct TBlueAPI_ACLStatusParamAuth
{
    TBlueAPI_LinkKeyType keyType; /**< Key type of the generated link key */
    uint8_t keySize;              /**< Size of the generated link key, in octets. In range \[#BLUEAPI_MIN_GENERATED_KEY_SIZE, #BLUEAPI_MAX_GENERATED_KEY_SIZE] */
} TBlueAPI_ACLStatusParamAuth, * PBlueAPI_ACLStatusParamAuth;

#if (F_BT_LE_PRIVACY_RESOLVING)
/** ACL Status Info parameter for ::blueAPI_ACLAddressResolved. */
typedef struct TBlueAPI_ACLStatusParamResolve
{
    uint8_t remote_BD[BLUE_API_BD_SIZE];  /**< Resolved Bluetooth Device Address of the remote device (after IRK exchange) */
    TBlueAPI_RemoteBDType remote_BD_type; /**< Resolved address type of #remote_BD */
} TBlueAPI_ACLStatusParamResolve, * PBlueAPI_ACLStatusParamResolve;
#endif /* (F_BT_LE_PRIVACY_RESOLVING) */

/** ACL Status Info parameter for ::blueAPI_ACLConnectedSniff. */
typedef struct TBlueAPI_ACLStatusParamSniff
{
    uint16_t interval; /**< Sniff Interval, in units of 0.625 ms. In range \[0x0002, 0xFFFE] (corresponds to \[1.25 ms, 40.96 s]) */
} TBlueAPI_ACLStatusParamSniff, * PBlueAPI_ACLStatusParamSniff;

/** ACL Status Info parameter for ::blueAPI_ACLConnectedSniffSubrate. */
typedef struct TBlueAPI_ACLStatusParamSniffSubrate
{
    uint16_t maxTxLatency;     /**< Maximum latency for data in TX direction, in units of 0.625 ms. In range \[0x0000, 0xFFFE] (corresponds to \[0, 40.96 s]) */
    uint16_t maxRxLatency;     /**< Maximum latency for data in RX direction, in units of 0.625 ms. In range \[0x0000, 0xFFFE] (corresponds to \[0, 40.96 s]) */
    uint16_t minRemoteTimeout; /**< Minimum Sniff Subrate Timeout of the remote device, in units of 1.25 ms. In range \[0x0000, 0x8000] (corresponds to \[0, 40.96 s]) */
    uint16_t minLocalTimeout;  /**< Minimum Sniff Subrate Timeout of the local device, in units of 1.25 ms. In range \[0x0000, 0x8000] (corresponds to \[0, 40.96 s]) */
} TBlueAPI_ACLStatusParamSniffSubrate, * PBlueAPI_ACLStatusParamSniffSubrate;

/** ACL Status Info parameter for ::blueAPI_ACLConnectedLinkStatus. */
typedef struct TBlueAPI_ACLStatusParamLinkStatus
{
    uint8_t linkQuality;     /**< Current quality of the underlying connection. Valid range depends on the Bluetooth Controller model */
    int8_t rssi;             /**< Current Received Signal Strength Indication (RSSI) value for the link, in dB. In range \[-128, 127] */
    uint16_t failedContacts; /**< Number of consecutive failed contacts for the underlying connection */
    int8_t txPower;          /**< Current Transmit Power Level for the underlying connection, in dBm. In range \[-30, 20] */
    int8_t absoluteRssi;     /**< Absolute RSSI. Implementation is platform-specific and may not be supported in each variant of BlueCode+ and for each Bluetooth Controller model */
} TBlueAPI_ACLStatusParamLinkStatus, * PBlueAPI_ACLStatusParamLinkStatus;

/** Generic ACL Status Info parameter. Enclosing structures contain a tag identifying the union member */
typedef union TBlueAPI_ACLStatusParam
{
    TBlueAPI_ACLStatusParamAuth auth;                 /**< ACL Status Info parameter for authentication events */
#if (F_BT_LE_PRIVACY_RESOLVING)
    TBlueAPI_ACLStatusParamResolve resolve;           /**< ACL Status Info parameter for address resolution events */
#endif /* (F_BT_LE_PRIVACY_RESOLVING) */
    TBlueAPI_ACLStatusParamSniff sniff;               /**< ACL Status Info parameter for Sniff Mode events */
    TBlueAPI_ACLStatusParamSniffSubrate sniffSubrate; /**< ACL Status Info parameter for Sniff Subrate information */
    TBlueAPI_ACLStatusParamLinkStatus linkStatus;     /**< ACL Status Info parameter for link status information */
} TBlueAPI_ACLStatusParam, * PBlueAPI_ACLStatusParam;

/** Generic structure of a BlueAPI message. */
typedef struct TBlueAPI_Generic
{
    union
    {
        TBlueAPIAppHandle appHandle;  /**< Context handle for BlueAPI messages that identifies the recipient client application */
        TBlueAPIHandle blueAPIHandle; /**< Context handle for BlueAPI messages that identifies the recipient BlueCode+ state */
    } u; /**< Handle identifying the recipient */
} TBlueAPI_Generic, * PBlueAPI_Generic;

/** Internal event identifier. */
typedef enum TBlueAPI_InternalEventType
{
    blueAPI_InternalEventInvalidCreateMDLConf                 = 0x01, /**< An invalid CreateMDLConf has been received */
#if (F_BLUE_API_RECONNECT_SUPPORT)
    blueAPI_InternalEventInvalidReconnectMDLConf              = 0x02, /**< An invalid ReconnectMDLConf has been received */
#endif /* (F_BLUE_API_RECONNECT_SUPPORT) */
    blueAPI_InternalEventInvalidDisconnectMDLConf             = 0x03, /**< An invalid DisconnectMDLConf has been received */
    blueAPI_InternalEventInvalidDataConf                      = 0x04, /**< An invalid DataConf has been received */
    blueAPI_InternalEventInvalidDIDDeviceConf                 = 0x05, /**< An invalid DIDDeviceConf has been received */
#if (F_BLUE_API_HDP_SUPPORT)
    blueAPI_InternalEventInvalidHDPServiceConf                = 0x06, /**< An invalid HDPServiceConf has been received */
    blueAPI_InternalEventInvalidHDPEndpointConf               = 0x07, /**< An invalid HDPEndpointConf has been received */
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT)
    blueAPI_InternalEventInvalidSPPEndpointConf               = 0x08, /**< An invalid SPPEndpointConf has been received */
#endif /* (F_BLUE_API_SPP_SUPPORT) */
#if (F_BLUE_API_OBEX_SUPPORT)
    blueAPI_InternalEventInvalidOBEXEndpointConf              = 0x09, /**< An invalid CreateMDLConf has been received */
#endif /* (F_BLUE_API_OBEX_SUPPORT) */
    blueAPI_InternalEventInvalidSecurityConf                  = 0x0A, /**< A confirmation message with invalid security data has been received */
    blueAPI_InternalEventInvalidRemoteEvent                   = 0x0B, /**< An unexpected remote event occurred */
    blueAPI_InternalEventCommunicationTimeout                 = 0x0C, /**< A communication timeout expired */
#if (F_BLUE_API_GATT_SUPPORT)
    blueAPI_InternalEventInvalidGATTAttributeReadConf         = 0x0D, /**< An invalid GATTAttributeReadConf has been received */
    blueAPI_InternalEventInvalidGATTAttributeWriteConf        = 0x0E, /**< An invalid GATTAttributeWriteConf has been received */
    blueAPI_InternalEventInvalidGATTAttributePrepareWriteConf = 0x0F, /**< An invalid GATTAttributePrepareWriteConf has been received */
    blueAPI_InternalEventInvalidGATTExecuteWriteConf          = 0x10, /**< An invalid GATTExecuteWriteConf has been received */
    blueAPI_InternalEventInvalidGATTDiscoveryConf             = 0x11, /**< An invalid GATTDiscoveryConf has been received */
    blueAPI_InternalEventInvalidGATTAttributeConf             = 0x12, /**< An invalid GATTAttributeConf has been received */
#endif /* (F_BLUE_API_GATT_SUPPORT) */
    blueAPI_InternalEventInvalidLEConnectionUpdateConf        = 0x13, /**< An invalid LEConnectionUpdateConf has been received */
#if (F_BLUE_API_GATT_SUPPORT)
    blueAPI_InternalEventInvalidGATTSDPDiscoveryConf          = 0x14, /**< An invalid GATTSDPDiscoveryConf has been received */
#endif /* (F_BLUE_API_GATT_SUPPORT) */
#ifdef V_BLUECODE_MAYBE_OBSOLETE
    blueAPI_InternalEventInvalidHIDDataChannelCount           = 0x15,
#endif
    blueAPI_InternalEventResourceError                        = 0x16, /**< An internal resource access encountered an error */
} TBlueAPI_InternalEventType;

/** Type of user interaction during an SSP procedure with local keyboard. */
typedef enum TBlueAPI_SSPKeyEvent
{
    blueAPI_SSPEntryStarted  = 0x00, /**< The passkey entry procedure has been started */
    blueAPI_SSPDigitEntered  = 0x01, /**< A passkey digit has been entered by the remote device's user */
    blueAPI_SSPDigitErased   = 0x02, /**< A passkey digit has been erased by the remote device's user */
    blueAPI_SSPCleared       = 0x03, /**< The remote device's user cleared the display */
    blueAPI_SSPEntryComplete = 0x04, /**< The passkey entry procedure has completed */
} TBlueAPI_SSPKeyEvent;

/** Configuration of available Bluetooth pairing functionality. */
typedef enum TBlueAPI_BluetoothMode
{
    blueAPI_BTMode21Disabled     = 0x00, /**< Disables all pairing functionality that was introduced in Bluetooth version 2.1 or later */
    blueAPI_BTMode21Enabled      = 0x01, /**< Enables available pairing functionality that was introduced in Bluetooth version 2.1 or later */
    blueAPI_BTMode21DebugEnabled = 0x02, /**< Enables available pairing functionality that was introduced in Bluetooth version 2.1 or later, but uses the SSP debug mode.
                                              Note that this mode shall only be used for debugging purposes as it disables secure over-the-air data encryption */
} TBlueAPI_BluetoothMode;

/** Configuration of available Input/Output (IO) capabilities for authentication. */
typedef enum TBlueAPI_IOCapabilities
{
    blueAPI_IOCapDisplayOnly     = 0x00, /**< Display available, keyboard or Yes/No keys not available */
    blueAPI_IOCapDisplayYesNo    = 0x01, /**< Display and Yes/No keys available */
    blueAPI_IOCapKeyboardOnly    = 0x02, /**< Keyboard available, display not available */
    blueAPI_IOCapNoIO            = 0x03, /**< No IO capabilities available */
    blueAPI_IOCapKeyboardDisplay = 0x04, /**< (Bluetooth Low Energy-only): Keyboard and Display available */
} TBlueAPI_IOCapabilities;

/** Configuration of authentication requirements for pairing procedures. */
typedef enum TBlueAPI_AuthRequirements
{
    blueAPI_AuthNoMITMRequiredNoStore          = 0x00, /**< Protection against man-in-the-middle attacks is not required and no bonding shall be performed */
    blueAPI_AuthMITMRequiredNoStore            = 0x01, /**< Protection against man-in-the-middle attacks is required (uses IO capabilities) and no bonding shall be performed */
    blueAPI_AuthNoMITMRequiredDedicatedBonding = 0x02, /**< Protection against man-in-the-middle attacks is not required and Dedicated Bonding shall be performed */
    blueAPI_AuthMITMRequiredDedicatedBonding   = 0x03, /**< Protection against man-in-the-middle attacks is required (uses IO capabilities) and Dedicated Bonding shall be performed */
    blueAPI_AuthNoMITMRequiredGeneralBonding   = 0x04, /**< Protection against man-in-the-middle attacks is not required and General Bonding shall be performed */
    blueAPI_AuthMITMRequiredGeneralBonding     = 0x05, /**< Protection against man-in-the-middle attacks is required (uses IO capabilities) and General Bonding shall be performed */
} TBlueAPI_AuthRequirements;

/** Storage method for bonding information. */
typedef enum TBlueAPI_StoreBondModes
{
    blueAPI_StoreBondModeNoStore  = 0x00, /**< Bonding information persists for the duration of the authenticated connection */
    blueAPI_StoreBondModeNVStore  = 0x01, /**< Bonding information is permanently stored in the non-volatile memory provided by OSIF */
    blueAPI_StoreBondModeRAMStore = 0x02, /**< Bonding information is stored in RAM, surviving disconnections, but not power cycles */
    blueAPI_StoreBondModeExtStore = 0x03, /**< Bonding information is stored by the client application */
} TBlueAPI_StoreBondModes;

/** Bluetooth scan mode (bitmask). Can be dynamically configured through corresponding values in #TBlueAPI_RadioMode. */
typedef enum TBlueAPI_BRPageScanMode
{
    blueAPI_BRScanModeNoScan             = 0x00, /**< Inquiry Scan off, Page Scan off. See ::blueAPI_RadioNonDiscoverable for effects */
    blueAPI_BRScanModeInquiryScan        = 0x01, /**< Inquiry Scan on, Page Scan off. See ::blueAPI_RadioVisible for effects */
    blueAPI_BRScanModePageScan           = 0x02, /**< Inquiry Scan off, Page Scan on. See ::blueAPI_RadioConnectable for effects */
    blueAPI_BRScanModeInquiryAndPageScan = 0x03, /**< Inquiry Scan on, Page Scan on. See ::blueAPI_RadioVisibleConnectable for effects */
} TBlueAPI_BRPageScanMode;

/** Bluetooth radio mode configuration. */
typedef enum TBlueAPI_RadioMode
{
    blueAPI_RadioVisibleConnectable = 0x01, /**< The device is visible to inquiring devices and scans for incoming connections (Inquiry Scan on, Page Scan on) */
    blueAPI_RadioVisible            = 0x02, /**< The device is visible to inquiring devices, but does not scan for incoming connections (Inquiry Scan on, Page Scan off) */
    blueAPI_RadioConnectable        = 0x03, /**< The device is not visible to inquiring devices, but scans for incoming connections (Inquiry Scan off, Page Scan on) */
    blueAPI_RadioNonDiscoverable    = 0x04, /**< The device is not visible for inquiring devices and does not scan for incoming connections (Inquiry Scan off, page Scan off). The device is still able to initiate connections */
    blueAPI_RadioDeepSleep          = 0x05, /**< The Bluetooth Radio is in a non-operational mode but retains its local configuration and can be restored to normal operation without reconfiguration */
    blueAPI_RadioOff                = 0x06, /**< The Bluetooth Radio is switched off and has to be reconfigured to restore normal operation */
} TBlueAPI_RadioMode;

/** Classic Bluetooth Page Scan Type. */
typedef enum TBlueAPI_BRPageScanType
{
    blueAPI_BRPageScanTypeStandard   = 0x00, /**< Standard Page Scan */
    blueAPI_BRPageScanTypeInterlaced = 0x01, /**< Interlaced Page Scan */
} TBlueAPI_BRPageScanType;

/** Classic Bluetooth Page Repetition Mode. */
typedef enum TBlueAPI_BRPageScanRepMode
{
    blueAPI_BRPageScanRepMode_Continous      = 0x00, /**< Page Scan Repetition Mode R0 */
    blueAPI_BRPageScanRepMode_1_28s_Interval = 0x01, /**< Page Scan Repetition Mode R1 */
    blueAPI_BRPageScanRepMode_2_56s_Interval = 0x02, /**< Page Scan Repetition Mode R2 */
    blueAPI_BRPageScanRepMode_Manual         = 0xFF, /**< Page Scan Repetition Mode R2 with custom interval/window parameters */
} TBlueAPI_BRPageScanRepMode;

/** Classic Bluetooth Inquiry Scan Type. */
typedef enum TBlueAPI_BRInquiryScanType
{
    blueAPI_BRPageInquiryTypeStandard   = 0x00, /**< Standard Inquiry Scan */
    blueAPI_BRPageInquiryTypeInterlaced = 0x01, /**< Interlaced Inquiry Scan */
} TBlueAPI_BRInquiryScanType;

/** Classic Bluetooth link policy for role switch and sniff mode (bitmask). */
typedef enum TBlueAPI_BRLinkPolicy
{
    blueAPI_BRLinkPolicyDisableAll       =   0x00, /**< Role switch disabled, sniff mode disabled */
    blueAPI_BRLinkPolicyEnableRoleSwitch = 1 << 0, /**< Role switch enabled, sniff mode disabled */
    blueAPI_BRLinkPolicyEnableSniffMode  = 1 << 2, /**< Role switch disabled, sniff mode enabled */
} TBlueAPI_BRLinkPolicy;

/** Desired device role identifier (Classic Bluetooth). */
typedef enum TBlueAPI_BRDeviceRole
{
    blueAPI_BRDeviceRoleDontCare        = 0x00, /**< No role preference */
    blueAPI_BRDeviceRoleMasterPreferred = 0x01, /**< If assigned Slave role, attempt a role switch to become Master */
    blueAPI_BRDeviceRoleMasterRequired  = 0x02, /**< If assigned Slave role, attempt a role switch to become Master and disconnect if the attempt fails */
    blueAPI_BRDeviceRoleSlavePreferred  = 0x03, /**< If assigned Master role, attempt a role switch to become Slave */
    blueAPI_BRDeviceRoleSlaveRequired   = 0x04, /**< If assigned Master role, attempt a role switch to become Slave and disconnect if the attempt fails */
} TBlueAPI_BRDeviceRole;

/** Operation identifier for a device configuration operation. */
typedef enum TBlueAPI_DeviceConfigOpcode
{
    blueAPI_DeviceConfigDevice      = 0x00, /**< Configure general device-specific parameters */
    blueAPI_DeviceConfigDID         = 0x01, /**< Configure DIP (Device ID Profile)-specific parameters */
    blueAPI_DeviceConfigSecurity    = 0x02, /**< Configure general security-related device-specific parameters */
#if (F_BLUE_API_HDP_SUPPORT)
    blueAPI_DeviceConfigHDP         = 0x03,
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT)
    blueAPI_DeviceConfigSPP         = 0x04, /**< Configure SPP security-related device-specific parameters */
#endif /* (F_BLUE_API_SPPP_SUPPORT) */
#if (F_BLUE_API_L2CAP_SUPPORT)
    blueAPI_DeviceConfigL2CAP       = 0x05,
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */
    blueAPI_DeviceConfigPagescan    = 0x06, /**< Configure Classic Bluetooth Page Scan parameters */
    blueAPI_DeviceConfigLinkpolicy  = 0x07, /**< Configure Classic Bluetooth connection parameters */
#if (BTEXT_RF_MAX_TX_PWR)
    blueAPI_DeviceConfigMaxTxPower  = 0x08, /**< Configure the maximum TX power of the Bluetooth controller */
#endif /* (BTEXT_RF_MAX_TX_PWR) */
    blueAPI_DeviceConfigInquiryScan = 0x09, /**< Configure Classic Bluetooth Inquiry Scan parameters */
} TBlueAPI_DeviceConfigOpcode;

#define BLUE_API_USE_LE_FIXED_DISPLAY_VALUE ((uint32_t) 0x80000000) /**< Bit flag for selecting a BLE SPP fixed display value via the dynamic configuration of security-related parameters */

/** Operation identifier for an ACL configuration operation */
typedef enum TBlueAPI_ACLConfigOpcode
{
    blueAPI_ACLConfigLinkpolicy = 0x00, /**< Configure link policy parameters */
    blueAPI_ACLConfigSniffmode  = 0x01, /**< Configure sniff and sniff subrating parameters */
#if (F_BT_HCI_RADIO_STATUS_CONF)
    blueAPI_ACLConfigLinkstatus = 0x02, /**< Enable/Disable periodic link status polling */
#endif /* (F_BT_HCI_RADIO_STATUS_CONF) */
} TBlueAPI_ACLConfigOpcode;

#if (F_BLUE_API_HID_SUPPORT)
/** HID Report Descriptor identifier. */
typedef enum TBlueAPI_HIDDescriptorID
{
    blueAPI_HIDDescriptorApplicationDefined = 0x00, /**< Application-defined HID Descriptor structure */
    blueAPI_HIDDescriptorInvalid            = 0xFF, /**< Invalid HID Report Descriptor */
#ifdef V_BLUECODE_DEV_NOTES
    // DevNote: blueAPI_HIDDescriptorInvalid shall be the largest enumeration value
#endif
} TBlueAPI_HIDDescriptorID, * PBlueAPI_HIDDescriptorID;

/** HID-specific message headers. For documentation, see:
 * @bthid{1.1,3,Bluetooth HID Protocol} */
typedef enum TBlueAPI_HIDMsgHeader
{
    /** @name HID message headers */
    /** @{ */
    // Sent by: Device
    blueAPI_HIDMsgHandshake                        = 0x00, /**< HID-specific message header */
    blueAPI_HIDMsgHandshakeSuccess                 = blueAPI_HIDMsgHandshake + 0x00,
    blueAPI_HIDMsgHandshakeNotReady                = blueAPI_HIDMsgHandshake + 0x01,
    blueAPI_HIDMsgHandshakeErrorInvalidReportID    = blueAPI_HIDMsgHandshake + 0x02,
    blueAPI_HIDMsgHandshakeErrorUnsupportedRequest = blueAPI_HIDMsgHandshake + 0x03,
    blueAPI_HIDMsgHandshakeErrorInvalidParameter   = blueAPI_HIDMsgHandshake + 0x04,
    blueAPI_HIDMsgHandshakeErrorUnknown            = blueAPI_HIDMsgHandshake + 0x0E,
    blueAPI_HIDMsgHandshakeErrorFatal              = blueAPI_HIDMsgHandshake + 0x0F,

    // Sent by: Device and Host
    blueAPI_HIDMsgControl                          = 0x10,
    blueAPI_HIDMsgControlSuspend                   = blueAPI_HIDMsgControl + 0x03,
    blueAPI_HIDMsgControlExitSuspend               = blueAPI_HIDMsgControl + 0x04,
    blueAPI_HIDMsgControlVirtualCableUnplug        = blueAPI_HIDMsgControl + 0x05,

    // Sent by: Host
    blueAPI_HIDMsgGetReport                        = 0x40,
    blueAPI_HIDMsgGetReportInput                   = blueAPI_HIDMsgGetReport + 0x01,
    blueAPI_HIDMsgGetReportOutput                  = blueAPI_HIDMsgGetReport + 0x02,
    blueAPI_HIDMsgGetReportFeature                 = blueAPI_HIDMsgGetReport + 0x03,
    blueAPI_HIDMsgGetReportInputWithSize           = blueAPI_HIDMsgGetReport + 0x09,
    blueAPI_HIDMsgGetReportOutputWithSize          = blueAPI_HIDMsgGetReport + 0x0A,
    blueAPI_HIDMsgGetReportFeatureWithSize         = blueAPI_HIDMsgGetReport + 0x0B,

    // Sent by: Host
    blueAPI_HIDMsgSetReport                        = 0x50,
    blueAPI_HIDMsgSetReportInput                   = blueAPI_HIDMsgSetReport + 0x01,
    blueAPI_HIDMsgSetReportOutput                  = blueAPI_HIDMsgSetReport + 0x02,
    blueAPI_HIDMsgSetReportFeature                 = blueAPI_HIDMsgSetReport + 0x03,

    // Sent by: Device and Host
    blueAPI_HIDMsgData                             = 0xA0,
    blueAPI_HIDMsgDataOther                        = blueAPI_HIDMsgData + 0x00,
    blueAPI_HIDMsgDataInput                        = blueAPI_HIDMsgData + 0x01,
    blueAPI_HIDMsgDataOutput                       = blueAPI_HIDMsgData + 0x02,
    blueAPI_HIDMsgDataFeature                      = blueAPI_HIDMsgData + 0x03,

    // Sent by: Device as response to GetReport sent by Host
    blueAPI_HIDMsgGetReportInputRsp                = 0xF1,
    blueAPI_HIDMsgGetReportOutputRsp               = 0xF2,
    blueAPI_HIDMsgGetReportFeatureRsp              = 0xF3,

    // Bits 7-4
    blueAPI_HIDMsgTypeMask                         = 0xF0,
    /** @} */
} TBlueAPI_HIDMsgHeader, * PBlueAPI_HIDMsgHeader;
#endif /* (F_BLUE_API_HID_SUPPORT) */

#if (F_APPLE_IAP2)
#error "Missing documentation here"
typedef enum TBlueAPI_IAP2SessionID
{
    blueAPI_IAP2SessionIDControlSession            = 0x00,
    blueAPI_IAP2SessionIDExternalAccessorySession  = 0x01
} TBlueAPI_IAP2SessionID, * PBlueAPI_IAP2SessionID;
#endif /* (F_APPLE_IAP2) */

#if (F_BLUE_API_OBEX_SUPPORT)
#error "Missing documentation here"
/* bit masks for MDEP_OBEXDataMask in RegOBEXMDEPReq                        */
#define BLUE_API_OBEX_SYNCH_MASK                          0x000F
#define BLUE_API_OBEX_OOP_MASK                            0x07F0

#define BLUE_API_OBEX_SYNCH_PHONEBOOK                     0x0001
#define BLUE_API_OBEX_SYNCH_CALENDAR                      0x0002
#define BLUE_API_OBEX_SYNCH_NOTES                         0x0004
#define BLUE_API_OBEX_SYNCH_MESSANGES                     0x0008

#define BLUE_API_OBEX_OOP_VCARD_V2_1                      0x0010
#define BLUE_API_OBEX_OOP_VCARD_V3_0                      0x0020
#define BLUE_API_OBEX_OOP_VCAL_V1_0                       0x0040
#define BLUE_API_OBEX_OOP_ICAL_V2_0                       0x0080
#define BLUE_API_OBEX_OOP_VNOTE                           0x0100
#define BLUE_API_OBEX_OOP_VMESSAGE                        0x0200
#define BLUE_API_OBEX_OOP_ANY                             0x0400

#endif /* (F_BLUE_API_OBEX_SUPPORT) */

#if (F_BLUE_API_GATT_SUPPORT)
#if (F_BT_GATT_SERVER)
/** GATT Service identifier. */
typedef enum TBlueAPI_GATTServiceID
{
    blueAPI_ServiceApplicationDefined = 0x00, /**< Application-defined GATT service */
#if (F_BLUE_API_DIS_SUPPORT)
    blueAPI_ServiceDIS                = 0x01, /**< Built-in Device Information Service (DIS) */
#endif /* (F_BLUE_API_DIS_SUPPORT) */
#ifdef V_BLUECODE_MAYBE_OBSOLETE
#if (F_BT_GATT_SVC_GLS)
    blueAPI_ServiceGLS                = 0x02, /**< Built-in Glucose Service (GLS) */
#endif /* (F_BT_GATT_SVC_GLS) */
#endif
#if (F_BLUE_API_BAS_SUPPORT)
    blueAPI_ServiceBAS                = 0x03, /**< Built-in Battery Service (BAS) */
#endif /* (F_BLUE_API_BAS_SUPPORT) */
#ifdef V_BLUECODE_MAYBE_OBSOLETE
#if (F_BT_GATT_SVC_CTS)
    blueAPI_ServiceCTS                = 0x04, /**< Built-in Current Time Service (CTS) */
#endif /* (F_BT_GATT_SVC_CTS) */
#if (F_BT_GATT_SVC_NDCS)
    blueAPI_ServiceNDCS               = 0x05, /**< Built-in Next DST Change Service (NDCS) */
#endif /* (F_BT_GATT_SVC_NDCS) */
#if (F_BT_GATT_SVC_RTUS)
    blueAPI_ServiceRTUS               = 0x06, /**< Built-in Reference Time Update service (RTUS) */
#endif /* (F_BT_GATT_SVC_RTUS) */
#if (F_BT_GATT_SVC_BLS)
    blueAPI_ServiceBLS                = 0x07, /**< Built-in Blood Pressure service (BLS) */
#endif /* (F_BT_GATT_SVC_BLS) */
#if (F_BT_GATT_SVC_HRS)
    blueAPI_ServiceHRS                = 0x08, /**< Built-in Heart Rate service (HRS) */
#endif /* (F_BT_GATT_SVC_HRS) */
    /* the following services are not (yet) available as built-in services:   */
    blueAPI_ServiceCGM                = 0x09,                      /* Continous Glucose Monitor service */
    blueAPI_ServiceBMS                = 0x0A,                      /* Bond Management service       */
    blueAPI_ServiceQUL                = 0x0B,                      /* Qualification test service    */
    blueAPI_ServiceTST                = 0x0C, /* Test service                  */
#endif
#if (F_BLUE_API_HOGP_SUPPORT)
    blueAPI_ServiceHOGP               = 0x80, /**< Built-in HID-over-GATT Service (HoGP) */
    blueAPI_ServiceHOGPNoMITM         = 0x81, /**< Built-in HID-over-GATT Service (HoGP), without MITM protection */
#endif /* (F_BLUE_API_HOGP_SUPPORT) */
#if (F_BLUE_API_TIO_SUPPORT)
    blueAPI_ServiceTIO                = 0x82, /**< Built-in Telit's proprietary Terminal I/O service (TIO) */
#endif /* (F_BLUE_API_TIO_SUPPORT) */
} TBlueAPI_GATTServiceID;

/** External GATT data storage access operation. There are two kinds of GATT information that can be stored per peer device: CCC Bit Blobs and Service Changed Handles/Flags */
typedef enum
{
    blueAPI_GATTStoreOpGetCCCBits,       /**< (Read access) (Individual) Read the CCC bits blob for a known peer device */
    blueAPI_GATTStoreOpSetCCCBits,       /**< (Write access) (Individual) Store a CCC bits blob for a known peer device. If no data is provided, the associated entry shall be deleted */
    blueAPI_GATTStoreOpGetAllCCCBits,    /**< (Read access) (Universal) Read the CCC bits blobs for all known peer devices */
    blueAPI_GATTStoreOpDeleteAllCCCBits, /**< (Delete access) (Universal) Delete the CCC bits blobs for all known peer devices */
    blueAPI_GATTStoreOpGetSrvChg,        /**< (Read access) (Individual) Read the Service Changed Handle/Flag for a known peer device */
    blueAPI_GATTStoreOpSetSrvChg,        /**< (Write access) (Individual) Store the Service Changed Handle/Flag for a known peer device */
    blueAPI_GATTStoreOpSetSrvChgFlag     /**< (Write access) (Universal) Set the byte of the Service Changed Handle/Flag data at offset #BLUEAPI_GATTSTORE_SRVCHG_OFFSET to 1 for all known peer devices */
} TBlueAPI_GATTStoreOpCode;
#endif /* (F_BT_GATT_SERVER) */

#if (F_BT_GATT_CLIENT)
/** Type of GATT discovery operation. */
typedef enum
{
    blueAPI_GATTDiscoveryServices          = 0x01, /**< Discovers all primary services. This implements the sub-procedure defined in:
                                                        @btspec{5.0,3,G,4.4.1,Discover All Primary Services} */
    blueAPI_GATTDiscoveryServiceByUUID     = 0x02, /**< Discovers a primary service by its UUID. This implements the sub-procedure defined in:
                                                        @btspec{5.0,3,G,4.4.2,Discover Primary Service by Service UUID} */
    blueAPI_GATTDiscoveryCharacteristics   = 0x03, /**< Discovers all characteristics (in a range). This implements the sub-procedure defined in:
                                                        @btspec{5.0,3,G,4.6.1,Discover All Characteristics of a Service} */
    blueAPI_GATTDiscoveryCharacDescriptors = 0x04, /**< Discovers all characteristic descriptors in a range. This implements the sub-procedure defined in:
                                                        @btspec{5.0,3,G,4.7.1,Discover All Characteristic Descriptors}
                                                        Note that when a range is specified that is not a characteristic handle range, BlueCode+ will discover all discoverable GATT elements
                                                        in that range, not just characteristic descriptors */
    blueAPI_GATTDiscoveryRelationship      = 0x05, /**< Discovers all include service declarations (service relationships) in a range. This implements the sub-procedure defined in:
                                                        @btspec{5.0,3,G,4.5.1,Find Included Services} */
} TBlueAPI_GATTDiscoveryType;

/** Type of GATT read operation. */
typedef enum
{
    blueAPI_GATTReadTypeBasic  = 0x01, /**< Reads an attribute with a known handle. This implements the sub-procedures defined in:
                                            @btspec{5.0,3,G,4.8.1,Read Characteristic Value}
                                            @btspec{5.0,3,G,4.8.3,Read Long Characteristic Values} */
    blueAPI_GATTReadTypeByUUID = 0x02, /**< Reads an attribute with a known UUID. This implements the sub-procedure defined in:
                                            @btspec{5.0,3,G,4.8.2,Read Using Characteristic UUID}
                                            This also implicitly provides the functionality of the sub-procedure defined in:
                                            @btspec{5.0,3,G,4.6.2,Discover Characteristics by UUID} */
} TBlueAPI_GATTReadType;

/** Type of GATT write operation. */
typedef enum
{
    blueAPI_GATTWriteTypeRequest     = 0x01, /**< Writes an attribute value, requiring an acknowledgment. This implements the sub-procedure defined in:
                                                  @btspec{5.0,3,G,4.9.3,Write Characteristic Value} */
    blueAPI_GATTWriteTypeCommand     = 0x02, /**< Writes an attribute value, not requiring an acknowledgment. This implements the sub-procedure defined in:
                                                  @btspec{5.0,3,G,4.9.1,Write Without Response} */
#if (F_BT_ATT_PREP_EXEC_WRITE)
#error "Missing documentation here"
    blueAPI_GATTWriteTypePrepRequest = 0x03,
#endif /* (F_BT_ATT_PREP_EXEC_WRITE) */
} TBlueAPI_GATTWriteType;
#endif /* (F_BT_GATT_CLIENT) */

/** ATT layer status codes (used for @p subcause parameters) */
typedef enum
{
    blueAPI_ATT_ERR_INVALID_HANDLE              = 0x0701, /**< An attribute handle value was not valid on the attribute server */
    blueAPI_ATT_ERR_READ_NOT_PERMITTED          = 0x0702, /**< An attribute read operation was not permitted */
    blueAPI_ATT_ERR_WRITE_NOT_PERMITTED         = 0x0703, /**< An attribute write operation was not permitted */
    blueAPI_ATT_ERR_INVALID_PDU                 = 0x0704, /**< An Attribute PDU was invalid */
    blueAPI_ATT_ERR_INSUFFICIENT_AUTHENTICATION = 0x0705, /**< An attribute operation could not be performed due to lack of authentication */
    blueAPI_ATT_ERR_UNSUPPORTED_REQUEST         = 0x0706, /**< An attribute server did not support the request received from the attribute client */
    blueAPI_ATT_ERR_INVALID_OFFSET              = 0x0707, /**< A specified offset was past the end of the attribute */
    blueAPI_ATT_ERR_INSUFFICIENT_AUTHORIZATION  = 0x0708, /**< An attribute operation could not be performed due to lack of authorization */
#if (F_BT_ATT_PREP_EXEC_WRITE)
    blueAPI_ATT_ERR_PREPARE_QUEUE_FULL          = 0x0709,
    #error "Missing documentation here"
#endif /* (F_BT_ATT_PREP_EXEC_WRITE) */
    blueAPI_ATT_ERR_ATTR_NOT_FOUND              = 0x070A, /**< No attribute was found within the given attribute handle range */
    blueAPI_ATT_ERR_ATTR_NOT_LONG               = 0x070B, /**< An attribute could not be read or written using the Read Blob Request or Prepare Write Request */
    blueAPI_ATT_ERR_INSUFFICIENT_KEY_SIZE       = 0x070C, /**< The Encryption Key Size of the link is insufficient for the requested attribute operation */
    blueAPI_ATT_ERR_INVALID_VALUE_SIZE          = 0x070D, /**< The attribute value length is invalid for the operation */
    blueAPI_ATT_ERR_UNLIKELY                    = 0x070E, /**< An attribute request that was requested has encountered an error that was very unlikely, and therefore could not be completed as requested */
    blueAPI_ATT_ERR_INSUFFICIENT_ENCRYPTION     = 0x070F, /**< An attribute operation could not be performed due to lack of encryption */
    blueAPI_ATT_ERR_UNSUPPORTED_GROUP_TYPE      = 0x0710, /**< The attribute type is not a supported grouping attribute */
    blueAPI_ATT_ERR_INSUFFICIENT_RESOURCES      = 0x0711, /**< Insufficient Resources to complete the request */
} TBlueAPI_ATTSubcause;

/** GATT layer status codes (used for @p subcause parameters) */
typedef enum
{
    blueAPI_GATT_ERR_OUT_OF_RESOURCE   = 0x0C01, /**< Insufficient Resources to complete the request */
    blueAPI_GATT_ERR_UNSUPPORTED       = 0x0C02, /**< The requested GATT operation is not supported by the local device */
    blueAPI_GATT_ERR_ILLEGAL_ROLE      = 0x0C03, /**< The requested operation is not applicable to the current GAP role */
    blueAPI_GATT_ERR_ILLEGAL_STATE     = 0x0C04, /**< The requested operation is not applicable to the current state of BlueCode+ */
    blueAPI_GATT_ERR_ILLEGAL_CODING    = 0x0C05, /**< The local or remote GATT server contains an invalid or unsupported service structure */
    blueAPI_GATT_ERR_ILLEGAL_PARAMETER = 0x0C07, /**< The request contained an invalid parameter and has been ignored */
    blueAPI_GATT_ERR_INTERNAL          = 0x0C08, /**< An unspecified GATT-related error occurred */
    blueAPI_GATT_ERR_NOT_ALLOWED       = 0x0C09, /**< The local properties of the attribute do not allow the requested operation */
    blueAPI_GATT_ERR_NOTIF_IND_NOT_CFG = 0x0C0A, /**< A GATT connection exists, but the CCCD for the characteristic is not set up for notifications/indications */
    blueAPI_GATT_ERR_NOTIF_IND_CFG     = 0x0C0B, /**< No notification/indication has been generated since no GATT connection exists */
    blueAPI_GATT_ERR_NOTIF_IND_CONF_PD = 0x0C0C, /**< An indication has been generated, but the client's confirmation is still pending */
    blueAPI_GATT_ERR_TIMEOUT           = 0x0C0D, /**< A timeout expired while waiting for a confirmation or response */
    blueAPI_GATT_ERR_LINK_DEACTIVATED  = 0x0C0E, /**< The underlying GATT link has been disconnected / lost */
    blueAPI_GATT_ERR_NOT_AUTHENTICATED = 0x0C0F, /**< The requested operation could not be performed due to lack of authentication */
} TBlueAPI_GATTSubcause;

/** GATT security requirement (bitmask). */
typedef enum
{
    blueAPI_GATTSecurityRequireMITM  = 1 << 0, /**< Requires protection against Man-in-the-Middle attacks (MITM secure pairing) */
    blueAPI_GATTSecurityForcePairing = 1 << 1, /**< Force a new authentication instead of using bonding information (stored keys) */
} TBlueAPI_GATTSecurityRequirement;
#endif /* (F_BLUE_API_GATT_SUPPORT) */

#if (F_BT_LOW_ENERGY)
/** Bluetooth Low Energy (LE) advertising mode. */
typedef enum
{
    blueAPI_LEAdvModeDisabled   = 0x00, /**< Not advertising */
    blueAPI_LEAdvModeUndirected = 0x01, /**< Performing LE Undirected Advertising */
    blueAPI_LEAdvModeDirected   = 0x02, /**< Performing LE Connectable Directed Advertising */
} TBlueAPI_LEAdvMode;

/** Bluetooth Low Energy (LE) Advertisement PDU Type. */
typedef enum
{
    blueAPI_LEAdvTypeUndirected     = 0x00, /**< Connectable Undirected Advertising (corresponds to link layer PDU type ADV_IND) */
    blueAPI_LEAdvTypeDirected       = 0x01, /**< Connectable Directed Advertising (corresponds to link layer PDU type ADV_DIRECT_IND) */
    blueAPI_LEAdvTypeScannable      = 0x02, /**< Scannable Undirected Advertising (corresponds to link layer PDU type ADV_SCAN_IND) */
    blueAPI_LEAdvTypeNonConnectable = 0x03, /**< Non-connectable Undirected Advertising (corresponds to link layer PDU type ADV_NONCONN_IND) */
    blueAPI_LEAdvTypeScanResponse   = 0x04, /**< Scan Response (corresponds to link layer PDU type SCAN_RSP) */
} TBlueAPI_LEAdvType;

/** Bluetooth Low Energy (LE) remote device filter policy. */
typedef enum
{
    blueAPI_LEFilterAny       = 0x00, /**< Remote devices are not filtered */
    blueAPI_LEFilterWhitelist = 0x01, /**< Remote device are filtered against the controller's whitelist */
} TBlueAPI_LEFilterPolicy;

/** Bluetooth Low Energy (LE) type of advertisement PDU payload. */
typedef enum
{
    blueAPI_LEDataTypeAdvertisingData  = 0x00, /**< Payload of an Undirected Advertisement PDU */
    blueAPI_LEDataTypeScanResponseData = 0x01, /**< Payload of a Scan Response PDU */
} TBlueAPI_LEDataType;

/** Bluetooth Low Energy (LE) scanning mode. */
typedef enum
{
    blueAPI_LEScanDisabled = 0x00, /**< Not scanning */
    blueAPI_LEScanPassive  = 0x01, /**< Performing Passive Scanning */
    blueAPI_LEScanActive   = 0x02, /**< Performing Active Scanning */
} TBlueAPI_LEScanMode;

/** Bluetooth Low Energy (LE) whitelist modification type. */
typedef enum
{
    blueAPI_LEWhitelistOpClear  = 0x00, /**< The whitelist is cleared */
    blueAPI_LEWhitelistOpAdd    = 0x01, /**< An entry is added to the whitelist */
    blueAPI_LEWhitelistOpRemove = 0x02, /**< An entry is removed from the whitelist */
} TBlueAPI_LEWhitelistOp;

#if (F_BT_LE_PRIVACY_MODE)
#error "Missing documentation here"
typedef enum
{
    blueAPI_LEPrivacyDisabled = 0,
    blueAPI_LEPrivacyPrivateStatic,
    blueAPI_LEPrivacyNonResolvable,
    blueAPI_LEPrivacyResolvable,
    blueAPI_LEPrivacyNewResolvable,
} TBlueAPI_LEPrivacyMode;
#endif /* (F_BT_LE_PRIVACY_MODE) */
#endif /* (F_BT_LOW_ENERGY) */

#if (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM)
#error "Missing documentation here"
typedef enum
{
    blueAPI_TestmodeHCIDIRECT = 1,
    blueAPI_TestmodeBEDUTM,
} TBlueAPI_Testmode;
#endif /* (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM) */

#if defined (__cplusplus)
}
#endif

#endif /* ndef __BLUECODE_BLUEAPI_DATATYPES_H */
