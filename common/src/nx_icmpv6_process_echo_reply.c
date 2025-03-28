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
/**   Internet Control Message Protocol (ICMP)                            */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "tx_thread.h"
#include "nx_packet.h"
#include "nx_ipv6.h"
#include "nx_icmpv6.h"

#ifdef NX_IPSEC_ENABLE
#include "nx_ipsec.h"
#endif /* NX_IPSEC_ENABLE */


#ifdef FEATURE_NX_IPV6



/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_icmpv6_process_echo_reply                       PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processes incoming echo reply message.  It matches    */
/*    the thread that has pending echo request, and unblocks the thread.  */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                IP stack instance             */
/*    packet_ptr                            The echo reply packet         */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_packet_release                   Release packet back to pool    */
/*    _tx_thread_system_resume             Resume the specified thread    */
/*    _tx_thread_system_preempt_check      Check for preemption           */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _nx_icmpv6_packet_process            Main ICMPv6 packet handler     */
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

VOID _nx_icmpv6_process_echo_reply(NX_IP *ip_ptr, NX_PACKET *packet_ptr)
{
TX_INTERRUPT_SAVE_AREA

NX_IPV6_HEADER *ipv6_header;
USHORT          sequence_num;
ULONG           suspended;
TX_THREAD      *thread_ptr;
NX_ICMPV6_ECHO *echo_ptr;


    /* Add debug information. */
    NX_PACKET_DEBUG(__FILE__, __LINE__, packet_ptr);

#ifndef NX_DISABLE_RX_SIZE_CHECKING
    /* Check packet length. */
    if (packet_ptr -> nx_packet_length < sizeof(NX_ICMPV6_ECHO))
    {
#ifndef NX_DISABLE_ICMP_INFO

        /* Increment the ICMP invalid message count.  */
        ip_ptr -> nx_ip_icmp_invalid_packets++;
#endif

        /* Invalid ICMP message, just release it.  */
        _nx_packet_release(packet_ptr);
        return;
    }
#endif /* NX_DISABLE_RX_SIZE_CHECKING */

    /* Points to the IPv6 header. */
    /*lint -e{927} -e{826} suppress cast of pointer to pointer, since it is necessary  */
    ipv6_header = (NX_IPV6_HEADER *)packet_ptr -> nx_packet_ip_header;

    /* Points to the ICMP echo reply message body. */
    /*lint -e{927} -e{826} suppress cast of pointer to pointer, since it is necessary  */
    echo_ptr = (NX_ICMPV6_ECHO *)packet_ptr -> nx_packet_prepend_ptr;
#ifndef NX_DISABLE_ICMP_INFO

    /* Increment the ICMP responses received count.  */
    ip_ptr -> nx_ip_ping_responses_received++;
#endif

    /* Discard the packet if source address is unspecified (::). */
    if (CHECK_UNSPECIFIED_ADDRESS(ipv6_header -> nx_ip_header_source_ip))
    {

#ifndef NX_DISABLE_ICMP_INFO

        /* Increment the ICMP invalid packet error. */
        ip_ptr -> nx_ip_icmp_invalid_packets++;
#endif /* NX_DISABLE_ICMP_INFO */

        /* Free the packet and return. */
        _nx_packet_release(packet_ptr);

        return;
    }

    /* For IPv6, if the interface IP address is not valid yet,
       do not respond to ping. */
    if (packet_ptr -> nx_packet_address.nx_packet_ipv6_address_ptr -> nxd_ipv6_address_state != NX_IPV6_ADDR_STATE_VALID)
    {


#ifndef NX_DISABLE_ICMP_INFO

        /* Increment the ICMP invalid packet error. */
        ip_ptr -> nx_ip_icmp_invalid_packets++;
#endif /* NX_DISABLE_ICMP_INFO */

        /* Free the packet and return. */
        _nx_packet_release(packet_ptr);

        return;
    }

    /* Pickup sequence number.  */
    sequence_num = echo_ptr -> nx_icmpv6_echo_sequence_num;

    /* Convert to host byte order, if little endian taget. */
    NX_CHANGE_USHORT_ENDIAN(sequence_num);

    /* Disable interrupts.  */
    TX_DISABLE

    /* Pickup the head pointer and the suspended count.  */
    thread_ptr =  ip_ptr -> nx_ip_icmp_ping_suspension_list;
    suspended =   ip_ptr -> nx_ip_icmp_ping_suspended_count;

    /* Temporarily disable preemption.  */
    _tx_thread_preempt_disable++;

    /* Restore interrupts.  */
    TX_RESTORE

    /* Search through the suspended threads waiting for a ECHO (ping) response
       in an attempt to find a matching sequence number.  */
    while (suspended--)
    {

        /* Determine if the sequence number matches a suspended thread.  */
        if (thread_ptr -> tx_thread_suspend_info == sequence_num)
        {

            /* Disable interrupts.  */
            TX_DISABLE

            /* See if this is the only suspended thread on the list.  */
            if (thread_ptr == thread_ptr -> tx_thread_suspended_next)
            {

                /* Yes, the only suspended thread.  */

                /* Update the head pointer.  */
                ip_ptr -> nx_ip_icmp_ping_suspension_list =  NX_NULL;
            }
            else
            {

                /* At least one more thread is on the same expiration list.  */

                /* Update the list head pointer.  */
                if (ip_ptr -> nx_ip_icmp_ping_suspension_list == thread_ptr)
                {
                    ip_ptr -> nx_ip_icmp_ping_suspension_list =  thread_ptr -> tx_thread_suspended_next;
                }

                /* Update the links of the adjacent threads.  */
                (thread_ptr -> tx_thread_suspended_next) -> tx_thread_suspended_previous =
                    thread_ptr -> tx_thread_suspended_previous;
                (thread_ptr -> tx_thread_suspended_previous) -> tx_thread_suspended_next =
                    thread_ptr -> tx_thread_suspended_next;
            }

            /* Decrement the suspension count.  */
            ip_ptr -> nx_ip_icmp_ping_suspended_count--;

            /* Prepare for resumption of the first thread.  */

            /* Clear cleanup routine to avoid timeout.  */
            thread_ptr -> tx_thread_suspend_cleanup =  TX_NULL;

            /* Temporarily disable preemption.  */
            _tx_thread_preempt_disable++;

            /* Restore interrupts.  */
            TX_RESTORE

            /* Adjust this packet to remove the ICMP header that is still in front of
               the response message.  */
            packet_ptr -> nx_packet_length      = packet_ptr -> nx_packet_length - (ULONG)sizeof(NX_ICMPV6_ECHO);
            packet_ptr -> nx_packet_prepend_ptr = packet_ptr -> nx_packet_prepend_ptr + sizeof(NX_ICMPV6_ECHO);

            /* Return this block pointer to the suspended thread waiting for
               a block.  */
            *((NX_PACKET **)thread_ptr -> tx_thread_additional_suspend_info) = packet_ptr;

            /* Add debug information. */
            NX_PACKET_DEBUG(__FILE__, __LINE__, packet_ptr);

            /* Clear packet pointer so we don't try to release it below.  */
            packet_ptr =  NX_NULL;

            /* Put return status into the thread control block.  */
            thread_ptr -> tx_thread_suspend_status = NX_SUCCESS;

            /* Resume thread.  */
            _tx_thread_system_resume(thread_ptr);

            /* Get out of the loop.  */
            break;
        }
        else
        {
            /* Just move to the next suspended thread.  */
            thread_ptr =  thread_ptr -> tx_thread_suspended_next;
        }
    }

    /* Determine if no match was made and we just have to release the packet.  */
    if (packet_ptr)
    {

#ifndef NX_DISABLE_ICMP_INFO

        /* Increment the ICMP invalid packet error. */
        ip_ptr -> nx_ip_icmp_invalid_packets++;
#endif /* NX_DISABLE_ICMP_INFO */

        /* Yes, just release the packet.  */
        _nx_packet_release(packet_ptr);
    }

    /* Disable interrupts.  */
    TX_DISABLE

    /* Release preemption disable.  */
    _tx_thread_preempt_disable--;

    /* Restore interrupts.  */
    TX_RESTORE

    /* Check for preemption.  */
    _tx_thread_system_preempt_check();
}


#endif /* FEATURE_NX_IPV6 */

