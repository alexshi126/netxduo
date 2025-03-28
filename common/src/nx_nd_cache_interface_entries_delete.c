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
/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_nd_cache_interface_entries_delete               PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function deletes entries associated with a specified interface */
/*    in the ND cache table.                                              */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                               Pointer to IP instance         */
/*    index                                 IP interface index            */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                               Completion status              */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_mutex_get                          Obtain protection mutex       */
/*    tx_mutex_put                          Release protection mutex      */
/*    _nx_nd_cache_delete_internal          Actual function to remove an  */
/*                                            entry from the cache.       */
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
UINT _nx_nd_cache_interface_entries_delete(NX_IP *ip_ptr, UINT index)
{

NX_INTERFACE *interface_ptr;
UINT          i;

    interface_ptr = &(ip_ptr -> nx_ip_interface[index]);

    for (i = 0; i < NX_IPV6_NEIGHBOR_CACHE_SIZE; i++)
    {
        if (ip_ptr -> nx_ipv6_nd_cache[i].nx_nd_cache_interface_ptr == interface_ptr)
        {

            _nx_nd_cache_delete_internal(ip_ptr, &ip_ptr -> nx_ipv6_nd_cache[i]);
        }
    }

    return(NX_SUCCESS);
}
#endif /* FEATURE_NX_IPV6 */

