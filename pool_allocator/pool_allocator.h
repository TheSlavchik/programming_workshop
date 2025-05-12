typedef struct block
{
    struct block *next;
} block;

typedef struct
{
    char *allocated_memory;
    int block_size;
    int free_blocks_amount;
    int used_blocks_amount;
    struct block *free_blocks;
} pool_allocator;

void init_allocator(pool_allocator *allocator, int block_size, int blocks_amount);
void *pool_alloc(pool_allocator *allocator);
void pool_free(pool_allocator *allocator, void *ptr);
void pool_destroy(pool_allocator *allocator);
