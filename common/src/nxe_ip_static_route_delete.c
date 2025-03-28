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

#if !defined(NX_DISABLE_IPV4) && defined(NX_ENABLE_IP_STATIC_ROUTING)
/* Bring in externs for caller checking code.  */
NX_CALLER_CHECKING_EXTERNS
#endif /* !NX_DISABLE_IPV4 && NX_ENABLE_IP_STATIC_ROUTING  */

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxe_ip_static_route_delete                         PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function deltes static routing entry from the routing table.   */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                Pointer to IP instance        */
/*    network_address                       network address, in host      */
/*                                            byte order.                 */
/*    net_mask                              Network Mask, in host byte    */
/*                                            order.                      */
/*                                                                        */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_ip_staic_route_delete             Acutal IP static routing      */
/*                                            table delete function.      */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application                                                         */
/*                                                                        */
/*  NOTE:                                                                 */
/*                                                                        */
/*    None                                                                */
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
UINT  _nxe_ip_static_route_delete(NX_IP *ip_ptr, ULONG network_address, ULONG net_mask)
{
#if !defined(NX_DISABLE_IPV4) && defined(NX_ENABLE_IP_STATIC_ROUTING)

UINT status;

    /* Check for invalid input pointers.  */
    if ((ip_ptr == NX_NULL) || (ip_ptr -> nx_ip_id != NX_IP_ID))
    {
        return(NX_PTR_ERROR);
    }

    /* Check for appropriate caller.  */
    NX_INIT_AND_THREADS_CALLER_CHECKING

    /* Call actual IP forwarding disable function.  */
    status =  _nx_ip_static_route_delete(ip_ptr, network_address, net_mask);

    /* Return completion status.  */
    return(status);


#else /* !NX_DISABLE_IPV4 && NX_ENABLE_IP_STATIC_ROUTING  */
    NX_PARAMETER_NOT_USED(ip_ptr);
    NX_PARAMETER_NOT_USED(network_address);
    NX_PARAMETER_NOT_USED(net_mask);

    return(NX_NOT_SUPPORTED);

#endif /* !NX_DISABLE_IPV4 && NX_ENABLE_IP_STATIC_ROUTING  */
}

