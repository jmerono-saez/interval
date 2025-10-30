#ifndef __INTERVAL_KERNEL_LOGGER_H__
#define __INTERVAL_KERNEL_LOGGER_H__

#include <interval/macros.h>

void l_print(void(* putc)(char c), const char * format, ...);

#endif
