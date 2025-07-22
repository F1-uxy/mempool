#include "mempool.h"
#include <stdint.h>

void initMemoryPool(MemoryPool* pool, void* memory, bool* used_flags, size_t block_size, size_t capacity)
{
    pool->memory = memory;
    pool->used = used_flags;
    pool->block_size = block_size;
    pool->capacity = capacity;

    for(size_t i = 0; i < capacity; i++)
    {
        pool->used[i] = false;
    }
}

void* allocateMemory(MemoryPool* pool, size_t count)
{
    if(pool == NULL)
    {
        fprintf(stderr, "Pool is not initialized\n");
        return NULL;
    }
    for(size_t i = 0; i <= pool->capacity; i++)
    {
        bool found = true;
        for(size_t j = 0; j < count; j++)
        {
            if(pool->used[i + j])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            for(size_t j = 0; j < count; j++)
            {
                pool->used[i + j] = true;
            }

            return (uint8_t*)pool->memory + i * pool->block_size;
        }
    }

    return NULL;
}

void freeMemory(MemoryPool* pool, void* ptr, size_t count)
{
    size_t index = ((uint8_t*)ptr - (uint8_t*)pool->memory) / pool->block_size;
    for(size_t i = 0; i < count; i++)
    {
        pool->used[index + i] = false;
    }
}
