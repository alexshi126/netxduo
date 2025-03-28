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
#ifdef FEATURE_NX_IPV6
#include "nx_ip.h"
#include "nx_ipv6.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_ipv6_multicast_leave                            PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    Leave IPv6 multicast group. This is an internal function.  The      */
/*    caller must hold the IP protection (mutex).                         */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                IP instance pointer           */
/*    multicast_address                     IPv6 multicast address        */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_mutex_get                          Obtain protection mutex       */
/*    tx_mutex_put                          Release protection mutex      */
/*    (ip_link_driver)                      Device driver entry point     */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _nxd_ipv6_address_delete                                            */
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
UINT _nx_ipv6_multicast_leave(NX_IP *ip_ptr, ULONG *multicast_addr, NX_INTERFACE *nx_interface)
{

NX_IP_DRIVER driver_request;


    /* Construct a driver command. */
    driver_request.nx_ip_driver_ptr = ip_ptr;
    driver_request.nx_ip_driver_command = NX_LINK_MULTICAST_LEAVE;
    driver_request.nx_ip_driver_physical_address_msw = 0x00003333;
    driver_request.nx_ip_driver_physical_address_lsw = multicast_addr[3];
    driver_request.nx_ip_driver_interface = nx_interface;

    /* Obtain the IP mutex so we can search the multicast join list.  */
    tx_mutex_get(&(ip_ptr -> nx_ip_protection), TX_WAIT_FOREVER);


    /* Call the device driver with the driver request. */
    (nx_interface -> nx_interface_link_driver_entry)(&driver_request);

    /* Release the protection over the IP instance.  */
    tx_mutex_put(&(ip_ptr -> nx_ip_protection));

    /*lint -e{644} suppress variable might not be initialized, since "nx_ip_driver_status" was initialized in nx_interface_link_driver_entry. */
    return(driver_request.nx_ip_driver_status);
}
#endif /* FEATURE_NX_IPV6 */

