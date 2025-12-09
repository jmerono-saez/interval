#ifndef __INTERVAL_OPERATIONS_H__
#define __INTERVAL_OPERATIONS_H__

#include <stddef.h>

static inline void * copy(void * p, void * q, size_t size) {
    /*
    #if (PLATFORM == "pc-i586")
        __asm__(
            "cld\n\t"
            "rep stosb"
            :
            "{edi}" (p),
            "{esi}" (q),
            "{ecx}" (size)
        );
        
        return p + size;
    #else
    */
        while (size--) {
            *((unsigned char *)(p++)) = *((unsigned char *)(q++));
        }
        
        return p;
    /*
    #endif
    */
}

#endif
