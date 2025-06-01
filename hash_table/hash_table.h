#include "../pool_allocator/pool_allocator.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_ALLOCATION_ERROR -1
#define NULL_KEY -2
#define KEY_NOT_FOUND -3

typedef struct hash_table_entry
{
    char *key;
    void *value;
    struct hash_table_entry *next;
} hash_table_entry;

typedef struct
{
    hash_table_entry **buckets;
    size_t capacity;
    pool_allocator *allocator;
} hash_table;

int hash_table_init(hash_table *table, size_t capacity, pool_allocator *allocator);
int hash_table_insert(hash_table *table, const char *key, void *value);
int hash_table_get(hash_table *table, const char *key, void **result);
int hash_table_delete(hash_table *table, const char *key);
void hash_table_free(hash_table *table);
