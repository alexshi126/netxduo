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


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxd_ip_raw_packet_send                             PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function sends a raw IP packet through the primary IP          */
/*    interface to the specified destination.                             */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                Pointer to IP control block   */
/*    packet_ptr                            Pointer to packet to send     */
/*    destination_ip                        Destination IP address        */
/*    protocol                              Value for the protocol field  */
/*    ttl                                   Value for ttl or hop limit    */
/*    tos                                   Value for tos or traffic      */
/*                                            class and flow label        */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Actual completion status      */
/*    NX_NOT_ENABLED                        Raw IP processing not enabled */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nxd_ip_raw_packet_source_send        Core raw packet send service  */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application                                                         */
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
UINT  _nxd_ip_raw_packet_send(NX_IP *ip_ptr, NX_PACKET *packet_ptr,
                              NXD_ADDRESS *destination_ip, ULONG protocol, UINT ttl, ULONG tos)
{

UINT status;

    status = _nxd_ip_raw_packet_source_send(ip_ptr, packet_ptr, destination_ip, 0, protocol, ttl, tos);

    return(status);
}

