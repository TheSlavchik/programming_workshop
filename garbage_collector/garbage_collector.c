#include "garbage_collector.h"

ref_count_t *gc_init(void *obj, pool_allocator *allocator)
{
    if (obj == NULL || allocator == NULL)
    {
        return NULL;
    }

    ref_count_t *rc = (ref_count_t *)pool_alloc(allocator);

    if (rc == NULL)
    {
        return NULL;
    }

    rc->count = 1;
    rc->object = obj;
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
            if (rc->object == NULL)
            {
                pool_free(allocator, rc);
                return;
            }

            pool_free(allocator, rc->object);
            pool_free(allocator, rc);
        }
    }
}
