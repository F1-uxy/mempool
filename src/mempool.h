#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define POOL_SIZE 1024

typedef struct 
{
    void* memory;
    bool* used;
    size_t block_size;
    size_t capacity;
} MemoryPool;

void initMemoryPool(MemoryPool* pool, void* memory, bool* used_flags, size_t block_size, size_t capacity);
void* allocateMemory(MemoryPool* pool, size_t count);
void freeMemory(MemoryPool* pool, void* ptr, size_t count);


#endif