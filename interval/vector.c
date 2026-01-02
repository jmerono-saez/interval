#include <interval/vector.h>

#include <interval/memory.h>
#include <interval/operations.h>

void vector_reduce_$(vector_t(void) * vector, long item_bytes) {
    if (vector->at != NULL) {
        free(vector->at);
        vector->at = NULL;
    }
    
    vector->count = 0;
    vector->limit = 0;
}

void vector_grow_$(vector_t(void) * vector, long item_bytes) {
    const long next_limit = vector->count + vector->count / 2 + 1;
    
    if (vector->count >= vector->limit) {
        void * at = alloc(next_limit * item_bytes);
        
        if (vector->at != NULL) {
            move(at, vector->at, vector->count * item_bytes);
            free(vector->at);
        }
        
        vector->limit = next_limit;
        vector->at = at;
    }
}

void vector_sort_$(vector_t(void) * vector, long item_bytes, long(* fn)(const void *, const void *, long)) {
    for (long i = 0; i < vector->count; i++) {
        for (long j = i + 1; j < vector->count; j++) {
            if (fn(vector->at + i * item_bytes, vector->at + j * item_bytes, item_bytes) < 0) {
                continue;
            }
            
            // TODO: do something better than bubble-like sort.
            swap(vector->at + i * item_bytes, vector->at + j * item_bytes, item_bytes);
        }
    }
}

void vector_heaped_push_$(vector_t(void) * vector, long item_bytes, compare_fn_t * fn) {
    // TODO: implement!
    return;
}

void vector_heaped_pull_$(vector_t(void) * vector, long item_bytes, compare_fn_t * fn) {
    // TODO: implement!
    return;
}
