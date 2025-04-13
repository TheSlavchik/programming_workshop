#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    struct block* next;
} block;

typedef struct
{
    int block_size;
    int free_blocks_amount;
    int used_blocks_amount;
    block* free_blocks;
} pool_allocator;

void init_allocator(pool_allocator* allocator, int block_size, int blocks_amount)
{
    allocator->block_size = block_size;
    allocator->free_blocks_amount = blocks_amount;
    allocator->used_blocks_amount = 0;
    allocator->free_blocks = NULL;
    
    char* allocated_memory = (char*)malloc((block_size + sizeof(block)) * blocks_amount);

    for (size_t i = 0; i < blocks_amount; i++)
    {
        block* current_block = (block*)(allocated_memory+ i * (block_size + sizeof(block)));
        current_block->next = allocator->free_blocks;
        allocator->free_blocks = current_block;
    }
}

void* pool_alloc(pool_allocator* allocator)
{
    if (allocator->free_blocks == NULL && allocator->free_blocks_amount == 0) 
    {
        return NULL;  
    }
    
    block* block = allocator->free_blocks;
    allocator->free_blocks = block->next;
    allocator->free_blocks_amount--;
    allocator->used_blocks_amount++;
    
    return (void*)block;
}

void pool_free(pool_allocator* allocator, void* ptr)
{
    block* current_block = (block*)ptr;
    current_block->next = allocator->free_blocks;
    allocator->free_blocks = current_block;
    allocator->free_blocks_amount++;
    allocator->used_blocks_amount--;
}

int main()
{
    pool_allocator* allocator = (pool_allocator*)malloc(sizeof(pool_allocator));
    
    init_allocator(allocator, 4, 3);
    
    int* a = (int*)pool_alloc(allocator);
    printf("%d, %d \n", allocator->free_blocks_amount, allocator->used_blocks_amount);
    int* b = (int*)pool_alloc(allocator);
    printf("%d, %d \n", allocator->free_blocks_amount, allocator->used_blocks_amount);
    int* c = (int*)pool_alloc(allocator);
    printf("%d, %d \n", allocator->free_blocks_amount, allocator->used_blocks_amount);
    int* d = (int*)pool_alloc(allocator);
    printf("%d, %d \n", allocator->free_blocks_amount, allocator->used_blocks_amount);
    printf("%p, %p, %p, %p, \n", a, b, c, d);

    pool_free(allocator, c);
    printf("%d, %d \n", allocator->free_blocks_amount, allocator->used_blocks_amount);
    d = (int*)pool_alloc(allocator);
    printf("%p, %p, %p, %p, \n", a, b, c, d);

    return 0;
}