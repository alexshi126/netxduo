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
/*    _nxe_secure_tls_remote_certificate_buffer_allocate  PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in allocating buffer space for      */
/*    incoming certificates from the remote host.                         */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    tls_session                           Pointer to TLS Session        */
/*    certs_number                          Number of client certs        */
/*    certificate_buffer                    Buffer allocated for certs    */
/*    buffer_size                           Buffer size in bytes          */
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
UINT  _nxe_secure_tls_remote_certificate_buffer_allocate(NX_SECURE_TLS_SESSION *tls_session, UINT certs_number, VOID *certificate_buffer, ULONG buffer_size)
{
UINT status;

    /* Check for NULL pointers. */
    if(tls_session == NX_NULL || certificate_buffer == NX_NULL)
    {
        return(NX_PTR_ERROR);
    }

    if(certs_number == 0 || buffer_size == 0)
    {
        return(NX_INVALID_PARAMETERS);
    }

    /* Make sure the session is initialized. */
    if(tls_session -> nx_secure_tls_id != NX_SECURE_TLS_ID)
    {
        return(NX_SECURE_TLS_SESSION_UNINITIALIZED);
    }

    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    /* Call actual function. */
    status = _nx_secure_tls_remote_certificate_buffer_allocate(tls_session, certs_number, certificate_buffer, buffer_size);

    /* Return completion status.  */
    return(status);
}

