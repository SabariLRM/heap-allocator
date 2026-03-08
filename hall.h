#ifndef MAL_H
#define MAL_H

#include <stddef.h>

void heap_init(size_t size);
void freeh(void);
char* alloc(int s);
void freec(char* p);

#endif
