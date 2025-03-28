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
/**   HMAC SHA1 Digest Algorithm (SHA1)                                   */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#include "nx_crypto_sha1.h"
#include "nx_crypto_hmac_sha1.h"
#include "nx_crypto_hmac.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_crypto_method_hmac_sha1_init                    PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is the common crypto method init callback for         */
/*    Microsoft supported HMAC SHA1 cryptographic algorithm.              */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    method                                Pointer to crypto method      */
/*    key                                   Pointer to key                */
/*    key_size_in_bits                      Length of key size in bits    */
/*    handler                               Returned crypto handler       */
/*    crypto_metadata                       Metadata area                 */
/*    crypto_metadata_size                  Size of the metadata area     */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Timothy Stapko           Initial Version 6.0           */
/*  09-30-2020     Timothy Stapko           Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*  10-31-2023     Yanwu Cai                Modified comment(s),          */
/*                                            resulting in version 6.3.0  */
/*                                                                        */
/**************************************************************************/
NX_CRYPTO_KEEP UINT  _nx_crypto_method_hmac_sha1_init(struct  NX_CRYPTO_METHOD_STRUCT *method,
                                                      UCHAR *key, NX_CRYPTO_KEY_SIZE key_size_in_bits,
                                                      VOID  **handle,
                                                      VOID  *crypto_metadata,
                                                      ULONG crypto_metadata_size)
{

    NX_CRYPTO_PARAMETER_NOT_USED(key_size_in_bits);
    NX_CRYPTO_PARAMETER_NOT_USED(handle);

    NX_CRYPTO_STATE_CHECK

    if ((method == NX_CRYPTO_NULL) || (key == NX_CRYPTO_NULL) || (crypto_metadata == NX_CRYPTO_NULL))
    {
        return(NX_CRYPTO_PTR_ERROR);
    }
    
    /* Verify the metadata address is 4-byte aligned. */
    if((((ULONG)crypto_metadata) & 0x3) != 0)
    {
        return(NX_CRYPTO_PTR_ERROR);
    }

    if(crypto_metadata_size < sizeof(NX_CRYPTO_SHA1_HMAC))
    {
        return(NX_CRYPTO_PTR_ERROR);
    }

    return(NX_CRYPTO_SUCCESS);
}


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_crypto_method_hmac_sha1_cleanup                 PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function cleans up the crypto metadata.                        */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    crypto_metadata                       Crypto metadata               */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    NX_CRYPTO_MEMSET                      Set the memory                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Timothy Stapko           Initial Version 6.0           */
/*  09-30-2020     Timothy Stapko           Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/
NX_CRYPTO_KEEP UINT  _nx_crypto_method_hmac_sha1_cleanup(VOID *crypto_metadata)
{

    NX_CRYPTO_STATE_CHECK

#ifdef NX_SECURE_KEY_CLEAR
    if (!crypto_metadata)
        return (NX_CRYPTO_SUCCESS);

    /* Clean up the crypto metadata.  */
    NX_CRYPTO_MEMSET(crypto_metadata, 0, sizeof(NX_CRYPTO_SHA1_HMAC));
#else
    NX_CRYPTO_PARAMETER_NOT_USED(crypto_metadata);
#endif/* NX_SECURE_KEY_CLEAR  */

    return(NX_CRYPTO_SUCCESS);
}


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_crypto_method_hmac_sha1_operation               PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function handles HMAC SHA1 Authentication operation.           */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    op                                    Operation Type                */
/*                                          Encrypt, Decrypt, Authenticate*/
/*    handler                               Pointer to crypto context     */
/*    key                                   Pointer to key                */
/*    key_size_in_bits                      Length of key size in bits    */
/*    input                                 Input Stream                  */
/*    input_length_in_byte                  Input Stream Length           */
/*    iv_ptr                                Initialized Vector            */
/*    output                                Output Stream                 */
/*    output_length_in_byte                 Output Stream Length          */
/*    crypto_metadata                       Metadata area                 */
/*    crypto_metadata_size                  Size of the metadata area     */
/*    packet_ptr                            Pointer to packet             */
/*    nx_crypto_hw_process_callback         Callback function pointer     */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_crypto_hmac                       Calculate the HMAC            */
/*    _nx_crypto_hmac_metadata_set          Set HMAC metadata             */
/*    _nx_crypto_hmac_initialize            Perform HMAC initialization   */
/*    _nx_crypto_hmac_update                Perform HMAC update           */
/*    _nx_crypto_hmac_digest_calculate      Calculate HMAC digest         */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Timothy Stapko           Initial Version 6.0           */
/*  09-30-2020     Timothy Stapko           Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*  10-31-2023     Yanwu Cai                Modified comment(s),          */
/*                                            resulting in version 6.3.0  */
/*                                                                        */
/**************************************************************************/
NX_CRYPTO_KEEP UINT  _nx_crypto_method_hmac_sha1_operation(UINT op,      /* Encrypt, Decrypt, Authenticate */
                                                           VOID *handle, /* Crypto handler */
                                                           struct NX_CRYPTO_METHOD_STRUCT *method,
                                                           UCHAR *key,
                                                           NX_CRYPTO_KEY_SIZE key_size_in_bits,
                                                           UCHAR *input,
                                                           ULONG input_length_in_byte,
                                                           UCHAR *iv_ptr,
                                                           UCHAR *output,
                                                           ULONG output_length_in_byte,
                                                           VOID *crypto_metadata,
                                                           ULONG crypto_metadata_size,
                                                           VOID *packet_ptr,
                                                           VOID (*nx_crypto_hw_process_callback)(VOID *packet_ptr, UINT status))
{
NX_CRYPTO_SHA1_HMAC    *ctx;
NX_CRYPTO_HMAC         *hmac_metadata;

    NX_CRYPTO_PARAMETER_NOT_USED(handle);
    NX_CRYPTO_PARAMETER_NOT_USED(iv_ptr);
    NX_CRYPTO_PARAMETER_NOT_USED(packet_ptr);
    NX_CRYPTO_PARAMETER_NOT_USED(nx_crypto_hw_process_callback);

    NX_CRYPTO_STATE_CHECK

    /* Verify the metadata address is 4-byte aligned. */
    if((method == NX_CRYPTO_NULL) || (crypto_metadata == NX_CRYPTO_NULL) || ((((ULONG)crypto_metadata) & 0x3) != 0))
    {
        return(NX_CRYPTO_PTR_ERROR);
    }

    if(crypto_metadata_size < sizeof(NX_CRYPTO_SHA1_HMAC))
    {
        return(NX_CRYPTO_PTR_ERROR);
    }

    ctx = (NX_CRYPTO_SHA1_HMAC *)crypto_metadata;
    hmac_metadata = &ctx->nx_sha1_hmac_metadata;

    _nx_crypto_hmac_metadata_set(hmac_metadata,
                                 &(ctx -> nx_sha1_hmac_context),
                                 method -> nx_crypto_algorithm,
                                 NX_CRYPTO_SHA1_BLOCK_SIZE_IN_BYTES,
                                 NX_CRYPTO_HMAC_SHA1_ICV_FULL_LEN_IN_BITS >> 3,
                                 (UINT (*)(VOID *, UINT))_nx_crypto_sha1_initialize,
                                 (UINT (*)(VOID *, UCHAR *, UINT))_nx_crypto_sha1_update,
                                 (UINT (*)(VOID *, UCHAR *, UINT))_nx_crypto_sha1_digest_calculate);

    switch (op)
    {
    case NX_CRYPTO_HASH_INITIALIZE:
        if(key == NX_CRYPTO_NULL)
        {
            return(NX_CRYPTO_PTR_ERROR);
        }

        _nx_crypto_hmac_initialize(hmac_metadata, key, key_size_in_bits >> 3);
        break;

    case NX_CRYPTO_HASH_UPDATE:
        _nx_crypto_hmac_update(hmac_metadata, input, input_length_in_byte);
        break;

    case NX_CRYPTO_HASH_CALCULATE:
        if(output_length_in_byte == 0)
        {
            return(NX_CRYPTO_INVALID_BUFFER_SIZE);
        }

        _nx_crypto_hmac_digest_calculate(hmac_metadata, output,
                                         (output_length_in_byte > (ULONG)((method -> nx_crypto_ICV_size_in_bits) >> 3) ? 
                                         ((method -> nx_crypto_ICV_size_in_bits) >> 3) : output_length_in_byte));
        break;

    default:
        if(key == NX_CRYPTO_NULL)
        {
            return(NX_CRYPTO_PTR_ERROR);
        }

        if(output_length_in_byte == 0)
        {
            return(NX_CRYPTO_INVALID_BUFFER_SIZE);
        }

        _nx_crypto_hmac(hmac_metadata, input, input_length_in_byte, key, (key_size_in_bits >> 3), output,
                        (output_length_in_byte > (ULONG)((method -> nx_crypto_ICV_size_in_bits) >> 3) ? 
                        ((method -> nx_crypto_ICV_size_in_bits) >> 3) : output_length_in_byte));
        break;
    }

    return NX_CRYPTO_SUCCESS;
}

