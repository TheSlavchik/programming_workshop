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

typedef struct
{
    ref_count_t *gc;
    void *ref_to;
} cycle_object;

ref_count_t *gc_init(void *obj, pool_allocator *allocator, constructor constructor, deconstructor destructor);
void gc_increase(ref_count_t *rc);
void gc_decrease(ref_count_t *rc, pool_allocator *allocator);
void default_destructor(void *object, pool_allocator *allocator);
cycle_object *create_cycle_object(pool_allocator *allocator);
void create_cycle_reference(cycle_object *obj1, cycle_object *obj2);
int detected_cycle(cycle_object *start);
void delete_cycle(pool_allocator *allocator, cycle_object *obj);
