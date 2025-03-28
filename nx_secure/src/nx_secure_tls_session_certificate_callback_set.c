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


#include "nx_secure_tls.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_secure_tls_session_certificate_callback_set     PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function sets up a function pointer that TLS will invoke when  */
/*    a certificate is received from a remote host, allowing the          */
/*    application to perform validation checks such as DNS validation,    */
/*    certificate revocation, and certificate policy enforcement.         */
/*                                                                        */
/*    NetX Secure TLS will perform basic validation on the certificate    */
/*    before invoking the callback to assure that the certificate can be  */
/*    traced to a certificate in the TLS trusted certificate store, but   */
/*    all other validation will be handled by this callback.              */
/*                                                                        */
/*    The callback provides the TLS session pointer and a pointer to the  */
/*    remote host identity certificate (the leaf in the certificate       */
/*    chain). The callback should return NX_SUCCESS if all validation is  */
/*    successful, otherwise it should return an error code indicating the */
/*    validation failure. Any value other than NX_SUCCESS will cause the  */
/*    TLS handshake to immediately abort.                                 */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    tls_session                           TLS control block             */
/*    func_ptr                              Pointer to callback function  */
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
UINT _nx_secure_tls_session_certificate_callback_set(NX_SECURE_TLS_SESSION *tls_session,
                                                     ULONG (*func_ptr)(NX_SECURE_TLS_SESSION *session,
                                                                       NX_SECURE_X509_CERT *certificate))
{
    /* Set the function pointer in the TLS session. */
    tls_session -> nx_secure_tls_session_certificate_callback = func_ptr;

    return(NX_SUCCESS);
}

