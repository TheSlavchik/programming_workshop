#include "array_list.h"
#include <assert.h>
#include <stdio.h>

int add_get_test()
{
    int a = 10, b = 20, c = 30, d = 40;

    pool_allocator allocator;
    init_allocator(&allocator, 32, 10);

    array_list list;
    array_list_init(&list, &allocator, sizeof(int));

    array_list_add(&list, &a, 0);
    array_list_add(&list, &b, 1);
    array_list_add(&list, &c, 1);
    array_list_add(&list, &d, 0);

    int *data;

    array_list_get(&list, 0, (void **)&data);
    assert(data[0] == 40);
    array_list_get(&list, 1, (void **)&data);
    assert(data[0] == 10);
    array_list_get(&list, 2, (void **)&data);
    assert(data[0] == 30);
    array_list_get(&list, 3, (void **)&data);
    assert(data[0] == 20);

    array_list_free(&list);

    return 0;
}

int remove_test()
{
    int a = 10, b = 20, c = 30, d = 40;

    pool_allocator allocator;
    init_allocator(&allocator, 32, 10);

    array_list list;
    array_list_init(&list, &allocator, sizeof(int));

    array_list_add(&list, &a, 0);
    array_list_add(&list, &b, 1);
    array_list_add(&list, &c, 1);
    array_list_add(&list, &d, 0);

    int *data;

    array_list_del(&list, 1);
    assert(list.size == 3);
    array_list_get(&list, 1, (void **)&data);
    assert(data[0] == 30);

    array_list_del(&list, 0);
    assert(list.size == 2);
    array_list_get(&list, 0, (void **)&data);
    assert(data[0] == 30);

    array_list_del(&list, 1);
    assert(list.size == 1);
    array_list_get(&list, 0, (void **)&data);
    assert(data[0] == 30);

    array_list_free(&list);

    return 0;
}

int out_of_bounds_test()
{
    int a = 10;

    pool_allocator allocator;
    init_allocator(&allocator, 32, 10);

    array_list list;
    array_list_init(&list, &allocator, sizeof(int));

    array_list_add(&list, &a, 0);

    int *data;

    assert(array_list_get(&list, 1, (void **)&data) == INDEX_OUT_OF_BOUNDS);
    assert(array_list_add(&list, &a, 2) == INDEX_OUT_OF_BOUNDS);
    assert(array_list_del(&list, 2) == INDEX_OUT_OF_BOUNDS);

    array_list_free(&list);

    return 0;
}

int allocator_error_test()
{
    int a = 10;

    pool_allocator allocator;
    init_allocator(&allocator, 32, 2);

    array_list list;
    array_list_init(&list, &allocator, sizeof(int));

    array_list_add(&list, &a, 0);
    assert(array_list_add(&list, &a, 1) == ALLOCATION_ERROR);

    array_list_free(&list);

    return 0;
}

int main()
{
    add_get_test();
    remove_test();
    out_of_bounds_test();
    allocator_error_test();

    return 0;
}
