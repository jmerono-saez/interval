#include <interval/stream.h>

#include <interval/operations.h>

// === basic functions ===

long write(stream_t * stream, const void * from, long bytes) {
    if (stream == NULL || stream->write == NULL) {
        return 0;
    }
    
    return stream->write(stream, from, bytes);
}

long read(stream_t * stream, void * to, long bytes) {
    if (stream == NULL || stream->read == NULL) {
        return 0;
    }
    
    return stream->read(stream, to, bytes);
}

bool is_empty(stream_t * stream) {
    if (stream == NULL || stream->is_empty == NULL) {
        return true;
    }
    
    return stream->is_empty(stream);
}

bool close(stream_t * stream) {
    if (stream == NULL || stream->close == NULL) {
        return false;
    }
    
    return stream->close(stream);
}

// === char-wide functions ===

bool write_char(stream_t * stream, char ch) {
    return (write(stream, &(ch), sizeof(char)) == sizeof(char));
}

char read_char(stream_t * stream, char empty_ch) {
    char ch;
    
    if (read(stream, &(ch), sizeof(char)) != sizeof(char)) {
        return empty_ch;
    }
    
    return ch;
}

// === text-wide functions ===

bool write_text(stream_t * stream, const char * from) {
    const long length = length_of(from);
    
    return (write(stream, from, length) == length);
}

long read_text(stream_t * stream, char * to, long limit, const char stop_ch) {
    long total = 0;
    
    while (total + 1 < limit) {
        char ch = read_char(stream, stop_ch);
        
        if (ch == stop_ch) {
            break;
        }
        
        to[total++] = ch;
    }
    
    if (limit) {
        to[total++] = '\x00';
    }
    
    return total;
}
