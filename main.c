
#include "main.h"




int main(void) {
    
    struct Memory mem1;
    struct Memory mem2; 


    SIZE_T bytes = 20;

    mem1 = malloc_new(bytes);
    mem2 = calloc_new(100, sizeof(int));

    for (int i = 0; i < 5; i++){
        add_to_mem(&mem2, &i, sizeof(i));
    }

    printf("Size of mem2 before realloc: %lu\n", HeapSize(GetProcessHeap(), 0, mem2.ptr) );
    int* ptr = mem2.ptr;
    for (int i = 0; i < 5; i++){
        printf("%d\n", ptr[i]);
    }

    mem2 = realloc_new(&mem2, 10);
    printf("Size of mem2 after realloc: %lu\n", HeapSize(GetProcessHeap(), 0, mem2.ptr) );
    ptr = mem2.ptr;
    for (int i = 0; i < 5; i++){
        printf("%d\n", ptr[i]);
    }

    
   
    return 1;
   
}


struct Memory malloc_new(SIZE_T size){
    HANDLE chunk = get_chunk(size);
    struct Memory mem = new_mem(size, chunk);
    return mem;
}


struct Memory calloc_new(SIZE_T num_elements, SIZE_T element_size){
    SIZE_T total_mem = num_elements * element_size;
    HANDLE chunk = get_chunk(total_mem);
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

    free(mem->ptr);
    mem->ptr = chunk;
    mem->mem_allocated = size;

  
    return *mem;
}




void free_new(struct Memory *mem){
    HANDLE heap = GetProcessHeap();
    BOOL ret = HeapFree(heap, 0, mem->ptr);
   
    if (ret == 0){
        printf("There was an error freeing this memory shutting down\nError: %lu",  GetLastError());
        exit(1);
    }
    mem->free = TRUE;
}



SIZE_T has_space(struct Memory obj){
    return obj.mem_allocated - obj.mem_used;
}


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

    
    SIZE_T mem_avail = has_space(*obj);
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