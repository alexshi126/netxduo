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
/*    _nx_secure_tls_local_certificate_find               PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function finds a local certificate based upon its Common Name  */
/*    field in the certificate's Subject section.                         */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    tls_session                           Pointer to TLS Session        */
/*    certificate                           Return certificate pointer    */
/*    common_name                           Certificate Common Name       */
/*    name_length                           Length of Common Name         */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_x509_certificate_list_find                               */
/*                                          Find certificate in local     */
/*                                            store by name               */
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
/*  04-02-2021     Timothy Stapko           Modified comment(s),          */
/*                                            updated X.509 return value, */
/*                                            resulting in version 6.1.6  */
/*  03-08-2023     Yanwu Cai                Modified comment(s),          */
/*                                            fixed compiler errors when  */
/*                                            x509 is disabled,           */
/*                                            resulting in version 6.2.1  */
/*                                                                        */
/**************************************************************************/
UINT  _nx_secure_tls_local_certificate_find(NX_SECURE_TLS_SESSION *tls_session,
                                            NX_SECURE_X509_CERT **certificate, UCHAR *common_name,
                                            UINT name_length)
{
#ifndef NX_SECURE_DISABLE_X509
UINT                              status;
NX_SECURE_X509_CERT              *list_head;
NX_SECURE_X509_CERTIFICATE_STORE *store;
NX_SECURE_X509_DISTINGUISHED_NAME name;

    /* Get the remote certificate store from our TLS session. */
    store = &tls_session -> nx_secure_tls_credentials.nx_secure_tls_certificate_store;

    /* Get the first certificate in the local store. */
    list_head = store -> nx_secure_x509_local_certificates;

    /* Set up the distinguished name - the find call below only uses the Common Name field to match
       certificates so it's ok if we only fill in the Common Name here. Also, the Distinguished Name
       is only used in this function's context, so it should be OK that we are assigning the pointer
       common_name instead of copying the string data. */
    name.nx_secure_x509_common_name = common_name;
    name.nx_secure_x509_common_name_length = (USHORT)name_length;

    /* Find the certificate using it's name. */
    status = _nx_secure_x509_certificate_list_find(&list_head, &name, 0, certificate);

    /* Translate some X.509 return values into TLS return values. */
    if (status == NX_SECURE_X509_CERTIFICATE_NOT_FOUND)
    {
        return(NX_SECURE_TLS_CERTIFICATE_NOT_FOUND);
    }

    /* Return completion status.  */
    return(status);
#else
    NX_PARAMETER_NOT_USED(tls_session);
    NX_PARAMETER_NOT_USED(certificate);
    NX_PARAMETER_NOT_USED(common_name);
    NX_PARAMETER_NOT_USED(name_length);

    return(NX_NOT_SUPPORTED);
#endif
}

