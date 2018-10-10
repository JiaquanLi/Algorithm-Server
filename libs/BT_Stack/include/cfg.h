/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/cfg.h,v $
 * Revision:    $Revision: 1.12 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_CFG_H
#define __BLUECODE_CFG_H

/** @file
 * Definition of static configuration structures. This header should be implemented by a source file called the <em>configuration file</em>, which will be linked to the BlueCode+ library.
 * The BlueCode+ Customer Package includes a template configuration file to simplify configuration changes. */

#ifndef V_BLUECODE_EXPORTED
#include "flags.h"   // Variant management
#endif
#include <stdint.h>  // uint*_t
#include <stdbool.h> // bool
#include <stddef.h>  // size_t

// Configuration construction

#define CFG_SECTION_START_LENGTH ((size_t  )          8) /**< Length of the head of a configuration structure */
#define CFG_SECTION_START        (           "CFG_SECT") /**< Prefix string of a configuration structure */
#define CFG_SECTION_MAGIC        ((uint32_t) 0x45524548) /**< Magic number included in the head of a configuration structure */

/** Helper macro for the definition of the head of a configuration structure */
#define BEGIN_OF_PARAMETER_SET_SECTION(sectionID) {CFG_SECTION_START, (sectionID), CFG_SECTION_MAGIC}
/** Helper macro for the definition of the end of a configuration structure */
#define END_OF_PARAMETER_SET {0,0}
/** Helper macro for the definition of a configuration item in a configuration structure */
#define CFG_PARAM(id, version, type, value) {(id), (version), (sizeof(type))}, value

/** Head of a configuration structure. Shall be the first element of every configuration structure, and constructed using #BEGIN_OF_PARAMETER_SET_SECTION. */
typedef struct TCfgSHead
{
    uint8_t   sectionLeadIn[CFG_SECTION_START_LENGTH]; /**< Prefix string */
    uint16_t  sectionID;                               /**< Section ID of the configuration structure */
    uint32_t  magic;                                   /**< Magic number for integrity checks etc. */
} TCfgSHead;

/** Head of a configuration item definition. Shall be prepended to every item value in a configuration structure. */
typedef struct TCfgPHead
{
    uint8_t  paraID;      /**< Configuration item ID */
    uint8_t  paraVersion; /**< Configuration item version */
    uint16_t paraLength;  /**< Length of the configuration item data, in octets */
} TCfgPHead;

// Configuration structures

#define CFG_PARAMETER_SET_ID_UNDEFINED ((uint16_t) 0) /**< Section ID for internal configuration items that are not mapped to an external configuration structure */

#define CFG_PARAMETER_SET_ID_BT        ((uint16_t) 1) /**< Section ID for configuration structure "BlueAPI" */

/** @cond Doxygen_Ignored */
#define CFG_IDSOURCE_ID                 1
#define CFG_PRODUCTID_ID                2
#define CFG_PRODUCTVERS_ID              3
#define CFG_VENDORID_ID                 4
#if (F_BLUE_API_HDP_SUPPORT)
#define CFG_HDPCCINTO_ID                5
#define CFG_HDPCCOUTTO_ID               6
#define CFG_HDPMCAPTO_ID                7
#define CFG_HDPNAME_ID                  8
#define CFG_HDPRECONNECT_ID             9
#define CFG_HDPRXAPDU_ID                10
#define CFG_HDPSINT_ID                  11
#define CFG_HDPAUTHORIN_ID              12
#define CFG_HDPAUTHOROUT_ID             13
#define CFG_HDPMITMIN_ID                14
#define CFG_HDPMITMOUT_ID               15
#endif /* (F_BLUE_API_HDP_SUPPORT) */
#if (F_MAYBE_OBSOLETE)
#define CFG_SPPSINT_ID                  16
#endif /* (F_MAYBE_OBSOLETE) */
#if (F_BLUE_API_SPP_SUPPORT)
#define CFG_SPPAUTHENOUT_ID             17
#define CFG_SPPAUTHOROUT_ID             18
#define CFG_SPPENCROUT_ID               19
#define CFG_SPPMITMOUT_ID               20
#endif /* (F_BLUE_API_SPP_SUPPORT) */
#if (TRACE_COUNT)
#define CFG_BAPITRC_ID                  21
#endif /* (TRACE_COUNT) */
#if (F_BLUE_API_L2CAP_SUPPORT)
#define CFG_L2CAPAUTHOROUT_ID           22
#define CFG_L2CAPMITMOUT_ID             23
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */
/** @endcond */

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing documentation here"
#define HDP_NAME_LEN ((size_t) 24)
typedef uint8_t CfgServiceName[HDP_NAME_LEN];
#endif /* (F_BLUE_API_HDP_SUPPORT) */

/** Configuration structure "BlueAPI". */
typedef struct TCfgParameterBLUE_API
{
    TCfgSHead cfgSHead; /**< Configuration structure head. Shall be constructed using #BEGIN_OF_PARAMETER_SET_SECTION */

    /** @name Configuration items */
    /** @{ */
    // DIP (Device ID Profile)-specific Configuration Items
    TCfgPHead hIDSource; /**< Member of configuration structure "BlueAPI". See your configuration file template for more details */
    uint8_t   IDSource;
    TCfgPHead hProductID;
    uint16_t  ProductID;
    TCfgPHead hProductVersion;
    uint16_t  ProductVersion;
    TCfgPHead hVendorID;
    uint16_t  VendorID;

#if (F_BLUE_API_HDP_SUPPORT)
#error "Missing formatting here"
    TCfgPHead hControlIdleTimeoutIn;
    uint16_t  ControlIdleTimeoutIn;                     /* HDPCCINTO          */
    TCfgPHead hControlIdleTimeoutOut;
    uint16_t  ControlIdleTimeoutOut;                    /* HDPCCOUTTO         */
    TCfgPHead hMCAP_Timeout;
    uint16_t  MCAP_Timeout;                             /* HDPMCAPTO          */
    TCfgPHead hServiceName;
    /* The service name length must not exceed HDP_NAME_LEN                   */
    CfgServiceName ServiceName;                /* HDPNAME            */
    TCfgPHead hHDPReconnectEnable;
    bool      HDPReconnectEnable;                       /* HDPRECONNECT       */
    TCfgPHead hMaxRxAPDUSize;
    uint16_t  MaxRxAPDUSize;                            /* HDPRXAPDU          */
    TCfgPHead hHDPSniffInterval;
    uint16_t  HDPSniffInterval;                         /* HDPSINT            */
    TCfgPHead hSecHDPRequireAuthorizationIn;
    bool      SecHDPRequireAuthorizationIn;             /* HDPAUTHORIN        */
    TCfgPHead hSecHDPRequireAuthorizationOut;
    bool      SecHDPRequireAuthorizationOut;            /* HDPAUTHOROUT       */
    TCfgPHead hSecHDPRequireMITMIn;
    bool      SecHDPRequireMITMIn;                      /* HDPMITMIN          */
    TCfgPHead hSecHDPRequireMITMOut;
    bool      SecHDPRequireMITMOut;                     /* HDPMITMOUT         */
#endif /* (F_BLUE_API_HDP_SUPPORT) */

#if (F_MAYBE_OBSOLETE)
    TCfgPHead hSPPSniffInterval;
    uint16_t  SPPSniffInterval;
#endif /* (F_MAYBE_OBSOLETE) */

#if (F_BLUE_API_SPP_SUPPORT)
    // SPP Security-related Configuration Items
    TCfgPHead hSecSPPRequireAuthenticationOut;
    bool      SecSPPRequireAuthenticationOut;
    TCfgPHead hSecSPPRequireAuthorizationOut;
    bool      SecSPPRequireAuthorizationOut;
    TCfgPHead hSecSPPRequireEncryptionOut;
    bool      SecSPPRequireEncryptionOut;
    TCfgPHead hSecSPPRequireMITMOut;
    bool      SecSPPRequireMITMOut;
#endif /* (F_BLUE_API_SPP_SUPPORT) */

#if (TRACE_COUNT)
    TCfgPHead hTrcMsk;
    uint16_t  TrcMsk;
#endif /* (TRACE_COUNT) */

#if (F_BLUE_API_L2CAP_SUPPORT)
    TCfgPHead hSecL2CAPRequireAuthorizationOut;
    bool      SecL2CAPRequireAuthorizationOut;
    TCfgPHead hSecL2CAPRequireMITMOut;
    bool      SecL2CAPRequireMITMOut;
#endif /* (F_BLUE_API_L2CAP_SUPPORT) */
    /** @} */

    TCfgPHead cfgSEnd;     /**< Configuration structure end. Shall be constructed using #END_OF_PARAMETER_SET */
} TCfgParameterBLUE_API;
typedef TCfgParameterBLUE_API * PCfgParametertBLUE_API, * LPCfgParameterBLUE_API;

#define CFG_PARAMETER_SET_ID_HDP ((uint16_t) 2) /**< Section ID for configuration structure "Security" */

/** @cond Doxygen_Ignored */
#define CFG_BCLASS_ID                   1
#define CFG_BLINKP_ID                   2
#define CFG_BNAME_ID                    3
#define CFG_BPSM_ID                     4
#define CFG_BPSRM_ID                    5
#define CFG_BROLE_ID                    6
#define CFG_BSUPTIM_ID                  7
#if (BTEXT_RF_MAX_TX_PWR)
#define CFG_RFMAXTXPWR_ID               8
#endif /* (BTEXT_RF_MAX_TX_PWR) */
#define CFG_BAUTHREQMTS_ID              9
#define CFG_BIOCAP_ID                   10
#define CFG_BNDS_ID                     11
#define CFG_BNDSIZE_ID                  12
#define CFG_BPAIRABLE_ID                13
/** @endcond */

#define BTSEC_OWN_DEVICE_NAME_LENGTH ((size_t) 50) /**< Maximum length of the statically configured device name. Do not modify this value (!) */

typedef uint8_t CfgDeviceName[BTSEC_OWN_DEVICE_NAME_LENGTH]; /**< Statically configured device name. */

/** Configuration structure "Security". */
typedef struct TCfgParameterBT
{
    TCfgSHead cfgSHead; /**< Configuration structure head. Shall be constructed using #BEGIN_OF_PARAMETER_SET_SECTION */

    /** @name Configuration items */
    /** @{ */
    // Part of General Device-Specific Configuration Items
    TCfgPHead hclassCode; /**< Member of configuration structure "Security". See your configuration file template for more details */
    uint32_t  classCode;

    // Part of Classic Bluetooth Connection Configuration Items
    TCfgPHead hLinkPolicy;
    uint8_t   LinkPolicy;

    // Part of General Device-Specific Configuration Items
    TCfgPHead hDeviceName;
    CfgDeviceName deviceName;

    // Classic Bluetooth Page Scan Configuration Items
    TCfgPHead hpageMode;
    uint8_t   pageMode;
    TCfgPHead hpageScanRepetitionMode;
    uint8_t   pageScanRepetitionMode;

    // Part of Classic Bluetooth Connection Configuration Items
    TCfgPHead hDeviceRole;
    uint8_t   DeviceRole;
    TCfgPHead hSupervisionTimeout;
    uint16_t  SupervisionTimeout;

#if (BTEXT_RF_MAX_TX_PWR)
#error "Missing documentation here"
    TCfgPHead hhwRfMaxTxPwr;
    char      hwRfMaxTxPwr;
#endif /* (BTEXT_RF_MAX_TX_PWR) */

    // General Security-related Configuration Items
    TCfgPHead hbauthreqmts;
    uint8_t   bauthreqmts;
    TCfgPHead hbiocap;
    uint8_t   biocap;
    TCfgPHead hStoreNewBondings;
    uint8_t   StoreNewBondings;
    TCfgPHead hSecBondTableSize;
    uint8_t   SecBondTableSize;
    TCfgPHead hbpairable;
    bool      bpairable;
    /** @} */

    TCfgPHead cfgSEnd;     /**< Configuration structure end. Shall be constructed using #END_OF_PARAMETER_SET */
} TCfgParameterBTSEC;
typedef TCfgParameterBTSEC * PCfgParameterBTSEC, * LPCfgParameterBTSEC;

#define CFG_PARAMETER_SET_ID_BLUE_API_DYNAMIC_CONFIG ((uint16_t) 3)  /**< Section ID for configuration structure "BlueAPI Dynamic" */

/** @cond Doxygen_Ignored */
#define CFG_DATA_STORE_ELEMENTS_PEER_ID  1
#define CFG_DATA_STORE_ELEMENTS_SMALL_ID 2
#define CFG_DATA_STORE_ELEMENTS_LARGE_ID 3
/** @endcond */

/** Configuration structure "BlueAPI Dynamic". */
typedef struct _TCfgBlueAPI_DynamicConfig
{
    TCfgSHead cfgSHead; /**< Configuration structure head. Shall be constructed using #BEGIN_OF_PARAMETER_SET_SECTION */

    /** @name Configuration items */
    /** @{ */
    TCfgPHead hDataStorePeerElements; /**< Member of configuration structure "BlueAPI Dynamic". See your configuration file template for more details */
    uint16_t dataStorePeerElements;
    TCfgPHead hDataStoreSmallElements;
    uint16_t dataStoreSmallElements;
    TCfgPHead hDataStoreLargeElements;
    uint16_t dataStoreLargeElements;
    /** @} */

    TCfgPHead cfgSEnd;     /**< Configuration structure end. Shall be constructed using #END_OF_PARAMETER_SET */
} TCfgBlueAPI_DynamicConfig;
typedef TCfgBlueAPI_DynamicConfig * PCfgBlueAPI_DynamicConfig;

#if (F_TRACE_BINARY)
#define CFG_PARAMETER_SET_ID_TRACE_DYNAMIC_CONFIG  ((uint16_t) 4) /**< Section ID for configuration structure "BlueAPI" */

/** @cond Doxygen_Ignored */
#define CFG_TRACE_BUFFER_SIZE_ID    1
#define CFG_TRACE_BUFFER_MAX_USE_ID 2
/** @endcond */

/** Configuration structure "Trace". */
typedef struct _TCfgTraceDynamicConfig
{
    TCfgSHead cfgSHead; /**< Configuration structure head. Shall be constructed using #BEGIN_OF_PARAMETER_SET_SECTION */

    /** @name Configuration items */
    /** @{ */
    TCfgPHead hBufferSize; /**< Member of configuration structure "Trace". See your configuration file template for more details */
    uint16_t  bufferSize;
    TCfgPHead hBufferMaxUse;
    uint16_t  bufferMaxUse;
    /** @} */

    TCfgPHead cfgSEnd;     /**< Configuration structure end. Shall be constructed using #END_OF_PARAMETER_SET */
} TCfgTraceDynamicConfig;
typedef TCfgTraceDynamicConfig * PCfgTraceDynamicConfig;
#endif /* (F_TRACE_BINARY) */

#if (F_APPLE_IAP)
#define CFG_PARAMETER_SET_ID_IAP ((uint16_t) 5)  /**< Section ID for configuration structure "iAP" */

/** @cond Doxygen_Ignored */
#define CFG_IAP1_ACC_INFO_NAME_ID         1
#define CFG_IAP1_ACC_INFO_MODEL_NBR_ID    2
#define CFG_IAP1_ACC_INFO_MANUFACTURER_ID 3
#define CFG_IAP1_ACC_INFO_FIRMWARE_ID     4
#define CFG_IAP1_ACC_INFO_HARDWARE_ID     5
#define CFG_IAP1_ACC_INFO_RF_CERTIF_ID    6
#define CFG_IAP1_EAPROTOCOL_ID            7
#define CFG_IAP1_BUNDLE_SEED_PREF_ID      8
#define CFG_IAP1_APPLICATION_ID_ID        9
#define CFG_IAP_LAUNCH_APPLICATION_ID    10
/** @endcond */

/** Configuration structure "iAP". */
typedef struct TCfgParameterIAP
{
    TCfgSHead cfgSHead; /**< Configuration structure head. Shall be constructed using #BEGIN_OF_PARAMETER_SET_SECTION */

    /** @name Configuration items */
    /** @{ */
    TCfgPHead hAccInfoName; /**< Member of configuration structure "iAP". See your configuration file template for more details */
    uint8_t * pAccInfoName;
    TCfgPHead hAccInfoModelNbr;
    uint8_t * pAccInfoModelNbr;
    TCfgPHead hAccInfoManufacturer;
    uint8_t * pAccInfoManufacturer;
    TCfgPHead hAccInfoFirmware;
    uint8_t * pAccInfoFirmware;
    TCfgPHead hAccInfoHardware;
    uint8_t * pAccInfoHardware;
    TCfgPHead hAccInfoRFCertif;
    uint8_t * pAccInfoRFCertif;
    TCfgPHead hEAProtocol;
    uint8_t * pEAProtocol;
    TCfgPHead hBundleSeedPref;
    uint8_t * pBundleSeedPref;
    TCfgPHead hApplicationID;
    uint8_t * pApplicationID;
    TCfgPHead hLaunchApplication;
    bool      launchApplication;
    /** @} */

    TCfgPHead cfgSEnd;     /**< Configuration structure end. Shall be constructed using #END_OF_PARAMETER_SET */
} TCfgParameterIAP;
typedef TCfgParameterIAP * PCfgParametertIAP, * LPCfgParameterIAP;
#endif /* (F_APPLE_IAP) */

// External declaration of configuration variables (shall be linked to BlueCode+)

extern TCfgParameterBLUE_API           cfgParameterBLUE_API;    /**< Configuration structure "BlueAPI" */
extern TCfgParameterBTSEC        const cfgParameterBTSEC;       /**< Configuration structure "Security" */
extern TCfgBlueAPI_DynamicConfig const cfgBlueAPIDynamicConfig; /**< Configuration structure "BlueAPI Dynamic" */
#if (F_TRACE_BINARY)
extern TCfgTraceDynamicConfig    const cfgTraceDynamicConfig;   /**< Configuration structure "Trace" */
#endif /* (F_TRACE_BINARY) */
#if (F_APPLE_IAP)
extern TCfgParameterIAP          const cfgParameterIAP;         /**< Configuration structure "iAP" */
#endif /* (F_APPLE_IAP) */

/** Handles the result of configuration item assignment.
 * Will be called by BlueCode+ during initial configuration. */
extern void cfgErrorHandlertgt(
        bool valueLegal,    /**< [in] false if the configured item was set to an illegal value */
        uint16_t sectionID, /**< [in] Section ID of the configured item, see CFG_PARAMETER_SET_ID_* definitions */
        uint8_t parameterID /**< [in] Parameter ID of the configured item, see CFG_*_ID definitions for the section identified by @p sectionID.
                                      Can also be 0 if an internal configuration step failed */);

#endif /* ndef __BLUECODE_CFG_H */
