/***************************************************************/
/* $Header: /var/lib/cvs/sw/./tool/flags.awk,v 1.24 2016/01/14 13:20:31 mj Exp $ */
/*                                                             */
/* !!! This file is generated automatically          !!!       */
/* !!! Don't change it manually                      !!!       */
/* !!! For additional FLAGS use file 'ADDFLAGS.H'    !!!       */
/*                                                             */
/***************************************************************/

#ifndef __FLAGS_H
#define __FLAGS_H      1


/***************************************************************/
/*Hardware / OEM definitions                                   */
/***************************************************************/


#ifdef  BLB1352
#undef  BLB1352
#define HW_NAME   "BLB0D52"
#ifndef BLB
#define BLB                      1
#endif
#define HW_BLB                   1
#define OEM                      135
#define OEM_VARIANT              2
#define F_OPTIMIZE_RAM_SIZE      0         /*Optimize RAM size*/
#define F_OPTIMIZE_CODE_SIZE     0         /*Optimize code size*/
#define F_LOW_PERFORMANCE        0         /*Low perfomance*/
#define F_ISDN                   0         /*ISDN protocol included*/
#define F_1TR6                   0         /*ISDN Protocol 1TR6*/
#define F_5ESS                   0         /*D-channel protocol*/
#define F_JATE                   0         /*D-channel protocol JAPAN*/
#define F_NI12                   0         /*D-channel protocol*/
#define F_VN                     0         /*D-channel protocol France*/
#define F_NMDS                   0         /*D-channel protocol NMDS*/
#define F_AUSTEL                 0         /*D-channel protocol Austalia*/
#define F_CSELT_PILOT            0         /*Italian national protocol*/
#define F_LEASED_LINE            0         /*D_Channel fake protocol*/
#define F_X31_D                  0         /**/
#define F_LAPD                   0         /*ITU-T Q.921*/
#define F_L3DC_SEGMENTATION      0         /*Use d channel layer 3 segmentation*/
#define F_L3_TRANSP_OVER_D2      0         /*L3 fully transparent over D2*/
#define F_L3_DSS1_T350           0         /*L3 private timer for L2 shutdown if idle*/
#define F_L3_TRACE_PDUTEXT       0         /*L3 trace mnemonic (PDU)*/
#define F_DSS1_NT                0         /**/
#define F_L1DC_NT                0         /**/
#define F_OKTOPUS                0         /*test Italian PILOT services on DSS1 switch*/
#define F_PRIMARY_RATE           0         /*Use primary rate interface*/
#define F_DYNAMIC_ISDN_RECONFIG  0         /*(Pseudo-)Dynamic ISDN stack reconfig.*/
#define F_CUSTOMER_MODULES       0         /*stack init./starts customer modules*/
#define F_CUSTOMER_INT_HANDLERS  0         /*customer provides interrupt handlers*/
#define F_B_CHANNEL_STACK        0         /*B-channel protocol stack available*/
#define F_T70NL                  0         /**/
#define F_T90NL                  0         /**/
#define F_X25                    0         /**/
#define F_X25MUX                 0         /*X25 like protocol for OEM 49*/
#define F_X75                    0         /*ITU-T X.75*/
#define F_LAPB                   0         /*ITU-T X.25 Layer 2*/
#define F_V120                   0         /*ITU-T V.120*/
#define F_LAPF                   0         /*ITU-T Q.922*/
#define F_V42BIS                 0         /*V42 Compression*/
#define F_AHDLC                  0         /*Async HDLC*/
#define F_V110                   0         /*Software V110 for L1 driver (HSCX, IPAC, etc.)*/
#define F_EXT_IOM                0         /*B-Channel data routed to external IOM device*/
#define F_EXT_AUDIO              0         /*B-Channel Audio data are handled else where (e.g. PCM)*/
#define F_ZVEI_PROT              0         /*electricity meter protocoll*/
#define F_HSHF_PROT              0         /*Headset Handsfree Headset*/
#define F_TELIM                  0         /*V21 Protocol with 10baud*/
#define F_SMS_PROTOCOL_1         0         /*SMS for PSTN/ISDN ETSI ES 201 912*/
#define F_SWTDT                  0         /*Software tone detect in L1HDLC module*/
#define F_L1_MODE_TE             0         /*ISDN S0 - TE mode*/
#define F_L1_MODE_LT_T           0         /*ISDN S0 - LT-T mode*/
#define F_L1_MODE_LT_S           0         /*ISDN S0 - LT-S mode*/
#define F_L1_MODE_NT             0         /*ISDN S0 -NT mode*/
#define F_L1_MODE_INT            0         /*ISDN U+S0 - intelligent NT*/
#define F_L1_REGISTER_ACCESS     0         /*DB access to chip registers*/
#define F_CAPI_EXTERNAL_DEVICES  0         /**/
#define F_CAPI_MNF_EXT           0         /**/
#define F_CAPI_MNF_MSG           0         /**/
#define F_CAPI_MNF_TRACE_IF      0         /*Access trace module with capi mnf extensions*/
#define F_CAPI_NET_MSG           0         /*Include definitions for virtual CAPI (VCAPI, LAN-CAPI)*/
#define F_CAPI_V11               0         /*CAPI V1.1*/
#define F_CAPI_GUARD             0         /*CAPI call supervision*/
#define F_CAPI_TRACE             0         /*CAPI (CM) trace*/
#define F_CAPI_TRACE_CMDTEXT     0         /*CAPI cmds additionally as text*/
#define F_CAPI_TRACE_EXT1        0         /*CAPI trace extension 1: ext. trace mask settings*/
#define F_CAPI_LINE_INTERCONN    0         /*CAPI line (basic) interconnection*/
#define F_CAPIAPP                0         /**/
#define F_CAPITRACE              0         /*CAPIAPP trace*/
#define F_FIXED_CAPI_PARAMETERS  0         /*CAPI parameters can not be changed*/
#define F_CAPI_X25_CALLOUT_NO_LISTENB3 0         /*CAPI send no listen B3 in case of X25 outgoimg call to avoid early b-channel activity*/
#define F_HAYES                  0         /*Hayes command interface only old dialer module*/
#define F_PAD                    0         /*PAD command interface only old dialer module*/
#define F_V25BIS                 0         /*V.25bis command interface*/
#define F_REMOTE                 0         /**/
#define F_MSP                    0         /**/
#define F_GATEWAY                0         /*gateway mode*/
#define F_DTCI                   0         /*DTMF Command Interface*/
#define F_NTCI                   0         /*Italian command inteface for iNTs*/
#define F_STEI                   0         /*French remote management*/
#define F_AUTOCALL               0         /*only old dialer module*/
#define F_HOTLINE                0         /*Hotline call modi only old dialer module*/
#define F_BLUEFACE_REMOTE        0         /*BlueFace API over serial interface*/
#define F_NFC_APP                0         /*Embedded NFC Application*/
#define F_INTELLIGENT_ABIF       0         /*a/b interface SW works as CAPI application*/
#define F_TWO_ABIF_TASKS         0         /*old a/b interface with two tasks*/
#define F_INTERNAL_CONNECTIONS   0         /*Internall call features for analog ports*/
#define F_SUPPL_3PTY             0         /*suppl. service THREE PARTY CONFERENCE*/
#define F_SUPPL_AOC_DSS1         0         /*suppl. service ADVICE OF CHARGE*/
#define F_SUPPL_AOC_QSIG         0         /*suppl. service AOC / QSIG*/
#define F_SUPPL_CCBS             0         /*suppl. service CCBS*/
#define F_SUPPL_CCNR             0         /*suppl. Service CCNR*/
#define F_SUPPL_CONF             0         /*suppl. Service CONF*/
#define F_SUPPL_CD               0         /*suppl. service CALL DEFLECTION*/
#define F_SUPPL_CF               0         /*suppl. service CALL FORWARDING*/
#define F_SUPPL_CF_INTERROGATION 0         /*suppl. service interrogation for CF*/
#define F_SUPPL_ECT              0         /*suppl. service EXPLICIT CALL TRANSFER*/
#define F_SUPPL_HOLD             0         /*suppl. service CALL HOLD*/
#define F_SUPPL_HOLD_TP_BCHNL_STACK 0         /*suppl. service HOLD/TP with B-chnl prot. Stack*/
#define F_SUPPL_MCID             0         /*malicious call identification*/
#define F_SUPPL_MLPP             0         /*suppl. Service precedence/preemption*/
#define F_SUPPL_NOTIFICATIONS    0         /*suppl. service notifications*/
#define F_SUPPL_TP               0         /*suppl. service TERMINAL PORTABILITY*/
#define F_SUPPL_MWI              0         /*suppl. service MWI*/
#define F_LCR                    0         /*Least Cost Router*/
#define F_DB                     0         /*Database*/
#define CIM_COUNT                0         /*Command Interface Manager Count equal to CI-channel in your system*/
#define F_CONFIG_APP             0         /*Configurator Application*/
#define F_SCONF                  0         /*Simple Configurator Application*/
#define F_CUSTOMER_CFG           1         /*Customer provides configuration settings source module.*/
#define F_SICNF                  0         /*Service/Serial Interface for CoNFigurator application*/
#define F_CF                     0         /**/
#define F_VMOD                   0         /*virtual modem*/
#define F_NO_MODUL_MANAGER       0         /*no modul manager*/
#define F_CCIF                   0         /*call control interface example for LCR*/
#define LIBCMDEMO_COUNT          0         /*Demo Appl. for LibCM usage*/
#define F_L1_ASYNC_LAYER         0         /*Using new L1ASYNC layer*/
#define F_L1_HDLC_LAYER          0         /*Using new L1 HDLC layer*/
#define F_BRDG                   0         /*L1(U<->S) Bridge module*/
#define F_H4DS                   0         /**/
#define F_APPLE_IAP              0         /*Apple iAP1 General Lingo subset*/
#define F_APPLE_IAP_ADD_LINGO_SUPPORT 0         /*Support of iAP1 additional Lingos*/
#define F_APPLE_IAP_SIMPLE_REMOTE 0         /*Support iAP1 Simple Remote Lingo subset*/
#define F_APPLE_IAP2             0         /*Apple iAP2*/
#define APPLE_IAP_LINK_COUNT     0         /*Supported link count*/
#define SICNF_FRAMELENGTH_COUNT  0         /*Length of Commandline*/
#define SICNF_ECHO_BUFFER_COUNT  0         /*Number of Echobuffer*/
#define SICNF_ASS_BUFFER_LENGTH_COUNT 0         /*Length of Assemblebuffer*/
#define SICNF_ASS_BUFFER_COUNT   0         /*Number of Assemblebuffer*/
#define F_SITNL                  0         /*Serial interface (data) tunnel*/
#define SITNL_SERIAL_COUNT       0         /*# of serial interf. Used by SITNL*/
#define F_INTELLIGENT_NT         0         /*Intelligent NT*/
#define F_ITALY_INT              0         /*Intelligent NT for Italy*/
#define F_TENDER3                0         /*Italy NT Spec. Dez. 98*/
#define F_NO_TRANSPARENT_S_BUS   0         /*No transparent d-channel (U<->S)*/
#define F_UART_AHDLC             0         /*UART Async. HDLC*/
#define F_IBRO30                 0         /*Async protocol similar to BTX*/
#define F_USB_CONFIG_SUPPORT     0         /*support for runtime configuration*/
#define F_USB_STRING_SUPPORT     0         /*string support for USB interface*/
#define F_USB_PACKET_LENGTH_VALID 0         /*first two bytes of non EP0 packets contain packet length*/
#define F_USB_PREVENT_ZERO_TERMIN 0         /*avoid zero packet as short packet by adding one fill byte to data in neccessary*/
#define F_USB_BULK_STREAMING     0         /*support for endles long BULK packets, no short packets needed*/
#define USB_ENDPOINTS_COUNT      0         /*amount of used endpints*/
#define USB_EP0_BUFFER_COUNT     0         /**/
#define USB_EP0_BUFFER_SIZE_COUNT 0         /**/
#define F_USB_EP1_IS_IN          0         /*direction of endpoint*/
#define USB_EP1_BUFFER_COUNT     0         /**/
#define USB_EP1_BUFFER_SIZE_COUNT 0         /**/
#define F_USB_EP2_IS_IN          0         /*direction of endpoint*/
#define USB_EP2_BUFFER_COUNT     0         /**/
#define USB_EP2_BUFFER_SIZE_COUNT 0         /**/
#define F_USB_EP3_IS_IN          0         /*direction of endpoint*/
#define USB_EP3_BUFFER_COUNT     0         /**/
#define USB_EP3_BUFFER_SIZE_COUNT 0         /**/
#define F_USB_EP4_IS_IN          0         /*direction of endpoint*/
#define USB_EP4_BUFFER_COUNT     0         /**/
#define USB_EP4_BUFFER_SIZE_COUNT 0         /**/
#define F_USB_EP5_IS_IN          0         /*direction of endpoint*/
#define USB_EP5_BUFFER_COUNT     0         /**/
#define USB_EP5_BUFFER_SIZE_COUNT 0         /**/
#define F_USB_EP6_IS_IN          0         /*direction of endpoint*/
#define USB_EP6_BUFFER_COUNT     0         /**/
#define USB_EP6_BUFFER_SIZE_COUNT 0         /**/
#define F_USB_EP7_IS_IN          0         /*direction of endpoint*/
#define USB_EP7_BUFFER_COUNT     0         /**/
#define USB_EP7_BUFFER_SIZE_COUNT 0         /**/
#define F_AUDIOHID_APP           0         /*USB Audio/HID dongle application*/
#define F_AUTOBAUD               0         /*Hayes baudrate detection*/
#define F_BLACKLISTING           0         /*Blacklisting for JAPAN*/
#define F_CALLBACK               0         /*reject incoming call and call back*/
#define F_FIXED_ISP              0         /*fixed ISP*/
#define F_DIAL_USERDATA          0         /*User to User Data*/
#define F_DMA                    0         /*Intel DMA*/
#define F_HWAPI                  0         /**/
#define F_HWAPI_PIO_CTRL         0         /*hwapi includes generic GPIO control functions*/
#define F_HWAPI_HIGHRES_TIMMER_SUPPORT 0         /*hwapi includes access to high resolution timers*/
#define F_SYSTEM_RESET_ON_ERROR  0         /*reset whole system on fatal error (hwardware reset)*/
#define F_SYSTEM_DO_NOT_SAVE_RESET_CAUSE 0         /*do not save reset cause*/
#define F_LOADABLE               0         /*FW can be loaded to flash EPROM by BOOT loader*/
#define F_MODULE                 0         /*module headers*/
#define F_BOOTLOADER_CHECK_HW_IN_FW_HEADER 0         /*bootloader checks HW ID within firmware header*/
#define F_HW_TEST                0         /*hardware test*/
#define F_HW_DB                  0         /*hw-module has db-parameters*/
#define F_HW_FLASH_WRITE_COUNTER 0         /*write counter for flash access (NVRAM)*/
#define F_DYNAMIC_TEI_SELECTION  0         /*dynamic handling of LAPD links*/
#define F_VOICE                  0         /*Voice messages on AB port*/
#define F_DIAG_CAPACITY          0         /*Capacitance test*/
#define F_ENHANCED_DIAG          0         /*Enhanced diagnostics (GB)*/
#define F_TAX_PULSES             0         /*TAX pulses on AB port*/
#define F_PROG_TAX_TYPE          0         /*Programable tax output signal type 12/16kHz or polarity reversal*/
#define F_TRANSP_DCH_INFO        0         /*Access to all D-chnl info elements*/
#define F_B_CH_DEBLOC            0         /*deblockade B-Channel*/
#define F_B_REAL_CH_DEBLOC       0         /*deblockade B-Channel*/
#define F_HW_POLL                0         /*Poll hardware events*/
#define F_HW_DTMF_DETECTION_SOFT 0         /*Do DTMF detection with software (Goertzel)*/
#define F_HW_DTMF_GENERATION_SOFT 0         /*Software algorythm for DTMF generation*/
#define F_HW_TONE_DETECTION_SOFT 0         /*Dial tone (425 Hz) detection (Goertzel)*/
#define F_HW_CLIP_DTAS_DETECTION_SOFT 0         /*CLIP DT-AS tone detection (Goertzel)*/
#define F_HW_CLIP_DETECTION_SOFT 0         /*Was ist das? sn*/
#define F_HW_CNG_DETECTION_SOFT  0         /*Was ist das? sn*/
#define F_HW_CHECK_SCLK          0         /*check slow clock availability*/
#define F_HW_VERSION_DETECTION   0         /*Hardware Version Detection by using hardware specific feature eg. GPIO*/
#define F_PASSWORD               0         /*Password protection for DB parameters.*/
#define F_BTX                    0         /*include BTX related code*/
#define F_BYPASS_AUTO_CONFIG     0         /*Bypass U/AB for Italy*/
#define F_CHB_TRP                0         /*Channel Bundling, transparent, HSCX*/
#define F_STATUS                 0         /*Send stack infos upstream to application*/
#define F_BLUE_TOOTH             1         /*includes bluetooth stack*/
#define F_DIAL_MLPPP             0         /*Dialler / Multilink PPP*/
#define F_MLPPP                  0         /*MLPPP / use capi hook*/
#define F_MLPPP_CALLIN           0         /*Handle incoming mlppp (server mode)*/
#define F_MLPPP_AUTHENTICATOR    0         /*mlppp module is authenticator too*/
#define F_MLPPP_UCB              0         /*mlppp unconditional (useless) callbumping*/
#define F_MS_CHAP                0         /*Microsoft CHAP*/
#define F_NO_LOCAL_CHAP          0         /*No local CHAP algorithm code*/
#define F_BOD                    0         /*Bandwidth on demand*/
#define F_AO_DI                  0         /*Always on/Dynamic ISDN*/
#define F_BACP                   0         /*Bandwidth alloc. Control protocol*/
#define F_PASSIVE_CARD           0         /*pc passive card or similar*/
#define F_SAM                    0         /*service and monitor (OEM 58)*/
#define F_S2EIP                  0         /*TCP/IP (special) for S2E Project (OEM 58)*/
#define F_COMPILER_LIB           1         /*use of builtin compiler libraries*/
#define F_BIG_ENDIAN             0         /*big endian mode (high byte first)*/
#define F_STATS                  0         /*Statistics and status of modules*/
#define F_FLASH                  0         /*Internal FLASH functions*/
#define F_FLASH_DB               0         /*Database using flash*/
#define F_ACCTAB                 0         /*Access number table*/
#define F_CLIP_ON_ANALOG_PORT    0         /*Caller ID on AB*/
#define F_CLIP_ON_USB            0         /*Caller-ID over USB*/
#define F_CLIP_RX                0         /*The device is the receiver of Caller ID data.*/
#define F_POWER_MANAGEMENT       0         /*Power reduction modes*/
#define F_STACK_CHECK            0         /*Check stack overflow*/
#define F_TRIGGER_RESCHEDULING   1         /*external trigger for rescheduling*/
#define F_DEFERRED_CALLBACK      1         /*Deferred buffer callback*/
#define F_OSIF                   1         /*OSIF environment message.h, tt-board.h etc.*/
#define F_OSIF_CALLBACK          1         /*General callback in osReschedule().*/
#define F_NO_IDLE_LOOP           0         /*No idle loop code and execution*/
#define F_MESSAGE_CONV           0         /*pack/unpack messages for communication between diff. CPU's*/
#define F_CONVTO_STATIC_BUFFER   0         /*use static Buffer for MESSAGE_CONV*/
#define F_HOTPLUG_L1             0         /*hoplugging for USB, etc*/
#define F_RTC                    0         /*Real time clock*/
#define F_TEST_APPLICATION       0         /*Test application (CPDemo)*/
#define F_NO_CONNECT_RESET       0         /*Reset after x sec with no connection*/
#define F_NO_HARDWARE            1         /*No hardware access*/
#define F_NO_BCHANNEL_HW         0         /*No B channel hardware*/
#define F_LINE_MONITOR           0         /*Line monitor*/
#define F_COM_PNP                0         /*PNP Id for serial driver*/
#define F_DTE_DCE                0         /*DTE and DCE mode (default - DCE mode only)*/
#define F_HOST_WAKEUP_CONTROL    0         /*use DSR signal to wakeup host if data is available*/
#define F_CABLE_REPLACEMENT      0         /*Cable replacement*/
#define F_RESOURCE_MANAGER       0         /*Resource manager*/
#define F_MEMORY_NOT_SEGMENTED   1         /*No memory segmentaion*/
#define F_NO_GLOBAL_POOL         1         /*No global pool*/
#define F_CLEAR_BSS              0         /*Help startup to clear BSS*/
#define F_NO_GLOBAL              1         /*No global struct*/
#define F_NO_NVRAM               0         /*No NVRAM*/
#define F_BONDING                0         /*Bonding*/
#define F_CAPIHOOK_BUNDLING      0         /*B-channel (X.75) bundling*/
#define CPHK_MAX_NCCI_COUNT      0         /*Max Bonding(B) Channel for all controller*/
#define CPHK_INSTANCE_COUNT      0         /*Max Capi Hook instances*/
#define BDG_DELAY_LENGTH_COUNT   0         /*Bonding Delay Length (L1 BlockSize)*/
#define F_TIME_LIMIT             0         /*Time limitation (e.g. demo version)*/
#define F_BD_CHECK_AFTER_DB      0         /*time limitation: bd check after DB read*/
#define F_DUMP                   0         /*enable of dump commands in config*/
#define F_LOADSW                 0         /*load and start sw command in config*/
#define F_USE_CFW_TIMERS         0         /*use ST-CFW timers*/
#define F_USE_ZVLL_TIMERS        0         /*use ZVLL timers*/
#define F_POLL_POWERDOWN         0         /*poll powerdown GPIO*/
#define F_SHORTHOLD              0         /*Shorthold module*/
#define F_HW_POWER_MODE          0         /*Power reduction modes*/
#define F_HW_RS485               0         /*RS 485 supported*/
#define F_RSSIIO_MODE1           0         /*RSSI gpio indication mode 1 supported*/
#define F_RSSIIO_MODE2           0         /*RSSI gpio indication mode 2 supported*/
#define F_FIX_7_BITS_TRANSFER    0         /*simulate 7E and 7O data transfer if chip does not support this*/
#define F_FW_EMERGENCY_ACCESS    0         /*firmware emergency access if UART not accessible due to parameter settings*/
#define F_OSLEC                  0         /**/
#define F_EXTERN_MODULE          0         /*external module*/
#define F_EXTERN_OVER_USB        0         /*access to external module over USB*/
#define F_EXTERN_OVER_DPR        0         /*access to external module over DPRAM*/
#define F_EXTERNAL_L1_MODULE     0         /*external layer 1 module*/
#define F_EXTERNAL_L2_MODULE     0         /*external layer 2 module*/
#define F_EXTERNAL_L3_MODULE     0         /*external layer 3 module*/
#define F_EXTERNAL_DC_MODULE     0         /*external layer 3 (D channel) module*/
#define F_NV_IN_FEP              0         /*Use FEP for NVRAM data*/
#define F_NV_PROTECTED_AREA      0         /*Reset protected NVRAM area*/
#define F_NV_SERIAL_NUMBER       0         /*Serial number in reset protected NVRAM area*/
#define F_NV_LNX                 0         /*use linux nvram emu*/
#define F_NO_TRACE_MESSAGE       1         /*No trace entry for messages (unpacked struct in PACKED(struct)).*/
#define TRC_TIMER_OUTPUT_VALUE_COUNT 0         /*Trace output control via timer in ticks*/
#define F_TRC_NO_FORCE_COLD_START 0         /*force Trace to reset the tracebuffer after SW-Reset*/
#define F_TRC_RESET_CAUSE        0         /*Target has reset cause*/
#define TRC_OUTPUT_BUFFER_COUNT  60       /*Trace buffer count*/
#define TRC_OUTPUT_BUFFER_BYTE_COUNT 0xE0     /*Trace buffer length*/
#define F_TRC_OUTPUT_ONLINE      1         /*Trace online (no trcread command)*/
#define F_TRACE_BINARY           0         /*Binary trace*/
#define F_TRACE_BINARY_DYNAMIC_CONFIG 0         /*Dynamic config*/
#define TRACE_BINARY_OUTPUT_BUFFER_COUNT 0         /*Trace buffer count*/
#define TRACE_BINARY_OUTPUT_BUFFER_BYTE_COUNT 0         /*Trace buffer length*/
#define TRACE_BINARY_MAX_USE_BUFFER_COUNT 0         /*Max. buffer for binary/string output*/
#define F_FLASH_CFI              0         /*use CFI either flash supports CFI or we are using predefined CFI structure*/
#define F_AM29LV800B             0         /*AMD 8Mbit Bottom*/
#define F_AM29LV400B             0         /*AMD 8Mbit Bottom*/
#define F_M29W400B               0         /*ST 4Mbit Bottom*/
#define F_M29W800DB              0         /*ST 8Mbit Bottom*/
#define F_ES29LV800DB            0         /*EXCEL 8Mbit Bottom*/
#define F_ES29LV400EB            0         /*EXCEL 4Mbit Bottom*/
#define F_EN29LV400AB            0         /*EON 4MBit Bottom*/
#define F_EN29LV800CB            0         /*EON 8MBit Bottom*/
#define F_F49L800BA              0         /*ESMT 8Mbit Bottom*/
#define F_FLASH_DEVICE8_BUS32    0         /*8 Bit flash 32 Bit bus*/
#define F_FLASH_DEVICE16_BUS16   0         /*16 Bit flash 16 Bit bus*/
#define F_FLASH_DEVICE16_BUS8    0         /*16 Bit flash 8 Bit bus*/
#define F_FLASH_DEVICE32_BUS32   0         /*32 Bit flash 32 Bit bus*/
#define ABIF_COUNT               0         /*analog terminal interfaces*/
#define ALIF_COUNT               0         /*analog line interfaces*/
#define ACE_COUNT                0         /*Acoustic Echo Canceller (PSB 2170)*/
#define AD5301_COUNT             0         /*Analog Device D/A converter*/
#define AFE_COUNT                0         /*Analog Frontend (PSB 4851)*/
#define ASC0_COUNT               0         /*serial interface from Siemens CPUs*/
#define ASYNC_DUMMY_COUNT        0         /*Dummy driver for L1ASYNC*/
#define AT91_ARM_COUNT           0         /*Atmel Arm Thumb Microcontroller*/
#define AT91_USART_COUNT         0         /*On Board USART Count*/
#define AT91SAM7SX_COUNT         0         /*Atmel AT91SAM7S32/256*/
#define AT91SAM7SX_TWI_COUNT     0         /*Atmel AT91SAM7S32/256 TWI*/
#define AT91SAM7SX_UART_COUNT    0         /*Atmel AT91SAM7S32/256 UART*/
#define F_AT91SAM7SX_UART_TRANSPARENT 0         /*Atmel UART transparentmode*/
#define AT32_COUNT               0         /*Atmel AVR32*/
#define AT32_UART_COUNT          0         /*Atmel AVR32 USART*/
#define AT32_UART_BAL_COUNT      0         /*Atmel AVR32 USART BAL*/
#define BLACKFIN_COUNT           0         /*ADSPBDxxx Analog Device*/
#define BLUESILK_COUNT           0         /*STLC2416 ARM Microcontroller*/
#define BLUESILK_I2C_COUNT       0         /*STLC2416 ARM Microcontroller I2C*/
#define BLUESILK_SSI_COUNT       0         /*STLC2416 ARM Microcontroller SSI*/
#define BUTTONS_COUNT            0         /*number of buttons on hardware*/
#define CCD_PCI2PI_BR_COUNT      0         /*Cologne PCI to PI FPGA bridge*/
#define COL_COUNT                0         /**/
#define CCPI_COUNT               0         /**/
#define CODEC_COUNT              0         /*general count. see specif. Count too!*/
#define COMAPI_COUNT             0         /*L1ASYNC with COMAPI*/
#define COMTASK_COUNT            0         /*L1 HCI protocol layer*/
#define CORTEX_M3_COUNT          0         /*ARM Core Cortex-M3*/
#define CORTEX_M4_COUNT          0         /*ARM Core Cortex-M4*/
#define CNX16550_COUNT           0         /*Conexant 06833 Modem UART*/
#define CS89X0_COUNT             0         /*Ethernet Controller cs8900/cs8920 from Cirrus Logic*/
#define DIP_SWITCH_COUNT         0         /**/
#define DMT_COUNT                0         /**/
#define DTMF_COUNT               0         /**/
#define DS12887_COUNT            0         /*Dallas Real Time Clock*/
#define DS2401_COUNT             0         /*DS2401 serial number chip*/
#define DS2502_COUNT             0         /*Dallas serial password chip*/
#define EEPROM_ATMEL_2416_COUNT  0         /*Atmel EEPROM*/
#define EEPROM_ST_2464_COUNT     0         /*ST EEPROM*/
#define EEPROM_ST_24256_COUNT    0         /*ST EEPROM*/
#define EEPROM_MICROCHIP_241025_COUNT 0         /*Microchip EEPROM 24xx1025*/
#define EEPROM_ON_CAT24C01_COUNT 0         /*On Semiconductor EEPROM CAT24C01*/
#define EPIC_COUNT               0         /**/
#define EXTERNAL_L1_COUNT        0         /*external layer 1 module*/
#define FALC_COUNT               0         /*L1 for E1*/
#define FM_COUNT                 0         /**/
#define GENERIC_CODEC_COUNT      0         /*use generic codec interface*/
#define GENERIC_L1DRV_COUNT      0         /*use generic L1 (customer suppl.) chip driver*/
#define HFCS_COUNT               0         /**/
#define HFCSMINI_COUNT           0         /*HFC-S mini (Cologne Chip)*/
#define HFC4S_COUNT              0         /*HFC-4/8S (Cologne Chip) 4 S0 interface*/
#define HFC8S_COUNT              0         /*HFC-4/8S (Cologne Chip) 8 S0 interface*/
#define HFCE1_COUNT              0         /*HFC-E1 (Cologne Chip)*/
#define HSCX_COUNT               0         /**/
#define ICC_COUNT                0         /**/
#define IDEC_COUNT               0         /**/
#define IEC_COUNT                0         /**/
#define IEPC_COUNT               0         /**/
#define INTCQ_COUNT              0         /**/
#define INTCQ2_COUNT             0         /*Infineon PEF 82912*/
#define INTCQ2_HDLC_COUNT        0         /*Use HDLC part of 82912*/
#define IPAC_COUNT               0         /**/
#define IPACX_COUNT              0         /*Infineon PSB 21150 (S transceiver)*/
#define ISAC_COUNT               0         /**/
#define ISACX_COUNT              0         /*Infineon PEB 3086 (S transceiver)*/
#define SCOUT_S_COUNT            0         /*Infineon PSB21384 (S transceiver with Arcofi)*/
#define ITAC_COUNT               0         /**/
#define L1BT_COUNT               0         /*Async Layer 1 module using Bluetooth*/
#define LAN91CXXX_COUNT          0         /*SMC LAN91Cxxx series*/
#define LED_COUNT                0         /**/
#define LM3S_COUNT               0         /*TI Stellaris Luminary Micro*/
#define LM3S9B96_COUNT           0         /*TI Stellaris Luminary Micro LM3S9B96*/
#define LM3S_I2C_COUNT           0         /*TI Stellaris Luminary Micro I2C*/
#define LNX_TTY_COUNT            0         /*Linux tty driver*/
#define LOGIF_COUNT              0         /*Logif V2/3 Layer*/
#define LPC17xx_COUNT            0         /*NXP LPC177x/8x Microcontroller*/
#define MAX6956_COUNT            0         /*MAXIM I/O expander*/
#define MC145484_COUNT           0         /*Motorola 5V PCM CODEC-Filter (MC145481 3V)*/
#define MC68SC302_COUNT          0         /**/
#define MFI_20_C_COUNT           0         /*Mfi Rev. 2.0 C*/
#define ML674000_COUNT           0         /*OKI ARM Base Micocontroller*/
#define ML674000_SIO_COUNT       0         /*SIO*/
#define MSM7732_COUNT            0         /*OKI Audio Codec MSM7732-01*/
#define MTC20276_COUNT           0         /*ALCATEL Single Chip ISDN NT 2B1Q (INTQ)*/
#define MTC20280_COUNT           0         /*ALCATEL ISDN/IDSL Terminal Controller (HDLC)*/
#define MTC40131_COUNT           0         /*ALCATEL SH POTS chipset*/
#define MUNICH_COUNT             0         /*MUNICH256 PEB 20256 E*/
#define N3HDLC_COUNT             0         /*N3DSLAP HDLC*/
#define NIOS2_UART_COUNT         0         /*Altera NIOS II UART*/
#define NS16550_COUNT            0         /**/
#define NTCT_COUNT               0         /*PEB 8090 Network Termination Controller (4B3T) NTC-T*/
#define NXP_NT3H1x01_COUNT       0         /*NXP NFC TAG I2C NT3H1101/NT3H1201*/
#define PAR_COUNT                0         /**/
#define PCD87750_COUNT           0         /*Philips Bluetooth baseband controller*/
#define PCF8591_COUNT            0         /*Philips 8-bit A/D and D/A converter*/
#define PCIF_COUNT               0         /**/
#define PIO_COUNT                0         /**/
#define PEC_HANDLE_COUNT         0         /**/
#define PRIMECELL_GPIO_COUNT     0         /*ARM PrimeCell GPIO*/
#define PRIMECELL_UART_COUNT     0         /*ARM PrimeCell UART*/
#define PRIMECELL_UDMA_COUNT     0         /*ARM PrimeCell uDMA*/
#define PRIMECELL_WDT_COUNT      0         /*ARM PrimeCell Watchdog Timer*/
#define QUAT_COUNT               0         /**/
#define QUICC_COUNT              0         /*68360 QUICC COUNT*/
#define QUICC_SCC_COUNT          0         /*68360 SCC COUNT*/
#define QUICC_SMC_UART_COUNT     0         /*68360 SMC UART COUNT*/
#define SBCX_COUNT               0         /**/
#define SBCXX_COUNT              0         /*Infineon PEB 3081*/
#define SEROCCO_COUNT            0         /*Infineon PEB 20525*/
#define SICOFI_COUNT             0         /**/
#define SI3050_COUNT             0         /*Silab 3050 anlog line interface, terminal side*/
#define SLICOFI2_COUNT           0         /*PEB 3265*/
#define SLICP_COUNT              0         /*PEB 4266*/
#define SMINTI_COUNT             0         /*PEF82902 4B3T and PEF82912 2B1Q*/
#define SOCKET_COUNT             0         /*D-Channel HDLC over TCP/IP*/
#define SRAE_COUNT               0         /*Stollmann Rate Adaption Epld*/
#define SSC_COUNT                0         /**/
#define STLC2410_COUNT           0         /*STMicroelectronics Bluetooth Baseband (stlc2410/15)*/
#define STLC2411_COUNT           0         /*STMicroelectronics Bluetooth Baseband (stlc2411/16)*/
#define STLC2410_BT_COUNT        0         /*STMicroelectronics Bluetooth Baseband (stlc241X)*/
#define STLC2410_I2C_COUNT       0         /*STMicroelectronics Bluetooth Baseband (stlc241X)*/
#define STLC2410_UART_COUNT      0         /*STMicroelectronics Bluetooth Baseband (stlc241X)*/
#define STM32_COUNT              0         /*STMicroelectronics STM32F10xxx Cortex-M3 core*/
#define STM32F2xx_COUNT          0         /*STMicroelectronics STM32F2xx Cortex-M3 core*/
#define STM32F4xx_COUNT          0         /*STMicroelectronics STM32F4xx Cortex-M4 core*/
#define STM32_UART_COUNT         0         /*STMicroelectronics STM32F10xxx UART*/
#define F_STM32_UART_HW_FLC_IN_TX_DIRECTION 0         /*Use HW-Flowcontrol in TX direction*/
#define STM32_I2C_COUNT          0         /*STMicroelectronics STM32F10xxx I2C*/
#define STM32_SPI_COUNT          0         /*STMicroelectronics STM32F10xxx SPI (Layer 1)*/
#define STM32_ADC_COUNT          0         /*STMicroelectronics STM32F10xxx ADC*/
#define STM32_I2C_ASYNC_COUNT    0         /*STMicroelectronics I2C using L1ASYNC*/
#define STR71x_COUNT             0         /*STMicroelectronics Microcontroller Arm7*/
#define STR71x_UART_COUNT        0         /*STMicroelectronics Microcontroller Arm7*/
#define STW5094_COUNT            0         /*STMicroelectronics Asynchronous stereo audio DAC*/
#define SWHDLC_COUNT             0         /*Software HDLC as ISDN L1 driver*/
#define TC2000_COUNT             0         /*Zeevo Single Chip Bluetooth (ARM core)*/
#define TC2001_COUNT             0         /*Zeevo Single Chip Bluetooth (ARM core)*/
#define TC2000_BT_COUNT          0         /*TC2000/TC2001 BT driver*/
#define TC2000_UART_COUNT        0         /*TC2000/TC2001 Uart*/
#define TMS_SW_UART_COUNT        0         /*Software UART for TMSC54xx*/
#define TMSC54xx_COUNT           0         /*TI TMS320C54xx*/
#define TMS320C62xx_COUNT        0         /*TI TMS320C62xx*/
#define TRACE_COUNT              1        /*Trace Module*/
#define UA_COUNT                 0         /*Universal Outputs for user*/
#define UE_COUNT                 0         /*Universal Inputs*/
#define UDLT_COUNT               0         /**/
#define USB_COUNT                0         /*USB Generic Driver*/
#define UTAH_COUNT               0         /*C165UTAH HDLC controller without USB*/
#define UTAH_ASC0_COUNT          0         /*C165UTAH ASC0 without HDLC controller and USB*/
#define VEGABB_COUNT             0         /*Phlips VEGA Bluebird*/
#define VOICE_INSTANCE_COUNT     0         /*No. Of voice output channels*/
#define W6690_COUNT              0         /**/
#define W6692_COUNT              0         /**/
#define X25160_COUNT             0         /**/
#define X25040_COUNT             0         /**/
#define XHFC1SU_COUNT            0         /*XHFC-1SU (Cologne chip)*/
#define XHFC2SU_COUNT            0         /*XHFC-2SU (Cologne chip)*/
#define XHFC4SU_COUNT            0         /*XHFC-4SU (Cologne chip)*/
#define Z8530_COUNT              0         /*Zilog SCC 85x30*/
#define ZV4002E_COUNT            0         /*Zeevo Single Chip Bluetooth (ARM core)*/
#define BR_DCHANNEL_COUNT        0         /*Nr. of D-Channel Prot-Stacks in Deblocade Module*/
#define ARM_DEBUG_COUNT          0         /*ARM with Debug communications channel (DCC)*/
#define AGILENT_ADNS_2030_COUNT  0         /*Agilent Optical Mouse Sensor*/
#define QSPAN_COUNT              0         /*Tundra PCI bridge*/
#define F_I2C                    0         /*flag should be set if one of the I2C counts above is non-zero*/
#define F_I2C_GENERIC            0         /*generic I2c Functions*/
#define F_ISTR_BUS_BYTE          0         /*8 bit device*/
#define F_ISTR_BUS_WORD          0         /*16 bit device*/
#define F_ISTR_BUS_DWORD         0         /*32 bit device*/
#define F_NO_B_ISTR_HW           0         /*No ISTR B channel hardware*/
#define F_ISTR_IOM_SDS1_B        0         /*Use SDS1 on IOM for B-Channels*/
#define F_ISTR_IOM_SDS2_B        0         /*Use SDS2 on IOM for B-Channels*/
#define F_SEROCCO_BUS_BYTE       0         /*8 bits device*/
#define F_SEROCCO_BUS_WORD       0         /*16 bits device*/
#define F_SEROCCO_BUS_DWORD      0         /*32 bits device*/
#define F_CS89X0_PACKET_PAGE_IS_IN_MEMORY 0         /*PacketPage is mapped to Memory*/
#define LINE_INTERFACE_COUNT     0         /*Number of line interfaces*/
#define DSS1_NT_TEI_COUNT        0         /*Max. TEI count for DSS1 NT stack*/
#define DSS1_TE_TEI_COUNT        0         /*Max. TEI count for DSS1 TE stack.*/
#define F_TRANSP_TEI_MANAGEMENT  0         /*use D-channel stack without tei management*/
#define F_MIXED_TEI              0         /*Fixed TEI in PTM mode*/
#define SERIAL_COUNT             0         /*Number of serial interfaces (not VMOD)*/
#define F_SERIAL_SYNC            0         /*serial synchron support*/
#define F_DTR_POLL               0         /*Polling DTR signal*/
#define F_RTS_POLL               0         /*Polling RTS signal*/
#define F_DCD_POLL               0         /*Polling DCD signal*/
#define F_RI_POLL                0         /*Polling RI signal*/
#define F_DSR_POLL               0         /*Polling DSR signal*/
#define F_HW_COM_CONTROL         0         /*HW/L0 support serial control lines*/
#define F_MM_NO_REMOVE_PROTOCOL_STACK_REQ 1         /*Protocol stack will not be removed*/
#define F_MM_NO_PENDING_PROTOCOL_STACK_REQ 1         /*All modules are started before BUILD_PROTOCOL_STACK_REQ*/
#define F_MM_BLUE_TOOTH_STACK_ONLY 1         /*Bluetooth only*/
#define F_MM_MULTIPLE_B_CHNL_L3  0         /*Support of prot. stacks with different B-chnl/L3 modules*/
#define MM_L1_HW_COUNT           0         /*Max. Layer 1 hardware (for all channel types)*/
#define MM_L1_HW_CHANNEL_COUNT   0         /*Max. Layer 1 channel nbr of one controller*/
#define MM_L1_DESCRIPTOR_COUNT   0         /*Max. Layer 1 descriptors*/
#define MM_L1_PROT_MODULE_COUNT  0         /*Max different layer 1 protocol modules*/
#define MM_PENDING_BUILD_PROT_STACK_REQ_COUNT 0         /*Max. pending messages*/
#define MM_ACTIVE_STACK_COUNT    0         /*Max. protocol stacks*/
#define MAX_MODULE_COUNT         6        /*Max. no of (protocol, CI_APPL and instance) modules (default 17)*/
#define CM_APPLICATION_COUNT     0         /*Max. applications*/
#define CM_PLCI_COUNT            0         /*Max. PLCI*/
#define CM_NCCI_COUNT            0         /*Max. NCCI*/
#define CM_LISTEN_COUNT          0         /*Max. LISTEN_REQ*/
#define F_MEM_DYNAMIC            0         /*dynamic memoy management*/
#define F_MEM_EXTERNAL           0         /*external buffer*/
#define F_OS_POOL_RELEASE        0         /*Releasing of buffer pools supported.*/
#define OS_QUEUE_ELEMENT_COUNT   56       /*max. number of queue elements*/
#define OS_QUEUE_NAME_TABLE_COUNT 60       /*Queuename table size*/
#define OS_QUEUE_NAME_ALIAS_COUNT 5        /*Max. q name alias*/
#define OS_POOL_NAME_TABLE_COUNT 10       /*Poolname table size*/
#define OS_POOL_NAME_ALIAS_COUNT 5        /*Max. q name alias*/
#define OS_CALLBACK_QUEUE_ELEMENT_COUNT 28       /*Number os queue element*/
#define OS_HEAP_COUNT            0         /*Number of heap*/
#define OS_HEAP_BYTES_COUNT      0         /*Heap size in bytes. Overrides OS_HEAP_KBYTE.*/
#define OS_HEAP_KBYTE_COUNT      0         /*Heap size in kbytes (use for F_MEM_DYNAMIC)*/
#define OS_HEAP_MEMORY_ALLOC_BYTES_COUNT 0x2400     /*Heap use for stMemoryAlloc*/
#define F_OS_HEAP_EXTERNAL       0         /*Use external heap*/
#define F_OS_MALLOC_EXTERNAL     1         /*Use external malloc*/
#define F_OS_EXT_INT_DISABLE     0         /*External disable/enable routines*/
#define F_OS_CHECK               0         /*Check function*/
#define F_OS_NO_BUFFER_DUPLICATE 1         /*Without osBufferDuplicate()*/
#define F_OS_NO_EXTENDED_BUFFER  1         /*Withoue extended buffers*/
#define OS_USER_TIMER_COUNT      0         /*User timer*/
#define OS_BUFFER_CALLBACK_BUFFER_COUNT 32       /*Max. number of buffer with callback*/
#define OS_BUFFER_CALLBACK_ELEMENT_COUNT 32       /*Max. number of buffer callback*/
#define OS_MODULE_WITH_QUEUENAMESET_COUNT 2        /*Max. number of protocol module with more than one queuename*/
#define F_OS_IDLE_CALLBACK       0         /*Idle callback function*/
#define F_OS_EARLY_INTERRUPT_ENABLE 0         /*Interrupt enabled in time after stop mode*/
#define F_OS_DEBUG               0         /*OSIF Debug*/
#define F_OS_FUNCTION_RENAME     1         /*Rename function (osXxx -> stOsXxx)*/
#define OS_TASK_EXIT_CALLBACK_QUEUE_COUNT 11       /*modules can register shall-exit functions*/
#define F_NO_SW_WATCHDOG         1         /*Do not use message supervision.*/
#define F_NO_HW_WATCHDOG         0         /*Do not use hardware watchdog*/
#define OSIF_SHORT_BUFFER_COUNT  0         /*Short Buffer Count for OSIF_CONV*/
#define OSIF_LONG_BUFFER_COUNT   0         /*Long Buffer Count for OSIF_CONV*/
#define OSIF_MAX_PROTOCOL_STACK_COUNT 0         /*Max protocol stack count in OSIF_CONV*/
#define OSIF_B_CHANNEL_COUNT_COUNT 0         /*Max B channel count to administrate*/
#define F_SECTION_LOCK_EXT       1         /*Use extended code section locks (locktgt.h ..)*/
#define F_LNX_INT_TASKLET        0         /*Deferred inter. handling thru tasklet*/
#define F_LNX_KTHREADS           0         /*Use kernel threads for inter. and scheduler*/
#define F_TIMER_CALLBACK         0         /*Timer callback*/
#define F_TIMER_NO_SUSPEND       1         /*Without suspend/resume timer*/
#define TIMER_QUEUE_ELEMENT_COUNT 12       /*Number of queue elements*/
#define F_USE_LONG_TIMER_IN_POWERDOWN 0         /*Use long timer in powerdown mode*/
#define F_STM32_RTC_LONG_TIMER   0         /*STM32 Use RTC for long timer (default SysTick)*/
#define STM32_RTC_LONG_TIMER_TICKS_COUNT 0         /*Number of ticks for long timer (0 -> default = 100 )*/
#define HW_POLL_MAX_ENTRIES_COUNT 0         /**/
#define HW_POLL_MAX_INDEX_COUNT  0         /**/
#define HW_SIGNAL_DEBOUNCE_COUNT 0         /*Number of (IRQ) driven signals to be debounced*/
#define F_L2_TRACE               0         /*More trace output for HDLC protocol*/
#define F_L2_HDLC_SREJ           0         /*use selective reject instead of normal reject see ISO/IEC 7809*/
#define X25_CHANNEL_COUNT        0         /*Max. X25 channels*/
#define F_X25_NATIVE             0         /*X.25 native mode, without D-Channel*/
#define F_X25_LBUF_AD            0         /*Large user buffer ass-/disassembly*/
#define F_X25_TRACE              0         /*More trace output for X.25 protocol*/
#define GW_CONNECTION_COUNT      0         /*Max. gateway connections*/
#define F_ISDN_API               0         /*target application interface*/
#define F_API_INTERNAL_DATAB3_BUFFER 0         /*Api allocate buffer for Data B3, application only allocate buffer for messages*/
#define API_MAX_DATA_B3_REQ_CBS_COUNT 0         /*# of pending DATA_B3_REQ descriptors*/
#define API_MAX_BUFFER_CBS_COUNT 0         /*# of undelivered OSIF buffer descriptors (DATA_B3_IND)*/
#define API_MAX_BUFFER_CBS_PER_CONN_COUNT 0         /*# of DATA_B3_IND buffer descr. per conn.*/
#define API_MAX_APPLICATIONS_COUNT 0         /*# of applic. supported by API (if 0 CM_APPLICATION is used)*/
#define API_MAX_B3_CONNECTIONS_COUNT 0         /*# of B3 connections supported by API (if 0 CM_NCCI is used)*/
#define CL_MAX_APP_COUNT         0         /*Max.  OEM Application count*/
#define CL_MAX_NCCI_COUNT        0         /*Max. NCCI count*/
#define F_LIBCM                  0         /*Use LIBCM for internal application*/
#define F_LIBCM_DIRECT_CM_ACCESS 0         /*Generate CM_DATA_xxx messages*/
#define F_LIBCM_WINDOWS_KERNEL   0         /*Use Windows Kernel CAPI Access*/
#define F_LIBCM_SYS_ACCESS       0         /*Use Windows Kernel NT-CAPI*/
#define F_LIBCM_VXD_ACCESS       0         /*Use Windows Kernel VXD-CAPI*/
#define F_EAPI                   0         /*Easy (open, close based) API to ISDN stack*/
#define F_SBSP_API               0         /*Simple Board Support Package API*/
#define F_SBSPDEMO               0         /*SBSP demo application*/
#define F_VMOD_DATAIF_CAPI       0         /*Data interface is CAPI (LIBCM)*/
#define F_VMOD_DATAIF_CAPI_WRAP  0         /*In case of CAPI (LIBCM) interface all DATAIFs wrapped together in one appl.*/
#define VMOD_NCCI_COUNT          0         /*NCCI Count per data initerface*/
#define VMOD_B3_DATA_BLOCKS_COUNT 0         /*Data B3 Block Count*/
#define VMOD_B3_DATA_SIZE_COUNT  0         /*Max Data B3 Bsize*/
#define F_VMOD_DATAIF_BT         0         /*Data interface is BlueTooth (BlueFace+)*/
#define F_VMOD_DATAIF_BLUE_API   0         /*Data interface is BlueAPI+*/
#define VMOD_DATAIF_BT_ALTERNATE_SERVICES_COUNT 0         /*number of alternate bt services provided by one bt data if*/
#define F_VMOD_BT_SCO            0         /*SCO-link support in VMOD-BT*/
#define F_VMOD_BT_SCO_CNTRL      0         /**/
#define F_VMOD_BT_RPN            0         /*remote port negotiation support in VMOD-BT*/
#define F_VMOD_DATAIF_TCP        0         /*Data interface is BlueTooth (BlueFace+)*/
#define F_VMOD_DATAIF_DEFAULT_PAR_BY_IDX 0         /*Param. defaults selectable by index (par. set nbr.)*/
#define F_VMOD_DATAIF_DTMF       0         /*Data interface use dtmf recog.*/
#define VMOD_DATAIF_CONNECTION_COUNT 0         /*Max Connections in Data interface*/
#define F_VMOD_DATAIF_DISCARD_NET_DATA 0         /*discard net data*/
#define F_HAYES_EXT              0         /*General Hayes extensions*/
#define F_HAYES_EXT_RVS          0         /*Hayes RVS-COM extensions*/
#define F_HAYES_EXT_USE_IOM      0         /*Hayes with special Commands for access IOM-Channel*/
#define F_HAYES_EXT_BT           0         /*Hayes with special Commands for Bluetooth*/
#define F_HAYES_EXT_HS           0         /*Hayes with special Commands for Headset control*/
#define F_HAYES_ALARM            0         /*Alarm extensions*/
#define F_HAYES_ONLINECMDMODE_KEEP_DI_DATA 0         /*save or dump of data in online command mode state*/
#define F_VMOD_X25_EXT           0         /*X.25 extensions*/
#define F_VMOD_ONLINE_REMOTE     0         /*escape Sequence to enter Remote while data conection from Net side*/
#define F_VMOD_UUS               0         /*UUS data*/
#define VMOD_LTECH_COUNT         0         /*lintech emulation command set count for vmod*/
#define VMOD_IDW_COUNT           0         /*special cmds for Westermo (mostly like hayes)*/
#define VMOD_HAYES_COUNT         0         /*hayes command set count for vmod*/
#define VMOD_AUTOCONN_COUNT      0         /*autoconnect command set count for vmod*/
#define F_VMOD_AUTOCONN_ECHO     0         /*echo data in command mode*/
#define VMOD_PAD_COUNT           0         /*pad command set count for vmod*/
#define VMOD_REMOTE_COUNT        0         /*Remote access via vmod*/
#define VMOD_ACDTR_IOM_COUNT     0         /*special cmds with autocall DTR, 2 DI and IOM*/
#define VMOD_ACIOM_COUNT         0         /*special cmds with autocall and IOM*/
#define VMOD_WTM_COUNT           0         /*special cmds with autocall and KWP 1281,2000 workaround*/
#define VMOD_DIGIIO_COUNT        0         /*special cmds for Westermo Alarm*/
#define VMOD_MODEM_IF_COUNT      0         /*Interface to Modem chip useing 16550*/
#define VMOD_DATAIF_COUNT        0         /*Number of data interfaces*/
#define VMOD_CMDIF_COUNT         0         /*Number of command interfaces*/
#define VMOD_LINKIF_COUNT        0         /*Number of link interfaces*/
#define VMOD_SERIAL_COUNT        0         /*Number of serial interfaces*/
#define F_VMOD_SERIAL_CONTROL_DTR 0         /*VMOD controls DTR settings*/
#define F_VMOD_SERIAL_CONTROL_FLC 0         /*VMOD controls FLC settings*/
#define F_VMOD_SERIAL_CONTROL_DBITS 0         /*VMOD controls DBITS settings*/
#define F_VMOD_SERIAL_CONTROL_SBITS 0         /*VMOD controls SBITS settings*/
#define F_VMOD_SERIAL_CONTROL_PRTY 0         /*VMOD controls PRTY settings*/
#define F_VMOD_SERIAL_CONTROL_DSR 0         /*VMOD controls DSR settings*/
#define F_VMOD_SERIAL_CONTROL_CTS 0         /*VMOD controls CTS settings*/
#define VMOD_RS366_COUNT         0         /*Number of RS366 interfaces*/
#define F_VMOD_SERIAL_ONE_DEF_PAR_SET 0         /*Only 1 common DEFAULT parameter set for ALL paramter sets*/
#define F_VMOD_DTR_SYS_RESET     0         /*feature to reset System by DTR drop*/
#define F_VMOD_DTR_DELAY         0         /*delayed DTR signal*/
#define F_VMOD_TRACE             0         /*VMOD trace (general)*/
#define F_VMOD_TCPIP             0         /*use PPPIP Interface*/
#define F_VMOD_DB                0         /*general VMOD DB Param*/
#define F_VMOD_BAUDRATE_460800_SUPPORT 0         /*enables the baudrate 460800 for parameter "br"*/
#define F_VMOD_BAUDRATE_921600_SUPPORT 0         /*enables the baudrate 921600 for parameter "br"*/
#define VMOD_CUSTOM_BAUDRATE_MIN_COUNT 0         /*min value of custom baudrate for "br" parameter*/
#define VMOD_CUSTOM_BAUDRATE_MAX_COUNT 0         /*min value of custom baudrate for "br" parameter*/
#define F_VMOD_FLC_XONXOFF_NOT_SUPPORTED 0         /*disable support of XonXoff flow control*/
#define F_VMOD_DIP_SWITCH        0         /*set some Parameter with DIP-Switches*/
#define F_VMOD_X31_REROUTE       0         /*reroute X31D to X25B on failure of X31D*/
#define F_VMOD_SMS               0         /*SMS functions*/
#define F_VMOD_ACCTAB            0         /*accesstable in VMOD*/
#define F_VMOD_UICP              0         /*UICP support in VMOD*/
#define F_VMOD_MUX               0         /*Mux support in VMOD*/
#define F_VMOD_NFC_HANDOVER      0         /*VMOD supports NFC Handover*/
#define VMOD_AUTODIAL_COUNT      0         /*VMOD supports auto dial*/
#define F_VMOD_HID               0         /*VMOD supports HID devices*/
#define F_BT_NDEF_LIB            0         /*Bleutooth NDEF Library*/
#define F_NFC_DYNAMIC_TAG_DRIVER 0         /*NFC dynamic TAG driver*/
#define F_ATMUX                  0         /*AT-Multiplexer (GSM 07.10)*/
#define F_ATMUX_MSC              0         /*AT-Multiplexer supports Modem Status Command.*/
#define F_ATMUX_MSC_FC           0         /*AT-Multiplexer supports flow control using MSC*/
#define F_MTC20285_DRIVER        0         /*MTC20285 is an advanced MTC20280*/
#define F_CCIF_DIRECT_CM_ACCESS  0         /*not via API or LIBCM*/
#define F_CCIF_D3_ADMIN_NT_BCHANNEL 0         /*d-channel layer 3 administrates nt side b-channels*/
#define F_CCIF_START_APPLIC      0         /*CCIF starts assoc. applic.*/
#define F_CCIF_APP_TERM_CONN     0         /*applic. may terminate connection*/
#define F_CCIF_MULTIPLE_CAPI     0         /*CCIF uses more than 1 CAPI*/
#define F_CCIF_DELAY_CONN        0         /*application may delay propagation of connect message*/
#define F_CCIF_CAPI_B3_CONN      0         /*CCIF uses B3/NCCI msgs*/
#define F_CCIF_CAPI_DATA_TO_APP  0         /*CCIF passes/rcvs B-channel data to/from applic.*/
#define F_CCIF_BCHNL_NBR_IND     0         /*CCIF B-chnl nbr. indication supported*/
#define CCIF_TRC_COUNT           0         /*internal trace of CCIF*/
#define CCIF_MAX_B3_CONNECTIONS_COUNT 0         /*max. # of B3 connections supported by CCIF*/
#define CCIF_MAX_B3_DATA_BLOCKS_COUNT 0         /*DATA_B3_REQ/IND window size*/
#define CCIF_MAX_DATA_BYTE_COUNT 0         /*max. packet size in DATA_B3_REQ/IND*/
#define F_AT91_AIC_DISABLE_INT   0         /*enhanced interrupt controller support*/
#define F_AT91M40400             0         /*Type of Controller*/
#define F_TMS320BIOS             0         /*TMS320DSP/BIOS*/
#define F_ASYNC_NO_RING_BUFFER   0         /*L1ASYNC without circular buffer*/
#define ASYNC_EXT_RING_BUFFER_COUNT 0         /*External circular buffer (number of UARTs)*/
#define F_ASYNC_SMALL_RING_BUFFER 0         /*Use small circular buffer*/
#define F_ASYNC_USE_DEFERRED_QUEUE 0         /*ASYNC module uses deferred Queue for TX*/
#define ASYNC_RX_BUFFER_USE_COUNT 0         /*Max.number of rx buffers used by L1ASYNC*/
#define ASYNC_MAX_RX_BUFFER_HIGH_WATER_COUNT 0         /*Max. value for 'RxBufferHighWater'*/
#define ASYNC_RX_BUFFER_COUNT_FOR_RX_DISABLE_COUNT 0         /*disable RX if this count of free buffers reached*/
#define ASYNC_RX_BUFFER_COUNT_FOR_RX_REENABLE_COUNT 0         /*reenable RX if this count of free buffers available*/
#define F_ASYNC_BUFFER_CALLBACK  0         /*ASYNC module use buffer callbacks*/
#define F_ASYNC_MORE_DATA_SUPPORTED 0         /*ASYNC with more data bit*/
#define F_ASYNC_TRACE            0         /*ASYNC trace*/
#define F_ASYNC_DB               0         /*ASYNC with DB parameter*/
#define F_ASYNC_BREAK_SIGNAL_SUPPORTED 0         /*ASYNC break signal*/
#define F_ASYNC_XON_XOFF_SUPPORTED 0         /*ASYNC XON/XOFF*/
#define F_ASYNC_POWER_MANAGEMENT 0         /*ASYNC with power management*/
#define F_ASYNC_BCP              0         /*ASYNC BlueClusterProtocol*/
#define F_ASYNC_MESHSR           0         /*ASYNC MeshSR packet*/
#define F_ASYNC_EHCILL           0         /*TI enhanced HCILL*/
#define F_ASYNC_UICP             0         /*UART Interface Control Protocol*/
#define F_ASYNC_INTERFACE_UP_DOWN 0         /*ASYNC supports interface up/down*/
#define F_ASYNC_H4DS             0         /**/
#define F_ASYNC_CUSTOM_BAUDRATE_SUPPORT 0         /*ASYNC supports custom baudrate. Upper layer application are responsible for validation of baudrate value*/
#define ASYNC_I2C_DEVICE_COUNT   0         /*ASYNC number of I2C devices*/
#define F_L1_ISDN_INTEGRATED     0         /*L1HDLC without L1_ISDN (HFCS, ...)*/
#define F_L1_SWITCH_DATA_PATH    0         /*L1HDLC handles SWITCH_DATA_PATH msg*/
#define F_L1_CODE_WAIT           0         /*L1 executes code that may wait/sleep (e.g. 2nd party chip driver)*/
#define F_L1_IRQ_STATUS_ONLY     0         /*L1/L0 IRQ handler only reads interrupt status registers*/
#define F_ASC0_ASYNC             0         /*ASC0 uses L1ASYNC module*/
#define F_ASC0_ASYNC_TRACE       0         /*ASC0 trace*/
#define F_16550_ASYNC            0         /*16550 uses L1ASYNC module*/
#define F_16550_BUS_BYTE         0         /*8 bit bus*/
#define F_16550_BUS_WORD         0         /*16 bit bus*/
#define F_16550_BUS_DWORD        0         /*32 bit bus*/
#define F_16550_RS485            0         /*use of RS485 driver*/
#define F_CNX_ASYNC              0         /**/
#define F_CNX_16550_BUS_BYTE     0         /*8 bit bus*/
#define F_CNX_16550_BUS_WORD     0         /*16 bit bus*/
#define F_CNX_16550_BUS_DWORD    0         /*32 bit bus*/
#define F_HFCS_HDLC              0         /*HFCS uses L1HDLC modul*/
#define DTCI_MAX_CLIENTS_COUNT   0         /*Max. simultaneous Clients*/
#define F_TCPIP                  0         /*TCPIP Protokols*/
#define F_PPPIP                  0         /*use Module PPPIP*/
#define F_AB_PROG_CLASS_ENA      0         /*CLIP enable*/
#define F_AB_PROG_CLASS_TYPE     0         /*CLIP protocol*/
#define F_AB_GLOBAL_CALL         0         /*global call (Austria only)*/
#define F_AB_PLUG_CHANGE         0         /*plug change (clear back time)*/
#define F_AB_WAKEUP_CALLS        0         /*wakeup calls*/
#define F_AB_WAKEUP_RING_TIME    0         /*ring time after wakeup*/
#define F_AB_CUG                 0         /*closed user group*/
#define F_AB_CHARGES_TO_NVRAM    0         /*store charges*/
#define F_AB_HOTLINE_CALL        0         /*hotline call number*/
#define F_AB_HOTLINE_CALL_ENABLE 0         /*hotline call enable*/
#define F_AB_HOTLINE_CALL_TIME   0         /*delay time for hotline call*/
#define F_AB_HOTLINE_WITH_SUBADDRESS 0         /*hotline calls with subaddress*/
#define F_AB_CALL_BUMPING        0         /*necessary ?*/
#define F_AB_CALL_BARRING        0         /*call barring*/
#define F_AB_SUBADDRESSING       0         /*subaddressing*/
#define F_AB_PERMANENT_CLIR      0         /*CLIR for all outgoing calls*/
#define F_AB_CALL_PICKUP         0         /*pickup call from other port*/
#define F_AB_DIFFERENT_RING      0         /*MSN specific ring*/
#define F_AB_PROGRAM_RING_SEQ    0         /*cadence selection for DIFFERENT_RING*/
#define F_AB_KEYPAD_FUNC         0         /*suppl. services keypad/functional*/
#define F_AB_PERMANENT_COLR      0         /*COLR for all incoming callsl*/
#define F_AB_PROG_CONN_SWITCH    0         /*ISDN switch type*/
#define F_AB_DTMF_PROG_LEVEL     0         /*what shall I say ?*/
#define F_AB_HANDLE_EMERGENCY    0         /*handling of restricted power*/
#define F_AB_BLIND_RECALL        0         /*recall of last caller*/
#define F_AB_DISABLE_PULSE_DIALLING 0         /*DTMF dialling only*/
#define F_AB_PORT_DISABLE        0         /*Ports can be disabled for in. or out. calls.*/
#define F_BT_OBEX                0         /*Object exchange protocol (experimentally)*/
#define F_BT_RFCOMM              1         /*RFCOMM protocol TS 07.10*/
#define F_BT_SCO                 0         /*Synchronous Connection-Oriented  (experimentally)*/
#define F_BT_SCO_HCI             0         /*SCO over HCI support*/
#define F_BT_SDP                 1         /*Service Discovery Protocol*/
#define F_BT_SDP_CLIENT          1         /*SDP client*/
#define F_BT_SDP_SERVER          1         /*SDP server*/
#define F_BT_TCSBIN              0         /*Telephony Control Protocol  (experimentally)*/
#define F_BT_TCI                 0         /*Test Control Interface*/
#define F_BT_HCRP_CLIENT         0         /*Hardcopy Cable Replacement Protocol Client*/
#define F_BT_HCRP_SERVER         0         /*Hardcopy Cable Replacement Protocol Server*/
#define F_BT_BNEP                0         /*Bluetooth Network Encapsulation Protocol*/
#define F_BT_AVDTP               0         /*Audio Video Distribution Transport Protocol*/
#define F_BT_CMTP                0         /*CAPI profile*/
#define F_BT_HEADSET             0         /*Headset Profile*/
#define F_BT_SECMAN              1         /*Security Manager*/
#define F_BT_GATT                1         /*Generic Attribute Protocol*/
#define F_BT_GATT_CLIENT         1         /*GATT client role*/
#define F_BT_GATT_SERVER_MIN     1         /*GATT server role (minimal functionality, GAP+GATT only)*/
#define F_BT_GATT_SERVER         1         /*GATT server role (full functionality)*/
#define F_BT_GATT_LE_ONLY        0         /*GATT over LE only*/
#define F_BT_GATT_SVC_DIS        1         /*support for built-in GATT DIS service*/
#define F_BT_GATT_SVC_DIS_PNP_ID 1         /*GATT DIS service includes PnP ID*/
#define F_BT_GATT_SVC_GLS        0         /*support for built-in GATT GLS service*/
#define F_BT_GATT_SVC_CTS        0         /*support for built-in GATT CTS service*/
#define F_BT_GATT_SVC_NDCS       0         /*support for built-in GATT NDCS service*/
#define F_BT_GATT_SVC_RTUS       0         /*support for built-in GATT RTUS service*/
#define F_BT_GATT_SVC_BAS        1         /*support for built-in GATT BAS service*/
#define F_BT_GATT_SVC_HRS        0         /*support for built-in GATT HRS service*/
#define F_BT_GATT_SVC_BLS        0         /*support for built-in GATT BLS service*/
#define F_BT_GATT_CONFORMANCE    0         /*GATT conformance tests*/
#define F_BT_UPL_L2CAP           1         /*Blueface Access to L2CAP*/
#define BT_MAX_APP_COUNT         1        /*Max. number of applications (default 4)*/
#define BT_MAX_LINK_COUNT        7        /*Max. number of links (default 4)*/
#define BT_RFCOMM_MAX_CHANNELS_COUNT 14       /*Maximum nbr of concurrent channels (consider Control channel)*/
#define BT_RFCOMM_CREDIT_COUNT   4        /*Credits for flow control*/
#define BT_RFCOMM_MTU_COUNT      330      /*Max Packet Size (if 0 derived from BT_xx_MTU_L2C_BYTE_COUNT)*/
#define F_BT_RFCOMM_EXPSERV_SUPPORTED 0         /*RFCOMM supports expedited services*/
#define F_BT_RFCOMM_CONFORMANCE  0         /*RFCOMM Protocol conformance test*/
#define BT_SDP_MAX_CHANNELS_COUNT 2        /*Maximun nbr of concurrent channels*/
#define BT_SDP_SERVER_MAX_SERVICES_COUNT 10       /*Maximum nbr of Service Record entries in database*/
#define BT_SDP_SERVER_BUFFER_BYTE_COUNT 0         /*size of Buffer used to build a response (on Stack)*/
#define BT_SDP_CLIENT_BUFFER_BYTE_COUNT 450      /*size of buffer to assemble segmented response*/
#define BT_SDP_CLIENT_BUFFER_COUNT 1        /*count for Buffer to assamble fragmeted response*/
#define F_BT_SDP_FW_VERSION      0         /*Added FW version in SDP database main record*/
#define F_BT_ATT_PREP_EXEC_WRITE 0         /*ATT Prepare/Execute Write support*/
#define BT_ATT_MTU_SIZE_LE_COUNT 23       /*Max. MTU size used on LE links*/
#define BT_GATT_MAX_CHANNELS_COUNT 3        /*Maximum nbr of concurent ATT bearer*/
#define BT_GATT_APPEARANCE_COUNT 0x03C1     /*GATT appearance value*/
#define F_BT_GATT_SERVICE_CHANGED 1         /*GATT service changed attribute supported*/
#define BT_GATT_SERVER_MAX_SERVICES_COUNT 8        /*Maximum nbr of registered services*/
#define BT_GATT_SERVER_MAX_CCC_BITS_COUNT 8        /*Maximum nbr of configured CCC bits*/
#define BT_GATT_US_WRITE_OFFSET_COUNT 48       /*Offset used in upstream messages*/
#define BT_GATT_DS_WRITE_OFFSET_COUNT 32       /*Obsolete, not used any longer*/
#define BT_GATT_DS_WSIZE_COUNT   16       /*Window size usable in notifications and write commands*/
#define BT_L2CAP_MAX_CHANNELS_COUNT 7        /*Maximum nbr of concurrent channels*/
#define BT_L2CAP_MAX_ENHANCED_FEATURE_CHANNELS_COUNT 7        /*Maximum nbr of concurrent channel for enhanced feature*/
#define F_BT_UPFL2C              0         /*UnPlugFest test for L2CAP  (experimentally)*/
#define F_BT_L2C_PING_SUPPORT    0         /*support of upper IF PING Request*/
#define F_BT_L2C_QOS_SUPPORT     0         /*support of QualityOfService Parameters*/
#define BT_L2C_MAX_CMD_RETRIES_COUNT 0         /*Max. Nbr of comand retries (if 0 reduced RAM and ROM size)*/
#define BT_L2C_MAX_PSM_COUNT     8        /*Max. Nbr of concurrent registered PSMs (upper layer queues)*/
#define F_BT_L2C_NO_DS_SEGMENTATION 1         /*Downstream Segmentation not supported (L2C DS MTU + 4 <= hci buffer size)*/
#define F_BT_L2C_LE_DS_FRAGMENTATION 0         /*Downstream Fragmentation supported*/
#define F_BT_L2C_EXT_FEATURE_SUPPORT 0         /*Not used - L2CAP extended feature*/
#define F_BT_L2C_ENHANCED_FEATURE_SUPPORT 1         /*L2CAP enhanced feature support*/
#define F_BT_L2C_ENHANCED_RETRANSMISSION_SUPPORT 1         /*Not used - L2CAP enhanced retransmission support*/
#define F_BT_L2C_STREAMING_MODE_SUPPORT 1         /*Not used - L2CAP enhanced streeming mode support*/
#define BT_L2C_WINDOW_SIZE_COUNT 1        /*eRTM Window Size*/
#define BT_L2C_MAX_RX_IFRAME_COUNT 0         /*Max. I frames send to upper layer*/
#define BT_L2C_MAX_RX_BUFFER_COUNT 0         /*Streaming Max. nbr of RxBuffer send to upper layer*/
#define F_BT_L2C_ENHANCED_CONFORMANCE 0         /*L2CAP enhanced conformation*/
#define BT_AVDTP_MAX_CHANNELS_COUNT 0         /*Max. nbr of concurrent channels (default 4)*/
#define BT_AVDTP_MAX_SEP_COUNT   0         /*Max. number of stream endpoints (default 2)*/
#define BT_AVDTP_SIGNALLING_BUFFER_SIZE_COUNT 0         /*Max. length of signalling (default L2CAP MTU)*/
#define F_BT_AVDTP_MULTIPLEXING_MODE 0         /*AVDTP multiplexing mode*/
#define F_BT_AVDTP_REPORTING     0         /*AVDTP reporting service*/
#define F_BT_AVDTP_RECOVERY      0         /*AVDTP recovery service*/
#define F_BT_HCI_DEVICE_NOT_VISIBLE 1         /*control of bluetooth device visibility after startup*/
#define BT_HCI_FIXED_PACKET_TYPES_COUNT 0         /*allowed packettypes the LLS may use, 0=HCI uses value depending on framesizes, see hci_code.h or HCI spec for values*/
#define F_BT_SNIFF               1         /*HCI supports SNIFF mode*/
#define F_BT_HCI_PAGE_SCAN_CONF  1         /*HCI supports page scan activity configuration*/
#define BT_HCI_PAGE_TIMEOUT_DEFAULT_COUNT 0         /*HCI default page timeout (0x2000 if undefined)*/
#define F_BT_HCI_INQUIRY_SCAN_CONF 0         /*HCI supports inquiry scan activity configuration*/
#define F_BT_HCI_RADIO_STATUS_CONF 1         /*HCI controls and handles radio status events*/
#define F_BT_HCI_HOST_FLOW_CAPABILITY 1         /*HCI host flow capability*/
#define F_BT_HCI_ENHANCED_SYNCRONOUS_CAPABILITY 0         /*HCI uses the 1.2 commands SYNCHRONOUS_CONNECTIONS instead of depreciated SCO cmds*/
#define F_BT_HCI_NON_HCI_LOCAL_NAME 0         /*HCI uses vendor specific command to set the local device name instead of the standard HCI_SET_LOCAL_NAME command*/
#define F_BT_HCI_WATCHDOG        0         /*Watchdog traffic on HCI interface*/
#define BT_HCI_INQIURY_RESULT_LOWWATER_COUNT 3        /*Low Watermark for deviceInq results from system pool*/
#define F_BT_HCI_BLUECLUSTER_FILTER 0         /*filters Bluecluster devices out of inquiry results*/
#define F_BT_HCI_POWERSWITCH     0         /*HCI has powerswitch / levelshifters*/
#define F_BT_HCI_CHECK_FOR_INFOPAGES 0         /*HCI requires both infopages to be present*/
#define F_BT_HCI_LLAPI           1         /*HCI uses Low Layer API*/
#define F_BT_HCI_COMAPI          1         /*Low Layer API is COMAPI*/
#define F_BT_L1_V24              0         /*Layer 1 is V.24*/
#define F_BT_L1_USB              0         /*Layer 1 is USB*/
#define F_BT_L1_LLS              0         /*direct on LowerLayerStack*/
#define F_BT_L1_INTELLIGENT      0         /*Layer 1 knows HCI packet structures*/
#define F_BT_L1_DUMB             0         /*Layer 1 does not know HCI packet structures*/
#define F_BT_QDATA_SUPPORTED     0         /*prioritized ACL data support*/
#define F_BT_HCI_SKIP_HCI_RESET  0         /*Skip HCI_RESET command after HW reset during startup*/
#define F_BT_HCI_SKIP_ALL_EVENTS_WHILE_HCI_RESET_COMPLETE 0         /*Skip all hci data while HCI_RESET_COMPLETE*/
#define F_BT_HCI_TRACE           0         /*HCI trace (hci_util.c)*/
#define F_BT_BB_BROADCOM         0         /*HCI knows Broadcom BB*/
#define F_BT_BB_CSR              0         /*HCI knows CSR BB*/
#define F_BT_BB_INFINEON         0         /*HCI knows Infineon BB*/
#define F_BT_BB_ST               0         /*HCI knows STMicroElectronics BB*/
#define F_BT_BB_TI               0         /*HCI knows Texas Instruments BB*/
#define F_BT_BB_CSR_ROM_FIRMWARE 0         /*use baudrate detection and load patches and pskeys*/
#define F_BT_BB_CSR_ROM_FIRMWARE_BOOTPINS 0         /*use bootpins to select HCI protocol (H4/H4DS)*/
#define F_BT_HCI_CSR_ROM_FIRMWARE_AUTOBAUD 0         /*use BCSP sync message*/
#define F_BT_HCI_CSR_ROM_FIRMWARE_FIX_EDR_BITS_IN_POWER_TABLE 0         /*set EDR control bits on three upper levels of tx power table*/
#define BT_HCI_CSR_MAX_ACL_PKTS_COUNT 0         /*maximum number of HCI ACL data packets being sent to air that can be held within the chip at any time*/
#define BT_HCI_CSR_MAX_ACL_PKT_LEN_COUNT 0         /*max length of data portion of HCI ACL data packets received from the host*/
#define F_BT_HCI_CSR_PATCH_8811A08_DSP_REV8 0         /*DSP patch dedicated for CSR8811 A08*/
#define F_BT_BB_TI_CC2560        0         /*CC2560 supported*/
#define F_BT_BB_TI_CC2560B       0         /*CC2560B supported*/
#define F_BT_BB_TI_CC2564        0         /*CC2564 supported*/
#define F_BT_BB_TI_CC2564B       0         /*CC2564B supported*/
#define F_BT_BB_TI_BRF6350       0         /*BRF6350 supported*/
#define F_BT_BB_TI_BL6450        0         /*BL6450 supported*/
#define F_BT_HCI_TI_EHCILL       0         /*HCI support TI EHCILL*/
#define F_BT4_0                  1         /*support V4.0*/
#define F_BT2_1                  1         /*support V2.1*/
#define F_BT1_2                  1         /*support V1.2*/
#define F_BT_LOW_ENERGY          1         /*support BT Low Energy*/
#define F_BT_LE_CENTRAL          1         /*support BLE Central Role*/
#define F_BT_LE_PERIPHERAL       1         /*support BLE Peripheral Role*/
#define F_BT_LE_PRIVACY_MODE     0         /*support BLE Privacy Mode (random resolvable address)*/
#define F_BT_LE_PRIVACY_RESOLVING 1         /*support BLE Random Resolvable Address Resolution*/
#define F_BT_LE_DATA_SIGNING     0         /*support BLE data signing*/
#define F_BT_USE_OSIF_IF         1         /*use message interface for blueface (instead of callback)*/
#define F_BT_DYNAMIC             1         /*allow stack configuration during runtime init (buffer size/count, link count, mtu size, etc.)*/
#define BT_MAX_ACL_CONNECTION_COUNT 7        /*Maximun Nbr of concurrent ACL connections (HCI + L2CAP)*/
#define BT_MAX_SCO_CONNECTION_COUNT 0        /*Maximun Nbr of concurrent SCO connections (HCI)*/
#define BT_DS_BUFFER_COUNT       32       /*Downstream buffer count*/
#define BT_RFCOMM_DS_BUFFER_COUNT 0         /*Buffer count for RFCOMM (DS)*/
#define BT_L2CAP_DS_BUFFER_COUNT 1        /*Buffer count for L2CAP (DS)*/
#define BT_US_BUFFER_COUNT       32       /*Upstream buffer count*/
#define BT_SCO_BUFFER_COUNT      0         /*Buffer count for SCO (US and DS)*/
#define BT_DS_MTU_L2C_BYTE_COUNT 65535     /*L2CAP DS MTU size*/
#define BT_US_MTU_L2C_BYTE_COUNT 65535     /*L2CAP US MTU size*/
#define BT_DS_PDU_L2C_BYTE_COUNT 335      /*L2CAP DS PDU size*/
#define BT_US_PDU_L2C_BYTE_COUNT 335      /*L2CAP US PDU size*/
#define BT_DS_UPFL2C_MTU_L2C_BYTE_COUNT 0         /*L2CAP MTU size (UnPlugFest)*/
#define BT_US_WRITE_OFFSET_COUNT 32       /*initial writeOffset for upstream data*/
#define BT_DS_WRITE_OFFSET_COUNT 32       /*initial writeOffset for downstream data*/
#define BT_SYS_SHORT_BUFFER_BYTE_COUNT 72       /*Short buffer size*/
#define BT_SYS_SHORT_BUFFER_COUNT 40       /*Short buffer count*/
#define BT_SYS_MIDDLE_BUFFER_BYTE_COUNT 283      /*Middle buffer size*/
#define BT_SYS_MIDDLE_BUFFER_COUNT 6        /*Middle buffer count*/
#define BT_SYS_LONG_BUFFER_BYTE_COUNT 512      /*Long buffer size*/
#define BT_SYS_LONG_BUFFER_COUNT 2        /*Long buffer count*/
#define F_BT_LOGGING             0         /*Enable / Disable Logging of BlueFace and PDU*/
#define F_BT_FLOWTRACE_2_TRACEMODULE 1         /*send flow trace output to trace Module (count TRACE)*/
#define BT_VERBOSITY_COUNT       1        /*verbosity level for trace output*/
#define F_TRACE_BACKGROUND       0         /*Print debug messages in background*/
#define TRACE_BACKGROUND_UART_ID_COUNT 0         /*Print debug messages over UART*/
#define F_BT_APP_POOL            0         /*Create pool for BT application*/
#define F_BTDB                   0         /*use BTDB module*/
#define DB_BT_MAX_KEY_COUNT      0         /*size of access rights table*/
#define F_BT_DBGUI               0         /*GUI for BT Database (Enquiry button, LED, ....)*/
#define DB_BT_PIN_SIZE_COUNT     0         /*PIN size for BT PIN/Key*/
#define F_DB_BT_PIN_ALPHA_NUMERIC 0         /*pin can contain alpha numeric chars*/
#define BT_SECURITY_SUPPORT_LEVEL_COUNT 0         /*levels of security (2=old, 3=new)*/
#define F_DB_BT_DIRECT_HCI_ACCESS 0         /*includes bhcidirect command*/
#define F_DB_BT_USER_INPUT       0         /*includes user PIN support*/
#define F_DB_BT_BDRAD            0         /*database parameter/command for remote server channel*/
#define F_DB_BT_BDINQ            0         /*database parameter/command for inquiry*/
#define F_DB_BT_CLASS            0         /*database parameter/command for class*/
#define F_DB_BT_PROFILE          0         /*database parameter/command for profile*/
#define DB_BT_BD_LIST_COUNT      0         /*database parameter/max. BD for inquiry*/
#define BT_SECMAN_POLICY_COUNT   5        /*maximum number of policies*/
#define F_BT_SECMAN_STATUS_UPDATES 1         /*generate security related status messages*/
#define F_BTSEC                  0         /*use BT-Secure modul*/
#define F_BTSEC_INQUIRY          0         /*BT-Secure handels inquiring*/
#define F_BTSEC_INQUIRY_UUID128_SUPPORT 0         /*Btsec supportes full size 128 bit UUIDs for service discovery*/
#define F_BTSEC_INQUIRY_COLLECT_DEVICE_INFO 0         /*Btsec collects all accessable device information from remote devices*/
#define BTSEC_INQUIRY_CLASS_MASK_COUNT 0         /*count for inquiry filter for each btsec client*/
#define F_BTSEC_INQUIRY_NO_DATABASE 0         /*no support for internal storage of Inquiry and service discovery results*/
#define F_BTSEC_INQUIRY_APP_REASSEMBLY_SUPPORT 0         /*support for SDP Attribute reassembly in application*/
#define F_BTSEC_SECURITY         0         /*BT-Secure handles security*/
#define F_BTSEC_SECURITY_TRUSTED_DEVICE_SUPPORT 0         /*BT-Secure supports specific security settings for known remode devices*/
#define F_BTSEC_SECURITY_USER_INPUT 0         /*BT-Secure handles user input (PIN)*/
#define BTSEC_SERVICE_RAW_DATA_SIZE_COUNT 0         /*BT-Secure max size of raw sdp data*/
#define BTSEC_SERVICE_UUID_SUPPORT_LIST_FLAGS_COUNT 0         /*BT-Secure flags for supported UUIDs ( 0 => support all )*/
#define BTSEC_SERVICE_UUID_SUPPORT_LIST_SIZE_COUNT 0         /*BT-Secure size for UUID support list, if not defined or zero, list sizes are set to default 30*/
#define BTSEC_SERVICE_HANDLE_SUPPORT_LIST_SIZE_COUNT 0         /*BT-Secure size for service handle support list, if not defined or zero, list sizes are set to default 20*/
#define F_BTSEC_QOS_SUPPORT      0         /*BT-Secure supports quality of service handling*/
#define BTSOS_CLIENT_POOL_ELEMENT_COUNT 0         /*Size of client pool*/
#define BTSOS_DEVICE_POOL_ELEMENT_COUNT 0         /*Size of device pool for inquiry results*/
#define BTSOS_SERVICE_POOL_ELEMENT_COUNT 0         /*Size of service pool for inquiry results*/
#define BTSOS_BOND_POOL_ELEMENT_COUNT 0         /*Size for bond pool for bonding results*/
#define BTSOS_CONTEXT_POOL_ELEMENT_COUNT 0         /*Size for App context pool*/
#define BTSOS_MESSAGE_POOL_ELEMENT_COUNT 0         /*Size for System message pool*/
#define BTSOS_TRUSTED_DEVICE_POOL_ELEMENT_COUNT 0         /*Size for trusted devices for security settings*/
#define BTSOS_QOS_POOL_ELEMENT_COUNT 0         /*Size of QoS entry pool*/
#define BTSOS_ATTRIBUTE_DATA_SIZE_COUNT 0         /*size for attribut data that can be requested by an app from a remote service*/
#define F_BTSOS_NO_DATABASE_SUPPORT 0         /*avoid database usage in BTSOS*/
#define F_BTSOS_NO_USER_COMMANDS 0         /*disable all user comands, parameter only*/
#define F_BTSOS_BOND_TABLE_NO_OVERWRITE 0         /*do not overwrite 'oldes' bond table entry with new bond table entry if bond table is full*/
#define F_BTSOS_ACT_INFO_SUPPORT 0         /*BTSOS generates an message to indicate that the initial stack konfiguration is done*/
#define F_BTSOS_SAVE_INQUIRY_TO_DB 0         /*save inquiry results in NV-RAM using BD module*/
#define F_BTSOS_EXTERNAL_NVRAM_SUPPORT 0         /*add functions to support target specific NVRAM read/write functions without DB*/
#define F_BTSOS_EXTENSIONS       0         /*add extension module for aditional BT parameter/commands*/
#define F_BTEXT_DIRECT_HCI_ACCESS 0         /*bhcidirect command*/
#define F_BTEXT_HCI_TUNNEL_REQ   0         /*bhcitunnelreq/bhcitunnelind commands*/
#define F_BTEXT_BTDB_COMMANDS    0         /*emulates BTDB commands*/
#define F_BTEXT_RF_MAX_TX_PWR    0         /*max transmitter power*/
#define F_BTEXT_TEMPERATURE_COMPENSATION 0         /*starts temeratur compensation*/
#define F_BTEXT_HCI_DIRECT       0         /*hci direct access on dual chip system (eg. uController + BB ROM based)*/
#define F_BTEXT_HCI_BEDUTM       0         /*hci command - device enable under test mode*/
#define F_BTEXT_READ_CLOCK       0         /*read baseband clocks*/
#define F_BLUE_API               1         /*MDP included in FW*/
#define F_BLUE_API_INQURTY_SUPPORT 1         /*support for BT Inquiry commands*/
#define F_BLUE_API_RECONNECT_SUPPORT 0         /*support for MCAP reconnect*/
#define F_BLUE_API_HDP_SUPPORT   0         /*support for HDP/MCAP connections*/
#define F_BLUE_API_SPP_SUPPORT   1         /*support for SPP/RFCOMM connections*/
#define F_BLUE_API_GATT_SUPPORT  1         /*support for GATT*/
#define F_BLUE_API_GATT_SDP_DIS_SUPPORT 0         /*support for discovery of GATT services via SDP*/
#define F_BLUE_API_DIS_SUPPORT   1         /*Support for Device Information Service (DIS)*/
#define F_BLUE_API_BAS_SUPPORT   1         /*Support for Battery Service (BAS)*/
#define F_BLUE_API_OBEX_SUPPORT  0         /*support for OBEX based profiles*/
#define F_BLUE_API_L2CAP_SUPPORT 0         /*support for L2CAP connections*/
#define F_BLUE_API_HID_SUPPORT   1         /*Support for HID connections*/
#define F_BLUE_API_HOGP_SUPPORT  1         /*Support for HID over GATT profile*/
#define F_BLUE_API_TIO_SUPPORT   1         /*Support for Terminal I/O profile*/
#define F_BLUE_API_HCI_TUNNEL_SUPPORT 0         /*hci tunnel req/ind supported*/
#define BLUE_API_LOCAL_DEVICE_NAME_COUNT 248      /*Max. length of local device name*/
#define BLUE_API_SPP_ENDPOINT_COUNT 8        /*number of supported SPP endpoints*/
#define BLUE_API_MCL_COUNT       8        /*number of MCL ACL connections*/
#define BLUE_API_MDL_COUNT       10       /*number of MDL data channels*/
#define BLUE_API_MDEP_COUNT      10       /*number of MDEP data endpoints*/
#define BLUE_API_MCL_DATA_LINK_COUNT 2        /*maximum number of data links per MCL*/
#define BLUE_API_DATASTORE_PEER_COUNT 0         /*maximum number of peers in datastore*/
#define BLUE_API_DATASTORE_SMALL_ENTRY_COUNT 0         /*maximum number of small entries in datastore (GATT CCC bits)*/
#define BLUE_API_DATASTORE_LARGE_ENTRY_COUNT 0         /*maximum number of large entries in datastore (BR/LE linkkeys)*/
#define BLUE_API_TIO_CLIENT_COUNT 3        /*maximum number TIO clients*/
#define F_BLUE_API_EXTERNAL_NVRAM_SUPPORT 1         /*direct access of NVRAM*/
#define BLUE_API_HID_USB_DESCRIPTOR_LENGTH_COUNT 96       /*maximum length of HID USB descriptor*/
#define F_BTLTP                  0         /*LTP App included to access BLUE_API*/
#define F_LTPLIB                 0         /*LTP library is used in project*/
#define F_LTPLIB_MDH_SUPPORT     0         /*LTP library includes MDH utility functions*/
#define F_LTPLIB_MDC_SUPPORT     0         /*LTP library includes MDC utility functions*/
#define F_LTPLIB_ASYNC_ASSEMBLY_SUPPORT 0         /*LTP library includes asynchronous LTP_RESET_REQ detection*/
#define F_LTPLIB_STANDALONE_SUPPORT 0         /*Set to 1 to include internal queue*/
#define F_BLUEBSP                0         /*Bluetooth Board Support package*/
#define F_HDPDEMO                0         /*HDP demo app included to access BLUE_API*/
#define F_SPPDEMO                0         /*SPP demo app*/
#define F_GATTDEMO               0         /*GATT demo application*/
#define F_HIDDEMO                0         /*HID demo application*/
#define F_MESHSR                 0         /*MeshSR Support*/
#define MESHSR_APP_BUFFER_COUNT  0         /*MeshSR Number of application buffers*/
#define F_MESHSRDEMO             0         /*MeshSR Demo uses BlueBSP*/
#define F_CMTP_AP_SUPPORT        0         /*Support for AP part of profile*/
#define F_CMTP_IC_SUPPORT        0         /*Support for IC part of profile*/
#define BTHSP_FOUND_DEVICES_POOL_ELEMENT_COUNT 0         /*size of pool for storing inquiry result*/
#define BT_PAIRED_DEVICES_COUNT  0         /*no of concurrent paired devices supported*/
#define F_BT_AGW                 0         /*AGW support enabled*/
#define F_BT_HANDSFREE           0         /*HANDSFREE support enabled*/
#define F_BT_REMOTE_VOLUME       0         /*remote vol control enabled*/
#define F_BT_PUSH_TO_TALK_SUPPORT 0         /*push to talk support enabled*/
#define F_BT_CMD                 0         /*bluetooth command interface application*/
#define F_BT_HID                 0         /*use BT_HID module*/
#define F_BT_HID_HID             0         /*Role HID device*/
#define F_BT_HID_HOST            0         /*Role host*/
#define F_BT_HID_OVER_SPP        0         /*Transport keyboard data over serial port profile*/
#define BT_HID_HOST_DEVICE_COUNT 0         /*Number of devices that can connect to this host*/
#define F_BTHST                  0         /*BT HID host application*/
#define F_BTKBD                  0         /*use Bluetooth HID seriall app (keyboard mouse joystick...)*/
#define F_BTKBD_KEYBOARD         0         /*i am a keyboard*/
#define F_BTKBD_KEYBOARD_MICROSOFT 0         /*Use Microsoft keyboard scancodes*/
#define F_BTKBD_KEYBOARD_INTELLI_OFFICE 0         /*Use "Intelli Office" keyboard scancodes*/
#define F_BTKBD_KEYBOARD_STM     0         /*Use STM reference design keyboard controller*/
#define F_BTKBD_MOUSE            0         /*i am a mouse*/
#define F_BT_HS_UI               0         /*User interface*/
#define F_BT_MPA                 0         /*Multi profile API exists*/
#define F_BT_MPA_SDAP            0         /*MPA supports the service discovery application profile*/
#define F_BT_MPA_SPP             0         /*MPA supports the serial port profile*/
#define F_BT_MPA_HFP_UNIT        0         /*MPA supports the hands free profile role unit*/
#define F_BT_MPA_HFP_AG          0         /*MPA supports the hands free profile role audio gateway*/
#define F_BT_MPA_HSP             0         /*MPA supports the headset profile*/
#define F_BT_MPA_OPP             0         /*MPA supports the object push profile*/
#define F_BT_MPA_SYNCP           0         /*MPA supports the synchronization profile*/
#define F_BT_MPA_A2DP_SOURCE     0         /*MPA supports the advanced audio distribution profile (role source)*/
#define F_BT_MPA_A2DP_SINK       0         /*MPA supports the advanced audio distribution profile (role sink)*/
#define BT_MPA_A2DP_SINK_PCM_BUFFER_SIZE_COUNT 0         /*Size of PCM buffers for SBC decoding*/
#define BT_MPA_A2DP_SINK_PCM_BUFFER_COUNT 0         /*Number of PCM buffers for SBC decoding*/
#define F_BT_MPA_CTP             0         /*MPA supports the cordless telephony profile*/
#define F_BT_MPA_FBUS            0         /*MPA supports Nokia bus protocol*/
#define F_BT_MPA_PBAP            0         /*MPA supports PBAP*/
#define F_BT_MPA_AVRCP           0         /*MPA supports AVRCP*/
#define F_BT_MPA_MULTI_CONTROLLER 0         /*MPA supports multi controller*/
#define F_BT_BECI                0         /*BECI exists*/
#define F_BT_BECI_SDAP           0         /*BECI supports the service discovery application profile*/
#define F_BT_BECI_SPP            0         /*BECI supports the serial port profile*/
#define F_BT_BECI_HFP_UNIT       0         /*BECI supports the hands free profile role unit*/
#define F_BT_BECI_HFP_AG         0         /*BECI supports the hands free profile role audio gateway*/
#define F_CONFIG_APP_SHOW_VERBOSE 0         /*Default: Show output in human readable format*/
#define F_CONFIG_APP_SHOW_AS_CSV 0         /*Show output in CSV (Character Separated Value) format*/
#define CONFIG_APP_CLIENTS_COUNT 0         /*Max. simultaneous clients*/
#define CONFIG_APP_TIMER_OUTPUT_COUNT 0         /*Output delay in timer ticks*/
#define F_CONFIG_APP_USE_POOL_CALLBACK 0         /*Use pool callback function*/
#define CONFIG_APP_PARAMETER_BUFFER_SIZE_COUNT 0         /*Buffer size for parameters*/
#define CONFIG_APP_BIG_BUFFER_SIZE_COUNT 0         /*Buffer size for show command*/
#define CONFIG_APP_SMALL_BUFFER_SIZE_COUNT 0         /*Temporary buffer size*/
#define F_RM_LED                 0         /*RM controls LED*/
#define F_RM_SERIAL              0         /*RM serial interface*/
#define RM_CLIENTS_COUNT         0         /*RM number of clients*/
#define F_RM_USER                0         /*RM user defined*/
#define F_RM_POWER_MODE          0         /*RM power up/down*/
#define F_RM_LED1_OFF_ON_DEACTIVATE_EVENT 0         /*LED1 id off when L1 is inactive*/
#define F_RM_POWER_MANAGER       0         /*Power Manager, extension of Resource Manager*/
#define RM_POWER_MANAGER_CLIENT_COUNT 0         /*number of Power Manager clients*/
#define F_RM_POWER_MANAGER_CUSTOM_BAUDRATE_SUPPORT 0         /*Power Manager supports custom baudrate. Upper layer application are responsible for validation of baudrate value*/
#define F_POWER_MANAGER          0         /*Power manager without resource manager*/
#define POWER_MANAGER_CLIENT_COUNT 0         /*number of Power Manager clients*/
#define F_POWER_MANAGER_CUSTOM_BAUDRATE_SUPPORT 0         /*Power Manager supports custom baudrate. Upper layer application are responsible for validation of baudrate value*/
#define DB_PARAMETER_SET_INFO_COUNT 0         /*Max. registered parametersets (Default is 16)*/
#define F_DB_AUTOSAVE            0         /*enable/disable automatic storing of Parameter*/
#define F_DS2401_CHECK_SERIAL_NUMBER 0         /*compare serial number on chip with predefined value*/
#define F_FLASH_FW_BANKED        0         /*flash has 2 banks, 2nd fw (linked to same addr.) can be act. without deleting the old one*/
#define F_OBEX_SERVER            0         /*Obex Server application*/
#define F_OBEX_CLIENT            0         /*Obex Client application*/
#define F_OBEX_PUSH              0         /*Obex Push Supported*/
#define F_OBEX_PULL              0         /*Obex Pull Supported*/
#define F_OBEX_SETPATH           0         /*Obex Set Path Supoorted*/
#define F_OBEX_RX_FILE           0         /*Obex RX File Supported*/
#define F_OBEX_DELETE_FILE       0         /*Obex Delete File Supported*/
#define F_OBEX_TX_FILE           0         /*Obex Transmit Supported*/
#define F_OBEX_CREATE_DIR        0         /*Obex Create Dir Supported*/
#define F_OBEX_GET_DIR           0         /*Obex Get Directory supported*/
#define OBEX_PDU_SIZE_COUNT      0         /*Obex PDU transfer size 0x4000 Standard*/
#define F_CTGW                   0         /*Cordless Telephony gateway application*/
#define CTGW_TL_CTP_COUNT        0         /*Gateway number of terminals (Cordless Telephony Profile)*/
#define CTGW_TL_HSP_COUNT        0         /*Gateway number of headsets (Headset Profile)*/
#define CTGW_LI_COUNT            0         /*CTGW number of line interfaces*/
#define F_CTGW_LI_AUTO_CONNECT   0         /*CTGW sotfware line interface*/
#define F_CTGW_LI_ANALOG_MODEM   0         /*CTGW line interface analog modem*/
#define F_CTGW_LI_TERMINAL_ADAPTER 0         /*CTGW line interface Stollmann TA*/
#define F_NFC                    0         /*Be NFC conform*/
#define F_NFC_MF_STD             0         /*NFC Mifare Standard as NFC Forum Tag*/
#define F_NFC_MF_ULTRALIGHT      0         /*NFC Mifare Ultralight as type 2 tag*/
#define F_NFC_MF_DESFIRE         0         /*NFC Mifare DESFire as type 4 tag*/
#define F_NFC_JEWEL              0         /*Innovision Jewel as type 1 tag*/
#define F_NFC_ISO14443_B         0         /*Support 14443 Type B*/
#define F_NFC_FELICA             0         /*Sony Felica as type 3 tag*/
#define F_NFC_MF_STD_MAD_CRC     0         /*MAD-CRC bei Mifare auswerten*/
#define F_NFC_WIRED_SE           0         /*Secure Element by Host Access*/
#define F_NFC_HOST_CE            0         /*Tag Emulation by Host*/
#define F_NFC_SECURE_CE          0         /*Tag Emulation by Secure Element*/
#define F_NFC_P2P_IN             0         /*Peer to Peer as Initiator*/
#define F_NFC_P2P_TG             0         /*Peer to Peer as Target*/
#define F_NFC_DATA_SIZE_4K       0         /**/
#define F_NFC_DATA_SIZE_8K       0         /**/
#define F_NFC_DATA_SIZE_16k      0         /**/
#define F_NFC_LLCP               0         /*NFC Logical Link Control Protocol*/
#define F_NFC_L1_V24             0         /**/
#define F_NFC_FRI_SDK            0         /*Build with NXP FRI SDK*/
#define F_NFC_ETSI_HCI           0         /*Use ETSI HCI LL*/
#define NFC_MAX_LINK_COUNT       0         /**/
#define NFC_MAX_APP_COUNT        0         /*Max Application in NFCman*/
#define NFC_SHORT_BUFFER_BYTE_COUNT 0         /**/
#define NFC_US_BUFFER_COUNT      0         /**/
#define NFC_DS_BUFFER_COUNT      0         /**/
#define NFC_53X_COUNT            0         /**/
#define NFC_512_COUNT            0         /**/
#define NFC_544_COUNT            0         /**/
#define NFC_STM21NFCA_COUNT      0         /**/
#define NFC_US_WRITE_OFFSET_COUNT 0         /**/
#define NFC_DS_WRITE_OFFSET_COUNT 0         /*initial writeOffset for downstream data*/
#define NFC_LLCP_LINK_COUNT      0         /*Max. LLCP links*/
#define NFC_LLCP_DS_BUFFER_BYTE_COUNT 0         /*LLCP DS buffer size*/
#define NFC_LLCP_DS_BUFFER_COUNT 0         /*LLCP DS buffer count*/
#define NFC_LLCP_CONTROL_BUFFER_COUNT 0         /*LLCP control buffer count*/
#define GLOBAL_SHORT_BUFFER_BYTE_COUNT 0         /*Short buffer size*/
#define GLOBAL_SHORT_BUFFER_COUNT 0         /*Short buffer count*/
#define GLOBAL_MIDDLE_BUFFER_BYTE_COUNT 0         /*Middle buffer size*/
#define GLOBAL_MIDDLE_BUFFER_COUNT 0         /*Middle buffer count*/
#define GLOBAL_LONG_BUFFER_BYTE_COUNT 0         /*Long buffer size*/
#define GLOBAL_LONG_BUFFER_COUNT 0         /*Long buffer count*/
#define GLOBAL_RAM_RESERVE_BYTES_COUNT 0         /*RAM reserve in bytes, overwrites Kbytes value if nonzero*/
#define GLOBAL_RAM_RESERVE_KBYTES_COUNT 0         /*RAM reserve in KBytes*/
#define GLOBAL_FLASH_RESERVE_BYTES_COUNT 0         /*Flash reserve in bytes, overwrites Kbytes value if nonzero*/
#define GLOBAL_FLASH_RESERVE_KBYTES_COUNT 0         /*Flash reserve in KBytes*/
#define F_BOOT_FLAGS             0         /*Bootloader uses flags BOOT_x*/
#define F_BOOT_DUMP              0         /*DUMP command*/
#define F_BOOT_DUMP_TYPE         0         /*DB, DW, DD commands*/
#define F_BOOT_WRITE_TYPE        0         /*WB, WW, WD commands*/
#define F_BOOT_NVRAM             0         /*NVRAM commands*/
#define F_BOOT_LOADSW            0         /*LOADSW command*/
#define F_BOOT_WRITE_PROTECT     0         /*Write protect BootLoader*/
#define F_BOOT_MAGIC_CHECK       0         /*Magic check*/
#define F_BOOT_CHECKSUM          0         /*Check FW checksum at startup*/
#define F_BOOT_LED               0         /*Bootloader supports LED*/
#define F_BOOT_CHECK_HARDWARE    0         /*Bootloader checks the hardware components.*/
#define BOOT_INFOPAGE_COUNT      0         /*INFOPAGEx command*/
#define F_PPP_CRC16              0         /*CRC Implementation for PPP Polynomial: X**0 + X**5 + X**12 + X16*/
#define F_BTX_CRC16              1         /*CRC Implementation for BTX Polynomial: X**0 + X**2 + X**15 + X16*/
#define F_ETS_CRC8               1         /*CRC/FCS routines based on ETSI TS 101 369 V6.3.0*/
#define F_COMMAND_PARSER         0         /*Command parser*/
#define F_COMMAND_PARSER_HELP    0         /*Command parser + help command*/
#define COMMAND_PARSER_CMDS_COUNT 0         /*Command parser + cmds command*/
#define F_CLIB_NUMBER_TABLE      0         /*Table handling (Nr. Table)*/
#define F_OS_EXTERNAL            1         /*OSIF underlies a external operating system*/
#define F_OS_FREERTOS            0         /*FreeRTOS Wittenstein*/
#define F_OS_EMBOS               0         /*enbOS Seggger*/
#define F_OS_LINUX               1         /*Linux OS*/
#define F_OS_WINDOWS             0         /*Windows*/
#endif

#if defined(_C166)
/* Without this definition the C166 compiler
 * complains about empty files */
typedef int TRemoveDummy;
#endif /* defined(_C166) */

#ifndef OEM
#error This HARDWARE/OEM combination is not defined in OEM.H
#endif
#include <addflags.h>
#endif /*__FLAGS_H*/
