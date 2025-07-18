#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <intsafe.h>
#include <string.h>



struct Memory{
    // points to the allocated memory
    void* ptr;
    // how much memory have we allocated
    SIZE_T mem_allocated;
    // 0 if we are using, 1 if its freed
    int free;
    // how much memory have we used
    SIZE_T mem_used;
    // size of what we are storing
    SIZE_T type_size;
}Memory;


struct Memory new_mem(SIZE_T mem_allowed, LPVOID ptr);

LPVOID get_chunk(SIZE_T);



struct Memory malloc_new(SIZE_T size);

struct Memory calloc_new(SIZE_T num_elements, SIZE_T element_size);

struct Memory realloc_new(void* ptr,  SIZE_T size);

void free_new(LPVOID ptr, HANDLE);


SIZE_T has_space(struct Memory);
int add_to_mem(struct Memory*, void* , SIZE_T);


