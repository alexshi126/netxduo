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
/*    _nxe_secure_dtls_ecc_initialize                     PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors when initializing ECC for DTLS.     */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dtls_session                          DTLS session control block    */
/*    supported_groups                      List of supported groups      */
/*    supported_group_count                 Number of supported groups    */
/*    curves                                List of curve methods         */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_dtls_ecc_initialize        Actual function call          */
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
UINT _nxe_secure_dtls_ecc_initialize(NX_SECURE_DTLS_SESSION *dtls_session,
                                    const USHORT *supported_groups, USHORT supported_group_count,
                                    const NX_CRYPTO_METHOD **curves)
{
#if defined(NX_SECURE_ENABLE_DTLS) && defined(NX_SECURE_ENABLE_ECC_CIPHERSUITE)
UINT status;

    /* Check pointers. */
    if (dtls_session == NX_NULL)
    {
        return(NX_PTR_ERROR);
    }

    if (supported_group_count > 0 &&
        (supported_groups == NX_NULL || curves == NX_NULL))
    {
        return(NX_PTR_ERROR);
    }

    /* Call actual function. */
    status = _nx_secure_dtls_ecc_initialize(dtls_session, supported_groups, supported_group_count, curves);

    return(status);
#else
    NX_PARAMETER_NOT_USED(dtls_session);
    NX_PARAMETER_NOT_USED(supported_groups);
    NX_PARAMETER_NOT_USED(supported_group_count);
    NX_PARAMETER_NOT_USED(curves);

    return(NX_NOT_SUPPORTED);
#endif /* NX_SECURE_ENABLE_DTLS && NX_SECURE_ENABLE_ECC_CIPHERSUITE */
}

