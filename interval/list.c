#include <interval/list.h>
#include <interval/memory.h>

// === functions ===

void list_init(list_t * list) {
    list->count = 0;
    
    list->begin = &(list->__iterator);
    list->end = &(list->__iterator);
    
    list->__iterator = ((iterator_t) {NULL, list, NULL});
}

void list_store(iterator_t * iterator, void * item) {
    list_t * list = iterator->list;
    
    iterator_t * next = alloc(sizeof(iterator_t));
    
    next->item = iterator->item;
    next->list = list;
    
    next->next = iterator->next;
    
    if (list->end == iterator) {
        list->end = next;
    }
    
    iterator->item = item;
    iterator->next = next;
    
    list->count++;
}

void list_clean(list_t * list) {
    iterator_t * iterator = list->begin;
    
    while (iterator != list->end) {
        iterator_t * next = iterator->next;
        
        if (iterator->item == NULL) {
            iterator->item = next->item;
            iterator->next = next->next;
            
            list->count--;
            
            if (list->end == next) {
                list->end = iterator;
            }
            
            free(next);
        } else {
            iterator = next;
        }
    }
}
