#include "array_list.h"
#include <assert.h>

void array_list_init(array_list *list, pool_allocator *allocator, size_t data_size)
{
    list->data = NULL;
    list->capacity = 0;
    list->size = 0;
    list->allocator = allocator;
    list->data_size = data_size;
}

void array_list_add(array_list *list, void *data, size_t index)
{
    if (index > list->size)
    {
        return;
    }

    if (list->size >= list->capacity)
    {
        size_t new_capacity = list->capacity == 0 ? 1 : list->capacity * 2;

        void **new_data = (void **)pool_alloc(list->allocator);
        if (!new_data)
            return;

        if (list->data)
        {
            memcpy(new_data, list->data, list->size * list->data_size);
            pool_free(list->allocator, list->data);
        }

        list->data = new_data;
        list->capacity = new_capacity;
    }

    for (size_t i = list->size; i > index; i--)
    {
        list->data[i] = list->data[i - 1];
    }

    list->data[index] = data;
    list->size++;
}

void *array_list_get(array_list *list, size_t index)
{
    if (index >= list->size)
    {
        return NULL;
    }
    return list->data[index];
}

void array_list_del(array_list *list, size_t index)
{
    if (index >= list->size)
    {
        return;
    }

    for (size_t i = index; i < list->size - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }

    list->size--;
}

void array_list_free(array_list *list)
{
    if (list->data)
    {
        pool_free(list->allocator, list->data);
        list->data = NULL;
    }
    list->capacity = 0;
    list->size = 0;
}
