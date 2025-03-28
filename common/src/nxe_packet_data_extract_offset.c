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
/** NetX Component                                                        */
/**                                                                       */
/**   Internet Protocol (IP)                                              */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_ip.h"
#include "nx_packet.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxe_packet_data_extract_offset                     PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in the packet data extract          */
/*    function call.                                                      */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    packet_ptr                        Pointer to the source packet      */
/*    buffer_start                      Pointer to destination data area  */
/*    buffer_length                     Size in bytes                     */
/*    bytes_copied                      Number of bytes copied            */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                            Completion status                 */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_packet_data_extract_offset    Acutal packet data extract offset */
/*                                         function                       */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*  09-30-2020     Yuxin Zhou               Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/
UINT  _nxe_packet_data_extract_offset(NX_PACKET *packet_ptr, ULONG offset, VOID *buffer_start, ULONG buffer_length, ULONG *bytes_copied)
{

    if (packet_ptr == NX_NULL)
    {
        return(NX_PTR_ERROR);
    }

    if (buffer_start == NX_NULL)
    {
        return(NX_PTR_ERROR);
    }

    if (bytes_copied == NX_NULL)
    {
        return(NX_PTR_ERROR);
    }


    return(_nx_packet_data_extract_offset(packet_ptr, offset, buffer_start, buffer_length, bytes_copied));
}

