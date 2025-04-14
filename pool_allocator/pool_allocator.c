#include "pool_allocator.h"
#include <stdio.h>
#include <stdlib.h>

void init_allocator(pool_allocator *allocator, int block_size, int blocks_amount)
{
    allocator->block_size = block_size;
    allocator->free_blocks_amount = blocks_amount;
    allocator->used_blocks_amount = 0;
    allocator->free_blocks = NULL;

    allocator->allocated_memory = (char *)malloc((block_size + sizeof(block)) * blocks_amount);

    for (size_t i = 0; i < blocks_amount; i++)
    {
        block *current_block = (block *)(allocator->allocated_memory + i * (block_size + sizeof(block)));
        current_block->next = allocator->free_blocks;
        allocator->free_blocks = current_block;
    }
}

void *pool_alloc(pool_allocator *allocator)
{
    if (allocator->free_blocks == NULL && allocator->free_blocks_amount == 0)
    {
        return NULL;
    }

    block *block = allocator->free_blocks;
    allocator->free_blocks = block->next;

    allocator->free_blocks_amount--;
    allocator->used_blocks_amount++;

    return (void *)block;
}

void pool_free(pool_allocator *allocator, void *ptr)
{
    block *current_block = (block *)ptr;
    current_block->next = allocator->free_blocks;
    allocator->free_blocks = current_block;
    allocator->free_blocks_amount++;
    allocator->used_blocks_amount--;
}

void pool_destroy(pool_allocator *allocator)
{
    free(allocator->allocated_memory);
    free(allocator);
}
