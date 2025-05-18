#include "array_list.h"
#include <assert.h>

int test()
{
    pool_allocator allocator;
    init_allocator(&allocator, 4, 100);

    array_list list;
    array_list_init(&list, &allocator, 8);

    assert(list.size == 0);
    assert(list.data == NULL);

    int a = 10, b = 20, c = 30, d = 40;

    array_list_add(&list, &a, 0);
    array_list_add(&list, &b, 1);
    array_list_add(&list, &c, 1);
    array_list_add(&list, &d, 0);

    assert(list.size == 4);
    assert(list.capacity >= 4);

    assert(*(int *)array_list_get(&list, 0) == 40);
    assert(*(int *)array_list_get(&list, 1) == 10);
    assert(*(int *)array_list_get(&list, 2) == 30);
    assert(*(int *)array_list_get(&list, 3) == 20);
    assert(array_list_get(&list, 4) == NULL);

    array_list_del(&list, 1);
    assert(list.size == 3);
    assert(*(int *)array_list_get(&list, 1) == 30);

    array_list_del(&list, 0);
    assert(list.size == 2);
    assert(*(int *)array_list_get(&list, 0) == 30);

    array_list_del(&list, 1);
    assert(list.size == 1);
    assert(*(int *)array_list_get(&list, 0) == 30);

    array_list_free(&list);
    assert(list.size == 0);
    assert(list.capacity == 0);
    assert(list.data == NULL);

    return 0;
}

int main()
{
    test();

    return 0;
}
