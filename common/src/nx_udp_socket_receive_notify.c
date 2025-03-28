/***************************************************************************
 * Copyright (c) 2024 Microsoft Corporation 
 * Copyright (c) 2025-present Eclipse ThreadX Contributors
 * 
 * This program and the accompanying materials are made available under the
 * terms of the MIT License which is available at
 * https://opensource.org/licenses/MIT.
 * 
 * SPDX-License-Identifier: MIT
 **************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** NetX Component                                                        */
/**                                                                       */
/**   User Datagram Protocol (UDP)                                        */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_udp.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_udp_socket_receive_notify                       PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function sets the receive notify function pointer to the       */
/*    function specified by the application, which is called whenever     */
/*    a packet is received on the socket.  If a NULL pointer is supplied, */
/*    the receive notify function is disabled.                            */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    socket_ptr                            Pointer to UDP socket         */
/*    udp_receive_notify                    Routine to call when one or   */
/*                                            receive packets are         */
/*                                            available for the socket    */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*  09-30-2020     Yuxin Zhou               Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/
UINT  _nx_udp_socket_receive_notify(NX_UDP_SOCKET *socket_ptr,
                                    VOID (*udp_receive_notify)(NX_UDP_SOCKET *socket_ptr))
{
TX_INTERRUPT_SAVE_AREA


    /* Disable interrupts.  */
    TX_DISABLE

    /* Setup the receive notify function pointer.  */
    socket_ptr -> nx_udp_receive_callback =  udp_receive_notify;

    /* Restore interrupts.  */
    TX_RESTORE

    /* If trace is enabled, insert this event into the trace buffer.  */
    NX_TRACE_IN_LINE_INSERT(NX_TRACE_UDP_SOCKET_RECEIVE_NOTIFY, socket_ptr -> nx_udp_socket_ip_ptr, socket_ptr, udp_receive_notify, 0, NX_TRACE_UDP_EVENTS, 0, 0);

    /* Return successful completion.  */
    return(NX_SUCCESS);
}

