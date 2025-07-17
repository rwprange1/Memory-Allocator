
#include "main.h"


int main(void) {
    HANDLE our_heap = GetProcessHeap(); //windows sys-call for heap handle

    if (!our_heap) {
        printf("Error fetching heap handle");
        exit(1);
    }

    void* temp = malloc_new(100);
    return 0;
}


/*
* returns a void pointer to an uninitialized chunk of memory on the heap
*
* size: the number of bytes to allocate
*
* returns: a void ptr to the chunk of memory
*/
void* malloc_new(size_t size){

    printf("User is requesting %zu bytes be allocated to the heap", size);


}

/*
 * returns a void pointer to an initialized chunk of memory on the heap
 *
 * num_elements: the number of elements we need to store
 * element_size: how big in bytes is each element
 *
 * returns: a void pointer to the initialized chunk of memory
 */
void* calloc_new(size_t num_elements, size_t element_size){

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
void free_new(void* ptr){

}