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
/*    _nxe_secure_tls_remote_certificate_allocate         PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in the TLS remote certificate       */
/*    allocate call.                                                      */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    tls_session                           Pointer to TLS Session        */
/*    certificate                           Pointer to certificate        */
/*    raw_certificate_buffer                Buffer for storing cert       */
/*    buffer_size                           Size of cert buffer           */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_tls_remote_certificate_allocate                          */
/*                                          Actual remote certificate     */
/*                                            allocate call               */
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
UINT  _nxe_secure_tls_remote_certificate_allocate(NX_SECURE_TLS_SESSION *tls_session,
                                                  NX_SECURE_X509_CERT *certificate,
                                                  UCHAR *raw_certificate_buffer, UINT buffer_size)
{
UINT status;



    /* Remote certificates must be assigned a buffer for parsing. */
    if ((tls_session == NX_NULL) || (certificate == NX_NULL) || (raw_certificate_buffer == NX_NULL))
    {
        return(NX_PTR_ERROR);
    }

    /* Make sure the session is initialized. */
    if(tls_session -> nx_secure_tls_id != NX_SECURE_TLS_ID)
    {
        return(NX_SECURE_TLS_SESSION_UNINITIALIZED);
    }

    if (buffer_size == 0)
    {
        return(NX_SECURE_TLS_INSUFFICIENT_CERT_SPACE);
    }

    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    status =  _nx_secure_tls_remote_certificate_allocate(tls_session, certificate, (UCHAR *)raw_certificate_buffer, buffer_size);

    /* Return completion status.  */
    return(status);
}

