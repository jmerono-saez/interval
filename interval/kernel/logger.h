#ifndef __INTERVAL_KERNEL_LOGGER_H__
#define __INTERVAL_KERNEL_LOGGER_H__

#include <stddef.h>

// === constants ===

#ifndef LOGGER_CIRCULAR_PAGES
#error "LOGGER_CIRCULAR_PAGES is not defined"
#endif

// === globals ===

extern void(* logger_early_putc)(char c);

extern char * logger_circular;
extern size_t logger_size;

extern size_t logger_tail;
extern size_t logger_head;

// === functions ===

void logger_early_init(void(* early_putc)(char c));
// void logger_init(output_t * output);

void logger_putc(char c);

void logger_print(const char * format, ...);

#endif
