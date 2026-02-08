#include <interval/operations.h>

// === functions ===

long hash(const void * pt, long bytes) {
    // this hash function was written to give decent-ish results while
    // being length-agnostic. the shift values in HASH_MULTIPLY were
    // chosen arbitrarily, and 0xF9 is my lucky number <3.
    
    unsigned long hash = 0;
    
    for (long i = 0; i < bytes; i++) {
        hash ^= ((const unsigned char *)(pt))[i];
        hash *= HASH_MULTIPLY;
    }
    
    return (long)(hash >> 1);
}

void move(void * to, const void * from, long bytes) {
    for (long i = 0; i < bytes; i++) {
        ((char *)(to))[i] = ((const char *)(from))[i];
    }
}

void swap(void * pt_1, void * pt_2, long bytes) {
    for (long i = 0; i < bytes; i++) {
        const char temp = ((char *)(pt_2))[i];
        
        ((char *)(pt_1))[i] = ((char *)(pt_2))[i];
        ((char *)(pt_2))[i] = temp;
    }
}

bool equals(const void * pt_1, const void * pt_2, long bytes) {
    for (long i = 0; i < bytes; i++) {
        if (((char *)(pt_1))[i] != ((char *)(pt_2))[i]) {
            return false;
        }
    }
    
    return true;
}

void sort(void * items, long item_bytes, long item_count, is_ordered_method_t * is_ordered) {
    static const long steps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    char temp[item_bytes];
    
    for (long s = 8; s >= 0; s--) {
        for (long i = steps[s]; i < item_count; i++) {
            long j = i;
            
            while (j >= steps[s]) {
                long next_j = j - steps[s];
                
                if (is_ordered(items + next_j * item_bytes, temp)) {
                    break;
                }
                
                move(items + j * item_bytes, items + next_j * item_bytes, item_bytes);
                j = next_j;
            }
            
            move(items + j * item_bytes, temp, item_bytes);
        }
    }
}

long length_of(const char * text) {
    long length = 0;
    
    while (text[length]) {
        length++;
    }
    
    return length;
}
