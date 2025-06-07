#include "garbage_collector.h"
#include <assert.h>

void create_reference_test()
{
    pool_allocator *allocator = (pool_allocator *)malloc(sizeof(pool_allocator));
    init_allocator(allocator, sizeof(ref_count_t), 10);

    void *object = (int *)pool_alloc(allocator);
    ref_count_t *ref_counter = gc_init(object, allocator);

    assert(ref_counter != NULL);
    assert(ref_counter->object == object);
    assert(ref_counter->count == 1);

    pool_destroy(allocator);
}

void increase_reference_test()
{
    pool_allocator *allocator = (pool_allocator *)malloc(sizeof(pool_allocator));
    init_allocator(allocator, sizeof(ref_count_t), 10);

    void *object = (int *)pool_alloc(allocator);
    ref_count_t *ref_counter = gc_init(object, allocator);

    gc_increase(ref_counter);
    assert(ref_counter->count == 2);

    pool_destroy(allocator);
}

void decrease_reference_test()
{
    pool_allocator *allocator = (pool_allocator *)malloc(sizeof(pool_allocator));
    init_allocator(allocator, sizeof(ref_count_t), 10);

    void *object = (int *)pool_alloc(allocator);
    ref_count_t *ref_counter = gc_init(object, allocator);

    gc_increase(ref_counter);
    gc_decrease(ref_counter, allocator);
    assert(ref_counter->count == 1);

    gc_decrease(ref_counter, allocator);
    pool_destroy(allocator);
}

int main()
{
    create_reference_test();
    increase_reference_test();
    decrease_reference_test();

    return 0;
}
