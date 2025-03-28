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
#include "tx_timer.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_ip_periodic_timer_entry                         PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function handles waking up the IP helper thread on a periodic  */
/*    basis.  Periodic IP processing includes ARP requests, IP fragment   */
/*    timeouts, and TCP timeouts.  All of which are driven from this      */
/*    single periodic timer.                                              */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_address                            IP address in a ULONG         */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_event_flags_set                    Set event flags to wakeup     */
/*                                            IP helper thread            */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    ThreadX system timer thread                                         */
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
VOID  _nx_ip_periodic_timer_entry(ULONG ip_address)
{

NX_IP *ip_ptr;


    /* Setup IP pointer.  */
    NX_TIMER_EXTENSION_PTR_GET(ip_ptr, NX_IP, ip_address)

    /* Wakeup this IP's helper thread.  */
    tx_event_flags_set(&(ip_ptr -> nx_ip_events), NX_IP_PERIODIC_EVENT, TX_OR);
}

