#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "mempool.h"

#define BLOCK_SIZE 16
#define BLOCK_COUNT 10

int main(void)
{
    uint8_t memory[BLOCK_SIZE * BLOCK_COUNT];
    bool used_flags[BLOCK_COUNT];

    MemoryPool pool;
    initMemoryPool(&pool, memory, used_flags, BLOCK_SIZE, BLOCK_COUNT);

    // Test: pool is correctly initialized
    for (size_t i = 0; i < BLOCK_COUNT; i++)
    {
        assert(pool.used[i] == false);
    }

    // Test: allocation of one block
    void* ptr1 = allocateMemory(&pool, 1);
    assert(ptr1 != NULL);
    assert(pool.used[0] == true);

    // Test: allocation of multiple blocks
    void* ptr2 = allocateMemory(&pool, 3);
    assert(ptr2 != NULL);

    size_t index2 = ((uint8_t*)ptr2 - memory) / BLOCK_SIZE;
    for (size_t i = 0; i < 3; i++)
    {
        assert(pool.used[index2 + i] == true);
    }

    // Test: free and reallocate
    freeMemory(&pool, ptr1, 1);
    assert(pool.used[0] == false);

    void* ptr3 = allocateMemory(&pool, 1);
    assert(ptr3 == memory); // Should return same as ptr1 if reused correctly

    // Test: exhaustion
    // Allocate remaining blocks
    while (allocateMemory(&pool, 1) != NULL);

    void* ptr_fail = allocateMemory(&pool, 1);
    assert(ptr_fail == NULL); // Should fail due to exhaustion

    printf("All mempool tests passed!\n");
    return 0;
}