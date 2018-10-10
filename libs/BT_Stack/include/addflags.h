
/********************************************************************
 * $Header: /var/lib/cvs/sw/./inc/addflags.h,v 1.115 2014/06/06 14:37:22 mj Exp $
 *
 * This file translates FLAGs from "FLAGS.H" to already existing FLAGs
 *
 ********************************************************************/
#if (F_AT91M40400) && (F_AT91_AIC_DISABLE_INT)
#error no support for this interrupt-mode <==> controller combination
#endif

#define XHFC_COUNT (XHFC2SU_COUNT + XHFC4SU_COUNT + XHFC1SU_COUNT)
#if (XHFC_COUNT > 0)
#if (XHFC4SU_COUNT > 0)
#define XHFC_INTERFACE_COUNT 4
#elif (XHFC2SU_COUNT > 0)
#define XHFC_INTERFACE_COUNT 2
#elif (XHFC1SU_COUNT > 0)
#define XHFC_INTERFACE_COUNT 1
#else
#error neither XHFC4SU XHFC2SU nor XHFC1SU
#endif
#endif /* XHFC_COUNT */


#define HFCXS_COUNT (HFC4S_COUNT+HFC8S_COUNT)

#if !defined(F_B_CHANNEL_STACK) || (!F_B_CHANNEL_STACK)
#undef F_B_CHANNEL_STACK
#if (F_T70NL) || (F_T90NL) || (F_X25) || (F_X25MUX) || (F_X75) || (F_LAPB) || \
    (F_V42BIS) || (F_AHDLC) || (F_V110) || (F_V120) || (F_LAPF) || \
    (F_X31_D) || (F_SMS_PROTOCOL_1)
#define F_B_CHANNEL_STACK 1
#else
#undef F_B_CHANNEL_STACK
#define F_B_CHANNEL_STACK 0
#endif
#endif /* !defined(F_B_CHANNEL_STACK) || (!F_B_CHANNEL_STACK) */

#if (F_X75) || (F_LAPD) || (F_LAPB) || (F_V120) || (F_LAPF)
#define F_HDLC 1
#else
#define F_HDLC 0
#endif

#if (F_V42BIS && !(F_X75 || F_V120))
#error Please add F_X75 or F_V120 for V.42bis
#endif

#if (F_T90NL) && !(F_X25)
#error Please add X.25 for T.90NL
#endif

#if (F_DIAL_MLPPP) && !(F_UART_AHDLC)
#error Please add F_UART_AHDLC for Multi Link PPP.
#endif

#if !defined(F_MLPPP_UCB)
#define  F_MLPPP_UCB  0
#endif

#if (F_DSS1_NT) && !(F_L1DC_NT)
#error Please add L1DC_NT for NT mode
#endif

#if !(F_VMOD) && ((F_HAYES) || (F_PAD) || (F_V25BIS) || (F_HOTLINE) || (F_CALLBACK))
#define F_DIAL 1
#else
#define F_DIAL 0
#endif

#if (F_VMOD)
#if (F_VMOD_DATAIF_CAPI)
#if !(F_LIBCM_DIRECT_CM_ACCESS) && !(F_LIBCM_WINDOWS_KERNEL)
#error Please add LIBCM access method
#endif
#endif /* F_VMOD_DATAIF_CAPI */

#if (F_VMOD_DATAIF_CAPI_WRAP) && !(F_VMOD_DATAIF_CAPI)
#error Please add VMOD_DATAIF_CAPI
#endif

#if (F_VMOD_DATAIF_BT)
#if !(F_BLUE_TOOTH)
#error Please add BLUE_TOOTH
#endif
#endif /* F_VMOD_DATAIF_BT */
#endif /* F_VMOD */

#if (F_CLIP_ON_ANALOG_PORT) && !(F_RTC)
#error please add RTC  /* someone means software clock, but designated this flag RTC */
#endif

#if ( (F_SUPPL_3PTY) || (F_SUPPL_ECT) ) && !(F_SUPPL_HOLD)
#error Please add SUPPL_HOLD for SUPPL_3PTY/SUPPL_ECT
#endif

#if (F_SUPPL_HOLD) || (F_SUPPL_3PTY) || (F_SUPPL_TP) || (F_SUPPL_ECT) || (F_SUPPL_CF) || (F_SUPPL_CD) || (F_SUPPL_CCBS) || (F_SUPPL_MCID) || (F_TRANSP_DCH_INFO)
#define F_SUPPLEMENTARY_SERVICES 1
#else
#define F_SUPPLEMENTARY_SERVICES 0
#endif

#if (F_LOADABLE) && !(F_MODULE)
#error Please add F_MODULE for F_LOADABLE
#endif

#if (F_DB) && (F_CF)
#error DATABASE and old CONFIG cannot be ON at the same time
#endif

#if (F_CONFIG_APP) && (F_SCONF)
#error Please choose either F_CONFIG_APP or F_SCONF
#endif

#if (F_CONFIG_APP) && !(F_DB)
#error Please add F_DB
#endif

#if (CIM_COUNT > 0) && !(F_DB)
#error Please add F_DB
#endif

#if (F_SCONF) && (!F_BTEXT_HCI_BEDUTM || !F_BTEXT_HCI_DIRECT)
#error Please add F_BTEXT_HCI_BEDUTM and F_BTEXT_HCI_DIRECT
#endif

#if (F_TRANSP_DCH_INFO) && !(F_CAPI_MNF_EXT)
#error Please add F_CAPI_MNF_EXT
#endif

#if (F_TIMER_CALLBACK) && !(F_OSIF_CALLBACK)
#error Please add F_OSIF_CALLBACK
#endif

#if (F_SUPPL_CCNR) && !(F_SUPPL_CCBS)
#error Please add F_SUPPL_CCBS
#endif

#if (F_B_CH_DEBLOC) && !(F_TRANSP_TEI_MANAGEMENT)
#error Please add F_TRANSP_TEI_MANAGEMENT with F_B_CH_DEBLOC
#endif


#if (IPACX_COUNT > 0) || (ISACX_COUNT > 0)

#if ((F_ISTR_BUS_BYTE + F_ISTR_BUS_WORD + F_ISTR_BUS_DWORD) > 1)
#error only one bus type for IPACX and/or ISACX devices
#endif
#if !(F_ISTR_BUS_BYTE) && !(F_ISTR_BUS_WORD) && !(F_ISTR_BUS_DWORD)
#define F_ISTR_BUS_WORD   TRUE  /* missed flag, default value is 16 bit */
#endif
#endif

#if (GENERIC_CODEC_COUNT > 0) && (CODEC_COUNT == 0)
#error CODEC_COUNT must be > 0
#endif

#if ((HFCSMINI_COUNT > 0) || (XHFC_COUNT > 0)) && !(F_L1_ISDN_INTEGRATED)
#endif

#if (XHFC_COUNT > 0) && (LINE_INTERFACE_COUNT == 0)
/* LINE_INTERFACE_COUNT = 1,2,4 * XHFCxSU_COUNT */
#error LINE_INTERFACE_COUNT must be non zero
#endif

#if (F_VMOD)
/* check vmod mismatching */

#if (F_HAYES) || (F_PAD) || (F_HOTLINE)
#error you want use old cmd interfaces with new vmod!
#error use VMOD_XXXX_COUNTs instead of F_XXXX
#endif

/* VMOD_REMOTE_COUNT use exclusiv 1 LINKIF 1 DATAIF and 1 CMDIF */
#if (VMOD_HAYES_COUNT + VMOD_REMOTE_COUNT    > VMOD_CMDIF_COUNT)    ||  \
    (VMOD_PAD_COUNT + VMOD_REMOTE_COUNT      > VMOD_CMDIF_COUNT)    ||  \
    (VMOD_AUTOCONN_COUNT + VMOD_REMOTE_COUNT > VMOD_CMDIF_COUNT)    ||  \
    (VMOD_WTM_COUNT + VMOD_REMOTE_COUNT      > VMOD_CMDIF_COUNT)
#error VMOD CmdIF count mismatch!
#endif

#if (VMOD_HAYES_COUNT + VMOD_REMOTE_COUNT    > VMOD_DATAIF_COUNT)   ||  \
    (VMOD_PAD_COUNT + VMOD_REMOTE_COUNT      > VMOD_DATAIF_COUNT)   ||  \
    (VMOD_AUTOCONN_COUNT + VMOD_REMOTE_COUNT > VMOD_DATAIF_COUNT)   ||  \
    (VMOD_WTM_COUNT + VMOD_REMOTE_COUNT      > VMOD_DATAIF_COUNT)
#error VMOD DataIF count mismatch!
#endif

#if  (VMOD_SERIAL_COUNT + VMOD_REMOTE_COUNT > VMOD_LINKIF_COUNT)
#error VMOD LinkIF count mismatch!
#endif

#if (STLC2410_COUNT > 0) || (STLC2411_COUNT > 0)
#if (F_BT_HCI_HOST_FLOW_CAPABILITY) && (BT_DS_MTU_L2C_BYTE_COUNT != 335)
#error STM Bluetooth CFW supports only packet size of 339!
#endif
#endif

#if (F_ASC0_ASYNC || F_16550_ASYNC)
#if (F_ASYNC_NO_RING_BUFFER)
#error Use ring buffer!
#endif
#endif

/* CAPI Ntive section */
#if (F_BIG_ENDIAN)
#if !(__CAPI_NATIVE_MODE__)
#error Big Endian needs native mode
#endif
#endif

#if (F_BT_L1_INTELLIGENT) && (F_BT_L1_V24)
#if (F_ASYNC_NO_RING_BUFFER)
#error Use ring buffer!
#endif
#endif

#if defined(__ADSPBLACKFIN__) && !(F_COMPILER_LIB)
#error Please add F_COMPILER_LIB for Blackfin
#endif /* defined(__ADSPBLACKFIN__) */

#if (F_MSP) && !(F_L2_HDLC_SREJ)
#error Please use for MSP mode F_L2_HDLC_SREJ
#error Attention old MSP reject is not compatible with slective reject
#error for further information ask sn
#endif

#endif /* (F_VMOD) */

  /* Linux specifics */
#if (F_LNX_INT_TASKLET) || (F_LNX_KTHREADS)
#if (F_LNX_INT_TASKLET) && (F_LNX_KTHREADS)
#error F_LNX_INT_TASKLET and F_LNX_KTHREADS are mutually exclusive!
#endif

#if !(F_TRIGGER_RESCHEDULING)
#error F_LNX_INT_TASKLET or F_LNX_KTHREADS req. F_TRIGGER_RESCHEDULING!
#endif
#endif /* (F_LNX_INT_TASKLET) || (F_LNX_KTHREADS) */


  /* critical section lock specifics */
#if (F_L1_CODE_WAIT) && !(F_SECTION_LOCK_EXT)
#error Please add F_SECTION_LOCK_EXT
#endif


  /* critical section lock specifics */
#if (F_OS_EXTERNAL) && !(F_SECTION_LOCK_EXT)
#error Please add F_SECTION_LOCK_EXT
#endif
#if (!F_H4DS && F_ASYNC_H4DS)
#error please add F_H4DS
#endif


#if (F_BLUE_TOOTH) /* [ */
#if (F_BT_L2C_ENHANCED_FEATURE_SUPPORT)
/* Enhanced retransmission or streaming mode: PDU size != 0 and MTU = SDU */
#if (BT_DS_PDU_L2C_BYTE_COUNT == 0 || BT_US_PDU_L2C_BYTE_COUNT == 0)
#error !!set BT_DS_PDU_L2C_BYTE_COUNT and BT_US_PDU_L2C_BYTE_COUNT
#endif
#else
/* Basic mode: PDU = MTU */
#if (BT_DS_PDU_L2C_BYTE_COUNT == 0)
#undef BT_DS_PDU_L2C_BYTE_COUNT
#define BT_DS_PDU_L2C_BYTE_COUNT   BT_DS_MTU_L2C_BYTE_COUNT
#endif
#if (BT_US_PDU_L2C_BYTE_COUNT == 0)
#undef BT_US_PDU_L2C_BYTE_COUNT
#define BT_US_PDU_L2C_BYTE_COUNT   BT_US_MTU_L2C_BYTE_COUNT
#endif
#endif

#if (F_BT_RFCOMM_EXPSERV_SUPPORTED && !F_BT_QDATA_SUPPORTED)
#error !!set BT_QDATA_SUPPORTED
#endif

#if (BT_HCI_PAGE_TIMEOUT_DEFAULT_COUNT == 0)
#undef BT_HCI_PAGE_TIMEOUT_DEFAULT_COUNT
#define BT_HCI_PAGE_TIMEOUT_DEFAULT_COUNT 0x2000
#endif

#if (F_BT_LOW_ENERGY && (!F_BT4_0))
#error BT Low Energy first defined in BT V4.0
#endif

#if (F_BT_LE_CENTRAL) || \
    (F_BT_LE_PERIPHERAL) || \
    (F_BT_LE_PRIVACY_RESOLVING) || \
    (F_BT_LE_PRIVACY_MODE)
#if (!F_BT_LOW_ENERGY)
#error !!set F_BT_LOW_ENERGY
#endif
#endif

#if (F_BT_LE_PRIVACY_RESOLVING) || (F_BT_LE_PRIVACY_MODE)
#if !(F_BT_SECMAN)
#error !!set F_BT_SECMAN
#endif
#endif

#if (F_BT_GATT)
#if !(F_BT_GATT_CLIENT) && !(F_BT_GATT_SERVER_MIN)
#error F_BT_GATT_CLIENT=1 or F_BT_GATT_SERVER_MIN=1 required
#endif
#if (F_BT_GATT_SERVER) && !(F_BT_GATT_SERVER_MIN)
#error F_BT_GATT_SERVER=1 requires F_BT_GATT_SERVER_MIN=1
#endif

#if (F_BT_GATT_SVC_DIS)  || \
    (F_BT_GATT_SVC_GLS)  || \
    (F_BT_GATT_SVC_CTS)  || \
    (F_BT_GATT_SVC_NDCS) || \
    (F_BT_GATT_SVC_RTUS) || \
    (F_BT_GATT_SVC_BAS)  || \
    (F_BT_GATT_SVC_HRS)  || \
    (F_BT_GATT_SVC_BLS)
#define F_BT_GATT_SVC_BUILTIN   1  /* built-in GATT services supported */
#else
#define F_BT_GATT_SVC_BUILTIN   0
#endif
#if (F_BT_GATT_SVC_BUILTIN) && !(F_BT_GATT_SERVER)
#error F_BT_GATT_SVC_BUILTIN=1 requires F_BT_GATT_SERVER=1
#endif

#if (BT_GATT_US_WRITE_OFFSET_COUNT == 0)
#undef BT_GATT_US_WRITE_OFFSET_COUNT
#define BT_GATT_US_WRITE_OFFSET_COUNT    28
#endif

#endif /* (F_BT_GATT) */

#if ((BT_US_WRITE_OFFSET_COUNT & 3) || (BT_DS_WRITE_OFFSET_COUNT & 3))
#error DWORD alignment required
#endif

#if (BT_ATT_MTU_SIZE_LE_COUNT)
#if (BT_ATT_MTU_SIZE_LE_COUNT < 23)
#error LE ATT MTU size must be >= 23
#endif
#else
#undef BT_ATT_MTU_SIZE_LE_COUNT
#define BT_ATT_MTU_SIZE_LE_COUNT 23
#endif


#if (F_BT_BB_TI_CC2560B) && (F_BT_BB_TI_CC2560 == 0)
#error F_BT_BB_TI_CC2560 must be set too !!!
#endif

#if (F_BT_BB_TI_CC2564B) && (F_BT_BB_TI_CC2564 == 0)
#error F_BT_BB_TI_CC2564 must be set too !!!
#endif

#endif /* ] (F_BLUE_TOOTH) */


#if (F_BLUE_API)

/*
 * ds buffers active at a time (only used for signaling):
 * - 2 per MCL for connect/disconnect (*req + *cnf)
 * - 3 per ACL for authentication (authreq + 2x *cnf)
 * - 2 per system for discovery (*req + *cnf)
 */
#define BLUE_API_MAX_DS_MSG_COUNT (BLUE_API_MCL_COUNT * 2) + (BT_MAX_ACL_CONNECTION_COUNT * 3) + 2

/*
 * us buffers (only used for signaling):
 * - 3 per MCL for connect/disconnect (*ind + 2x MCLStatusInfo)
 * - 3 per ACL for authentication (2x *ind + 1x ACLStatusInfo)
 * - 3 per system for discovery (*ind + 2x InternalEventInfo)
 * - <bondtablesize> buffers for AuthListInfo
 */
#define BLUE_API_MAX_US_MSG_COUNT (BLUE_API_MCL_COUNT * 3) + (BT_MAX_ACL_CONNECTION_COUNT * 3) + 3 + BTSOS_BOND_POOL_ELEMENT_COUNT

#if (F_BT_DYNAMIC)
#undef BLUE_API_DATASTORE_PEER_COUNT
#undef BLUE_API_DATASTORE_SMALL_ENTRY_COUNT
#undef BLUE_API_DATASTORE_LARGE_ENTRY_COUNT
#if (F_DB)
#error F_BT_DYNAMIC can not be used with F_DB (sizeof(TBlueAPI_DSNVData) not known)
#endif /* (F_DB) */
#else /* (F_BT_DYNAMIC) */
#if (BLUE_API_DATASTORE_LARGE_ENTRY_COUNT < BLUE_API_DATASTORE_PEER_COUNT)
#error need at least one large entry per peer (BR/EDR linkkey)
#endif
#endif /* (F_BT_DYNAMIC) */

#endif /* (F_BLUE_API) */


/****************************************************************************/
/* I2C                                                                      */
/****************************************************************************/

#if (BLUESILK_I2C_COUNT > 0) || (STLC2410_I2C_COUNT > 0) || (STM32_I2C_COUNT > 0)
#undef F_I2C
#define F_I2C 1       /* summarize I2C counts */
#endif

/****************************************************************************/
/* STM32                                                                    */
/****************************************************************************/

#if (STM32_COUNT > 0)   /* STM32F1xx */ && (STM32F2xx_COUNT > 0)
#if (CORTEX_M3_COUNT == 0)
#error !! set CORTEX_M3
#endif
#endif /* (STM32_COUNT > 0) */

#if (STM32F4xx_COUNT > 0)
#if (CORTEX_M4_COUNT == 0)
#error !! set CORTEX_M4
#endif
#endif /* (STM32_COUNT > 0) */

/****************************************************************************/
/* ASYNC power manegement                                                   */
/****************************************************************************/

#if ((F_ASYNC_EHCILL) || (F_ASYNC_UICP)) && (!F_ASYNC_INTERFACE_UP_DOWN)
#error !!set F_ASYNC_INTERFACE_UP_DOWN
#endif

#if ((F_ASYNC_EHCILL) || (F_ASYNC_UICP) || (F_ASYNC_INTERFACE_UP_DOWN)) && \
    (!F_ASYNC_POWER_MANAGEMENT)
#error !!set ASYNC_POWER_MANAGEMENT
#endif

/****************************************************************************/
/* power manager                                                            */
/****************************************************************************/

#if (F_RM_POWER_MANAGER) && (F_POWER_MANAGER)
#error !! Reset flag RM Power manager, power manager works without resource manager
#endif

#if (F_RM_POWER_MANAGER) || (F_POWER_MANAGER)
#if (!F_TRIGGER_RESCHEDULING)
#error !!Set flags in FLAGS.REC
#endif

#if (STM32_COUNT > 0) || (STM32F2xx_COUNT) || (STM32F4xx_COUNT)
#if ((!F_USE_LONG_TIMER_IN_POWERDOWN) || (!F_STM32_RTC_LONG_TIMER))
#error !!Set flags in FLAGS.REC
#endif

#if (F_OS_IDLE_CALLBACK)
#if (!F_OS_EARLY_INTERRUPT_ENABLE)
#error !!Set flags in FLAGS.REC
#endif
#else /* (F_OS_IDLE_CALLBACK) */
#error !!Set flags in FLAGS.REC
#endif
#endif
#else /* (F_RM_POWER_MANAGER) */
#if (F_USE_LONG_TIMER_IN_POWERDOWN)
#error !!reset flags in FLAGS.REC
#endif
#endif

/****************************************************************************/
/* FlashDB                                                                  */
/****************************************************************************/

#if (F_FLASH_DB)
#if (!F_BTX_CRC16)
#error !!!set flag
#endif
#if (!F_FLASH_CFI)   /* support only CFI */
#error !!!set flag
#endif
#endif /* (F_FLASH_DB) */


/****************************************************************************/
/* Apple iAP1 (iPod Accessory Protocol 1)                                   */
/****************************************************************************/

#if (F_APPLE_IAP_ADD_LINGO_SUPPORT)
#if (!F_APPLE_IAP_SIMPLE_REMOTE)
#error !! at least one additional Lingo required
#endif
#else
#if (F_APPLE_IAP_SIMPLE_REMOTE)
#error !! F_APPLE_IAP_ADD_LINGO_SUPPORT=1 required
#endif
#endif


