#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

void *bsearch(const void *key,
              const void *base,
              size_t num,
              size_t size,
              int (*compar)(const void *, const void *));


int compare_int(const void *a, const void *b);
int compare_float(const void *a, const void *b);
int compare_string(const void *a, const void *b);


typedef struct {
    int         id;
    const char *name;
} Item;
int compare_struct_item_by_id(const void *a, const void *b);

#endif /* SEARCH_H */
