#include <stdlib.h>
#include <strings.h>

void *mem_alloc(size_t size) {
    void *mem = malloc(size);
    bzero(mem, size);
    return mem;
}