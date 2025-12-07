#include <interval/kernel/logger.h>

#include <interval/kernel/page.h>

#include <stdarg.h>

void(* logger_early_putc)(char c) = NULL;

char * logger_circular = NULL;
size_t logger_size = 0;

size_t logger_tail = 0;
size_t logger_head = 0;

void logger_early_init(void(* early_putc)(char c)) {
    logger_early_putc = early_putc;
    
    logger_circular = page_alloc(LOGGER_CIRCULAR_PAGES);
    logger_size = LOGGER_CIRCULAR_PAGES * PAGE_BYTES;
    
    logger_tail = 0;
    logger_head = 0;
}

void logger_putc(char c) {
    if (logger_early_putc != NULL) {
        logger_early_putc(c);
    }
    
    // if (output != NULL) {
    //     output_write_byte(c);
    // }
    
    logger_circular[logger_head++] = c;
    logger_head %= logger_size;
    
    if (logger_tail == logger_head) {
        // TODO: this will result in an infinite loop if a line ends up
        // being too long.
        
        while (logger_circular[logger_tail] != '\n') {
            logger_circular[logger_tail++] = '\0';
            logger_tail %= logger_size;
        }
        
        logger_circular[logger_tail++] = '\0';
        logger_tail %= logger_size;
    }
}

void logger_print(const char * format, ...) {
    va_list args;
    va_start(args, format);
    
    char c;
    
    while (c = *(format++)) {
        if (c == '%') {
            c = *(format++);
            
            if (c == 's') {
                const char * string = va_arg(args, void *);
                while (c = *(string++)) logger_putc(c);
            }
            
            if (c == 'z') {
                size_t z = va_arg(args, size_t);
                
                char buffer[30];
                size_t length = 0;
                
                while (z) {
                    buffer[length++] = (z % 10) + '0';
                    z = z / 10;
                }
                
                if (length == 0) {
                    buffer[length++] = '0';
                }
                
                while (length--) {
                    logger_putc(buffer[length]);
                }
            }
        } else {
            logger_putc(c);
        }
    }
    
    va_end(args);
}

void logger_dump(const void * region, size_t size) {
    const unsigned char * byte_list = region;
    const char * digits = "0123456789ABCDEF";
    
    for (size_t i = 0; i < size; i++) {
        logger_putc(digits[(byte_list[i] >> 4) & 0x0F]);
        logger_putc(digits[(byte_list[i]) & 0x0F]);
    }
    
    logger_putc(0x0A);
}
