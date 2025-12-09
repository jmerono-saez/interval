#ifndef __INTERVAL_MACROS_H__
#define __INTERVAL_MACROS_H__

#include <stddef.h>

// === constants ===

// when C supports the "uz" prefix I will be so happy.
#define uz(z) ((size_t)(z))

// intentionally prepended with "macro_" to know they are macros.
#define macro_max(x, y) ((x) < (y) ? (y) : (x))
#define macro_min(x, y) ((x) < (y) ? (x) : (y))

// useful for parsing aligned structures.
#define align(p, w) ((p) = (void *)(((intptr_t)(p) + (w) - 1) & -(w)))

#endif
