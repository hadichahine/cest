#include <stdlib.h>
#include "mem_alloc.h"

typedef struct Assert {
	int result;
}Assert;

Assert *Assert_create(){
	Assert *assert = (Assert*)mem_alloc(sizeof(Assert));
	assert->result = 1;
	return assert;
}

void Assert_assertTrue(Assert *assert,int boolean){
	assert->result = assert->result && boolean;
}

int Assert_result(Assert *assert){
    return assert->result;
}