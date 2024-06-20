#include<inttypes.h>

#define LIMIT 10

uint32_t data[8*1024*1024] = {0};

size_t count_gt(uint32_t* array, size_t size) {
    size_t counter = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] > LIMIT) {
            counter += 1;
        }
    }
    return counter;
}

size_t count_zeroes( const void *data, size_t sz ) {
    size_t counter = 0;
    uint8_t *c = (uint8_t*)data;
    for (size_t i = 0; i < sz; i++) {
        if (*(c + i) == 0) {
            counter++;
        }
    }
    return counter;
}

int main() {
    return 0;
}