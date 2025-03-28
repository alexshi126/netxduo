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
/*    _nx_secure_dtls_server_local_certificate_remove     PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function removes a local server identity certificate from a    */
/*    DTLS server instance, either using the Common Name or the           */
/*    certificate id ("cert_id" parameter) assigned when the certificate  */
/*    was added.                                                          */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    server_ptr                            DTLS server control block     */
/*    common_name                           Certificate Common Name       */
/*    common_name_length                    Length of Common Name         */
/*    cert_id                               Numeric ID for certificate    */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_tls_server_certificate_remove                            */
/*                                          Remove certificate using ID   */
/*    _nx_secure_tls_local_certificate_remove                             */
/*                                          Remove certificate using CN   */
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
/*  09-30-2020     Timothy Stapko           Modified comment(s), and      */
/*                                            fixed compiler warnings,    */
/*                                            resulting in version 6.1    */
/*  03-08-2023     Yanwu Cai                Modified comment(s),          */
/*                                            fixed compiler errors when  */
/*                                            x509 is disabled,           */
/*                                            resulting in version 6.2.1  */
/*                                                                        */
/**************************************************************************/
UINT _nx_secure_dtls_server_local_certificate_remove(NX_SECURE_DTLS_SERVER *server_ptr,
                                                     UCHAR *common_name, UINT common_name_length, UINT cert_id)
{
#if defined(NX_SECURE_ENABLE_DTLS) && !defined(NX_SECURE_DISABLE_X509)
UINT status;
UINT i;
NX_SECURE_DTLS_SESSION *current_session;
NX_SECURE_TLS_SESSION *tls_session;
NX_SECURE_X509_CERT *list_head = NX_NULL;
UINT num_sessions;

    /* Figure out number of sessions. */
    num_sessions = server_ptr -> nx_dtls_server_sessions_count;

    /* Remove certificate from the first session. */
    if (num_sessions > 0)
    {
        /* Get the first session. */
        current_session = &(server_ptr -> nx_dtls_server_sessions[0]);

        /* Get the internal TLS session instance. */
        tls_session = &(current_session -> nx_secure_dtls_tls_session);

        if(cert_id > 0)
        {
            /* Remove the server certificate with the provided ID. */
            status = _nx_secure_tls_server_certificate_remove(tls_session, cert_id);
        }
        else
        {
            /* Remove the server certificate with the provided CN. */
            status = _nx_secure_tls_local_certificate_remove(tls_session, common_name, common_name_length);
        }

        if(status != NX_SUCCESS)
        {
            return(status);
        }

        /* Store the certificates list head for other sessions. */
        list_head = tls_session -> nx_secure_tls_credentials.nx_secure_tls_certificate_store.nx_secure_x509_local_certificates;
    }

    /* Remove certificate from the remaining sessions. */
    for(i = 1; i < num_sessions; ++i)
    {
        /* Get the current session. */
        current_session = &(server_ptr -> nx_dtls_server_sessions[i]);

        /* Get the internal TLS session instance. */
        tls_session = &(current_session -> nx_secure_dtls_tls_session);

        /* Set the local certificates list to the same as the first session. */
        tls_session -> nx_secure_tls_credentials.nx_secure_tls_certificate_store.nx_secure_x509_local_certificates = list_head;
    }

    return(NX_SUCCESS);
#else
    NX_PARAMETER_NOT_USED(server_ptr);
    NX_PARAMETER_NOT_USED(common_name);
    NX_PARAMETER_NOT_USED(common_name_length);
    NX_PARAMETER_NOT_USED(cert_id);

    return(NX_NOT_SUPPORTED);
#endif /* NX_SECURE_ENABLE_DTLS && !NX_SECURE_DISABLE_X509 */
}

