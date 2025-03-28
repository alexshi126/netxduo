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
/**   Internet Group Management Protocol (IGMP)                           */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_ip.h"
#include "nx_igmp.h"

/* Bring in externs for caller checking code.  */
NX_CALLER_CHECKING_EXTERNS


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxe_igmp_info_get                                  PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in the IGMP information get         */
/*    function call.                                                      */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                IP instance pointer           */
/*    igmp_reports_sent                     Destination for the number    */
/*                                            of IGMP reports sent        */
/*    igmp_queries_received                 Destination for the number    */
/*                                            of IGMP queries received    */
/*    igmp_checksum_errors                  Destination for the number    */
/*                                            of IGMP checksum errors     */
/*    current_groups_joined                 Destination for the number    */
/*                                            of IGMP multicast groups    */
/*                                            currently joined            */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_igmp_info_get                     Actual IGMP information get   */
/*                                            function                    */
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
UINT  _nxe_igmp_info_get(NX_IP *ip_ptr, ULONG *igmp_reports_sent, ULONG *igmp_queries_received,
                         ULONG *igmp_checksum_errors, ULONG *current_groups_joined)
{

#ifndef NX_DISABLE_IPV4
UINT status;


    /* Check for invalid input pointers.  */
    if ((ip_ptr == NX_NULL) || (ip_ptr -> nx_ip_id != NX_IP_ID))
    {
        return(NX_PTR_ERROR);
    }

    /* Check to see if IGMP is enabled.  */
    if (!ip_ptr -> nx_ip_igmp_packet_receive)
    {
        return(NX_NOT_ENABLED);
    }

    /* Check for appropriate caller.  */
    NX_INIT_AND_THREADS_CALLER_CHECKING

    /* Call actual IGMP information get function.  */
    status =  _nx_igmp_info_get(ip_ptr, igmp_reports_sent, igmp_queries_received,
                                igmp_checksum_errors, current_groups_joined);

    /* Return completion status.  */
    return(status);
#else /* NX_DISABLE_IPV4  */
    NX_PARAMETER_NOT_USED(ip_ptr);
    NX_PARAMETER_NOT_USED(igmp_reports_sent);
    NX_PARAMETER_NOT_USED(igmp_queries_received);
    NX_PARAMETER_NOT_USED(igmp_checksum_errors);
    NX_PARAMETER_NOT_USED(current_groups_joined);

    return(NX_NOT_SUPPORTED);
#endif /* !NX_DISABLE_IPV4  */
}

