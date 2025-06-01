#include "hash_table.h"

static long hash_function(const char *key, size_t capacity)
{
    long hash = 7401;
    int c;
    while (c = *key++)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

int hash_table_init(hash_table *table, size_t capacity, pool_allocator *allocator)
{
    table->capacity = capacity;
    table->allocator = allocator;
    table->buckets = (hash_table_entry **)calloc(capacity, sizeof(hash_table_entry *));

    if (!table->buckets)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    return 0;
}

int hash_table_insert(hash_table *table, const char *key, void *value)
{
    if (!key)
    {
        return NULL_KEY;
    }

    long index = hash_function(key, table->capacity);
    hash_table_entry *entry = (hash_table_entry *)pool_alloc(table->allocator);

    if (!entry)
    {
        return MEMORY_ALLOCATION_ERROR;
    }

    entry->key = strdup(key);
    if (!entry->key)
    {
        pool_free(table->allocator, entry);
        return MEMORY_ALLOCATION_ERROR;
    }

    entry->value = value;
    entry->next = table->buckets[index];
    table->buckets[index] = entry;

    return 0;
}

int hash_table_get(hash_table *table, const char *key, void **result)
{
    if (!key)
    {
        return NULL_KEY;
    }

    long index = hash_function(key, table->capacity);
    hash_table_entry *entry = table->buckets[index];

    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            *result = entry->value;
            return 0;
        }
        entry = entry->next;
    }

    return KEY_NOT_FOUND;
}

int hash_table_delete(hash_table *table, const char *key)
{
    if (!key)
    {
        return NULL_KEY;
    }

    long index = hash_function(key, table->capacity);
    hash_table_entry **entry_ptr = &table->buckets[index];

    while (*entry_ptr)
    {
        hash_table_entry *entry = *entry_ptr;
        if (strcmp(entry->key, key) == 0)
        {
            *entry_ptr = entry->next;
            free(entry->key);
            pool_free(table->allocator, entry);
            return 0;
        }
        entry_ptr = &(*entry_ptr)->next;
    }

    return 0;
}

void hash_table_free(hash_table *table)
{
    for (size_t i = 0; i < table->capacity; i++)
    {
        hash_table_entry *entry = table->buckets[i];
        while (entry)
        {
            hash_table_entry *next = entry->next;
            free(entry->key);
            pool_free(table->allocator, entry);
            entry = next;
        }
    }

    free(table->buckets);
}
