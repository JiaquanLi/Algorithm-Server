/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/blueapi_msg_downstream.h,v $
 * Revision:    $Revision: 2.1 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_BLUEAPI_MSG_DOWNSTREAM_H
#define __BLUECODE_BLUEAPI_MSG_DOWNSTREAM_H

/** @file
 * BlueAPI downstream interface of BlueCode+ (External message interface). BlueAPI application code that shall trigger BlueAPI operations by enqueueing messages should include this header. */

#ifndef V_BLUECODE_EXPORTED
#include "flags.h"             // Variant management
#endif
#include "blueapi_datatypes.h" // BlueAPI data types
#include "gatt.h"              // GATT data types

#ifdef __cplusplus
extern "C" {
#endif

// BlueAPI downstream message interface

/** @cond Doxygen_Ignored */

#if (F_BLUE_API_HDP_SUPPORT)
typedef struct TBlueAPI_ConnectMDLReqHDP
{
    uint16_t remote_Control_PSM;
    uint16_t remote_Data_PSM;
    uint8_t remote_MDEP_ID;
} TBlueAPI_ConnectMDLReqHDP, * PBlueAPI_ConnectMDLReqHDP;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
typedef struct TBlueAPI_ConnectMDLReqSPP
{
    uint8_t remote_MDEP_ID;
} TBlueAPI_ConnectMDLReqSPP, * PBlueAPI_ConnectMDLReqSPP;
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_BLUE_API_HID_SUPPORT)
typedef struct TBlueAPI_ConnectMDLReqHID
{
    uint8_t remote_MDEP_ID;
} TBlueAPI_ConnectMDLReqHID, * PBlueAPI_ConnectMDLReqHID;
#endif /* (F_BLUE_API_HID_SUPPORT) */

typedef struct TBlueAPI_ConnectMDLReqGATT
{
    uint16_t scanInterval;
    uint16_t scanWindow;
    uint16_t scanTimeout;
    uint16_t connIntervalMin;
    uint16_t connIntervalMax;
    uint16_t connLatency;
    uint16_t supervisionTimeout;
} TBlueAPI_ConnectMDLReqGATT, * PBlueAPI_ConnectMDLReqGATT;

typedef struct TBlueAPI_ConnectMDLReqL2CAP
{
    uint16_t remote_Data_PSM;
} TBlueAPI_ConnectMDLReqL2CAP, * PBlueAPI_ConnectMDLReqL2CAP;

typedef union TBlueAPI_ConnectMDLReqParam
{
#if (F_BLUE_API_HDP_SUPPORT)
    TBlueAPI_ConnectMDLReqHDP hdp;
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT)
    TBlueAPI_ConnectMDLReqSPP spp;
#endif /* (F_BLUE_API_SPP_SUPPORT) */
    TBlueAPI_ConnectMDLReqGATT gatt;
    TBlueAPI_ConnectMDLReqL2CAP l2cap;
#if (F_BLUE_API_HID_SUPPORT)
    TBlueAPI_ConnectMDLReqHID hid;
#endif /* (F_BLUE_API_HID_SUPPORT) */
} TBlueAPI_ConnectMDLReqParam, * PBlueAPI_ConnectMDLReqParam;

typedef struct TBlueAPI_ConnectMDLReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType remote_BD_Type;
    uint8_t local_MDEP_ID;
    TBlueAPI_LinkConfigType linkConfigType;
    TBlueAPI_ConnectMDLReqParam p;
} TBlueAPI_ConnectMDLReq, * PBlueAPI_ConnectMDLReq;

typedef struct TBlueAPI_CreateMDLConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_LinkConfigType linkConfigType;
    uint8_t maxTPDUusCredits;
    TBlueAPI_Cause cause;
}  TBlueAPI_CreateMDLConf, * PBlueAPI_CreateMDLConf;

typedef struct TBlueAPI_DisconnectMDLReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_Cause cause;
}  TBlueAPI_DisconnectMDLReq, * PBlueAPI_DisconnectMDLReq;

typedef struct TBlueAPI_DisconnectMDLConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
}  TBlueAPI_DisconnectMDLConf, * PBlueAPI_DisconnectMDLConf;

typedef struct TBlueAPI_ReconnectMDLReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    uint16_t remote_Control_PSM;
    uint16_t remote_Data_PSM;
}  TBlueAPI_ReconnectMDLReq, * PBlueAPI_ReconnectMDLReq;

typedef struct TBlueAPI_ReconnectMDLConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_Cause cause;
}  TBlueAPI_ReconnectMDLConf, * PBlueAPI_ReconnectMDLConf;

typedef struct TBlueAPI_RegisterReq
{
    TBlueAPIAppHandle appHandle;
    void * MDHmsgHandlerCallback;
    uint16_t MDHmsgHandlerQueueID;
    uint32_t apiVersion;
} TBlueAPI_RegisterReq, * PBlueAPI_RegisterReq;

typedef struct TBlueAPI_ReleaseReq
{
    TBlueAPIHandle blueAPIHandle;
} TBlueAPI_ReleaseReq, * PBlueAPI_ReleaseReq;

typedef struct TBlueAPI_ReleaseConf
{
    TBlueAPIHandle blueAPIHandle;
} TBlueAPI_ReleaseConf, * PBlueAPI_ReleaseConf;

typedef struct TBlueAPI_DataReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_FrameType frameType;
    uint16_t frameLength;
    uint16_t payloadLength;
    uint16_t gap;
    uint8_t data[1];
} TBlueAPI_DataReq, * PBlueAPI_DataReq;

typedef struct TBlueAPI_DataConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_Cause cause;
} TBlueAPI_DataConf, * PBlueAPI_DataConf;

typedef struct TBlueAPI_PairableModeSetReq
{
    TBlueAPIHandle blueAPIHandle;
    bool enablePairableMode;
    TBlueAPI_BluetoothMode BluetoothMode;
    TBlueAPI_AuthRequirements AuthRequirements;
    TBlueAPI_IOCapabilities IOCapabilities;
    bool remoteOOBDataPresent;
} TBlueAPI_PairableModeSetReq, * PBlueAPI_PairableModeSetReq;

typedef struct TBlueAPI_RadioModeSetReq
{
    TBlueAPIHandle blueAPIHandle;
    TBlueAPI_RadioMode localRadioMode;
    bool limitedDiscoverable;
} TBlueAPI_RadioModeSetReq, * PBlueAPI_RadioModeSetReq;

typedef struct TBlueAPI_DeviceConfigDevice
{
    uint32_t classOfDevice;
    uint8_t deviceName[BLUE_API_LOCAL_DEVICE_NAME_LENGTH];
} TBlueAPI_DeviceConfigDevice;

typedef struct TBlueAPI_DeviceConfigDID
{
    uint16_t vendorID;
    uint8_t vendorIDSource;
    uint16_t productID;
    uint16_t productVersion;
} TBlueAPI_DeviceConfigDID;

typedef struct TBlueAPI_DeviceConfigSecurity
{
    TBlueAPI_StoreBondModes storeBondMode;
    uint8_t storeBondSize;
    uint32_t leFixedDisplayValue;
} TBlueAPI_DeviceConfigSecurity;

#if (F_BLUE_API_HDP_SUPPORT)
typedef struct TBlueAPI_DeviceConfigHDP
{
    uint8_t reconnectEnable;
    uint16_t maxRxAPDUSize;
    uint8_t secMITMout;
    uint8_t secAUTHORout;
    uint8_t secMITMin;
    uint8_t secAUTHORin;
    uint8_t serviceName[BLUE_API_HDP_SERVICE_NAME_LENGTH];
} TBlueAPI_DeviceConfigHDP;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
typedef struct TBlueAPI_DeviceConfigSPP
{
    uint8_t secAUTHENout;
    uint8_t secENCRout;
    uint8_t secMITMout;
    uint8_t secAUTHORout;
} TBlueAPI_DeviceConfigSPP;
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_BLUE_API_L2CAP_SUPPORT)
typedef struct TBlueAPI_DeviceConfigL2CAP
{
    uint8_t secMITMout;
    uint8_t secAUTHORout;
} TBlueAPI_DeviceConfigL2CAP;
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */

typedef struct TBlueAPI_DeviceConfigPagescan
{
    TBlueAPI_BRPageScanType scanType;
    TBlueAPI_BRPageScanRepMode repMode;
    uint16_t repInterval;
    uint16_t repWindow;
    uint16_t pageTimeout;
} TBlueAPI_DeviceConfigPagescan;

typedef struct TBlueAPI_DeviceConfigInquiryScan
{
    TBlueAPI_BRInquiryScanType scanType;
    uint16_t scanInterval;
    uint16_t scanWindow;
} TBlueAPI_DeviceConfigInquiryScan;

typedef struct TBlueAPI_DeviceConfigLinkpolicy
{
    TBlueAPI_BRLinkPolicy linkPolicy;
    TBlueAPI_BRDeviceRole deviceRole;
    uint16_t supervisionTimeout;
} TBlueAPI_DeviceConfigLinkpolicy;

#if (BTEXT_RF_MAX_TX_PWR)
typedef struct TBlueAPI_DeviceConfigMaxTxPower
{
    int16_t txPower;
} TBlueAPI_DeviceConfigMaxTxPower;
#endif /* (BTEXT_RF_MAX_TX_PWR) */

typedef struct TBlueAPI_DeviceConfigSetReq
{
    TBlueAPIHandle blueAPIHandle;
    TBlueAPI_DeviceConfigOpcode opCode;
    union {
        TBlueAPI_DeviceConfigDevice device;
        TBlueAPI_DeviceConfigDID did;
        TBlueAPI_DeviceConfigSecurity security;
#if (F_BLUE_API_HDP_SUPPORT)
        TBlueAPI_DeviceConfigHDP hdp;
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_BLUE_API_SPP_SUPPORT)
        TBlueAPI_DeviceConfigSPP spp;
#endif /* (F_BLUE_API_SPP_SUPPORT) */
#if (F_BLUE_API_L2CAP_SUPPORT)
        TBlueAPI_DeviceConfigL2CAP l2cap;
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */
        TBlueAPI_DeviceConfigPagescan pagescan;
        TBlueAPI_DeviceConfigInquiryScan inquiryScan;
        TBlueAPI_DeviceConfigLinkpolicy linkpolicy;
#if (BTEXT_RF_MAX_TX_PWR)
        TBlueAPI_DeviceConfigMaxTxPower txpower;
#endif /* (BTEXT_RF_MAX_TX_PWR) */
    } p;
} TBlueAPI_DeviceConfigSetReq, * PBlueAPI_DeviceConfigSetReq;

typedef struct TBlueAPI_ACLConfigParamLinkpolicy
{
    TBlueAPI_BRLinkPolicy linkPolicy;
    TBlueAPI_BRDeviceRole deviceRole;
    uint16_t supervisionTimeout;
} TBlueAPI_ACLConfigParamLinkpolicy, * PBlueAPI_ACLConfigParamLinkpolicy;

typedef struct TBlueAPI_ACLConfigParamSniffmode
{
    uint16_t minInterval;
    uint16_t maxInterval;
    uint16_t sniffAttempt;
    uint16_t sniffTimeout;
    uint16_t maxLatency;
    uint16_t minRemoteTimeout;
    uint16_t minLocalTimeout;
} TBlueAPI_ACLConfigParamSniffmode, * PBlueAPI_ACLConfigParamSniffmode;

#if (F_BT_HCI_RADIO_STATUS_CONF)
typedef struct TBlueAPI_ACLConfigParamLinkstatus
{
    uint16_t pollInterval;
} TBlueAPI_ACLConfigParamLinkstatus, * PBlueAPI_ACLConfigParamLinkstatus;
#endif /* (F_BT_HCI_RADIO_STATUS_CONF) */

typedef union TBlueAPI_ACLConfigParam
{
    TBlueAPI_ACLConfigParamLinkpolicy linkpolicy;
    TBlueAPI_ACLConfigParamSniffmode sniffmode;
#if (F_BT_HCI_RADIO_STATUS_CONF)
    TBlueAPI_ACLConfigParamLinkstatus linkstatus;
#endif /* (F_BT_HCI_RADIO_STATUS_CONF) */
} TBlueAPI_ACLConfigParam, * PBlueAPI_ACLConfigParam;

typedef struct TBlueAPI_ACLConfigReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType remote_BD_Type;
    TBlueAPI_ACLConfigOpcode opCode;
    TBlueAPI_ACLConfigParam p;
} TBlueAPI_ACLConfigReq, * PBlueAPI_ACLConfigReq;

typedef struct TBlueAPI_AuthReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
} TBlueAPI_AuthReq, * PBlueAPI_AuthReq;

typedef struct TBlueAPI_UserAuthorizationReqConf
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_Cause cause;
} TBlueAPI_UserAuthorizationReqConf, * PBlueAPI_UserAuthorizationReqConf;

typedef struct TBlueAPI_AuthResultRequestConf
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType remote_BD_Type;
    uint8_t linkKeyLength;
    uint8_t linkKey[BLUEAPI_MAX_LINK_KEY_SIZE];
    TBlueAPI_LinkKeyType keyType;
    uint16_t restartHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_AuthResultRequestConf, * PBlueAPI_AuthResultRequestConf;

typedef struct TBlueAPI_UserAuthRequestConf
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    uint8_t AuthCodeLength;
    uint8_t AuthCode[BLUEAPI_MAX_AUTHCODE_LENGTH];
    TBlueAPI_Cause cause;
} TBlueAPI_UserAuthRequestConf, * PBlueAPI_UserAuthRequestConf;

typedef struct TBlueAPI_UserConfirmationReqConf
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_Cause cause;
} TBlueAPI_UserConfirmationReqConf, * PBlueAPI_UserConfirmationReqConf;

typedef struct TBlueAPI_UserPasskeyReqConf
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_Cause cause;
} TBlueAPI_UserPasskeyReqConf, * PBlueAPI_UserPasskeyReqConf;

typedef struct TBlueAPI_UserPasskeyReqReplyReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    uint32_t passKey;
    TBlueAPI_Cause cause;
} TBlueAPI_UserPasskeyReqReplyReq, * PBlueAPI_UserPasskeyReqReplyReq;

typedef struct TBlueAPI_KeypressNotificationReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_SSPKeyEvent eventType;
} TBlueAPI_KeypressNotificationReq, * PBlueAPI_KeypressNotificationReq;

#define BLUEAPI_AUTH_C_LENGTH ((uint8_t) 16) /**< Length of the "C" parameter for out-of-band authentication in octets */
#define BLUEAPI_AUTH_R_LENGTH ((uint8_t) 16) /**< Length of the "R" parameter for out-of-band authentication in octets */

typedef struct TBlueAPI_RemoteOOBDataReqConf
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    uint8_t C[BLUEAPI_AUTH_C_LENGTH];
    uint8_t R[BLUEAPI_AUTH_R_LENGTH];
    TBlueAPI_Cause cause;
} TBlueAPI_RemoteOOBDataReqConf, * PBlueAPI_RemoteOOBDataReqConf;

typedef struct TBlueAPI_LocalOOBDataReq
{
    TBlueAPIHandle blueAPIHandle;
} TBlueAPI_LocalOOBDataReq, * PBlueAPI_LocalOOBDataReq;

typedef struct TBlueAPI_AuthResultConf
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType remote_BD_Type;
    uint32_t AppData;
    TBlueAPI_Cause cause;
} TBlueAPI_AuthResultConf, * PBlueAPI_AuthResultConf;

typedef struct TBlueAPI_AuthDeleteReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType remote_BD_Type;
} TBlueAPI_AuthDeleteReq, * PBlueAPI_AuthDeleteReq;

typedef struct TBlueAPI_AuthListReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType remote_BD_Type;
} TBlueAPI_AuthListReq, * PBlueAPI_AuthListReq;

#if (F_BLUE_API_HDP_SUPPORT)
typedef struct TBlueAPI_RegHDPMDEPReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t MDEP_ID;
    TBlueAPI_MDEPDataType MDEP_DataType;
    TBlueAPI_MDEPRole MDEP_Role;
    uint8_t MDEP_Description[BLUE_API_MDEP_NAME_LENGTH_HDP_SDP];
} TBlueAPI_RegHDPMDEPReq, * PBlueAPI_RegHDPMDEPReq;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
typedef struct TBlueAPI_RegSPPMDEPReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t MDEP_ID;
    TBlueAPI_MDEPDataType MDEP_DataType;
    uint8_t MDEP_Description[BLUE_API_MDEP_NAME_LENGTH];
    bool RequireAuthenticationIn;
    bool RequireAuthorizationIn;
    bool RequireMITMIn;
    bool RequireEncryptionIn;
} TBlueAPI_RegSPPMDEPReq, * PBlueAPI_RegSPPMDEPReq;
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_BLUE_API_HID_SUPPORT)
typedef struct TBlueAPI_RegHIDMDEPReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t MDEP_ID;
    uint8_t MDEP_Description[BLUE_API_MDEP_NAME_LENGTH];
    uint8_t MDEP_DeviceSubClass;
    uint8_t MDEP_CountryCode;
    uint8_t MDEP_ReconnectInitiate;
    bool RequireAuthenticationIn;
    bool RequireAuthorizationIn;
    bool RequireMITMIn;
    bool RequireEncryptionIn;
    TBlueAPI_HIDDescriptorID HIDDescriptorID;
    uint16_t HIDDescriptorLength;
    uint8_t const * pHIDDescriptor;
} TBlueAPI_RegHIDMDEPReq, * PBlueAPI_RegHIDMDEPReq;

typedef struct TBlueAPI_HIDMessageReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_HIDMsgHeader hidMsgHeader;
    uint16_t payloadLength;
    uint16_t gap;
    uint8_t data[1];
} TBlueAPI_HIDMessageReq, * PBlueAPI_HIDMessageReq;

typedef struct TBlueAPI_HIDMessageConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_HIDMsgHeader hidMsgHeader;
    TBlueAPI_Cause cause;
} TBlueAPI_HIDMessageConf, * PBlueAPI_HIDMessageConf;
#endif /* (F_BLUE_API_HID_SUPPORT) */

#if (F_APPLE_IAP2)
typedef struct TBlueAPI_IAP2MessageReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_IAP2SessionID sessionID;
    uint16_t payloadLength;
    uint16_t gap;
    uint8_t data[1];
} TBlueAPI_IAP2MessageReq, * PBlueAPI_IAP2MessageReq;

typedef struct TBlueAPI_IAP2MessageConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_IAP2SessionID sessionID;
    TBlueAPI_Cause cause;
} TBlueAPI_IAP2MessageConf, * PBlueAPI_IAP2MessageConf;
#endif /* (F_APPLE_IAP2) */

#if (F_BLUE_API_OBEX_SUPPORT)
typedef struct TBlueAPI_RegOBEXMDEPReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t MDEP_ID;
    TBlueAPI_MDEPDataType MDEP_DataType;
    uint8_t MDEP_Description[BLUE_API_MDEP_NAME_LENGTH];
    uint16_t MDEP_OBEXDataMask;
    bool RequireAuthenticationIn;
    bool RequireAuthorizationIn;
    bool RequireMITMIn;
    bool RequireEncryptionIn;
} TBlueAPI_RegOBEXMDEPReq, * PBlueAPI_RegOBEXMDEPReq;
#endif /* (F_BLUE_API_OBEX_SUPPORT) */

#if (F_BLUE_API_L2CAP_SUPPORT)
typedef struct TBlueAPI_RegL2CAPMDEPReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t MDEP_PSM;
    uint16_t MDEP_Protocol;
    TBlueAPI_LinkConfigType MDEP_LinkConfigType;
    uint8_t MDEP_Description[BLUE_API_MDEP_NAME_LENGTH];
    bool RequireAuthorizationIn;
    bool RequireMITMIn;
} TBlueAPI_RegL2CAPMDEPReq, * PBlueAPI_RegL2CAPMDEPReq;
#endif/* (F_BLUE_API_L2CAP_SUPPORT) */

typedef struct TBlueAPI_RelMDEPReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t MDEP_EntryHandle;
} TBlueAPI_RelMDEPReq, * PBlueAPI_RelMDEPReq;

#if (F_BLUE_API_GATT_SUPPORT)
#if (F_BT_GATT_SERVER)
typedef struct TBlueAPI_GATTServiceRegisterReq
{
    TBlueAPIHandle blueAPIHandle;
    TBlueAPI_GATTServiceID serviceID;
    uint16_t nbrOfAttrib;
    TAttribAppl * pService;
    uint8_t serviceChanged;
} TBlueAPI_GATTServiceRegisterReq, * PBlueAPI_GATTServiceRegisterReq;

typedef struct TBlueAPI_GATTAttributeUpdateReq
{
    TBlueAPIHandle blueAPIHandle;
    void * serviceHandle;
    void * requestHandle;
    uint16_t attribIndex;
    uint16_t attribLength;
    uint16_t gap;
    uint8_t data[1];
} TBlueAPI_GATTAttributeUpdateReq, * PBlueAPI_GATTAttributeUpdateReq;

typedef struct TBlueAPI_GATTAttributeUpdateStatusConf
{
    TBlueAPIHandle blueAPIHandle;
    void * serviceHandle;
    void * requestHandle;
    uint16_t attribIndex;
} TBlueAPI_GATTAttributeUpdateStatusConf, * PBlueAPI_GATTAttributeUpdateStatusConf;

typedef struct TBlueAPI_GATTAttributeReadConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    void * serviceHandle;
    TBlueAPI_Cause cause;
    uint16_t subCause;
    uint16_t attribIndex;
    uint16_t attribLength;
    uint16_t gap;
    uint8_t data[1];
} TBlueAPI_GATTAttributeReadConf, * PBlueAPI_GATTAttributeReadConf;

typedef struct TBlueAPI_GATTAttributeWriteConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    void * serviceHandle;
    TBlueAPI_Cause cause;
    uint16_t subCause;
    uint16_t attribIndex;
} TBlueAPI_GATTAttributeWriteConf, * PBlueAPI_GATTAttributeWriteConf;

#if (F_BT_ATT_PREP_EXEC_WRITE)
typedef TBlueAPI_GATTAttributeReadConf TBlueAPI_GATTAttributePrepareWriteConf, * PBlueAPI_GATTAttributePrepareWriteConf;

typedef struct TBlueAPI_GATTExecuteWriteConf
{
    TBlueAPIAppHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_Cause cause;
    uint16_t subCause;
    void * serviceHandle;
    uint16_t attribIndex;
} TBlueAPI_GATTExecuteWriteConf, * PBlueAPI_GATTExecuteWriteConf;
#endif /* (F_BT_ATT_PREP_EXEC_WRITE) */
#endif /* (F_BT_GATT_SERVER) */

#if (F_BT_GATT_CLIENT)
typedef struct TBlueAPI_GATTDiscoveryReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_GATTDiscoveryType discoveryType;
    uint16_t startHandle;
    uint16_t endHandle;
    uint16_t UUID16;
    uint8_t UUID128[16];
} TBlueAPI_GATTDiscoveryReq, * PBlueAPI_GATTDiscoveryReq;

typedef struct TBlueAPI_GATTDiscoveryConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_GATTDiscoveryType discoveryType;
    uint16_t startHandle;
    uint16_t endHandle;
} TBlueAPI_GATTDiscoveryConf, * PBlueAPI_GATTDiscoveryConf;

typedef struct TBlueAPI_GATTAttributeReadReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_GATTReadType readType;
    uint16_t readOffset;
    uint16_t startHandle;
    uint16_t endHandle;
    uint16_t UUID16;
    uint8_t UUID128[16];
} TBlueAPI_GATTAttributeReadReq, * PBlueAPI_GATTAttributeReadReq;

typedef struct TBlueAPI_GATTAttributeWriteReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_GATTWriteType writeType;
    uint16_t attribHandle;
    uint16_t attribLength;
    uint16_t writeOffset;
    uint16_t gap;
    uint8_t data[1];
} TBlueAPI_GATTAttributeWriteReq, * PBlueAPI_GATTAttributeWriteReq;

#if (F_BT_ATT_PREP_EXEC_WRITE)
/* execute write */
typedef struct TBlueAPI_GATTExecuteWriteReq
{
    TBlueAPIAppHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    uint8_t flags;
} TBlueAPI_GATTExecuteWriteReq, * PBlueAPI_GATTExecuteWriteReq;
#endif /* (F_BT_ATT_PREP_EXEC_WRITE) */

typedef struct TBlueAPI_GATTAttributeConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
} TBlueAPI_GATTAttributeConf, * PBlueAPI_GATTAttributeConf;

typedef struct TBlueAPI_GATTSDPDiscoveryReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    uint16_t remote_GATT_UUID;
    bool remote_DID_Discovery;
} TBlueAPI_GATTSDPDiscoveryReq, * PBlueAPI_GATTSDPDiscoveryReq;

typedef struct TBlueAPI_GATTSDPDiscoveryConf
{
    TBlueAPIHandle blueAPIHandle;
    uint32_t serviceHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_GATTSDPDiscoveryConf, * PBlueAPI_GATTSDPDiscoveryConf;
#endif /* (F_BT_GATT_CLIENT) */

typedef struct TBlueAPI_GATTSecurityReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    uint16_t requirements;
    uint8_t minKeySize;
} TBlueAPI_GATTSecurityReq, * PBlueAPI_GATTSecurityReq;

typedef struct TBlueAPI_GATTServerStoreConf
{
    TBlueAPIHandle blueAPIHandle;
    TBlueAPI_GATTStoreOpCode opCode;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType remote_BD_Type;
    uint16_t restartHandle;
    uint8_t dataLength;
    uint8_t data[32];
    TBlueAPI_Cause cause;
} TBlueAPI_GATTServerStoreConf, * PBlueAPI_GATTServerStoreConf;
#endif /* (F_BLUE_API_GATT_SUPPORT) */

typedef struct TBlueAPI_InquiryReq
{
    TBlueAPIHandle blueAPIHandle;
    bool limitedInquiry;
    bool cancelInquiry;
} TBlueAPI_InquiryReq, * PBlueAPI_InquiryReq;

typedef struct TBlueAPI_DeviceNameReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
} TBlueAPI_DeviceNameReq, * PBlueAPI_DeviceNameReq;

#if (F_BLUE_API_HDP_SUPPORT)
typedef struct TBlueAPI_HDPDiscoveryReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_MDEPRole remote_MDEP_Role;
    TBlueAPI_MDEPDataType remote_MDEP_DataType;
} TBlueAPI_HDPDiscoveryReq, * PBlueAPI_HDPDiscoveryReq;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

typedef struct TBlueAPI_DIDDeviceConf
{
    TBlueAPIHandle blueAPIHandle;
    uint32_t serviceHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_DIDDeviceConf, * PBlueAPI_DIDDeviceConf;

#if (F_BLUE_API_HDP_SUPPORT)
typedef struct TBlueAPI_HDPServiceConf
{
    TBlueAPIHandle blueAPIHandle;
    uint32_t serviceHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_HDPServiceConf, * PBlueAPI_HDPServiceConf;

typedef struct TBlueAPI_HDPEndpointConf
{
    TBlueAPIHandle blueAPIHandle;
    uint32_t serviceHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_HDPEndpointConf, * PBlueAPI_HDPEndpointConf;
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_BLUE_API_SPP_SUPPORT)
typedef struct TBlueAPI_SPPDiscoveryReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_MDEPDataType remote_MDEP_DataType;
    bool remote_DID_Discovery;
} TBlueAPI_SPPDiscoveryReq, * PBlueAPI_SPPDiscoveryReq;

typedef struct TBlueAPI_SPPEndpointConf
{
    TBlueAPIHandle blueAPIHandle;
    uint32_t serviceHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_SPPEndpointConf, * PBlueAPI_SPPEndpointConf;
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (F_BLUE_API_OBEX_SUPPORT)
typedef struct TBlueAPI_OBEXDiscoveryReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_MDEPDataType remote_MDEP_DataType;
} TBlueAPI_OBEXDiscoveryReq, * PBlueAPI_OBEXDiscoveryReq;

typedef struct TBlueAPI_OBEXEndpointConf
{
    TBlueAPIHandle blueAPIHandle;
    uint32_t serviceHandle;
    TBlueAPI_Cause cause;
} TBlueAPI_OBEXEndpointConf, * PBlueAPI_OBEXEndpointConf;
#endif /* (F_BLUE_API_OBEX_SUPPORT) */

#if (F_BLUE_API_HCI_TUNNEL_SUPPORT)
typedef struct TBlueAPI_HCITunnelReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t length;
    uint8_t hciCommand[BLUE_API_HCI_TUNNEL_DATA_LENGTH];
} TBlueAPI_HCITunnelReq, * PBlueAPI_HCITunnelReq;
#endif /* (F_BLUE_API_HCI_TUNNEL_SUPPORT) */

#if (F_BT_LOW_ENERGY)
typedef struct TBlueAPI_LEAdvertiseReq
{
    TBlueAPIHandle blueAPIHandle;
    TBlueAPI_LEAdvMode advMode;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType remote_BD_type;
} TBlueAPI_LEAdvertiseReq, * PBlueAPI_LEAdvertiseReq;

typedef struct TBlueAPI_LEAdvertiseParameterSetReq
{
    TBlueAPIHandle blueAPIHandle;
    TBlueAPI_LEAdvType advType;
    TBlueAPI_LEFilterPolicy filterScanReq;
    TBlueAPI_LEFilterPolicy filterConnectReq;
    uint16_t minAdvInterval;
    uint16_t maxAdvInterval;
} TBlueAPI_LEAdvertiseParameterSetReq, * PBlueAPI_LEAdvertiseParameterSetReq;

typedef struct TBlueAPI_LEAdvertiseDataSetReq
{
    TBlueAPIHandle blueAPIHandle;
    TBlueAPI_LEDataType dataType;
    uint8_t dataLength;
    uint8_t data[31];
} TBlueAPI_LEAdvertiseDataSetReq, * PBlueAPI_LEAdvertiseDataSetReq;

typedef struct TBlueAPI_LEScanReq
{
    TBlueAPIHandle blueAPIHandle;
    TBlueAPI_LEScanMode scanMode;
    uint16_t scanInterval;
    uint16_t scanWindow;
    TBlueAPI_LEFilterPolicy filterPolicy;
    uint8_t filterDuplicates;
} TBlueAPI_LEScanReq, * PBlueAPI_LEScanReq;

typedef struct TBlueAPI_LEModifyWhitelistReq
{
    TBlueAPIHandle blueAPIHandle;
    TBlueAPI_LEWhitelistOp operation;
    uint8_t remote_BD[BLUE_API_BD_SIZE];
    TBlueAPI_RemoteBDType remote_BD_type;
} TBlueAPI_LEModifyWhitelistReq, * PBlueAPI_LEModifyWhitelistReq;

typedef struct TBlueAPI_LEConnectionUpdateReq
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    uint16_t connIntervalMin;
    uint16_t connIntervalMax;
    uint16_t connLatency;
    uint16_t supervisionTimeout;
} TBlueAPI_LEConnectionUpdateReq, * PBlueAPI_LEConnectionUpdateReq;

typedef struct TBlueAPI_LEConnectionUpdateConf
{
    TBlueAPIHandle blueAPIHandle;
    uint16_t local_MDL_ID;
    TBlueAPI_Cause cause;
} TBlueAPI_LEConnectionUpdateConf, * PBlueAPI_LEConnectionUpdateConf;

#if (F_BT_LE_PRIVACY_MODE)
typedef struct TBlueAPI_LEPrivacyModeReq
{
    TBlueAPIAppHandle blueAPIHandle;
    TBlueAPI_LEPrivacyMode privacyMode;
} TBlueAPI_LEPrivacyModeReq, * PBlueAPI_LEPrivacyModeReq;
#endif /* (F_BT_LE_PRIVACY_MODE) */
#endif /* (F_BT_LOW_ENERGY) */

#if (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM)
typedef struct TBlueAPI_TestmodeReq
{
    TBlueAPIAppHandle blueAPIHandle;
    TBlueAPI_Testmode testmode;
} TBlueAPI_TestmodeReq, * PBlueAPI_TestmodeReq;
#endif /* (F_BTEXT_HCI_DIRECT) || (F_BTEXT_HCI_BEDUTM) */

#if (F_BLUE_API_BAS_SUPPORT)
typedef struct TBlueAPI_BatteryLevelSetReq
{
    TBlueAPIHandle blueAPIHandle;
    uint8_t level;
} TBlueAPI_BatteryLevelSetReq, * PBlueAPI_BatteryLevelSetReq;
#endif /* (F_BLUE_API_BAS_SUPPORT) */

/** @endcond */

#ifdef __cplusplus
}
#endif

#endif /* ndef __BLUECODE_BLUEAPI_MSG_DOWNSTREAM_H */
