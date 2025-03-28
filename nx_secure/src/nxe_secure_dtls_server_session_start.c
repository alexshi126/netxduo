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
/*    _nxe_secure_dtls_server_session_start               PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in a DTLS server session start call.*/
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dtls_session                          DTLS control block            */
/*    wait_option                           Suspension option             */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_dtls_server_session_start  Start the DTLS session        */
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
UINT _nxe_secure_dtls_server_session_start(NX_SECURE_DTLS_SESSION *dtls_session, UINT wait_option)
{
#ifdef NX_SECURE_ENABLE_DTLS
UINT status;

    /* Check pointers. */
    if (dtls_session == NX_NULL)
    {
        return(NX_PTR_ERROR);
    }

    /* This API requires that the UDP socket already be assigned. */
    if (dtls_session->nx_secure_dtls_udp_socket == NX_NULL || 
        (!dtls_session -> nx_secure_dtls_session_in_use) ||
        dtls_session->nx_secure_dtls_tls_session.nx_secure_tls_id != NX_SECURE_TLS_ID)
    {
        return(NX_SECURE_TLS_SESSION_UNINITIALIZED);
    }

    /* Call actual function. */
    status = _nx_secure_dtls_server_session_start(dtls_session, wait_option);

    return(status);
#else
    NX_PARAMETER_NOT_USED(dtls_session);
    NX_PARAMETER_NOT_USED(wait_option);

    return(NX_NOT_SUPPORTED);
#endif /* NX_SECURE_ENABLE_DTLS */
}
