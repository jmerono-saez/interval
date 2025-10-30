#ifndef __INTERVAL_MACROS_H__
#define __INTERVAL_MACROS_H__

#include <stddef.h>

// when C supports the "uz" prefix I will be so happy.
#define uz(z) ((size_t)(z))

// intentionally prepended with "macro_" to know they are macros.
#define macro_max(x, y) ((x) < (y) ? (y) : (x))
#define macro_min(x, y) ((x) < (y) ? (x) : (y))

// usually used to turn __FILE__ and __LINE__ into strings.
#define __stringify(z) #z
#define stringify(z) __stringify(z)

#endif
