#include <interval/rwable.h>
#include <stdarg.h>

// === functions ===

bool write_ul(rwable_t * rw, unsigned long ul) {
    return rw->write(rw, &(ul), sizeof(unsigned long));
}

unsigned long read_ul(rwable_t * rw, unsigned long empty_ul) {
    unsigned long ul;
    
    return rw->read(rw, &(ul), sizeof(unsigned long)) ? ul : empty_ul;
}

bool write_ch(rwable_t * rw, char ch) {
    return rw->write(rw, &(ch), sizeof(char));
}

char read_ch(rwable_t * rw, char empty_ch) {
    char ch;
    
    return rw->read(rw, &(ch), sizeof(char)) ? ch : empty_ch;
}

long format(rwable_t * rw, const char * text, ...) {
    va_list args;
    va_start(args, text);
    
    long bytes = 0;
    
    for (long i = 0; text[i]; i++) {
        // TODO: implement this!
    }
    
    va_end(args);
    
    return bytes;
}
