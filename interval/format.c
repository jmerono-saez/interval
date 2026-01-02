#include <interval/format.h>

#include <interval/operations.h>

long format_va(stream_t * stream, const char * text, va_list args) {
    long bytes = 0;
    
    for (long i = 0; text[i]; i++) {
        if (text[i] != '%') {
            bytes += write(stream, text + i, 1);
            continue;
        }
        
        // TODO: implement this!
    }
    
    // TODO: optimize such that buffering is performed!
    va_end(args);
    
    return bytes;
}

long format(stream_t * stream, const char * text, ...) {
    va_list args;
    va_start(args, text);
    
    return format_va(stream, text, args);
}
