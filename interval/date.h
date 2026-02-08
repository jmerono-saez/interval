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

long leap_years(long y);
long days_in_year(long y);
long days_since_year(long y, long m, long d);
long days_in_month(long y, long m);

void date_normalize(date_t * date);

bool date_compare(const date_t * date_1, const date_t * date_2);

long date_to_days(const date_t * date);
long date_to_seconds(const date_t * date, bool is_period);
long date_weekday(const date_t * date);

#endif
