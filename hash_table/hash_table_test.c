#include "hash_table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_init_free()
{
    pool_allocator allocator;
    init_allocator(&allocator, sizeof(struct hash_table_entry), 10);

    hash_table table;
    assert(hash_table_init(&table, 5, &allocator) == 0);

    assert(table.capacity == 5);
    assert(table.allocator == &allocator);

    hash_table_free(&table);
}

void test_insert_get()
{
    pool_allocator allocator;
    init_allocator(&allocator, 32, 10);
    hash_table table;
    hash_table_init(&table, 5, &allocator);

    int value = 42;
    assert(hash_table_insert(&table, NULL, &value) == NULL_KEY);
    assert(hash_table_insert(&table, "key1", &value) == 0);

    int *retrieved;
    hash_table_get(&table, "key1", (void **)&retrieved);
    assert(retrieved != NULL);
    assert(retrieved[0] == 42);
    hash_table_free(&table);
}

void test_delete()
{
    pool_allocator allocator;
    init_allocator(&allocator, sizeof(struct hash_table_entry), 10);
    hash_table table;
    hash_table_init(&table, 5, &allocator);

    int value = 100;
    int *retrieved;
    hash_table_insert(&table, "key1", &value);

    hash_table_delete(&table, "key1");
    assert(hash_table_delete(&table, NULL) == NULL_KEY);
    assert(hash_table_get(&table, "key1", (void **)&retrieved) == KEY_NOT_FOUND);

    hash_table_free(&table);
}

void test_collisions()
{
    pool_allocator allocator;
    init_allocator(&allocator, sizeof(struct hash_table_entry), 20);
    hash_table table;
    hash_table_init(&table, 1, &allocator);

    int values[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        char key[10];
        sprintf(key, "key%d", i);
        assert(hash_table_insert(&table, key, (void **)&values[i]) == 0);
    }

    for (int i = 0; i < 5; i++)
    {
        char key[10];
        sprintf(key, "key%d", i);
        int *val;
        hash_table_get(&table, key, (void **)&val);
        assert(val != NULL);
        assert(val[0] == i + 1);
    }

    hash_table_free(&table);
}

void test_allocator_overflow()
{
    pool_allocator allocator;
    init_allocator(&allocator, sizeof(struct hash_table_entry), 2);

    hash_table table;
    hash_table_init(&table, 5, &allocator);

    int v1 = 1, v2 = 2, v3 = 3;
    int *retrieved;
    hash_table_insert(&table, "key1", &v1);
    hash_table_insert(&table, "key2", &v2);
    assert(hash_table_insert(&table, "key3", &v3) == MEMORY_ALLOCATION_ERROR);
    assert(hash_table_get(&table, "key3", (void **)&retrieved) == KEY_NOT_FOUND);
}

int main()
{
    test_init_free();
    test_insert_get();
    test_delete();
    test_collisions();
    test_allocator_overflow();
    return 0;
}
