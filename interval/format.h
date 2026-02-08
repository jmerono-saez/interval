#ifndef __INTERVAL_FORMAT_H__
#define __INTERVAL_FORMAT_H__

#include <interval/stream.h>

#include <stdarg.h>

// === functions ===

long format_va(stream_t * stream, const char * text, va_list args);
long format(stream_t * stream, const char * text, ...);

#endif
