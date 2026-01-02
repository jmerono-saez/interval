#include <interval/operations.h>

void move(void * to, const void * from, long size) {
    for (long i = 0; i < size; i++) {
        ((char *)(to))[i] = ((const char *)(from))[i];
    }
}

void swap(void * data_1, void * data_2, long size) {
    for (long i = 0; i < size; i++) {
        const char temp = ((char *)(data_2))[i];
        
        ((char *)(data_1))[i] = ((char *)(data_2))[i];
        ((char *)(data_2))[i] = temp;
    }
}

long compare(const void * data_1, const void * data_2, long size) {
    for (long i = 0; i < size; i++) {
        const long c = ((signed char *)(data_1))[i] - ((signed char *)(data_2))[i];
        if (c) return c;
    }
    
    return 0;
}

long length_of(const char * text) {
    long length = 0;
    
    while (text[length]) length++;
    return length;
}
