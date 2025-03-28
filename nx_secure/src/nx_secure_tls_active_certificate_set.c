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

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_secure_tls_active_certificate_set               PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function sets the active local certificate, overriding any     */
/*    previously added local certificates. Normally, a single certificate */
/*    is used for a TLS instance, but in some cases the server or client  */
/*    may need to choose a specific certificate during the handshake. By  */
/*    calling this function in the TLS server or client callback, an      */
/*    application can choose the active local certificate at runtime      */
/*    after a ClientHello or ServerHello is received.                     */
/*                                                                        */
/*    NOTE: The certificate MUST be in the local store before calling     */
/*    this function (using nx_secure_tls_local_certificate_add) or the    */
/*    proper certificate chain may not be sent to the remote host!        */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    tls_session                           Pointer to TLS Session        */
/*    certificate                           Pointer to certificate        */
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
/*  03-08-2023     Yanwu Cai                Modified comment(s),          */
/*                                            fixed compiler errors when  */
/*                                            x509 is disabled,           */
/*                                            resulting in version 6.2.1  */
/*                                                                        */
/**************************************************************************/
UINT _nx_secure_tls_active_certificate_set(NX_SECURE_TLS_SESSION *tls_session,
                                           NX_SECURE_X509_CERT *certificate)
{
#ifdef NX_SECURE_DISABLE_X509
    NX_PARAMETER_NOT_USED(tls_session);
    NX_PARAMETER_NOT_USED(certificate);

    return(NX_NOT_SUPPORTED);
#else
    /* Set the active certificate (should be in the store). */
    tls_session -> nx_secure_tls_credentials.nx_secure_tls_active_certificate = certificate;

    /* Return completion status.  */
    return(NX_SUCCESS);
#endif
}

