

#include "test.h"
#include "main.h"



int passes = 0;
int fails = 0;

void test(BOOL cond, char* msg, char* val){
    printf(cond ? "Pass: %s, %s\n" : "Fail: %s, %s\n", msg, val);

    if (cond == TRUE) {
        passes++;
    }else{
        fails++;
    }



}

void test_malloc(){
    printf("Hello World\n");
    //test for small allocation
    SIZE_T size = 64;
    char* msg = "Malloc: Allocating 64 bytes";
    char expected[23+32] = "Expecting 64, Actual: ";
    char rec[32];

    struct Memory mal = malloc_new(size);
    SIZE_T allocated = mal.mem_allocated;

    sprintf(rec, "%llu", allocated);

    strncpy(expected, rec, sizeof(rec));

    test(allocated == size, msg, expected);


    



}





void test_realloc(){

}

void test_free(){

}