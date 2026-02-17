#include <interval/rwable.h>
#include <stdarg.h>

// === functions ===

bool write_char(rwable_t * rw, char ch) {
    return (rw->write(rw, &(ch), sizeof(char)) == sizeof(char));
}

char read_char(rwable_t * rw, char empty_ch) {
    char ch;
    
    if (rw->read(rw, &(ch), sizeof(char)) != sizeof(char)) {
        return empty_ch;
    }
    
    return ch;
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
