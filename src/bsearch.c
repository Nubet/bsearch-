#include "search.h"
#include <string.h>

void *bsearch(const void *key, const void *base,
        size_t num, size_t size,
        int (*compar)(const void *, const void *))
{
	//empty array
	if (num == 0) {
        return NULL;
    }
    
    size_t low  = 0; // first index
    size_t high = num - 1; // last index

    while (low <= high) {
        size_t mid  = low + (high - low) / 2;
        const void *elem = (const char *)base + mid * size;

        if (compar(key, elem) == 0) {
            return (void *)elem;
        }
        else if (compar(key, elem) < 0) { // left half
            if (mid == 0) break;   // avoid underflow
            high = mid - 1;
        }
        else { // right half
            low = mid + 1;
        }
    }
    return NULL;
}

/* comparator: –1, 0 or +1 */
int compare_int(const void *a, const void *b)
{
     return (*(int *)a - *(int *)b);
}

int compare_float(const void *a, const void *b)
{
    return *(float *)a - *(float *)b;
}

int compare_string(const void *a, const void *b)
{
 return strcmp(*(const char* const*)a, *(const char* const*)b);
}

int compare_struct_item_by_id(const void *a, const void *b)
{
   return ((const Item*)a)->id - ((const Item*)b)->id;
}
