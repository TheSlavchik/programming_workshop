#include "garbage_collector.h"
#include <assert.h>

void create_reference_test()
{
    pool_allocator *allocator = (pool_allocator *)malloc(sizeof(pool_allocator));
    init_allocator(allocator, sizeof(ref_count_t), 10);

    void *object = (int *)pool_alloc(allocator);
    ref_count_t *ref_counter = gc_init(object, allocator, NULL, NULL);

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
    ref_count_t *ref_counter = gc_init(object, allocator, NULL, NULL);

    gc_increase(ref_counter);
    assert(ref_counter->count == 2);

    pool_destroy(allocator);
}

void decrease_reference_test()
{
    pool_allocator *allocator = (pool_allocator *)malloc(sizeof(pool_allocator));
    init_allocator(allocator, sizeof(ref_count_t), 10);

    void *object = (int *)pool_alloc(allocator);
    ref_count_t *ref_counter = gc_init(object, allocator, NULL, NULL);

    gc_increase(ref_counter);
    gc_decrease(ref_counter, allocator);
    assert(ref_counter->count == 1);
    gc_decrease(ref_counter, allocator);
    pool_destroy(allocator);
}

void custom_destructor_constructor_test()
{
    typedef struct
    {
        char a;
        int b;
    } test_t;

    void destructor(void *object, pool_allocator *allocator)
    {
        if (object == NULL)
        {
            return;
        }
        test_t *t = (test_t *)object;
        pool_free(allocator, t);
    }

    void *constructor(pool_allocator * allocator)
    {
        test_t *t = (test_t *)pool_alloc(allocator);
        if (t == NULL)
        {
            return NULL;
        }
        t->a = 'a';
        t->b = 740;
        return (void *)t;
    }

    pool_allocator *allocator = (pool_allocator *)malloc(sizeof(pool_allocator));
    init_allocator(allocator, sizeof(ref_count_t), 10);

    void *object = (int *)pool_alloc(allocator);
    ref_count_t *gc = gc_init(NULL, allocator, constructor, destructor);

    assert(gc != NULL);
    assert(gc->count == 1);
    test_t *test = (test_t *)gc->object;
    assert(test->a == 'a');
    assert(test->b == 740);
    assert(gc->constructor == constructor);
    assert(gc->destructor == destructor);

    gc_decrease(gc, allocator);
    pool_destroy(allocator);
}

void default_destructor_constructor_test()
{
    pool_allocator *allocator = (pool_allocator *)malloc(sizeof(pool_allocator));
    init_allocator(allocator, sizeof(ref_count_t), 10);

    void *object = (int *)pool_alloc(allocator);
    ref_count_t *ref_counter = gc_init(object, allocator, NULL, NULL);

    assert(ref_counter->destructor == default_destructor);
    assert(ref_counter->constructor == NULL);

    gc_decrease(ref_counter, allocator);
    pool_destroy(allocator);
}

int main()
{
    create_reference_test();
    increase_reference_test();
    decrease_reference_test();
    custom_destructor_constructor_test();
    default_destructor_constructor_test();

    return 0;
}
