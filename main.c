
#include "main.h"

int main(void) {
    HANDLE our_heap = GetProcessHeap();
    
    struct Memory mem1 = malloc_new(5);
    struct Memory mem2 = calloc_new(5, sizeof(int));
    
    for (int i =0; i < 5; i++){
        int* a = mem1.ptr;
        int* b = mem2.ptr;
        printf("Malloc: %d\n Calloc: %d\n\n", a[i], b[i]);
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


struct Memory realloc_new(void* ptr,  size_t size){
      struct Memory a;
    return a;
}




void free_new(LPVOID ptr, HANDLE heap){
    BOOL ret = HeapFree(heap, 0, ptr);

    if (ret == 0){
        printf("There was an error freeing this memory shutting down\n");
        exit(1);
    }

}



SIZE_T has_space(struct Memory obj){
    return obj.mem_allocated - obj.mem_used;
}


int add_to_mem(struct Memory *obj, void *to_add , SIZE_T size_to_add){
    if(!obj->type_size){
        obj->type_size = size_to_add;
    }
    
    if (obj->free == 1){
        return 0;
    }

    if(obj->type_size != size_to_add){
        return -1;
    }

    
    SIZE_T mem_avail = has_space(*obj);
    if (mem_avail < size_to_add){
        return -2;
    }

    memcpy(obj->ptr, to_add, obj->type_size);

    return 0;
}

struct Memory new_mem(SIZE_T mem_allowed, LPVOID ptr){

    struct Memory mem;
    mem.ptr = ptr;
    mem.mem_allocated = mem_allowed;
    mem.mem_used = 0;
    mem.type_size = 0;
    mem.free = 0;

    return mem;
}

LPVOID get_chunk(SIZE_T bytes_to_allocate){
    HANDLE heap = GetProcessHeap();
    return HeapAlloc(heap,HEAP_GENERATE_EXCEPTIONS, bytes_to_allocate);

}