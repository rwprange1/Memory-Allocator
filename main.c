
#include "main.h"

int main(void) {
    HANDLE our_heap = GetProcessHeap();
    
    
    
  

}


/*
* returns a void pointer to an uninitialized chunk of memory on the heap
*
* size: the number of bytes to allocate
*
* returns: a void ptr to the chunk of memory
*/
void* malloc_new(SIZE_T size, HANDLE heap){
    LPVOID chunk = HeapAlloc(heap,HEAP_GENERATE_EXCEPTIONS, size );
    SIZE_T actualSize = HeapSize(heap, 0, chunk);
    printf("Malloc block size %zu\n", actualSize);
    return chunk;

}

/*
 * returns a void pointer to an initialized chunk of memory on the heap
 *
 * num_elements: the number of elements we need to store
 * element_size: how big in bytes is each element
 *
 * returns: a void pointer to the initialized chunk of memory
 */
void* calloc_new(SIZE_T num_elements, SIZE_T element_size, HANDLE heap ){
    LPVOID chunk = HeapAlloc(heap,HEAP_GENERATE_EXCEPTIONS, num_elements * element_size );
    SIZE_T actualSize = HeapSize(heap, 0, chunk);
    printf("calloc block size %zu\n", actualSize);
    return chunk;
}


/*
 * Given a pointer to a chunk of memory in the heap if possible allocate size
 * more bytes for this chunk
 *
 * prt: the pointer to the chunk in heap
 * size: how many bytes to allocate
 *
 * returns: a void pointer to the reallocated chunk
*/
void* realloc_new(void* ptr,  size_t size){

}


/*
 * given a pointer to a chunk in memory free it
 *
 * ptr: the pointer to the chunk in memory
 *
 * returns: void
 */
void free_new(LPVOID ptr, HANDLE heap){
    BOOL ret = HeapFree(heap, 0, ptr);

    if (ret == 0){
        printf("There was an error freeing this memory shutting down\n");
        exit(1);
    }

}