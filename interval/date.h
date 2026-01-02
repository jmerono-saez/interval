#ifndef __INTERVAL_DATE_H__
#define __INTERVAL_DATE_H__

// === constants ===

#define date_null ((date_t) {0, 0, 0, 0, 0, 0})

// === types ===

typedef struct date_t date_t;

struct date_t {
    long y, m, d, h, i, s;
};

// === functions ===

void date_normalize(date_t * date);

long date_compare(const date_t * date_1, const date_t * date_2);

#endif
