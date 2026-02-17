#include <interval/list.h>
#include <interval/memory.h>

// === iterator_t functions ===

void iterator_store(iterator_t * it, void * item) {
    list_t * list = it->list;
    
    iterator_t * next_it = alloc(sizeof(iterator_t));
    
    next_it->item = it->item;
    next_it->list = list;
    
    next_it->next = it->next;
    
    if (list->end == it) {
        list->end = next_it;
    }
    
    it->item = item;
    it->next = next_it;
    
    list->count++;
}

// === list_t functions ===

void list_init(list_t * list) {
    list->count = 0;
    
    list->begin = &(list->__iterator);
    list->end = &(list->__iterator);
    
    list->__iterator = ((iterator_t) {NULL, list, NULL});
}

void list_clean(list_t * list) {
    iterator_t * it = list->begin;
    
    while (it != list->end) {
        iterator_t * next_it = it->next;
        
        if (it->item == NULL) {
            it->item = next_it->item;
            it->next = next_it->next;
            
            list->count--;
            
            if (list->end == next_it) {
                list->end = it;
            }
            
            free(next_it);
        } else {
            it = next_it;
        }
    }
}
