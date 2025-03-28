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
/**    Datagram Transport Layer Security (DTLS)                           */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SECURE_SOURCE_CODE

#include "nx_secure_dtls.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_secure_dtls_server_session_send                 PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function sends data using an active DTLS Server session,       */
/*    handling all encryption and hashing before sending data over the    */
/*    UDP socket to the internally-stored IP address and port.            */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dtls_session                          DTLS control block            */
/*    packet_ptr                            Pointer to packet data        */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_dtls_session_send          Send DTLS encrypted record    */
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
/*                                                                        */
/**************************************************************************/
UINT _nx_secure_dtls_server_session_send(NX_SECURE_DTLS_SESSION *dtls_session, NX_PACKET *packet_ptr)
{
#ifdef NX_SECURE_ENABLE_DTLS
UINT status;

    status = _nx_secure_dtls_session_send(dtls_session, packet_ptr, &(dtls_session->nx_secure_dtls_remote_ip_address), dtls_session->nx_secure_dtls_remote_port);

    return(status);
#else
    NX_PARAMETER_NOT_USED(dtls_session);
    NX_PARAMETER_NOT_USED(packet_ptr);

    return(NX_NOT_SUPPORTED);
#endif /* NX_SECURE_ENABLE_DTLS */
}

