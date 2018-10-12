/**********************************************************************!MA*
 * Copyright (c)           2018 Telit Wireless Solutions GmbH
 *                         Friesenweg 4, Haus 14
 *                         22763 Hamburg
 *                         Germany
 *                         Phone: +49 40 890 88 0
 * All Rights Reserved
 * Archive:     $Source: /var/lib/cvs/sw/./inc/comapi.h,v $
 * Revision:    $Revision: 2.40.2.6 $
 * Date:        $Date: 2018/04/20 10:42:51 $
 * Author:      $Author: ConnorRo $
 * ------------------------------------------------------------------------
 **********************************************************************!HE*/

#ifndef __BLUECODE_COMAPI_H
#define __BLUECODE_COMAPI_H

/** @file
 * COMAPI interface of BlueCode+. Customer porting code should provide an implementation with platform-specific handlers. */

#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>  // uint*_t
#include <stdbool.h> // bool

typedef void * HCOM; /**< Context handle for an HCI transport that COMAPI provides to BlueCode+ in #comOpen */

/** Event code for event signaling from COMAPI to BlueCode+. */
typedef enum TComEvent
{
  comeOpenCompleted    = 0x00, /**< The HCI transport has been opened and is ready for operation, or opening the transport failed, as indicated by the "uStatus" parameter of #PComCallBack */
  comeCloseCompleted   = 0x01, /**< The HCI transport has been closed and all shared resources including buffers, handles and callbacks have been discarded / released. The HCI transport may now be opened again */
  comeDataIndication   = 0x02, /**< An HCI packet has been received from the controller and is provided to BlueCode+.
                                    BlueCode+ may reject the packet to apply flow control, see "uStatus" parameter of #PComCallBack.
                                    The packet buffer may not be discarded or re-used until released by #comResponse as ownership is shared with BlueCode+.
                                    Independent of packet rejections, packets may only be indicated in the order they have been received in.
                                    A packet may not be indicated via this event if a packet that has been received earlier has not been accepted by the event handler. */
  comeDataTransmitted  = 0x03, /**< An HCI packet has been sent to the controller and the packet buffer's shared ownership is released */
  comeError            = 0x04, /**< A critical error has occurred during operation and the HCI transport can no longer be used */
} TComEvent;

/** Result status code for COMAPI operations and event handling. */
typedef enum TComResult
{
  comResultSuccess       = 0x00, /**< The operation completed successfully */
  comResultPending       = 0x01, /**< The operation has been started and completion will be signaled via a callback */
  comResultUnspecified   = 0x02, /**< The operation failed with an unspecified error */
  comResultNoResources   = 0x03, /**< The operation could not be completed due to lack of resources */
  comResultOpenfailed    = 0x04, /**< The underlying transport could not be opened */
  comResultInvalidState  = 0x05, /**< The COMAPI is not in a state where it can perform the requested operation */
  comResultInvalidParam  = 0x06, /**< An invalid parameter has been given for a requested operation */
} TComResult;

typedef uint8_t COMAPIPacketIndicator; /**< Indicator for the HCI Packet Type of an exchanged packet. */

#define HCI_PACKET_TYPE_COMMAND ((COMAPIPacketIndicator) 0x01) /**< HCI Command Packet Type */
#define HCI_PACKET_TYPE_ACL     ((COMAPIPacketIndicator) 0x02) /**< HCI ACL Data Packet Type */
#define HCI_PACKET_TYPE_SYNC    ((COMAPIPacketIndicator) 0x03) /**< HCI Synchronous Data Packet Type */
#define HCI_PACKET_TYPE_EVENT   ((COMAPIPacketIndicator) 0x04) /**< HCI Event Packet Type */

// Internal callback interface structure

/** Can be called by COMAPI to signal an event to BlueCode+.
 * @param pvContext [in,out] Context handle provided by BlueCode+
 * @param event     [in] Event code
 * @param uStatus   [in] If the event is signals the completion of an operation, result code of that operation, otherwise the parameter will be ignored
 * @param pvBuffer  [in,out] If @p event is:
 *                           <table><tr><td> comeDataIndication  <td> Buffer containing the received HCI packet. Ownership is shared
 *                                  <tr><td> comeDataTransmitted <td> Buffer previously provided by BlueCode+ that contains the transmitted HCI packet. Ownership is released
 *                                  <tr><td> any other value     <td> Will be ignored </table>
 * @param uLength   [in] Length of @p pvBuffer
 * @retval ::comResultNoResources if the event is ::comeDataIndication and the packet has been rejected to apply flow control.
 *                                The COMAPI shall then not discard the packet and retry signaling the event until ::comResultSuccess is returned.
 *                                It is recommended to delay further attempts until #comResponse acknowledges a previous packet (sliding window).
 * @retval ::comResultSuccess if the callback was handled successfully.
 * @return an error status code if an unspecified error occurred. */
typedef TComResult (* PComCallBack)(
        void * pvContext,
        TComEvent event,
        TComResult uStatus,
        void * pvBuffer,
        uint32_t uLength);

// External interface. Should be implemented in porting code

/** Can be called by BlueCode+ to establish the HCI connection. Any vendor- or target-specific controller or transport initialization procedures (e.g., open and configure a serial device for HCI H4,
 * upload of controller ROM patches, configuration of custom Bluetooth address) shall be completed before signaling ::comeOpenCompleted asynchronously.
 * When this functions returns ::comResultSuccess, or the COMAPI signals ::comeOpenCompleted and the status parameter is ::comResultSuccess,
 * BlueCode+ will expect the HCI transport to be open, fully configured and functional.
 * Any other status parameter indicates failure to open the transport.
 * During graceful termination, BlueCode+ will call #comClose to close an open HCI transport and release all allocated resources.
 * @retval ::comResultSuccess if the connection has been established synchronously and the transport is ready for operation.
 * @retval ::comResultPending if the connection will be established asynchronously and ::comeOpenCompleted will be signaled.
 * @return an error status code if connection establishment failed. */
TComResult comOpen(
        char * pszDeviceName,   /**< [in] Historical argument, will be ignored */
        char * pszParameter,    /**< [in] Historical argument, will be ignored */
        PComCallBack callBack,  /**< [in] COMAPI callback handler to signal events. Ownership is shared */
        void * callBackContext, /**< [in,out] BlueCode+-provided context handle for future invocations of @p callback */
        HCOM * phCom            /**< [out] COMAPI-provided context handle for future calls to com* functions on the same transport */);

/** Can be called by BlueCode+ to close an HCI transport previously established via #comOpen.
 * The COMAPI shall release all allocated resources and discard shared references provided by BlueCode+ before signaling ::comeCloseCompleted asynchronously.
 * When this functions returns ::comResultSuccess, or the COMAPI signals ::comeCloseCompleted, BlueCode+ will expect the HCI transport to be closed and ready to be opened again.
 * @retval ::comResultSuccess if the transport has been closed synchronously and the transport is ready to be opened again.
 * @retval ::comResultPending if the transport will be closed asynchronously and ::comeCloseCompleted will be signaled.
 * @return an error status code if closing the transport failed. */
TComResult comClose(
        HCOM hCom /**< [in] Context handle provided by the COMAPI in #comOpen */);

/** Can be called by BlueCode+ to request the transmission of an HCI packet over an open HCI transport.
 * If the COMAPI accepts the packet, it shall send its contents to the controller and then signal ::comeDataTransmitted asynchronously.
 * Synchronous response is not allowed. The COMAPI may reject the packet to apply flow control. In this case, BlueCode+ may delay further transmission attempts until ::comeDataTransmitted is signaled.
 * @retval ::comResultSuccess if the COMAPI accepts the packet and ::comeDataTransmitted will be signaled.
 * @retval ::comResultNoResources if the COMAPI rejects the packet to apply flow control.
 * @return an error status code if COMAPI could not accept the packet due to an error. */
TComResult comWrite(
        HCOM hCom,             /**< [in] Context handle provided by the COMAPI in #comOpen */
        uint8_t * pvBuffer,    /**< [in] Buffer containing the HCI packet. Ownership is shared */
        uint32_t uBufferLength /**< [in] Length of @p pvBuffer */);

/** Can be called by BlueCode+ to acknowledge the reception of an HCI packet previously signaled via ::comeDataIndication.
 * This releases BlueCode+'s shared ownership of the packet buffer.
 * @retval ::comResultSuccess if the packet acknowledgment has been handled successfully.
 * @return an error status code if any error occurred. */
TComResult comResponse(
        HCOM hCom,         /**< [in] Context handle provided by the COMAPI in #comOpen */
        uint8_t * pvBuffer /**< [in] Buffer previously provided by the COMAPI that contains the acknowledged HCI packet. Ownership is released */);

#if defined (__cplusplus)
}
#endif

#endif /* ndef __BLUECODE_COMAPI_H */
