#include <interval/io.h>

stream_t * io_stream = NULL;

void io_init(stream_t * stream) {
    io_stream = stream;
}
