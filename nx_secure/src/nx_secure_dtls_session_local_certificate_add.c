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
/*    _nx_secure_dtls_session_local_certificate_add       PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function adds a local identity certificate to a DTLS session   */
/*    instance. The certificate is used to identify the DTLS session to   */
/*    a remote host. For DTLS Servers, this certificate is required. For  */
/*    DTLS Clients, the certificate is only needed if the remote server   */
/*    requests one.                                                       */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dtls_session                          DTLS session control block    */
/*    certificate                           Pointer to identity cert      */
/*    cert_id                               Numeric ID for cert           */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_tls_server_certificate_add                               */
/*                                          Add certificate to TLS        */
/*                                            session.                    */
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
UINT _nx_secure_dtls_session_local_certificate_add(NX_SECURE_DTLS_SESSION *dtls_session,
                                                   NX_SECURE_X509_CERT *certificate, UINT cert_id)
{
#if defined(NX_SECURE_ENABLE_DTLS) && !defined(NX_SECURE_DISABLE_X509)
UINT status;
NX_SECURE_TLS_SESSION *tls_session;

    /* Get the internal TLS session instance. */
    tls_session = &(dtls_session -> nx_secure_dtls_tls_session);

    /* Add the certificate with the provided ID. Note that the TLS API called here allows us to
       add a local cert with a numeric ID (legacy local certificate add API does not have id).  */
    status = _nx_secure_tls_server_certificate_add(tls_session, certificate, cert_id);

    return(status);
#else
    NX_PARAMETER_NOT_USED(dtls_session);
    NX_PARAMETER_NOT_USED(certificate);
    NX_PARAMETER_NOT_USED(cert_id);

    return(NX_NOT_SUPPORTED);
#endif /* NX_SECURE_ENABLE_DTLS && !NX_SECURE_DISABLE_X509 */
}

