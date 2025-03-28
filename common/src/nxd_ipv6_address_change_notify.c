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
#include "nx_ipv6.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxd_ipv6_address_change_notify                     PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function registers an application callback routine that NetX   */
/*    Duo calls whenever the IPv6 Address is changed.                     */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                IP control block pointer      */
/*    ip_address_change_notify              Application callback function */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_mutex_get                          Get protection mutex          */
/*    tx_mutex_put                          Put protection mutex          */
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
UINT  _nxd_ipv6_address_change_notify(NX_IP *ip_ptr, VOID (*ip_address_change_notify)(NX_IP *ip_ptr, UINT status, UINT interface_index, UINT address_index, ULONG *ip_address))
{

#if defined(NX_ENABLE_IPV6_ADDRESS_CHANGE_NOTIFY) && defined(FEATURE_NX_IPV6)
TX_INTERRUPT_SAVE_AREA


    /* If trace is enabled, insert this event into the trace buffer.  */
    NX_TRACE_IN_LINE_INSERT(NXD_TRACE_IPV6_ADDRESS_CHANGE_NOTIFY, ip_ptr, ip_address_change_notify, 0, 0, NX_TRACE_IP_EVENTS, 0, 0);

    /* Get mutex protection.  */
    tx_mutex_get(&(ip_ptr -> nx_ip_protection), TX_WAIT_FOREVER);

    /* Disable interrupts.  */
    TX_DISABLE

    /* Setup the IP address change callback function and the additional information pointers. */
    ip_ptr -> nx_ipv6_address_change_notify =  ip_address_change_notify;

    /* Restore interrupts.  */
    TX_RESTORE

    /* Release mutex protection.  */
    tx_mutex_put(&(ip_ptr -> nx_ip_protection));

    /* Return completion status.  */
    return(NX_SUCCESS);

#else
    NX_PARAMETER_NOT_USED(ip_ptr);
    NX_PARAMETER_NOT_USED(ip_address_change_notify);

    return(NX_NOT_SUPPORTED);

#endif /* NX_ENABLE_IPV6_ADDRESS_CHANGE_NOTIFY && FEATURE_NX_IPV6 */
}

