#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <intsafe.h>
#include <string.h>







struct Memory{
    // points to the allocated memory
    HANDLE ptr;
    // how much memory have we allocated
    SIZE_T mem_allocated;
    // 0 if we are using, 1 if its freed
    BOOL free;
    // how much memory have we used
    SIZE_T mem_used;
    // size of what we are storing
    SIZE_T type_size;
};


enum Errors{
    USE_AFTER_FREE,
    INVALID_TYPE,
    INSUFFIECNT_MEMORY,
    OK,
};


struct Memory new_mem(SIZE_T mem_allowed, LPVOID ptr);

void print_error_value(enum Errors);

LPVOID get_chunk(SIZE_T);



struct Memory malloc_new(SIZE_T size);

struct Memory calloc_new(SIZE_T num_elements, SIZE_T element_size);

struct Memory realloc_new(struct Memory*,  SIZE_T size);

void free_new(struct Memory*);


SIZE_T has_space(struct Memory);
enum Errors add_to_mem(struct Memory*, void* , SIZE_T);


#endif