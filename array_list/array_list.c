#include "array_list.h"

void array_list_init(array_list *list, pool_allocator *allocator, size_t data_size)
{
    list->data = NULL;
    list->capacity = 0;
    list->size = 0;
    list->allocator = allocator;
    list->data_size = data_size;
}

int array_list_add(array_list *list, void *data, size_t index)
{
    if (index > list->size)
    {
        return INDEX_OUT_OF_BOUNDS;
    }

    if (list->size >= list->capacity)
    {
        size_t new_capacity = list->capacity == 0 ? 1 : list->capacity * 2;
        void **new_data = (void **)pool_alloc(list->allocator);

        if (!new_data)
        {
            return ALLOCATION_ERROR;
        }

        memcpy(new_data, list->data, list->size * sizeof(void *));

        if (list->data)
        {
            pool_free(list->allocator, list->data);
        }

        list->data = new_data;
        list->capacity = new_capacity;
    }

    void *new_element = pool_alloc(list->allocator);

    if (!new_element)
    {
        return ALLOCATION_ERROR;
    }

    memcpy(new_element, data, list->data_size);

    for (size_t i = list->size; i > index; i--)
    {
        list->data[i] = list->data[i - 1];
    }

    list->data[index] = new_element;
    list->size++;

    return 0;
}

int array_list_get(array_list *list, size_t index, void **data)
{
    if (index >= list->size)
    {
        return INDEX_OUT_OF_BOUNDS;
    }

    data[0] = list->data[index];

    return 0;
}

int array_list_del(array_list *list, size_t index)
{
    if (index >= list->size)
    {
        return INDEX_OUT_OF_BOUNDS;
    }

    for (size_t i = index; i < list->size - 1; i++)
    {
        list->data[i] = list->data[i + 1];
    }

    list->size--;

    return 0;
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
