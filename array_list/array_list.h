#include "../pool_allocator/pool_allocator.h"
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    struct node *next;
} node;

typedef struct
{
    void **data;
    size_t capacity;
    size_t size;
    pool_allocator *allocator;
    size_t data_size;
} array_list;

void array_list_init(array_list *list, pool_allocator *allocator, size_t data_size);
void array_list_add(array_list *list, void *data, size_t index);
void *array_list_get(array_list *list, size_t index);
void array_list_del(array_list *list, size_t index);
void array_list_free(array_list *list);
