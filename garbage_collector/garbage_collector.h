#include "../pool_allocator/pool_allocator.h"
#include <stdlib.h>

typedef struct
{
    size_t count;
    void *object;
} ref_count_t;

ref_count_t *gc_init(void *obj, pool_allocator *allocator);
void gc_increase(ref_count_t *rc);
void gc_decrease(ref_count_t *rc, pool_allocator *allocator);
