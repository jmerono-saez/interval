#include <interval/date.h>

static const long month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const long month_sums[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

static inline long good_division(long p, long q) {
    if (p < 0) {
        return (p - q + 1) / q;
    }
    
    return p / q;
}

long leap_years(long y) {
    return good_division(y + 4 - 1, 4) - good_division(y + 100 - 1, 100) + good_division(y + 400 - 1, 400);
}

long days_in_year(long y) {
    return 365 + leap_years(y + 1) - leap_years(y);
}

long days_since_year(long y, long m, long d) {
    if (m <= 2 || leap_years(y) == leap_years(y + 1)) {
        d--;
    }
    
    return month_sums[m] + d;
}

long days_in_month(long y, long m) {
    return ((m == 2 && leap_years(y) != leap_years(y + 1)) ? 29 : month_days[m]);
}

void date_normalize(date_t * date) {
    date->i += good_division(date->s, 60);
    date->s -= good_division(date->s, 60) * 60;
    
    date->h += good_division(date->i, 60);
    date->i -= good_division(date->i, 60) * 60;
    
    date->d += good_division(date->h, 24);
    date->h -= good_division(date->h, 24) * 24;
    
    while (true) {
        if (date->d <= 0) {
            date->y--;
            date->d += days_in_year(date->y);
        } else if (date->d >= days_in_year(date->y) + 1) {
            date->d -= days_in_year(date->y);
            date->y++;
        } else {
            break;
        }
    }
    
    while (true) {
        if (date->d <= 0) {
            date->m--;
            
            if (date->m <= 0) {
                date->y--;
                date->m += 12;
            }
            
            date->d += days_in_month(date->y, date->m);
        } else if (date->d >= days_in_month(date->y, date->m) + 1) {
            date->d -= days_in_month(date->y, date->m);
            date->m++;
            
            if (date->m >= 13) {
                date->m -= 12;
                date->y++;
            }
        } else {
            break;
        }
    }
    
    date->y += good_division(date->m - 1, 12);
    date->m -= good_division(date->m - 1, 12) * 12;
}

bool date_compare(const date_t * date_1, const date_t * date_2) {
    if (date_1->y != date_2->y) {
        return (date_1->y >= date_2->y);
    } else if (date_1->m != date_2->m) {
        return (date_1->m >= date_2->m);
    } else if (date_1->d != date_2->d) {
        return (date_1->d >= date_2->d);
    } else if (date_1->h != date_2->h) {
        return (date_1->h >= date_2->h);
    } else if (date_1->i != date_2->i) {
        return (date_1->i >= date_2->i);
    } else {
        return (date_1->s >= date_2->s);
    }
}

long date_to_days(const date_t * date) {
    long leaps = leap_years(date->y);
    return date->y * 365 + leaps + days_since_year(date->y, date->m, date->d);
}

long date_to_seconds(const date_t * date, bool is_period) {
    long days = (is_period ? date->d : date_to_days(date));
    return days * 86400 + date->h * 3600 + date->i * 60 + date->s;
}

long date_weekday(const date_t * date) {
    return (date_to_days(date) + 5) % 7;
}
