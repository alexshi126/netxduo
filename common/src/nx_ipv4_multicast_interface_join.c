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


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_ipv4_multicast_interface_join                   PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function handles the request to join the specified multicast   */
/*    group on a specified network device.  This function notifies the    */
/*    IP layer to receive on the multicast group address.  However it     */
/*    does not invoke IGMP group membership report messages.              */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                IP instance pointer           */
/*    group_address                         Multicast group to join       */
/*    interface_index                       Index to the interface        */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_igmp_multicast_interface_join_internal                          */
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
UINT  _nx_ipv4_multicast_interface_join(NX_IP *ip_ptr, ULONG group_address, UINT interface_index)
{

#ifndef NX_DISABLE_IPV4
    return(_nx_igmp_multicast_interface_join_internal(ip_ptr, group_address, interface_index, NX_WAIT_FOREVER));
#else /* NX_DISABLE_IPV4  */
    NX_PARAMETER_NOT_USED(ip_ptr);
    NX_PARAMETER_NOT_USED(group_address);
    NX_PARAMETER_NOT_USED(interface_index);

    return(NX_NOT_SUPPORTED);
#endif /* !NX_DISABLE_IPV4  */
}

