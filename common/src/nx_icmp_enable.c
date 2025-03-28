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
/**   Internet Control Message Protocol (ICMP)                            */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_icmp.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_icmp_enable                                     PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function enables the ICMP management component for the         */
/*    specified IP instance.                                              */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                IP instance pointer           */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
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
UINT  _nx_icmp_enable(NX_IP *ip_ptr)
{

#ifndef NX_DISABLE_IPV4
    /* If trace is enabled, insert this event into the trace buffer.  */
    NX_TRACE_IN_LINE_INSERT(NX_TRACE_ICMP_ENABLE, ip_ptr, 0, 0, 0, NX_TRACE_ICMP_EVENTS, 0, 0);

    /* Setup the ICMP packet queue processing routine.  */
    ip_ptr -> nx_ip_icmp_queue_process =  _nx_icmp_queue_process;

    /* Setup the ICMP packet receiving routine, thereby enabling ICMP traffic.  */
    ip_ptr -> nx_ip_icmp_packet_receive =  _nx_icmp_packet_receive;

    /* Setup the ICMPv4 packet process routine */
    ip_ptr -> nx_ip_icmpv4_packet_process = _nx_icmpv4_packet_process;

    /* Return a successful status!  */
    return(NX_SUCCESS);
#else /* NX_DISABLE_IPV4  */
    NX_PARAMETER_NOT_USED(ip_ptr);

    return(NX_NOT_SUPPORTED);
#endif /* !NX_DISABLE_IPV4  */
}

