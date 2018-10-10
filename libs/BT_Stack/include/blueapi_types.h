/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/blueapi_types.h,v $
 * Revision:    $Revision: 1.98 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_BLUEAPI_TYPES_H
#define __BLUECODE_BLUEAPI_TYPES_H

/** @file
 * Data types for BlueAPI interface of BlueCode+ (External message interface). BlueAPI application code that shall process or construct BlueAPI message should include this header. */

#ifndef V_BLUECODE_EXPORTED
#include "flags.h"                  // Variant management
#endif
#include "blueapi_datatypes.h"      // BlueAPI data types
#include "blueapi_msg_upstream.h"   // BlueAPI upstream message interface
#include "blueapi_msg_downstream.h" // BlueAPI downstream message interface

#if defined (__cplusplus)
extern "C" {
#endif

/** Variable-sized message data of a BlueAPI message. See #TBlueAPI_Message. */
typedef union TBlueAPI_CommandData
{
    /** @name Message-specific parameters */
    /** @{ */
    TBlueAPI_Generic                        Generic;          /**< BlueAPI message-specific parameters */
    TBlueAPI_ConnectMDLReq                  ConnectMDLReq;
    TBlueAPI_ConnectMDLRsp                  ConnectMDLRsp;
#if (F_BLUE_API_RECONNECT_SUPPORT)
    TBlueAPI_ReconnectMDLReq                ReconnectMDLReq;
    TBlueAPI_ReconnectMDLRsp                ReconnectMDLRsp;
    TBlueAPI_ReconnectMDLInd                ReconnectMDLInd;
#endif /* (F_BLUE_API_RECONNECT_SUPPORT) */
    TBlueAPI_ReconnectMDLConf               ReconnectMDLConf;
    TBlueAPI_DisconnectMDLReq               DisconnectMDLReq;
    TBlueAPI_DisconnectMDLRsp               DisconnectMDLRsp;
    TBlueAPI_DisconnectMDLInd               DisconnectMDLInd;
    TBlueAPI_DisconnectMDLConf              DisconnectMDLConf;
    TBlueAPI_CreateMDLInd                   CreateMDLInd;
    TBlueAPI_CreateMDLConf                  CreateMDLConf;
    TBlueAPI_DeleteMDLInfo                  DeleteMDLInfo;
    TBlueAPI_ConnectMDLInfo                 ConnectMDLInfo;
    TBlueAPI_MCLStatusInfo                  MCLStatusInfo;
    TBlueAPI_ACLStatusInfo                  ACLStatusInfo;
    TBlueAPI_RegisterReq                    RegisterReq;
    TBlueAPI_RegisterRsp                    RegisterRsp;
    TBlueAPI_ReleaseReq                     ReleaseReq;
    TBlueAPI_ReleaseInd                     ReleaseInd;
    TBlueAPI_ReleaseConf                    ReleaseConf;
    TBlueAPI_ReleaseRsp                     ReleaseRsp;
    TBlueAPI_ActInfo                        ActInfo;
    TBlueAPI_DeactInfo                      DeactInfo;
    TBlueAPI_InternalEventInfo              InternalEventInfo;
#if (F_BLUE_API_HDP_SUPPORT)
    TBlueAPI_RegHDPMDEPReq                  RegHDPMDEPReq;
    TBlueAPI_RegHDPMDEPRsp                  RegHDPMDEPRsp;
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT)
    TBlueAPI_RegSPPMDEPReq                  RegSPPMDEPReq;
    TBlueAPI_RegSPPMDEPRsp                  RegSPPMDEPRsp;
#endif /* (F_BLUE_API_SPP_SUPPORT) */
#if (F_BLUE_API_HID_SUPPORT)
    TBlueAPI_RegHIDMDEPReq                  RegHIDMDEPReq;
    TBlueAPI_RegHIDMDEPRsp                  RegHIDMDEPRsp;
#endif /* (F_BLUE_API_HID_SUPPORT) */
#if (F_BLUE_API_OBEX_SUPPORT)
    TBlueAPI_RegOBEXMDEPReq                 RegOBEXMDEPReq;
    TBlueAPI_RegOBEXMDEPRsp                 RegOBEXMDEPRsp;
#endif /* (F_BLUE_API_OBEX_SUPPORT) */
#if (F_BLUE_API_L2CAP_SUPPORT)
    TBlueAPI_RegL2CAPMDEPReq                RegL2CAPMDEPReq;
    TBlueAPI_RegL2CAPMDEPRsp                RegL2CAPMDEPRsp;
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */
    TBlueAPI_RelMDEPReq                     RelMDEPReq;
    TBlueAPI_RelMDEPRsp                     RelMDEPRsp;
    TBlueAPI_DataReq                        DataReq;
    TBlueAPI_DataRsp                        DataRsp;
    TBlueAPI_DataInd                        DataInd;
    TBlueAPI_DataConf                       DataConf;
    TBlueAPI_InquiryReq                     InquiryReq;
    TBlueAPI_InquiryRsp                     InquiryRsp;
    TBlueAPI_InquiryDeviceInfo              InquiryDeviceInfo;
    TBlueAPI_DeviceNameReq                  DeviceNameReq;
    TBlueAPI_DeviceNameRsp                  DeviceNameRsp;
#if (F_BLUE_API_HDP_SUPPORT)
    TBlueAPI_HDPDiscoveryReq                HDPDiscoveryReq;
    TBlueAPI_HDPDiscoveryRsp                HDPDiscoveryRsp;
#endif /* (F_BLUE_API_HDP_SUPPORT) */
    TBlueAPI_DIDDeviceInd                   DIDDeviceInd;
    TBlueAPI_DIDDeviceConf                  DIDDeviceConf;
#if (F_BLUE_API_HDP_SUPPORT)
    TBlueAPI_HDPServiceInd                  HDPServiceInd;
    TBlueAPI_HDPServiceConf                 HDPServiceConf;
    TBlueAPI_HDPEndpointInd                 HDPEndpointInd;
    TBlueAPI_HDPEndpointConf                HDPEndpointConf;
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT)
    TBlueAPI_SPPDiscoveryReq                SPPDiscoveryReq;
    TBlueAPI_SPPDiscoveryRsp                SPPDiscoveryRsp;
    TBlueAPI_SPPEndpointInd                 SPPEndpointInd;
    TBlueAPI_SPPEndpointConf                SPPEndpointConf;
#endif /* (F_BLUE_API_SPP_SUPPORT) */
#if (F_BLUE_API_OBEX_SUPPORT)
    TBlueAPI_OBEXDiscoveryReq               OBEXDiscoveryReq;
    TBlueAPI_OBEXDiscoveryRsp               OBEXDiscoveryRsp;
    TBlueAPI_OBEXEndpointInd                OBEXEndpointInd;
    TBlueAPI_OBEXEndpointConf               OBEXEndpointConf;
#endif /* (F_BLUE_API_OBEX_SUPPORT) */
    TBlueAPI_RadioModeSetReq                RadioModeSetReq;
    TBlueAPI_RadioModeSetRsp                RadioModeSetRsp;
    TBlueAPI_DeviceConfigSetReq             DeviceConfigSetReq;
    TBlueAPI_DeviceConfigSetRsp             DeviceConfigSetRsp;
#if (F_BLUE_API_GATT_SUPPORT)
#if (F_BT_GATT_SERVER)
    TBlueAPI_GATTServiceRegisterReq         GATTServiceRegisterReq;
    TBlueAPI_GATTServiceRegisterRsp         GATTServiceRegisterRsp;
    TBlueAPI_GATTAttributeUpdateReq         GATTAttributeUpdateReq;
    TBlueAPI_GATTAttributeUpdateRsp         GATTAttributeUpdateRsp;
    TBlueAPI_GATTAttributeUpdateStatusInd   GATTAttributeUpdateStatusInd;
    TBlueAPI_GATTAttributeUpdateStatusConf  GATTAttributeUpdateStatusConf;
    TBlueAPI_GATTAttributeReadInd           GATTAttributeReadInd;
    TBlueAPI_GATTAttributeReadConf          GATTAttributeReadConf;
    TBlueAPI_GATTAttributeWriteInd          GATTAttributeWriteInd;
    TBlueAPI_GATTAttributeWriteConf         GATTAttributeWriteConf;
    TBlueAPI_GATTAttributeWriteCommandInfo  GATTAttributeWriteCommandInfo;
#if (F_BT_ATT_PREP_EXEC_WRITE)
    TBlueAPI_GATTAttributePrepareWriteInd   GATTAttributePrepareWriteInd;
    TBlueAPI_GATTAttributePrepareWriteConf  GATTAttributePrepareWriteConf;
    TBlueAPI_GATTExecuteWriteInd            GATTExecuteWriteInd;
    TBlueAPI_GATTExecuteWriteConf           GATTExecuteWriteConf;
#endif
    TBlueAPI_GATTCCCDInfo                   GATTCCCDInfo;
#endif /* (F_BT_GATT_SERVER) */
#if (F_BT_GATT_CLIENT)
    TBlueAPI_GATTDiscoveryReq               GATTDiscoveryReq;
    TBlueAPI_GATTDiscoveryRsp               GATTDiscoveryRsp;
    TBlueAPI_GATTDiscoveryInd               GATTDiscoveryInd;
    TBlueAPI_GATTDiscoveryConf              GATTDiscoveryConf;
    TBlueAPI_GATTAttributeReadReq           GATTAttributeReadReq;
    TBlueAPI_GATTAttributeReadRsp           GATTAttributeReadRsp;
    TBlueAPI_GATTAttributeWriteReq          GATTAttributeWriteReq;
    TBlueAPI_GATTAttributeWriteRsp          GATTAttributeWriteRsp;
#if (F_BT_ATT_PREP_EXEC_WRITE)
    TBlueAPI_GATTExecuteWriteReq            GATTExecuteWriteReq;
    TBlueAPI_GATTExecuteWriteRsp            GATTExecuteWriteRsp;
#endif
    TBlueAPI_GATTAttributeInd               GATTAttributeInd;
    TBlueAPI_GATTAttributeConf              GATTAttributeConf;
    TBlueAPI_GATTAttributeNotificationInfo  GATTAttributeNotificationInfo;
#if (F_BLUE_API_GATT_SDP_DIS_SUPPORT)
    TBlueAPI_GATTSDPDiscoveryReq            GATTSDPDiscoveryReq;
    TBlueAPI_GATTSDPDiscoveryRsp            GATTSDPDiscoveryRsp;
    TBlueAPI_GATTSDPDiscoveryInd            GATTSDPDiscoveryInd;
    TBlueAPI_GATTSDPDiscoveryConf           GATTSDPDiscoveryConf;
#endif /* (F_BLUE_API_GATT_SDP_DIS_SUPPORT) */
#endif /* (F_BT_GATT_CLIENT) */
    TBlueAPI_GATTSecurityReq                GATTSecurityReq;
    TBlueAPI_GATTSecurityRsp                GATTSecurityRsp;
    TBlueAPI_GATTServerStoreInd             GATTServerStoreInd;
    TBlueAPI_GATTServerStoreConf            GATTServerStoreConf;
    TBlueAPI_GATTMtuSizeInfo                GATTMtuSizeInfo;
#endif /* (F_BLUE_API_GATT_SUPPORT) */
    TBlueAPI_PairableModeSetReq             PairableModeSetReq;
    TBlueAPI_PairableModeSetRsp             PairableModeSetRsp;
    TBlueAPI_UserAuthorizationReqInd        UserAuthorizationReqInd;
    TBlueAPI_UserAuthorizationReqConf       UserAuthorizationReqConf;
    TBlueAPI_AuthReq                        AuthReq;
    TBlueAPI_AuthRsp                        AuthRsp;
    TBlueAPI_UserAuthRequestInd             UserAuthRequestInd;
    TBlueAPI_UserAuthRequestConf            UserAuthRequestConf;
    TBlueAPI_AuthResultRequestInd           AuthResultRequestInd;
    TBlueAPI_AuthResultRequestConf          AuthResultRequestConf;
    TBlueAPI_UserConfirmationReqInd         UserConfirmationReqInd;
    TBlueAPI_UserConfirmationReqConf        UserConfirmationReqConf;
    TBlueAPI_UserPasskeyReqInd              UserPasskeyReqInd;
    TBlueAPI_UserPasskeyReqConf             UserPasskeyReqConf;
    TBlueAPI_UserPasskeyReqReplyReq         UserPasskeyReqReplyReq;
    TBlueAPI_UserPasskeyReqReplyRsp         UserPasskeyReqReplyRsp;
    TBlueAPI_UserPasskeyNotificationInfo    UserPasskeyNotificationInfo;
    TBlueAPI_KeypressNotificationReq        KeypressNotificationReq;
    TBlueAPI_KeypressNotificationRsp        KeypressNotificationRsp;
    TBlueAPI_KeypressNotificationInfo       KeypressNotificationInfo;
    TBlueAPI_RemoteOOBDataReqInd            RemoteOOBDataReqInd;
    TBlueAPI_RemoteOOBDataReqConf           RemoteOOBDataReqConf;
    TBlueAPI_LocalOOBDataReq                LocalOOBDataReq;
    TBlueAPI_LocalOOBDataRsp                LocalOOBDataRsp;
    TBlueAPI_AuthResultInd                  AuthResultInd;
    TBlueAPI_AuthResultConf                 AuthResultConf;
    TBlueAPI_AuthDeleteReq                  AuthDeleteReq;
    TBlueAPI_AuthDeleteRsp                  AuthDeleteRsp;
    TBlueAPI_AuthListReq                    AuthListReq;
    TBlueAPI_AuthListInfo                   AuthListInfo;
    TBlueAPI_AuthListRsp                    AuthListRsp;
#if (F_BLUE_API_HCI_TUNNEL_SUPPORT)
    TBlueAPI_HCITunnelReq                   HCITunnelReq;
    TBlueAPI_HCITunnelRsp                   HCITunnelRsp;
#endif /* (F_BLUE_API_HCI_TUNNEL_SUPPORT) */
#if (F_BT_LOW_ENERGY)
    TBlueAPI_LEAdvertiseReq                 LEAdvertiseReq;
    TBlueAPI_LEAdvertiseRsp                 LEAdvertiseRsp;
    TBlueAPI_LEAdvertiseParameterSetReq     LEAdvertiseParameterSetReq;
    TBlueAPI_LEAdvertiseParameterSetRsp     LEAdvertiseParameterSetRsp;
    TBlueAPI_LEAdvertiseDataSetReq          LEAdvertiseDataSetReq;
    TBlueAPI_LEAdvertiseDataSetRsp          LEAdvertiseDataSetRsp;
    TBlueAPI_LEScanReq                      LEScanReq;
    TBlueAPI_LEScanRsp                      LEScanRsp;
    TBlueAPI_LEScanInfo                     LEScanInfo;
    TBlueAPI_LEModifyWhitelistReq           LEModifyWhitelistReq;
    TBlueAPI_LEModifyWhitelistRsp           LEModifyWhitelistRsp;
    TBlueAPI_LEConnectionUpdateReq          LEConnectionUpdateReq;
    TBlueAPI_LEConnectionUpdateRsp          LEConnectionUpdateRsp;
    TBlueAPI_LEConnectionUpdateInd          LEConnectionUpdateInd;
    TBlueAPI_LEConnectionUpdateConf         LEConnectionUpdateConf;
    TBlueAPI_LEConnectionParameterInfo      LEConnectionParameterInfo;
#if (F_BT_LE_PRIVACY_MODE)
    TBlueAPI_LEPrivacyModeReq               LEPrivacyModeReq;
    TBlueAPI_LEPrivacyModeRsp               LEPrivacyModeRsp;
#endif /* (F_BT_LE_PRIVACY_MODE) */
#endif /* (F_BT_LOW_ENERGY) */
#if (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM)
    TBlueAPI_TestmodeReq                    TestmodeReq;
    TBlueAPI_TestmodeRsp                    TestmodeRsp;
#endif /* (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM) */
    TBlueAPI_ACLConfigReq                   ACLConfigReq;
    TBlueAPI_ACLConfigRsp                   ACLConfigRsp;
#if (F_BLUE_API_HID_SUPPORT)
    TBlueAPI_HIDMessageReq                  HIDMessageReq;
    TBlueAPI_HIDMessageRsp                  HIDMessageRsp;
    TBlueAPI_HIDMessageInd                  HIDMessageInd;
    TBlueAPI_HIDMessageConf                 HIDMessageConf;
#endif /* (F_BLUE_API_HID_SUPPORT) */
#if (F_APPLE_IAP2)
    TBlueAPI_IAP2MessageReq                 IAP2MessageReq;
    TBlueAPI_IAP2MessageRsp                 IAP2MessageRsp;
    TBlueAPI_IAP2MessageInd                 IAP2MessageInd;
    TBlueAPI_IAP2MessageConf                IAP2MessageConf;
#endif /* (F_APPLE_IAP2) */
#if (F_BLUE_API_BAS_SUPPORT)
    TBlueAPI_BatteryLevelSetReq             BatteryLevelSetReq;
    TBlueAPI_BatteryLevelSetRsp             BatteryLevelSetRsp;
#endif /* (F_BLUE_API_BAS_SUPPORT) */
    /** @} */
} TBlueAPI_CommandData, * PBlueAPI_CommandData;

/** BlueAPI message. Minimal communication unit of the general message protocol followed by the client application and BlueAPI */
typedef struct TBlueAPI_Message
{
    TBlueAPI_Command Command; /**< Message command identifier. Also serves as a union tag for #p: If Command is blueAPI_Event\<name\>, the field \<name\> of p with type TBlueAPI_\<name\> is set */
    uint16_t Length;          /**< Total length of the message in #p, including its complete inner message header */
    TBlueAPI_CommandData p;   /**< Message data containing fixed size header, gap and variable size payload (message parameters) */
} TBlueAPI_Message, * PBlueAPI_Message;

/** Callback for the client application to implement to receive BlueAPI messages from BlueCode+.
 * @param message [in,out] BlueAPI upstream message (Response, Indication or Information) */
typedef void (* BlueAPICallback) (
        PBlueAPI_Message message);

#ifdef V_BLUECODE_MAYBE_OBSOLETE
typedef struct _TBlueAPI_Reg
{
    char comPort[32];
} TBlueAPI_Reg;
typedef TBlueAPI_Reg * LPBlueAPI_Reg;

/*--------------------------------------------------------*/
/*                    function prototypes                 */
/*--------------------------------------------------------*/
void blueAPI_Startup(LPBlueAPI_Reg pReg);
void blueAPI_Shutdown(void);
#endif

#ifdef V_BLUECODE_INTERNAL
bool blueAPI_PutMessage(void * pBuffer, PBlueAPI_Message pMsg);
#endif

#ifdef V_BLUECODE_MAYBE_OBSOLETE
/* function pointers for BlueAPI Interface functions */
typedef void (* PBlueAPI_Startup)(LPBlueAPI_Reg pReg);
typedef void (* PBlueAPI_Shutdown)(void);

typedef bool (* PBlueAPI_PutMessage)(void * pBuffer, PBlueAPI_Message pMsg);

typedef TBlueAPI_Cause (* PBlueAPI_BufferGet)(
        TBlueAPIHandle blueAPIHandle,
        uint16_t  local_MDL_ID,
        uint16_t  dsPoolID,
        uint16_t  dsTPDUSize,
        uint16_t  dsDataOffset,
        void    **ppBuffer
);

typedef TBlueAPI_Cause (* PBlueAPI_BufferRelease)(
        TBlueAPIHandle blueAPIHandle,
        void *  pBuffer
);
#endif

#if defined (__cplusplus)
}
#endif

#endif /* ndef __BLUECODE_BLUEAPI_TYPES_H */
