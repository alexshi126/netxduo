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
#include "nx_packet.h"


/* Bring in externs for caller checking code.  */

NX_CALLER_CHECKING_EXTERNS


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxe_ip_raw_packet_source_send                      PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in the IP raw packet send           */
/*    function call.                                                      */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ip_ptr                                Pointer to IP control block   */
/*    packet_ptr                            Pointer to packet to send     */
/*    destination_ip                        Destination IP address        */
/*    address_index                         Index of IPv4 or IPv6 address */
/*                                            to use as the source address*/
/*    type_of_service                       Type of service for packet    */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_ip_raw_packet_source_send         Actual IP raw packet send     */
/*                                            function                    */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application                                                         */
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
UINT  _nxe_ip_raw_packet_source_send(NX_IP *ip_ptr, NX_PACKET **packet_ptr_ptr,
                                     ULONG destination_ip, UINT address_index, ULONG type_of_service)
{

#ifndef NX_DISABLE_IPV4
NX_PACKET *packet_ptr;


    /* Setup packet pointer.  */
    packet_ptr =  *packet_ptr_ptr;

    /* Check for invalid input pointers.  */
    /*lint -e{923} suppress cast of ULONG to pointer.  */
    if ((ip_ptr == NX_NULL) || (ip_ptr -> nx_ip_id != NX_IP_ID) ||
        (packet_ptr == NX_NULL) || (packet_ptr -> nx_packet_union_next.nx_packet_tcp_queue_next != ((NX_PACKET *)NX_PACKET_ALLOCATED)))
    {
        return(NX_PTR_ERROR);
    }

    /* Check to see if IP raw packet processing is enabled.  */
    if (!ip_ptr -> nx_ip_raw_ip_processing)
    {
        return(NX_NOT_ENABLED);
    }

    /* Check for invalid IP address.  */
    if (!destination_ip)
    {
        return(NX_IP_ADDRESS_ERROR);
    }

    /* Check for valid type of service.  */
    if (type_of_service & ~(NX_IP_TOS_MASK))
    {
        return(NX_OPTION_ERROR);
    }

    /* Check for an invalid packet prepend pointer.  */
    /*lint -e{946} suppress pointer subtraction, since it is necessary. */
    if ((packet_ptr -> nx_packet_prepend_ptr - sizeof(NX_IPV4_HEADER)) < packet_ptr -> nx_packet_data_start)
    {
        return(NX_UNDERFLOW);
    }

    /* Check for an invalid packet append pointer.  */
    /*lint -e{946} suppress pointer subtraction, since it is necessary. */
    if (packet_ptr -> nx_packet_append_ptr > packet_ptr -> nx_packet_data_end)
    {
        return(NX_OVERFLOW);
    }


    /* Validate the interface index. */
    if (address_index >= NX_MAX_IP_INTERFACES)
    {
        return(NX_INVALID_INTERFACE);
    }

    if (!(ip_ptr -> nx_ip_interface[address_index].nx_interface_valid))
    {
        return(NX_INVALID_INTERFACE);
    }


    /* Check for appropriate caller.  */
    NX_THREADS_ONLY_CALLER_CHECKING

    /* Call actual IP raw packet send function.  */
    _nx_ip_raw_packet_source_send(ip_ptr, packet_ptr, destination_ip, address_index, type_of_service);

    /* Now clear the application's packet pointer so it can't be accidentally
        used again by the application.  This is only done when error checking is
        enabled.  */
    *packet_ptr_ptr =  NX_NULL;

    /* Return completion status.  */
    return(NX_SUCCESS);
#else /* NX_DISABLE_IPV4  */
    NX_PARAMETER_NOT_USED(ip_ptr);
    NX_PARAMETER_NOT_USED(packet_ptr_ptr);
    NX_PARAMETER_NOT_USED(destination_ip);
    NX_PARAMETER_NOT_USED(address_index);
    NX_PARAMETER_NOT_USED(type_of_service);

    return(NX_NOT_SUPPORTED);
#endif /* !NX_DISABLE_IPV4  */
}

