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
/** NetX Crypto Component                                                 */
/**                                                                       */
/**   Crypto                                                              */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/
/*                                                                        */
/*  COMPONENT DEFINITION                                   RELEASE        */
/*                                                                        */
/*    nx_crypto_port.h                                   Cortex-M3/GNU    */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file contains data type definitions for the NetX Security      */
/*    Encryption component.                                               */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  09-30-2020     Timothy Stapko           Initial Version 6.1           */
/*                                                                        */
/**************************************************************************/

#ifndef _NX_CRYPTO_PORT_H_
#define _NX_CRYPTO_PORT_H_
#include <stdlib.h>
#include <string.h>

#ifdef NX_CRYPTO_STANDALONE_ENABLE

/* Default to little endian, since this is what most ARM targets are.  */
#define NX_CRYPTO_LITTLE_ENDIAN 1

/* Define macros that swap the endian for little endian ports.  */
#if NX_CRYPTO_LITTLE_ENDIAN
#define NX_CRYPTO_CHANGE_ULONG_ENDIAN(arg)       (arg) = __builtin_bswap32(arg)
#define NX_CRYPTO_CHANGE_USHORT_ENDIAN(arg)      (arg) = __builtin_bswap16(arg)
#else
#define NX_CRYPTO_CHANGE_ULONG_ENDIAN(a)
#define NX_CRYPTO_CHANGE_USHORT_ENDIAN(a)
#endif

#ifndef VOID 
#define VOID                                      void
typedef char                                      CHAR;
typedef unsigned char                             UCHAR;
typedef int                                       INT;
typedef unsigned int                              UINT;
typedef long                                      LONG;
typedef unsigned long                             ULONG;
typedef short                                     SHORT;
typedef unsigned short                            USHORT;
#endif

#endif /* NX_CRYPTO_STANDALONE_ENABLE */

#endif /* _NX_CRYPTO_PORT_H_ */
