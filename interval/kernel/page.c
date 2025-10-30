#include <interval/kernel/page.h>

#include <interval/macros.h>

// === globals ===

void * p_page_region;
size_t p_page_n;

unsigned char * p_tree;
unsigned char p_tree_d;

// === functions ===

void p_init(void * region, size_t n, unsigned char * tree) {
    p_page_region = region;
    p_page_n = n;
    
    p_tree = tree;
    p_tree_d = 0;
    
    while (n >= 2) {
        n = (n + 1) / 2;
        p_tree_d++;
    }
    
    // TODO: replace this with memory operation.
    
    size_t tree_size = (uz(2) << p_tree_d);
    
    for (size_t i = 0; i < tree_size; i++) {
        p_tree[i] = 0;
    }
    
    p_mark(p_tree, (tree_size + PAGE_BYTES - 1) / PAGE_BYTES);
}

void p_mark(void * p, size_t n) {
    // may seem ineficient, but that is just because it is.
    
    size_t o = (p - p_page_region) / PAGE_BYTES;
    size_t i = (uz(1) << p_tree_d) + o - 1;
    
    while (n >= 1) {
        p_tree[i] = P_USED_NODE;
        p_sift(i);
        
        i++, n--;
    }
}

void * p_alloc(size_t n) {
    size_t i = 0;
    
    unsigned char d = 0;
    
    while (n >= 2) {
        n = (n + 1) / 2;
        d++;
    }
    
    while (true) {
        if (d == p_width(i)) {
            break;
        }
        
        // here we choose which node to go down to based on how tightly
        // it fits the requested allocation.
        
        if (p_width(P_DOWN(i, 1)) >= d) {
            i = P_DOWN(i, 1);
        } else {
            i = P_DOWN(i, 2);
        }
    }
    
    p_tree[i] = P_USED_NODE;
    p_sift(i);
    
    return p_node_to_region(i);
}

void p_free(void * p) {
    size_t i = p_region_to_node(p);
    
    p_tree[i] = P_FREE_NODE;
    p_sift(i);
}

// === inner functions ===

unsigned char p_depth(size_t i) {
    unsigned char d = 0;
    
    while (i >= 1) {
        i = P_UP(i);
        d++;
    }
    
    return d;
}

size_t p_index(size_t i) {
    return i + 1 - (uz(1) << p_depth(i));
}

size_t p_width(size_t i) {
    return p_tree_d - (p_tree[i] + p_depth(i));
}

void * p_node_to_region(size_t i) {
    // the easy one, get depth and index and do math.
    
    size_t bytes = uz(PAGE_BYTES) << (p_tree_d - p_depth(i));
    
    return p_page_region + p_index(i) * bytes;
}

size_t p_region_to_node(void * p) {
    // the hard one, get leaf and go up until you get P_USED_NODE.
    
    size_t o = (p - p_page_region) / PAGE_BYTES;
    size_t i = (uz(1) << p_tree_d) + o - 1;
    
    while (i >= 1) {
        if (p_tree[i] == P_USED_NODE) {
            break;
        }
        
        i = P_UP(i);
    }
    
    return i;
}

void p_sift(size_t i) {
    unsigned char u, v, w;
    
    while (i >= 1) {
        i = P_UP(i);
        
        u = p_tree[P_DOWN(i, 1)];
        v = p_tree[P_DOWN(i, 2)];
        w = macro_min(u, v) + 1;
        
        if (u == v) {
            if (u == P_FREE_NODE || u == P_USED_NODE) {
                w = u;
            }
        }
        
        if (p_tree[i] == w) {
            break;
        }
        
        p_tree[i] = w;
    }
}
