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
/*    _nx_secure_dtls_server_notify_set                   PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function assigns the optional notification callback routines   */
/*    for errors and disconnect events to a DTLS session. These callbacks */
/*    can be used to monitor errors (and timeouts) during a DTLS          */
/*    handshake and when DTLS connections are closed.                     */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    server_ptr                            DTLS server control block     */
/*    disconnect_notify                     DTLS disconnect callback      */
/*    error_notify                          DTLS error callback           */
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
/*  05-19-2020     Timothy Stapko           Initial Version 6.0           */
/*  09-30-2020     Timothy Stapko           Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/
UINT _nx_secure_dtls_server_notify_set(NX_SECURE_DTLS_SERVER *server_ptr,
                                       UINT (*disconnect_notify)(NX_SECURE_DTLS_SESSION *dtls_session),
                                       UINT (*error_notify)(NX_SECURE_DTLS_SESSION *dtls_session, UINT error_code))


{
#ifdef NX_SECURE_ENABLE_DTLS

    /* Assign callbacks. */
    server_ptr->nx_secure_dtls_disconnect_notify = disconnect_notify;
    server_ptr->nx_secure_dtls_error_notify = error_notify;

    return(NX_SUCCESS);
#else
    NX_PARAMETER_NOT_USED(server_ptr);
    NX_PARAMETER_NOT_USED(disconnect_notify);
    NX_PARAMETER_NOT_USED(error_notify);

    return(NX_NOT_SUPPORTED);
#endif /* NX_SECURE_ENABLE_DTLS */
}

