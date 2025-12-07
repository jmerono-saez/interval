#include <interval/pc-i586/boot.h>

#include <stddef.h>

rsdp_t * dp_find_in_memory(void * left, void * right) {
    for (void * head = left; head < right; head += 16) {
        rsdp_t * rsdp = head;
        
        if (rsdp->sign == RSDP_SIGN) {
            return rsdp;
        }
    }
    
    return NULL;
}

void * dt_search(const rsdp_t * rsdp, bool is_v2, uint32_t sign) {
    if (rsdp == NULL) {
        return NULL;
    }
    
    const rsdt_t * rsdt = (is_v2 ? rsdp->v2.p : rsdp->v1.p);
    const size_t size = rsdt->header.size - sizeof(dt_header_t);
    
    for (size_t i = 0; i * (is_v2 ? 8 : 4) < size; i++) {
        dt_header_t * header = (is_v2 ? rsdt->v2[i].p : rsdt->v1[i].p);
        
        if (header->sign == sign) {
            return (void *)(header);
        }
    }
    
    return NULL;
}
