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
#include "nx_secure_x509.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_secure_tls_trusted_certificate_remove           PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function removes an NX_SECURE_TLS_CERTIFICATE instance from    */
/*    the trusted certificates store, keyed on the Common Name field.     */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    tls_session                           Pointer to TLS Session        */
/*    common_name                           String to match "CN" field    */
/*    common_name_length                    Length of name                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_mutex_get                          Get protection mutex          */
/*    tx_mutex_put                          Put protection mutex          */
/*    _nx_secure_x509_store_certificate_remove                            */
/*                                          Remove certificate from store */
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
UINT _nx_secure_tls_trusted_certificate_remove(NX_SECURE_TLS_SESSION *tls_session,
                                               UCHAR *common_name, UINT common_name_length)
{
#ifndef NX_SECURE_DISABLE_X509
UINT                              status;
NX_SECURE_X509_DISTINGUISHED_NAME name;


    /* Get the protection. */
    tx_mutex_get(&_nx_secure_tls_protection, TX_WAIT_FOREVER);

    /* Set up the distinguished name with the passed-in common name. */
    name.nx_secure_x509_common_name_length = (USHORT)common_name_length;
    name.nx_secure_x509_common_name = common_name;

    /* Remove the certificate from the local certificates list in our TLS control block. */
    status = _nx_secure_x509_store_certificate_remove(&tls_session -> nx_secure_tls_credentials.nx_secure_tls_certificate_store,
                                                      &name, NX_SECURE_X509_CERT_LOCATION_TRUSTED, 0);


    /* Release the protection. */
    tx_mutex_put(&_nx_secure_tls_protection);

    /* Translate some X.509 return values into TLS return values. */
    if (status == NX_SECURE_X509_CERTIFICATE_NOT_FOUND)
    {
        return(NX_SECURE_TLS_CERTIFICATE_NOT_FOUND);
    }

    return(status);
#else
    NX_PARAMETER_NOT_USED(tls_session);
    NX_PARAMETER_NOT_USED(common_name);
    NX_PARAMETER_NOT_USED(common_name_length);

    return(NX_NOT_SUPPORTED);
#endif
}

