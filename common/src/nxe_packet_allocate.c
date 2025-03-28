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
/**   Packet Pool Management (Packet)                                     */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_packet.h"


/* Bring in externs for caller checking code.  */

NX_CALLER_CHECKING_EXTERNS


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxe_packet_allocate                                PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in the packet allocate function     */
/*    call.                                                               */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    pool_ptr                              Pool to allocate the packet   */
/*    packet_ptr                            Pointer to place allocated    */
/*                                            packet pointer              */
/*    packet_type                           Type of packet to allocate    */
/*    wait_option                           Suspension option             */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_packet_allocate                   Actual packet allocate service*/
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
UINT  _nxe_packet_allocate(NX_PACKET_POOL *pool_ptr,  NX_PACKET **packet_ptr,
                           ULONG packet_type, ULONG wait_option)
{

UINT status;


    /* Check for invalid input pointers.  */
    if ((pool_ptr == NX_NULL) || (pool_ptr -> nx_packet_pool_id != NX_PACKET_POOL_ID) || (packet_ptr == NX_NULL))
    {
        return(NX_PTR_ERROR);
    }

    /* Check for an invalid packet type - for alignment purposes, it must be evenly divisible by the size
       of a ULONG.  */
    if (packet_type % sizeof(ULONG))
    {
        return(NX_OPTION_ERROR);
    }

    /* Check for a thread caller if the wait option specifies suspension.  */
    NX_THREAD_WAIT_CALLER_CHECKING

    /* Call actual packet allocate function.  */
    status =  _nx_packet_allocate(pool_ptr,  packet_ptr, packet_type, wait_option);

    /* Return completion status.  */
    return(status);
}

