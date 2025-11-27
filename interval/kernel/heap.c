#include <interval/kernel/heap.h>

#include <interval/kernel/page.h>

// === globals ===

heap_unit_t * heap_chain_list[HEAP_N];
size_t heap_f_list[HEAP_N];

// === functions ===

void heap_init(void) {
    for (size_t i = 0; i < HEAP_N; i++) {
        heap_chain_list[i] = NULL;
        
        if (i < 2) {
            heap_f_list[i] = i + 2;
        } else {
            heap_f_list[i] = heap_f_list[i - 1] + heap_f_list[i - 2];
        }
    }
}

void * heap_alloc(size_t bytes) {
    size_t needed_bytes = bytes + sizeof(heap_unit_t);
    
    size_t i = 0;
    size_t n = (needed_bytes + PAGE_BYTES - 1) / PAGE_BYTES;
    
    while (i < HEAP_N && heap_unit_bytes(i) < needed_bytes) {
        i++;
    }
    
    if (i < HEAP_N) {
        if (heap_obtain(i)) {
            heap_unit_t * unit = heap_chain_list[i];
            
            heap_chain_list[i] = unit->next;
            
            unit->i = i;
            return (void *)(unit + 1);
        } else {
            return NULL;
        }
    } else {
        heap_unit_t * unit = page_alloc(n);
        
        if (unit == NULL) {
            return NULL;
        }
        
        unit->i = HEAP_N + n;
        return (void *)(unit + 1);
    }
}

void heap_free(void * p) {
    heap_unit_t * unit = (heap_unit_t *)(p) - 1;
    
    if (unit->i < HEAP_N) {
        heap_insert_unit(unit, unit->i);
    } else {
        page_free(unit);
    }
}

// === inner functions ===

size_t heap_unit_bytes(size_t i) {
    return heap_f_list[i] * sizeof(heap_unit_t);
}

bool heap_obtain(size_t i) {
    if (heap_chain_list[i] != NULL) return true;
    
    if (i + 2 < HEAP_N && heap_obtain(i + 2)) {
        heap_unit_t * unit = heap_chain_list[i + 2];
        
        heap_chain_list[i + 2] = unit->next;
        
        heap_insert_unit(unit, i + 1);
        heap_insert_unit(unit + heap_f_list[i + 1], i);
        
        return true;
    }
    
    if (i + 1 < HEAP_N && heap_obtain(i + 1)) {
        heap_unit_t * unit = heap_chain_list[i + 1];
        
        heap_chain_list[i + 1] = unit->next;
        
        heap_insert_unit(unit, i);
        heap_insert_unit(unit + heap_f_list[i], i - 1);
        
        return true;
    }
    
    return heap_expand();
}

void heap_insert_unit(heap_unit_t * unit, size_t i) {
    unit->next = heap_chain_list[i];
    heap_chain_list[i] = unit;
}

bool heap_expand(void) {
    size_t i = HEAP_N - 1;
    size_t n = (heap_unit_bytes(i) + PAGE_BYTES - 1) / PAGE_BYTES;
    
    void * p = page_alloc(n);
    if (p == NULL) return false;
    
    size_t bytes = n * PAGE_BYTES;
    
    while (true) {
        size_t unit_bytes = heap_unit_bytes(i);
        
        if (bytes < unit_bytes) {
            if (i) i--;
            else break;
        } else {
            heap_insert_unit(p, i);
            
            p += unit_bytes;
            bytes -= unit_bytes;
        }
    }
    
    return true;
}
