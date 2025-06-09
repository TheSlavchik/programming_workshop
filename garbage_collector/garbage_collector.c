#include "garbage_collector.h"

void default_destructor(void *object, pool_allocator *allocator)
{
    if (object)
    {
        pool_free(allocator, object);
    }
}

ref_count_t *gc_init(void *obj, pool_allocator *allocator, constructor constructor, deconstructor destructor)
{
    if (allocator == NULL)
    {
        return NULL;
    }

    ref_count_t *rc = (ref_count_t *)pool_alloc(allocator);

    if (rc == NULL)
    {
        return NULL;
    }

    rc->count = 1;

    rc->constructor = constructor;

    if (constructor)
    {
        rc->object = constructor(allocator);
        if (rc->object == NULL)
        {
            pool_free(allocator, rc);
            return NULL;
        }
    }
    else
    {
        rc->object = obj;
    }

    if (destructor)
    {
        rc->destructor = destructor;
    }
    else
    {
        rc->destructor = default_destructor;
    }

    return rc;
}

void gc_increase(ref_count_t *rc)
{
    if (rc)
    {
        rc->count++;
    }
}

void gc_decrease(ref_count_t *rc, pool_allocator *allocator)
{
    if (rc)
    {
        rc->count--;
        if (rc->count == 0)
        {
            if (rc->destructor)
            {
                rc->destructor(rc->object, allocator);
            }

            pool_free(allocator, rc);
        }
    }
}
