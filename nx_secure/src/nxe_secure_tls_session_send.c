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
/** NetX Secure Component                                                 */
/**                                                                       */
/**    Transport Layer Security (TLS)                                     */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SECURE_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_secure_tls.h"

/* Bring in externs for caller checking code.  */

NX_SECURE_CALLER_CHECKING_EXTERNS

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxe_secure_tls_session_send                        PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in the TLS session send call.       */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    tls_session                           TLS control block             */
/*    packet_ptr                            Pointer to packet data        */
/*    wait_option                           Indicates behavior if TCP     */
/*                                          socket cannot send packet     */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_tls_session_send           Actual TLS session send call. */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Timothy Stapko           Initial Version 6.0           */
/*  09-30-2020     Timothy Stapko           Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*  10-31-2023     Yanwu Cai                Modified comment(s), added    */
/*                                            record length checking,     */
/*                                            resulting in version 6.3.0  */
/*                                                                        */
/**************************************************************************/
UINT  _nxe_secure_tls_session_send(NX_SECURE_TLS_SESSION *tls_session, NX_PACKET *packet_ptr,
                                   ULONG wait_option)
{
UINT status;

    if (tls_session == NX_NULL)
    {
        return(NX_PTR_ERROR);
    }

    if (packet_ptr == NX_NULL)
    {
        return(NX_PTR_ERROR);
    }

    if (packet_ptr -> nx_packet_length == 0)
    {
        /* Must check for empty packets here, as TLS data will make a packet's contents
        non-empty. _nx_tcp_socket_send_internal has a check for an empty packet
        that correctly works in an HTTP session but will result in a false negative if
        the session is HTTPS. Thus, this check is performed before the TLS session
        operations that modify the packet.  */
        return(NX_INVALID_PACKET);
    }

    if (tls_session -> nx_secure_tls_tcp_socket == NX_NULL)
    {
        return(NX_SECURE_TLS_SESSION_UNINITIALIZED);
    }

    /* Make sure the session is initialized. */
    if (tls_session -> nx_secure_tls_id != NX_SECURE_TLS_ID)
    {
        return(NX_SECURE_TLS_SESSION_UNINITIALIZED);
    }

    /* Check the plaintext length as the fragmentation is not supported currently. */
    if (packet_ptr -> nx_packet_length > NX_SECURE_TLS_MAX_PLAINTEXT_LENGTH)
    {
        return(NX_SECURE_TLS_RECORD_OVERFLOW);
    }

    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    status =  _nx_secure_tls_session_send(tls_session, packet_ptr, wait_option);

    /* Return completion status.  */
    return(status);
}

