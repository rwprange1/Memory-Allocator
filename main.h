#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <intsafe.h>






void* malloc_new(SIZE_T size, HANDLE heap);

void* calloc_new(SIZE_T num_elements, SIZE_T element_size, HANDLE heap);

void* realloc_new(void* ptr,  SIZE_T size);

void free_new(LPVOID ptr);