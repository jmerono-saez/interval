#include <interval/kernel/logger.h>

#include <stdarg.h>

static long offset = 0;

void l_print(void(* putc)(char c), const char * format, ...) {
    va_list args;
    va_start(args, format);
    
    volatile unsigned char * vga_text = (unsigned char *)(0x000B8000);
    char c;
    
    while (c = *(format++)) {
        if (c == '%') {
            c = *(format++);
            
            if (c == 's') {
                const char * string = va_arg(args, void *);
                while (c = *(string++)) putc(c);
            }
        } else {
            putc(c);
        }
    }
    
    va_end(args);
}
