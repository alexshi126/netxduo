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
/*    _nx_secure_tls_shutdown                             PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function cleans up and/or deletes the various control data     */
/*    structures for the TLS component.                                   */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Shutdown success/fail         */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_mutex_delete                       Delete TLS protection mutex   */
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
UINT _nx_secure_tls_shutdown(VOID)
{
UINT status;

    /* _nx_secure_tls_session_delete updates the linked list of sessions so
       continue to delete all sessions until the created pointer is NULL. */
    while (_nx_secure_tls_created_ptr)
    {       
        /* Delete the head session. */
        _nx_secure_tls_session_delete(_nx_secure_tls_created_ptr);
    }

    /* Clear out the created TLS instance variables. */
    _nx_secure_tls_created_count = 0;

    /* Delete the internal TLS protection mutex. */
    status = tx_mutex_delete(&_nx_secure_tls_protection);

    return(status);
}

