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
/**   Crypto Self Test                                                    */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_CRYPTO_SOURCE_CODE


/* Include necessary system files.  */
#include "nx_crypto_method_self_test.h"
#include "nx_crypto_pkcs1_v1.5.h"

#ifdef NX_CRYPTO_SELF_TEST

static UCHAR pub_e_2048[] = {0x01, 0x00, 0x01};

static UCHAR pri_e_2048[] = {
0x13, 0xFF, 0x74, 0x29, 0xF8, 0xE8, 0x51, 0xF1, 0x07, 0x9C, 0xCF, 0xCE, 0x3B, 0x3C, 0xD8, 0x60, 
0x6A, 0xBA, 0x86, 0x07, 0xAD, 0x85, 0xCB, 0xB3, 0x05, 0x75, 0x01, 0xEB, 0xD5, 0x88, 0x11, 0xF3, 
0xC0, 0x48, 0x23, 0x17, 0x1F, 0x19, 0x2C, 0x04, 0x8E, 0x1E, 0x88, 0x3A, 0xF8, 0xCF, 0x95, 0x88, 
0x10, 0x15, 0x1D, 0x38, 0x74, 0xAE, 0xDC, 0x8E, 0xC4, 0xF8, 0x8D, 0x20, 0x65, 0xC5, 0x81, 0x56, 
0x9F, 0x1E, 0x20, 0x08, 0x52, 0xDD, 0x40, 0xB6, 0xDF, 0xD1, 0x65, 0x26, 0x59, 0x08, 0x5A, 0x9D, 
0xD1, 0xD3, 0xB8, 0x69, 0xEA, 0x36, 0x17, 0xD9, 0x04, 0xD2, 0x09, 0xDE, 0x15, 0x6A, 0x60, 0xBA, 
0x59, 0x29, 0xD0, 0x2F, 0x16, 0x43, 0x02, 0x73, 0xD1, 0x07, 0x20, 0xC2, 0xF2, 0x8D, 0x2B, 0x95, 
0x68, 0x4D, 0xCA, 0xA6, 0xB9, 0xF6, 0xA5, 0x08, 0xEA, 0x2C, 0xBB, 0xC1, 0x1B, 0x9F, 0x3F, 0x30, 
0xD6, 0x20, 0x1E, 0xA6, 0xCF, 0xFB, 0xBF, 0x1C, 0x44, 0x25, 0x5C, 0xEC, 0x58, 0xEE, 0x70, 0xDB, 
0xC8, 0x72, 0x44, 0x2B, 0xCC, 0xF1, 0x15, 0xD8, 0xF7, 0x43, 0x55, 0x7B, 0x5D, 0xE5, 0xF4, 0x2D, 
0xDD, 0xA6, 0xCE, 0xAE, 0x79, 0x77, 0x79, 0x3C, 0xC9, 0xD9, 0x0A, 0xDF, 0xE6, 0x5E, 0x52, 0x0F, 
0x55, 0x20, 0xB6, 0x15, 0xCF, 0x3B, 0x8C, 0x2D, 0xC8, 0x2D, 0x7A, 0xC7, 0x5E, 0xDB, 0x12, 0x97, 
0xCF, 0x38, 0xAB, 0x23, 0xA3, 0x7E, 0xED, 0x18, 0xD4, 0xDD, 0x45, 0xD9, 0xAD, 0x05, 0x1B, 0x26, 
0x40, 0x1B, 0xE8, 0x6E, 0x8C, 0x8E, 0x53, 0xF9, 0x58, 0x5A, 0x70, 0x2D, 0x02, 0xF1, 0xB5, 0xBD, 
0x65, 0xF6, 0x73, 0x9D, 0xFA, 0x6B, 0xFF, 0xE5, 0x60, 0xCA, 0x13, 0x0B, 0x6F, 0x1D, 0x47, 0x79, 
0xC5, 0x56, 0xC0, 0x6D, 0x9C, 0xD2, 0x9F, 0xB7, 0x2D, 0x88, 0x51, 0x90, 0x4F, 0x9C, 0xDE, 0xE9, 
};

static UCHAR m_2048[] = {
0xE0, 0xF5, 0x05, 0x99, 0x66, 0xA8, 0xAE, 0xC4, 0xBF, 0x7C, 0xDA, 0xC8, 0xAE, 0x24, 0x30, 0xBD, 
0xF6, 0x1C, 0x54, 0xD0, 0x9C, 0xAB, 0x99, 0x63, 0xCB, 0xF9, 0xA5, 0x2A, 0xC6, 0x41, 0xE3, 0x84, 
0xB6, 0x43, 0x1D, 0x3B, 0x6A, 0x9D, 0x18, 0x11, 0x51, 0x9A, 0x29, 0x04, 0xE1, 0x17, 0x0A, 0x44, 
0x44, 0x6C, 0x80, 0xE7, 0x63, 0x8A, 0x4A, 0xF2, 0x72, 0x0A, 0x76, 0x54, 0xAB, 0x74, 0x0D, 0x8A, 
0x15, 0x1F, 0xDD, 0x21, 0x6F, 0x3D, 0x69, 0x33, 0x42, 0x2F, 0xD9, 0xAC, 0x14, 0xAE, 0xDE, 0x9C, 
0xCD, 0x02, 0x1E, 0xA7, 0x9E, 0x46, 0x92, 0x5F, 0x4B, 0x18, 0xFD, 0x1A, 0xF2, 0xC0, 0x07, 0x3C, 
0xFC, 0x3A, 0x69, 0xAC, 0x71, 0xA2, 0xB3, 0x67, 0x3D, 0x08, 0x13, 0x6C, 0xDB, 0x01, 0xC3, 0x79, 
0x89, 0x26, 0x01, 0xC7, 0xC8, 0x57, 0xD6, 0x80, 0x18, 0xDA, 0xE9, 0x24, 0xCB, 0x8C, 0xD2, 0x93, 
0x77, 0xA1, 0x4C, 0x75, 0x2B, 0x92, 0xBA, 0xFF, 0x14, 0xC3, 0xA4, 0x97, 0x25, 0xAE, 0x2F, 0xEF, 
0xAA, 0xD4, 0x68, 0x6D, 0x8A, 0x7D, 0x9F, 0x94, 0xEB, 0x11, 0xBF, 0x81, 0xE0, 0x5B, 0xD5, 0xD2, 
0x58, 0x65, 0x26, 0xFB, 0x12, 0x9E, 0x73, 0x53, 0x9F, 0x92, 0x23, 0xD4, 0x96, 0xB2, 0xAC, 0xA2, 
0x3C, 0xCA, 0xCC, 0x34, 0xD5, 0xB1, 0x85, 0x33, 0xBD, 0x0F, 0x58, 0x15, 0xA7, 0x6F, 0x94, 0xF4, 
0xF5, 0x5D, 0x96, 0x5F, 0xE6, 0x15, 0x99, 0xB4, 0x4B, 0xD8, 0xFB, 0xAD, 0x35, 0xF4, 0x2B, 0x61, 
0x2A, 0x4C, 0x4F, 0x27, 0x65, 0xB2, 0x09, 0x7A, 0x5C, 0x00, 0x90, 0xEA, 0x81, 0x66, 0xD9, 0xC6, 
0xDA, 0x1E, 0x03, 0xB6, 0x11, 0x97, 0x36, 0xB7, 0x94, 0x60, 0x04, 0x91, 0xC4, 0x84, 0x33, 0x13, 
0x2D, 0x0F, 0x15, 0xD5, 0xDE, 0x3B, 0xB4, 0x27, 0x0D, 0xF6, 0xBC, 0x90, 0x12, 0xB7, 0x49, 0x31, 
};

static UCHAR msg[] = {
0x40, 0x53, 0x93, 0x9A, 0x9F, 0xF6, 0xAC, 0x88, 0x6C, 0x03, 0x6A, 0xE2, 0xE1, 0x5E, 0x6E, 0xD7,
0x3D, 0xD7, 0x99, 0xD4, 0x0D, 0x5B, 0x73, 0x54, 0xAA, 0x6B, 0xC9, 0xF8, 0x03, 0xCE, 0x9B, 0xDA,
0x9C, 0x83, 0x35, 0x1F, 0xD7, 0xFA, 0x9B, 0xCB, 0x73, 0x84, 0x2A, 0xD9, 0x52, 0x07, 0x7D, 0x8C,
0x7F, 0xF6, 0x8E, 0x00, 0x6F, 0x80, 0x1D, 0x04, 0x87, 0x08, 0x56, 0x2C, 0xDF, 0xD6, 0xAE, 0x21,
0x46, 0x0C, 0x0E, 0x3C, 0x86, 0xDB, 0x33, 0x53, 0xE9, 0xF6, 0x55, 0xD3, 0xFB, 0x47, 0x06, 0x0F,
0x92, 0xE2, 0x5E, 0xD8, 0x0C, 0x37, 0x55, 0x4E, 0xD8, 0x8B, 0x70, 0xF5, 0x38, 0xA9, 0xA0, 0x0C,
0x44, 0xD4, 0x67, 0x1A, 0x33, 0x01, 0x3C, 0xC9, 0xD6, 0x43, 0x31, 0xF7, 0x65, 0x87, 0xD3, 0x0B,
0x7E, 0x81, 0x51, 0x85, 0x6B, 0xE6, 0xE1, 0xDA, 0xA4, 0xDC, 0x60, 0x7E, 0x94, 0xAF, 0x38, 0x42
};

static UCHAR s[] = {
0x5c, 0x49, 0x25, 0xc1, 0x17, 0x72, 0x00, 0x48, 0x09, 0x15, 0x62, 0x38, 0xab, 0xbf, 0x42, 0x82,
0x30, 0x4c, 0x42, 0xa0, 0x1f, 0x01, 0xa2, 0xc0, 0xc1, 0x67, 0xe0, 0xd2, 0x3c, 0x81, 0x86, 0x59,
0x5e, 0xca, 0xa6, 0x46, 0x27, 0x0c, 0x89, 0x8e, 0x2a, 0xa8, 0x43, 0x39, 0x61, 0x12, 0xf9, 0xb4,
0x35, 0x71, 0xe0, 0xd4, 0x28, 0x22, 0xbc, 0x03, 0xe5, 0x24, 0x64, 0x08, 0xc3, 0x87, 0x14, 0x92,
0xb6, 0xc7, 0x1f, 0xfa, 0x5b, 0x33, 0xee, 0xa1, 0x4f, 0x87, 0x86, 0xe4, 0xc2, 0x49, 0x05, 0x53,
0x37, 0xc8, 0x4e, 0x9a, 0xdc, 0xd2, 0x1e, 0x5e, 0x47, 0x2a, 0xb7, 0xdb, 0x12, 0xa4, 0x2b, 0x9a,
0x67, 0x72, 0xc6, 0x3e, 0x92, 0x62, 0x7f, 0x52, 0xe4, 0x65, 0xb2, 0x3e, 0x7e, 0xab, 0xd8, 0xb0,
0x7a, 0x9f, 0x96, 0x92, 0xd5, 0x8b, 0xd1, 0x49, 0x31, 0xb5, 0xa7, 0xca, 0xa4, 0x63, 0x62, 0xcd,
0x0b, 0xf9, 0xa3, 0x9c, 0xb3, 0xaf, 0x44, 0x61, 0xd3, 0x2a, 0x1e, 0xca, 0x9e, 0xab, 0xc9, 0x0f,
0x66, 0x25, 0x2a, 0x9c, 0x38, 0x48, 0x3f, 0xfc, 0x5f, 0x6e, 0x70, 0xb2, 0x75, 0x5f, 0xc3, 0xac,
0xa8, 0xe9, 0xa5, 0xab, 0xeb, 0x1d, 0x61, 0x4b, 0x42, 0x35, 0x86, 0x40, 0x35, 0x35, 0x7c, 0x77,
0x11, 0x94, 0x33, 0x60, 0xcb, 0xe4, 0xcb, 0x49, 0x9a, 0xd7, 0x6e, 0x3e, 0xc1, 0x79, 0x93, 0x61,
0x1d, 0x81, 0xe9, 0x5b, 0x9f, 0x91, 0x74, 0x2a, 0x20, 0x74, 0x64, 0xb1, 0xd0, 0x25, 0xd3, 0x6b,
0xd5, 0xeb, 0x35, 0x89, 0x51, 0x07, 0xe9, 0x77, 0x2e, 0xd1, 0x45, 0xc3, 0xcf, 0xc9, 0x81, 0xd9,
0xd3, 0xf9, 0xa3, 0xb5, 0x7c, 0x9a, 0x9f, 0x43, 0xc4, 0xde, 0xeb, 0x08, 0x2a, 0x83, 0x64, 0x32,
0x25, 0xf3, 0x63, 0xea, 0xc8, 0xe6, 0xe0, 0x00, 0x8c, 0x1b, 0x64, 0xfa, 0x4d, 0xb6, 0xd2, 0x0d
};

static UCHAR output[512];

extern NX_CRYPTO_METHOD crypto_method_rsa;
extern NX_CRYPTO_METHOD crypto_method_sha256;

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    nx_crypto_method_self_test_pkcs1                    PORTABLE C      */
/*                                                           6.4.3        */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Timothy Stapko, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function performs the Known Answer Test for PKCS1#v1.5 crypto  */
/*    method.                                                             */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    method_ptr                            Pointer to the crypto method  */
/*                                            to be tested.               */
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
/*  06-02-2021     Bhupendra Naphade        Modified comment(s),          */
/*                                            renamed FIPS symbol to      */
/*                                            self-test,                  */
/*                                            resulting in version 6.1.7  */
/*                                                                        */
/**************************************************************************/
NX_CRYPTO_KEEP UINT _nx_crypto_method_self_test_pkcs1(NX_CRYPTO_METHOD *crypto_method_pkcs1,
                                                      VOID *metadata, UINT metadata_size)
{
NX_CRYPTO_PKCS1_OPTIONS pkcs1_options;
UCHAR *modulus;
UINT   modulus_len;
UCHAR *pub_e;
UINT   pub_e_len;
UCHAR *pri_e;
UINT   pri_e_len;
UCHAR *plain_text;
UINT   input_length;
UCHAR *cipher_text;
UINT   status;


    /* Validate the crypto method */
    if(crypto_method_pkcs1 == NX_CRYPTO_NULL)
        return(NX_CRYPTO_PTR_ERROR);

    /* Set the test data.  */
    pkcs1_options.public_cipher_method = &crypto_method_rsa;
    pkcs1_options.public_cipher_metadata = (UCHAR *)metadata + sizeof(NX_CRYPTO_PKCS1);
    pkcs1_options.public_cipher_metadata_size = crypto_method_rsa.nx_crypto_metadata_area_size;
    pkcs1_options.hash_method = &crypto_method_sha256;
    pkcs1_options.hash_metadata = (UCHAR *)pkcs1_options.public_cipher_metadata + sizeof(NX_CRYPTO_RSA);
    pkcs1_options.hash_metadata_size = crypto_method_sha256.nx_crypto_metadata_area_size;

    modulus = m_2048;
    modulus_len = sizeof(m_2048);
    pub_e = pub_e_2048;
    pub_e_len = sizeof(pub_e_2048);
    pri_e = pri_e_2048;
    pri_e_len = sizeof(pri_e_2048);
    plain_text = msg;
    input_length = sizeof(msg);
    cipher_text = s;

    /* Clear the output buffer.  */
    NX_CRYPTO_MEMSET(output, 0, sizeof(output));

    /* Call the crypto initialization function.  */
    if (crypto_method_pkcs1 -> nx_crypto_init)
    {
        status = crypto_method_pkcs1 -> nx_crypto_init(crypto_method_pkcs1,
                                                       NX_CRYPTO_NULL,
                                                       0,
                                                       NX_CRYPTO_NULL,
                                                       metadata,
                                                       metadata_size);

        if (status != NX_CRYPTO_SUCCESS)
        {
            return(status);
        }
    }

    if (crypto_method_pkcs1 -> nx_crypto_operation == NX_CRYPTO_NULL)
    {
        return(NX_CRYPTO_PTR_ERROR);
    }

    /* Call the crypto operation function.  */
    status = crypto_method_pkcs1 -> nx_crypto_operation(NX_CRYPTO_SET_ADDITIONAL_DATA,
                                                        NX_CRYPTO_NULL,
                                                        crypto_method_pkcs1,
                                                        modulus,
                                                        modulus_len << 3,
                                                        (UCHAR *)&pkcs1_options,
                                                        sizeof(pkcs1_options),
                                                        NX_CRYPTO_NULL,
                                                        NX_CRYPTO_NULL,
                                                        0,
                                                        metadata,
                                                        metadata_size,
                                                        NX_CRYPTO_NULL, NX_CRYPTO_NULL);
    if (status != NX_CRYPTO_SUCCESS)
    {
        return(status);
    }

    status = crypto_method_pkcs1 -> nx_crypto_operation(NX_CRYPTO_AUTHENTICATE,
                                                        NX_CRYPTO_NULL,
                                                        crypto_method_pkcs1,
                                                        pri_e,
                                                        pri_e_len << 3,
                                                        plain_text,
                                                        input_length,
                                                        NX_CRYPTO_NULL,
                                                        output,
                                                        modulus_len,
                                                        metadata,
                                                        metadata_size,
                                                        NX_CRYPTO_NULL, NX_CRYPTO_NULL);
    if (status != NX_CRYPTO_SUCCESS)
    {
        return(status);
    }

    /* Validate the output.  */
    if(NX_CRYPTO_MEMCMP(output, cipher_text, modulus_len) != 0)
    {
        return(NX_CRYPTO_NOT_SUCCESSFUL);
    }

    status = crypto_method_pkcs1 -> nx_crypto_operation(NX_CRYPTO_VERIFY,
                                                        NX_CRYPTO_NULL,
                                                        crypto_method_pkcs1,
                                                        pub_e,
                                                        pub_e_len << 3,
                                                        plain_text,
                                                        input_length,
                                                        NX_CRYPTO_NULL,
                                                        cipher_text,
                                                        modulus_len,
                                                        metadata,
                                                        metadata_size,
                                                        NX_CRYPTO_NULL, NX_CRYPTO_NULL);

    /* Check the status.  */
    if(status != NX_CRYPTO_SUCCESS)
    {
        return(status);
    }

    if (crypto_method_pkcs1 -> nx_crypto_cleanup)
    {
        status = crypto_method_pkcs1 -> nx_crypto_cleanup(metadata);
    }

    return(status);
}
#endif
