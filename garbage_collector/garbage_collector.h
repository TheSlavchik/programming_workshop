#include "../pool_allocator/pool_allocator.h"
#include <stdlib.h>

typedef void (*deconstructor)(void *object, pool_allocator *allocator);
typedef void *(*constructor)(pool_allocator *allocator);

typedef struct
{
    size_t count;
    void *object;
    deconstructor destructor;
    constructor constructor;
} ref_count_t;

ref_count_t *gc_init(void *obj, pool_allocator *allocator, constructor constructor, deconstructor destructor);
void gc_increase(ref_count_t *rc);
void gc_decrease(ref_count_t *rc, pool_allocator *allocator);
void default_destructor(void *object, pool_allocator *allocator);
