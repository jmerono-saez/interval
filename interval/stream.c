#include <interval/stream.h>

long write(stream_t * stream, const void * from, long bytes) {
    if (stream == NULL || stream->write_fn == NULL) {
        return 0;
    }
    
    return stream->write_fn(stream, from, bytes);
}

long read(stream_t * stream, void * to, long bytes) {
    if (stream == NULL || stream->read_fn == NULL) {
        return 0;
    }
    
    return stream->read_fn(stream, to, bytes);
}

bool is_empty(stream_t * stream) {
    if (stream == NULL || stream->is_empty_fn == NULL) {
        return true;
    }
    
    return stream->is_empty_fn(stream);
}
