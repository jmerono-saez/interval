#include <interval/format.h>

long format_va(stream_t * stream, const char * text, va_list args) {
    long bytes = 0;
    
    for (long i = 0; text[i]; i++) {
        // TODO: implement this!
        
        if (text[i] == '%') {
            switch (text[++i]) {
                case 'c':
                    bytes++;
                    break;
            }
        } else {
            bytes++;
        }
    }
    
    va_end(args);
    
    return bytes;
}

long format(stream_t * stream, const char * text, ...) {
    va_list args;
    va_start(args, text);
    
    return format_va(stream, text, args);
}
