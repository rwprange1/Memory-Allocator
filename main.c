#include "main.h"
#include "test.h"




int main(void) {
    
    test_malloc();
   

    printf("Passes\n");
    return 1;
   
}

/*
    Initialize our own

 */
struct Memory malloc_new(SIZE_T size){
    HANDLE chunk = get_chunk(size);

     if(chunk == NULL){
        printf("There was an error requesting memory from the OS\n");
        exit(1);
    }
    struct Memory mem = new_mem(size, chunk);
    return mem;
}


struct Memory calloc_new(SIZE_T num_elements, SIZE_T element_size){
    SIZE_T total_mem = num_elements * element_size;
    HANDLE chunk = get_chunk(total_mem);

    if(chunk == NULL){
        printf("There was an error requesting memory from the OS\n");
        exit(1);
    }

    struct Memory mem = new_mem(total_mem, chunk);
    memset(mem.ptr, 0, total_mem);
    return mem;
}


struct Memory realloc_new(struct Memory *mem,  SIZE_T size){
    // let windows try to handle the realloc
    LPVOID chunk = HeapReAlloc(GetProcessHeap(),HEAP_REALLOC_IN_PLACE_ONLY, mem->ptr, size);
    if (chunk != NULL){
       return *mem;
    }

    // if windows cant we will try to 
    chunk = get_chunk(size);
    if( chunk == NULL){
        printf("Error getting a chunk of memory from OS");
        exit(1);
    }

    if (size > mem->mem_used){
        memcpy(chunk, mem->ptr, mem->mem_used );
    }else{
        memcpy(chunk, mem->ptr, size);
    }

    BOOL ret = HeapFree(GetProcessHeap(), 0, mem->ptr);
    if (ret == 0){
        printf("(realloc_new) There was an error freeing this memory shutting down\nError: %lu",  GetLastError());
        exit(1);
    }
    mem->ptr = chunk;
    mem->mem_allocated = size;

  
    return *mem;
}




void free_new(struct Memory *mem){
    HANDLE heap = GetProcessHeap();
    BOOL ret = HeapFree(heap, 0, mem->ptr);
   
    if (ret == 0){
        printf("(free_new) There was an error freeing this memory shutting down\nError: %lu",  GetLastError());
        exit(1);
    }
    mem->free = TRUE;
}



/*
 A helper method to simulate an addition to our memory structure

 obj: the Memory struct to add to
 to_add: a pointer to the thing we want to add
 size_to_add: the size in bytes of the thing to add

 returns: an errors enum value which indicates sucessful and erroneous uses of this method

*/
enum Errors add_to_mem(struct Memory *obj, void *to_add , SIZE_T size_to_add){
    if(!obj->type_size){
        obj->type_size = size_to_add;
    }
    
    if (obj->free == TRUE){
        return USE_AFTER_FREE;
    }

    if(obj->type_size != size_to_add){
        return INVALID_TYPE;
    }

    
    SIZE_T mem_avail = obj->mem_allocated - obj->mem_used;
    if (mem_avail < size_to_add){
        return INSUFFIECNT_MEMORY;
    }


    //pointer arithmetic to make sure we are adding the element to the correct 'index'
    memcpy((char*)obj->ptr + obj->mem_used , to_add, obj->type_size);
    obj->mem_used = obj->mem_used + size_to_add;

    return OK;
}

/*
    A method to initialize a Memory struct with the given values

    mem_allowed: the size in bytes we have allocated
    ptr: the pointer to the allocated memory

    returns: a new struct with the given values

*/
struct Memory new_mem(SIZE_T mem_allowed, LPVOID ptr){

    struct Memory mem;
    mem.ptr = ptr;
    mem.mem_allocated = mem_allowed;
    mem.mem_used = 0;
    mem.type_size = 0;
    mem.free = FALSE;

    return mem;
}


/*
    Get a chunk of memory from the heap of size bytes_to_allocate 

    bytes_to_allocate: the number of bytes to request

    returns: a void pointer or LPVOID which points to the allocated memory on the heap

*/
LPVOID get_chunk(SIZE_T bytes_to_allocate){
    HANDLE heap = GetProcessHeap();

    if(bytes_to_allocate <= 0){
        return NULL;
    }

    return HeapAlloc(heap, HEAP_GENERATE_EXCEPTIONS, bytes_to_allocate);
}


void print_error_value(enum Errors value){
    switch (value) {
        case OK:
            printf("Safe memory usage\n");
            break;
        case USE_AFTER_FREE:
            printf("Error use after free\n");
            break;
        case INVALID_TYPE:
            printf("Error invalid type usage\n");
            break;
        case INSUFFIECNT_MEMORY:
            printf("Error the memory obj has run out of memory\n");
            break;    


    }
}