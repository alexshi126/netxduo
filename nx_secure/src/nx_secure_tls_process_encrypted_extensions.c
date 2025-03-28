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

#if (NX_SECURE_TLS_TLS_1_3_ENABLED)
/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_secure_tls_process_encrypted_extensions         PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processes the encrypted extensions received after a   */
/*    ServerHello message in a TLS 1.3 encrypted handshake.               */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    tls_session                           TLS control block             */
/*    packet_buffer                         Pointer to message data       */
/*    message_length                        Length of message data (bytes)*/
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_secure_tls_ciphersuite_lookup     Lookup current ciphersuite    */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _nx_secure_tls_server_handshake       Process extensions            */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Timothy Stapko           Initial Version 6.0           */
/*  09-30-2020     Timothy Stapko           Modified comment(s), update   */
/*                                            ciphersuite lookup method,  */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/
UINT _nx_secure_tls_process_encrypted_extensions(NX_SECURE_TLS_SESSION *tls_session,
                                                 UCHAR *packet_buffer, UINT message_length)
{
UINT status;

    status = NX_SUCCESS;

    /* Process encrypted extensions here! */
    NX_PARAMETER_NOT_USED(packet_buffer);
    NX_PARAMETER_NOT_USED(message_length);

#ifndef NX_SECURE_TLS_CLIENT_DISABLED

    /* Set our state to indicate we successfully parsed the Certificate message. */
    tls_session -> nx_secure_tls_client_state = NX_SECURE_TLS_CLIENT_STATE_ENCRYPTED_EXTENSIONS;
#else
    NX_PARAMETER_NOT_USED(tls_session);
#endif


    return(status);
}
#endif

