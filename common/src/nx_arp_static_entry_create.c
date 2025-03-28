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
/**   Address Resolution Protocol (ARP)                                   */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_arp.h"
#include "nx_ip.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_arp_static_entry_create                         PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function dynamically allocates an ARP entry for the application*/
/*    to make a static IP to hardware mapping.                            */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                IP instance pointer           */
/*    ip_address                            IP Address to bind to         */
/*    physical_msw                          Physical address MSW          */
/*    physical_lsw                          Physical address LSW          */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_ip_route_find                     Find suitable outgoing        */
/*                                            interface                   */
/*    _nx_arp_entry_allocate                Allocate an ARP entry         */
/*    _nx_arp_queue_send                    Send the queued packet        */
/*    tx_mutex_get                          Obtain protection mutex       */
/*    tx_mutex_put                          Release protection mutex      */
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
UINT  _nx_arp_static_entry_create(NX_IP *ip_ptr, ULONG ip_address,
                                  ULONG physical_msw, ULONG physical_lsw)
{

#ifndef NX_DISABLE_IPV4
TX_INTERRUPT_SAVE_AREA
NX_ARP       *arp_ptr;
NX_ARP       *search_ptr;
NX_ARP       *arp_list_head;
UINT          index;
UINT          status;
NX_INTERFACE *nx_interface = NX_NULL;
ULONG         next_hop_address;

    /* If trace is enabled, insert this event into the trace buffer.  */
    NX_TRACE_IN_LINE_INSERT(NX_TRACE_ARP_STATIC_ENTRY_CREATE, ip_ptr, ip_address, physical_msw, physical_lsw, NX_TRACE_ARP_EVENTS, 0, 0);

    /* Make sure the destination address is directly accessible. */
    if (_nx_ip_route_find(ip_ptr, ip_address, &nx_interface, &next_hop_address) != NX_SUCCESS)
    {

        return(NX_IP_ADDRESS_ERROR);
    }

    /*lint -e{644} suppress variable might not be initialized, since "next_hop_address" was initialized in _nx_ip_route_find. */
    if (next_hop_address != ip_address)
    {

        return(NX_IP_ADDRESS_ERROR);
    }

    /* Obtain protection on this IP instance for access into the ARP dynamic
       list.  */
    tx_mutex_get(&(ip_ptr -> nx_ip_protection), TX_WAIT_FOREVER);

    /* Calculate the hash index for the specified IP address.  */
    index =  (UINT)((ip_address + (ip_address >> 8)) & NX_ARP_TABLE_MASK);

    /* Pickup the head pointer of the ARP entries for this IP instance.  */
    arp_list_head =  ip_ptr -> nx_ip_arp_table[index];

    /* Search the ARP list for the same IP address.  */
    search_ptr =  arp_list_head;
    arp_ptr =     NX_NULL;
    while (search_ptr)
    {

        /* Determine if there is a duplicate IP address.  */
        if (search_ptr -> nx_arp_ip_address == ip_address)
        {

            /* Yes, the IP address matches, setup the ARP entry pointer.  */
            arp_ptr =  search_ptr;

            /* Get out of the loop.  */
            break;
        }

        /* Move to the next entry in the active list.  */
        search_ptr =  search_ptr -> nx_arp_active_next;

        /* Determine if the search pointer is back at the head of
           the list.  */
        if (search_ptr == arp_list_head)
        {

            /* End of the ARP list, end the search.  */
            break;
        }
    }

    /* Determine if we find an ARP entry.  */
    if (arp_ptr)
    {

        /* Determine if this is a static entry. */
        if (arp_ptr -> nx_arp_route_static == NX_FALSE)
        {

            /* Disable interrupts temporarily.  */
            TX_DISABLE

            /* Remove this entry from the ARP dynamic list.  */

            /* Determine if this is the only ARP entry on the dynamic list.  */
            if (arp_ptr == arp_ptr -> nx_arp_pool_next)
            {

                /* Remove the sole entry from the dynamic list head.  */
                ip_ptr -> nx_ip_arp_dynamic_list =  NX_NULL;
            }
            else
            {

                /* Remove the entry from a list of more than one entry.  */

                /* Update the links of the adjacent ARP dynamic pool entries.  */
                (arp_ptr -> nx_arp_pool_next) -> nx_arp_pool_previous = arp_ptr -> nx_arp_pool_previous;
                (arp_ptr -> nx_arp_pool_previous) -> nx_arp_pool_next = arp_ptr -> nx_arp_pool_next;

                /* Update the list head pointer.  */
                if (ip_ptr -> nx_ip_arp_dynamic_list == arp_ptr)
                {
                    ip_ptr -> nx_ip_arp_dynamic_list =  arp_ptr -> nx_arp_pool_next;
                }
            }

            /* Decrement the number of active dynamic entries.  */
            ip_ptr -> nx_ip_arp_dynamic_active_count--;

            /* Add the entry to the ARP static list.  */

            /* Determine if the ARP static list is empty.  */
            if (ip_ptr -> nx_ip_arp_static_list == NX_NULL)
            {

                /* Just place this single ARP entry on the list.  */
                arp_ptr -> nx_arp_pool_next =     arp_ptr;
                arp_ptr -> nx_arp_pool_previous = arp_ptr;
                ip_ptr -> nx_ip_arp_static_list = arp_ptr;
            }
            else
            {

                /* Add to the end of the ARP static list.  */
                arp_ptr -> nx_arp_pool_next = ip_ptr -> nx_ip_arp_static_list;
                arp_ptr -> nx_arp_pool_previous = (ip_ptr -> nx_ip_arp_static_list) -> nx_arp_pool_previous;
                ((ip_ptr -> nx_ip_arp_static_list) -> nx_arp_pool_previous) -> nx_arp_pool_next = arp_ptr;
                (ip_ptr -> nx_ip_arp_static_list) -> nx_arp_pool_previous = arp_ptr;
            }

            /* Restore interrupts.  */
            TX_RESTORE

#ifndef NX_DISABLE_ARP_INFO
            /* Increment the ARP static entry count.  */
            ip_ptr -> nx_ip_arp_static_entries++;
#endif
        }
    }
    /* Determine if we didn't find an ARP entry and need to allocate a new
       static entry.  */
    else
    {

        /* No matching IP address in the ARP cache.  */

        /* Allocate a static ARP entry.  */
        status =  _nx_arp_entry_allocate(ip_ptr, &(ip_ptr -> nx_ip_arp_table[index]), NX_TRUE);

        /* Determine if an error occurred.  */
        if (status != NX_SUCCESS)
        {

            /* Release the mutex.  */
            tx_mutex_put(&(ip_ptr -> nx_ip_protection));

            /* Return the error status.  */
            return(status);
        }

        /* Otherwise, setup a pointer to the new ARP entry.  The newly allocated
           ARP entry was allocated at the end of the ARP list so it should be
           referenced using the previous pointer from the list head.  */
        arp_ptr =  (ip_ptr -> nx_ip_arp_table[index]) -> nx_arp_active_previous;
    }

    /* Indicate the entry does not need updating.  */
    arp_ptr -> nx_arp_entry_next_update =  0;

    /* Place the important information in the ARP structure.  */
    arp_ptr -> nx_arp_route_static =          NX_TRUE;
    arp_ptr -> nx_arp_ip_address =            ip_address;
    arp_ptr -> nx_arp_physical_address_msw =  physical_msw;
    arp_ptr -> nx_arp_physical_address_lsw =  physical_lsw;

    /*lint -e{644} suppress variable might not be initialized, since "nx_interface" was initialized in _nx_ip_route_find. */
    arp_ptr -> nx_arp_ip_interface =          nx_interface;

    /* Call queue send function to send the packet queued up, if the original entry is dynamic entry.  */
    _nx_arp_queue_send(ip_ptr, arp_ptr);

    /* Release the protection on the ARP list.  */
    tx_mutex_put(&(ip_ptr -> nx_ip_protection));

    /* Return status to the caller.  */
    return(NX_SUCCESS);
#else /* NX_DISABLE_IPV4  */
    NX_PARAMETER_NOT_USED(ip_ptr);
    NX_PARAMETER_NOT_USED(ip_address);
    NX_PARAMETER_NOT_USED(physical_msw);
    NX_PARAMETER_NOT_USED(physical_lsw);

    return(NX_NOT_SUPPORTED);
#endif /* !NX_DISABLE_IPV4  */
}

