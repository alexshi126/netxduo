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
/**   Transmission Control Protocol (TCP)                                 */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_tcp.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_tcp_socket_delete                               PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function deletes a previously created socket and unbound       */
/*    socket.  If the socket is still bound, an error is returned.        */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    socket_ptr                            Pointer to TCP socket         */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
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
UINT  _nx_tcp_socket_delete(NX_TCP_SOCKET *socket_ptr)
{

TX_INTERRUPT_SAVE_AREA

NX_IP *ip_ptr;


    /* Setup the pointer to the associated IP instance.  */
    ip_ptr =  socket_ptr -> nx_tcp_socket_ip_ptr;

    /* If trace is enabled, insert this event into the trace buffer.  */
    NX_TRACE_IN_LINE_INSERT(NX_TRACE_TCP_SOCKET_DELETE, ip_ptr, socket_ptr, socket_ptr -> nx_tcp_socket_state, 0, NX_TRACE_TCP_EVENTS, 0, 0);

    /* Obtain the IP mutex so we can process the socket delete request.  */
    tx_mutex_get(&(ip_ptr -> nx_ip_protection), TX_WAIT_FOREVER);

    /* Determine if the socket has been created.  */
    if (socket_ptr -> nx_tcp_socket_id != NX_TCP_ID)
    {

        /* Release the protection mutex.  */
        tx_mutex_put(&(ip_ptr -> nx_ip_protection));

        /* Return a not created error code.  */
        return(NX_NOT_CREATED);
    }

    /* Determine if the socket is still bound to port.  */
    if ((socket_ptr -> nx_tcp_socket_bound_next) ||
        (socket_ptr -> nx_tcp_socket_bind_in_progress) ||
        (socket_ptr -> nx_tcp_socket_state != NX_TCP_CLOSED))
    {

        /* Release the protection mutex.  */
        tx_mutex_put(&(ip_ptr -> nx_ip_protection));

        /* Return a still bound error code.  */
        return(NX_STILL_BOUND);
    }

    /* Disable interrupts.  */
    TX_DISABLE

    /* Now, remove the TCP socket from the created socket list.  */

    /* Clear the socket ID to make it invalid.  */
    socket_ptr -> nx_tcp_socket_id =  0;

    /* See if the socket is the only one on the list.  */
    if (socket_ptr == socket_ptr -> nx_tcp_socket_created_next)
    {

        /* Only created socket, just set the created list to NULL.  */
        ip_ptr -> nx_ip_tcp_created_sockets_ptr =  NX_NULL;
    }
    else
    {

        /* Link-up the neighbors.  */
        (socket_ptr -> nx_tcp_socket_created_next) -> nx_tcp_socket_created_previous =
            socket_ptr -> nx_tcp_socket_created_previous;
        (socket_ptr -> nx_tcp_socket_created_previous) -> nx_tcp_socket_created_next =
            socket_ptr -> nx_tcp_socket_created_next;

        /* See if we have to update the created list head pointer.  */
        if (ip_ptr -> nx_ip_tcp_created_sockets_ptr == socket_ptr)
        {

            /* Yes, move the head pointer to the next link. */
            ip_ptr -> nx_ip_tcp_created_sockets_ptr =  socket_ptr -> nx_tcp_socket_created_next;
        }
    }

    /* Decrease the created sockets count.  */
    ip_ptr -> nx_ip_tcp_created_sockets_count--;

    /* Restore interrupts.  */
    TX_RESTORE

    /* If trace is enabled, unregister this object.  */
    NX_TRACE_OBJECT_UNREGISTER(ip_ptr);

    /* Release the IP protection mutex.  */
    tx_mutex_put(&(ip_ptr -> nx_ip_protection));

    /* Return success.  */
    return(NX_SUCCESS);
}

