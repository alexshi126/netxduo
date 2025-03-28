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
/**   User Datagram Protocol (UDP)                                        */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_ip.h"
#include "nx_udp.h"


/* Bring in externs for caller checking code.  */

NX_CALLER_CHECKING_EXTERNS

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxe_udp_info_get                                   PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in the UDP information get          */
/*    function call.                                                      */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                Pointer to IP control block   */
/*    udp_packets_sent                      Destination to the number of  */
/*                                            packets sent                */
/*    udp_bytes_sent                        Destination to the number of  */
/*                                            bytes sent                  */
/*    udp_packets_received                  Destination to the number of  */
/*                                            packets received            */
/*    udp_bytes_received                    Destination to the number of  */
/*                                            bytes received              */
/*    udp_invalid_packets                   Destination to the number of  */
/*                                            invalid packets             */
/*    udp_receive_packets_dropped           Destination to the number of  */
/*                                            receive packets dropped     */
/*    udp_checksum_errors                   Destination to the number of  */
/*                                            checksum errors             */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_udp_info_get                      Actual UDP information get    */
/*                                            function                    */
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
UINT  _nxe_udp_info_get(NX_IP *ip_ptr, ULONG *udp_packets_sent, ULONG *udp_bytes_sent,
                        ULONG *udp_packets_received, ULONG *udp_bytes_received,
                        ULONG *udp_invalid_packets, ULONG *udp_receive_packets_dropped,
                        ULONG *udp_checksum_errors)
{

UINT status;


    /* Check for invalid input pointers.  */
    if ((ip_ptr == NX_NULL) || (ip_ptr -> nx_ip_id != NX_IP_ID))
    {
        return(NX_PTR_ERROR);
    }

    /* Check to see if UDP is enabled.  */
    if (!ip_ptr -> nx_ip_udp_packet_receive)
    {
        return(NX_NOT_ENABLED);
    }

    /* Check for appropriate caller.  */
    NX_NOT_ISR_CALLER_CHECKING

    /* Call actual UDP information get function.  */
    status =  _nx_udp_info_get(ip_ptr, udp_packets_sent, udp_bytes_sent, udp_packets_received,
                               udp_bytes_received, udp_invalid_packets, udp_receive_packets_dropped,
                               udp_checksum_errors);

    /* Return completion status.  */
    return(status);
}

