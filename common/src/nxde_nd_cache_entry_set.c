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
/**   Neighbor Discovery Cache                                            */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_nd_cache.h"
#ifdef FEATURE_NX_IPV6
#include "nx_ip.h"
#include "nx_ipv6.h"

/* Bring in externs for caller checking code.  */
NX_CALLER_CHECKING_EXTERNS


#endif /* FEATURE_NX_IPV6 */


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxde_ipv6_nd_cache_entry_set                       PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function performs error checking for the service that adds an  */
/*    IPv6-MAC mapped entry to the neighbor discovery cache.              */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                Pointer to the IP instance    */
/*    dest_ip                               Pointer to the IP address     */
/*                                            to add (map)                */
/*    interface_index                       Index to the network          */
/*                                            interface                   */
/*    mac                                   Pointer to the MAC address to */
/*                                            be added (map)              */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nxd_nd_cache_entry_set               Actual function to add an     */
/*                                             entry to the cache.        */
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
UINT _nxde_nd_cache_entry_set(NX_IP *ip_ptr, ULONG *dest_ip, UINT interface_index, CHAR *mac)
{
#ifdef FEATURE_NX_IPV6

    /* Check for validate user input. */
    if ((ip_ptr == NX_NULL) || (ip_ptr -> nx_ip_id != NX_IP_ID) || (dest_ip == NX_NULL) || (mac == NX_NULL))
    {
        return(NX_PTR_ERROR);
    }

    /* Validate the interface. */
    if (interface_index >= NX_MAX_PHYSICAL_INTERFACES)
    {
        return(NX_INVALID_INTERFACE);
    }

    /* Check for appropriate caller.  */
    NX_INIT_AND_THREADS_CALLER_CHECKING

    /* Call the actual service and return completion status. */
    return(_nxd_nd_cache_entry_set(ip_ptr, dest_ip, interface_index, mac));

#else /* !FEATURE_NX_IPV6 */
    NX_PARAMETER_NOT_USED(ip_ptr);
    NX_PARAMETER_NOT_USED(dest_ip);
    NX_PARAMETER_NOT_USED(interface_index);
    NX_PARAMETER_NOT_USED(mac);

    return(NX_NOT_SUPPORTED);

#endif /* FEATURE_NX_IPV6 */
}

