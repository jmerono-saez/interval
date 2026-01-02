#ifndef __INTERVAL_IO_H__
#define __INTERVAL_IO_H__

#include <stddef.h>

#include <interval/format.h>
#include <interval/stream.h>

// === globals ===

extern stream_t * io_stream;

// === functions ===

void io_init(stream_t * stream);

#define io_printf(...) format(io_stream, __VA_ARGS__)

#endif
