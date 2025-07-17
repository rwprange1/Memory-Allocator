#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void* malloc_new(size_t size);

void* calloc_new(size_t num_elements, size_t element_size);

void* realloc_new(void* ptr,  size_t size);

void free_new(void* ptr);