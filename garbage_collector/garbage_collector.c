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

    ref_count_t *gc = (ref_count_t *)pool_alloc(allocator);

    if (gc == NULL)
    {
        return NULL;
    }

    gc->count = 1;

    gc->constructor = constructor;

    if (constructor)
    {
        gc->object = constructor(allocator);
        if (gc->object == NULL)
        {
            pool_free(allocator, gc);
            return NULL;
        }
    }
    else
    {
        gc->object = obj;
    }

    if (destructor)
    {
        gc->destructor = destructor;
    }
    else
    {
        gc->destructor = default_destructor;
    }

    return gc;
}

void gc_increase(ref_count_t *gc)
{
    if (gc)
    {
        gc->count++;
    }
}

void gc_decrease(ref_count_t *gc, pool_allocator *allocator)
{
    if (gc)
    {
        gc->count--;
        if (gc->count == 0)
        {
            if (gc->destructor)
            {
                gc->destructor(gc->object, allocator);
            }

            pool_free(allocator, gc);
        }
    }
}

cycle_object *create_cycle_object(pool_allocator *allocator)
{
    if (allocator == NULL)
    {
        return NULL;
    }
    cycle_object *obj = (cycle_object *)pool_alloc(allocator);
    if (obj == NULL)
    {
        return NULL;
    }
    obj->gc = gc_init(obj, allocator, NULL, NULL);
    if (obj->gc == NULL)
    {
        pool_free(allocator, obj);
        return NULL;
    }
    obj->ref_to = NULL;
    return obj;
}

void create_cycle_reference(cycle_object *obj1, cycle_object *obj2)
{
    if (obj1 == NULL || obj2 == NULL || obj1->gc == NULL || obj2->gc == NULL)
    {
        return;
    }
    obj1->ref_to = obj2;
    obj2->ref_to = obj1;
    gc_increase(obj1->gc);
    gc_increase(obj2->gc);
}

int detected_cycle(cycle_object *start)
{
    if (start == NULL || start->ref_to == NULL)
    {
        return 0;
    }
    cycle_object *obj1 = start;
    cycle_object *obj2 = start->ref_to;
    while (obj2 && obj2->ref_to)
    {
        if (obj1 == obj2)
        {
            return 1;
        }
        obj1 = (cycle_object *)obj1->ref_to;
        obj2 = ((cycle_object *)obj2->ref_to)->ref_to;
    }
    return 0;
}

void delete_cycle(pool_allocator *allocator, cycle_object *obj)
{
    if (obj == NULL || obj->gc == NULL || allocator == NULL)
    {
        return;
    }
    if (detected_cycle(obj))
    {
        cycle_object *current = obj;
        cycle_object *next;
        do
        {
            next = (cycle_object *)current->ref_to;
            if (next == NULL)
            {
                break;
            }
            current->ref_to = NULL;
            if (next->gc)
            {
                gc_decrease(next->gc, allocator);
            }
            current = next;
        } while (current && current != obj);
        gc_decrease(obj->gc, allocator);
    }
}
