//malloc.c
//Create Year:2024
//Author : A.Goktug
//malloc-free implementation 
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define HEAP_SIZE 1024

static uint8_t heap[HEAP_SIZE];
static uint8_t *heap_end = heap;
static uint8_t *heap_max = heap + HEAP_SIZE;

typedef struct BlockHeader {
    size_t size;
    struct BlockHeader *next;
} BlockHeader;

static BlockHeader *free_list = NULL;

void print_memory_status(const char *message) {
    printf("%s\n", message);
    printf("Heap end: %p\n", heap_end);
    printf("Free list: %p\n", free_list);
    for (BlockHeader *block = free_list; block != NULL; block = block->next) {
        printf("  Block at %p, size %zu\n", block, block->size);
    }
}

void *malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    size_t total_size = size + sizeof(BlockHeader);

    BlockHeader *prev = NULL;
    BlockHeader *current = free_list;

    while (current != NULL) {
        if (current->size >= total_size) {
            if (current->size - total_size >= sizeof(BlockHeader) + 1) {
                BlockHeader *new_block = (BlockHeader *)((uint8_t *)current + total_size);
                new_block->size = current->size - total_size;
                new_block->next = current->next;
                current->size = total_size - sizeof(BlockHeader);
                current->next = new_block;
            }
            if (prev == NULL) {
                free_list = current->next;
            } else {
                prev->next = current->next;
            }
            return (void *)((uint8_t *)current + sizeof(BlockHeader));
        }
        prev = current;
        current = current->next;
    }

    if (heap_end + total_size > heap_max) {
        return NULL;
    }

    BlockHeader *new_block = (BlockHeader *)heap_end;
    new_block->size = size;
    heap_end += total_size;

    return (void *)((uint8_t *)new_block + sizeof(BlockHeader));
}

void free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    BlockHeader *block = (BlockHeader *)((uint8_t *)ptr - sizeof(BlockHeader));
    block->next = free_list;
    free_list = block;
}