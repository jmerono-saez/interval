#ifndef __INTERVAL_OPERATIONS_H__
#define __INTERVAL_OPERATIONS_H__

void move(void * to, const void * from, long size);
void swap(void * data_1, void * data_2, long size);

long compare(const void * data_1, const void * data_2, long size);

long length_of(const char * text);

#endif
