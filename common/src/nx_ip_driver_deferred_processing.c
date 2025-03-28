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


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_ip_driver_deferred_processing                   PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function causes the driver to be called from the IP helper     */
/*    thread in order to finish some deferred processing. A typical       */
/*    example of this is the transmit complete interrupt. Instead of      */
/*    loading the packet inside the transmit complete interrupt, the      */
/*    driver can setup some internal variables and call this routine      */
/*    to be called subsequently from the IP helper thread to finish       */
/*    the transmit complete interrupt processing.                         */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                Pointer to IP control block   */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_event_flags_set                    Set event flags to wake IP    */
/*                                            helper thread               */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Driver                                                  */
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
VOID  _nx_ip_driver_deferred_processing(NX_IP *ip_ptr)
{

    /* Set event flags to wake the IP helper thread, which will in turn
       call the driver with the NX_LINK_DEFERRED_PROCESSING command.  */
    tx_event_flags_set(&(ip_ptr -> nx_ip_events), NX_IP_DRIVER_DEFERRED_EVENT, TX_OR);
}

