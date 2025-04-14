#include "pool_allocator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void int_test()
{
    pool_allocator *allocator = (pool_allocator *)malloc(sizeof(pool_allocator));
    init_allocator(allocator, sizeof(int), 3);

    int *a = (int *)pool_alloc(allocator);
    assert(a != NULL);
    assert(allocator->free_blocks_amount == 2);
    assert(allocator->used_blocks_amount == 1);

    int *b = (int *)pool_alloc(allocator);
    assert(b != NULL);
    assert(allocator->free_blocks_amount == 1);
    assert(allocator->used_blocks_amount == 2);

    int *c = (int *)pool_alloc(allocator);
    assert(c != NULL);
    assert(allocator->free_blocks_amount == 0);
    assert(allocator->used_blocks_amount == 3);

    int *d = (int *)pool_alloc(allocator);
    assert(d == NULL);
    assert(allocator->free_blocks_amount == 0);
    assert(allocator->used_blocks_amount == 3);

    pool_free(allocator, b);
    assert(allocator->free_blocks_amount == 1);
    assert(allocator->used_blocks_amount == 2);

    d = (int *)pool_alloc(allocator);
    assert(d != NULL);
    assert(allocator->free_blocks_amount == 0);
    assert(allocator->used_blocks_amount == 3);

    pool_destroy(allocator);
}

int main()
{
    int_test();

    return 0;
}