#include "nx_api.h"
#if defined(NX_TAHI_ENABLE) && defined(FEATURE_NX_IPV6)  
#include "netx_tahi.h"

static char pkt1[] = {
    0x33, 0x33, 0xff, 0x33, 0x44, 0x56, 0x00, 0x11, 
    0x22, 0x33, 0x44, 0x56, 0x86, 0xdd, 0x60, 0x00, 
    0x00, 0x00, 0x00, 0x18, 0x3a, 0xff, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x02, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x01, 0xff, 0x33, 0x44, 0x56, 0x87, 0x00, 
    0xd0, 0x03, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x11, 
    0x22, 0xff, 0xfe, 0x33, 0x44, 0x56              
};

TAHI_TEST_SEQ tahi_dhcpv6_01_001[] = {
    {TITLE,     "dhcpv6 01-001",   13,           0},
    {WAIT,      NX_NULL,           0,            5},
    {CHECK,     &pkt1[0],          sizeof(pkt1), 5},
    {CLEANUP,   NX_NULL,           0,            0},
    {DUMP,      NX_NULL,           0,            0}

};

int  tahi_dhcpv6_01_001_size = sizeof(tahi_dhcpv6_01_001) / sizeof(TAHI_TEST_SEQ);
#endif
