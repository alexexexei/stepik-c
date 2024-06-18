#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>

void array_int_print(int64_t arr[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%lld ", arr[i]);
    }
    printf("\n");
}

void print_newline() {
    printf("\n");
}

// <--1-->
int64_t read_int64() {
    int64_t iVal;
    scanf("%" SCNd64, &iVal);
    return iVal;
}

size_t read_size() {
    size_t zSize;
    scanf("%zu", &zSize);
    return zSize;
}

void array_int_fill( int64_t* array, size_t size ) {
    for (size_t i = 0; i < size; i++) {
        int64_t iVal = read_int64();
        *(array + i) = iVal;
    }
}

int64_t* array_int_read( size_t* size ) {
    *size = read_size();
    if (size == 0 || *size == 0) {
        return NULL;
    }

    int64_t *array = malloc( sizeof(int64_t) * (*size) );
    if (!array) {
        return NULL;
    }

    array_int_fill(array, *size);
    return array;
}
// <--end 1-->

// 2
int64_t* array_int_min( int64_t* array, size_t size ) {
    if (size <= 0) {
        return NULL;
    }

    int64_t *min_ptr = array;
    if (min_ptr == NULL) {
        return NULL;
    }

    int64_t min = *array;
    for (size_t i = 1; i < size; i++) {
        if (*(array + i) < min) {
            min = *(array + i);
            min_ptr = array + i;
        }
    }
    return min_ptr;
}

// <--3-->
void intptr_print( int64_t* x ) {
    if (x == NULL) {
        printf("%s", "None");
    } else {
        printf("%" PRId64, *x);
    }
}

void perform() {
    size_t zSize;
    int64_t* array = array_int_read(&zSize);

    if (array) {
        intptr_print(array_int_min(array, zSize));

        free(array);
    }
}
// <--end 3-->

// <--4-->
int64_t** marray_read( size_t* rows, size_t** sizes ) {
    scanf("%zu", rows);
    
    int64_t **double_arr = malloc( sizeof(int64_t*) * (*rows) );
    if (!double_arr) {
        return NULL;
    }

    *sizes = malloc( sizeof(size_t) * (*rows) );
    if (!sizes) {
        free(double_arr);
        return NULL;
    }

    for (size_t i = 0; i < *rows; i++) {
        double_arr[i] = array_int_read(&((*sizes)[i]));
    }

    return double_arr;
}

void marray_print(int64_t** marray, size_t* sizes, size_t rows) {
    for( size_t i = 0; i < rows; i = i + 1 ) {
        array_int_print( marray[i], sizes[i] );
        print_newline();
    }
}
// <--end 4-->

// 5
void marray_free( int64_t** marray, size_t rows ) {
    for (size_t i = 0; i < rows; i++) {
        free(*(marray + i));
    }
    free(marray);
}

// <--6-->
int64_t* int64_ptr_min(int64_t* x, int64_t* y) {
    if (x == NULL && y == NULL) {
        return NULL;
    }
    
    if (x == NULL) {
        return y;
    }
    
    if (y == NULL) {
        return x;
    }
    
    return (*x < *y) ? x : y;
}

int64_t* marray_int_min( int64_t** marray, size_t* sizes, size_t rows ) {
    if (!marray || !sizes || !rows) {
        return NULL;
    }
    
    int64_t min;
    if (marray[0] != NULL) {
        min = marray[0][0];
    } else {
        min = INT_MAX;
    }
    
    int64_t *min_ptr = &min;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < *(sizes + i); j++) {
            if (*(marray + i) == NULL) {
                continue;
            }
            
            int64_t *potential_min_ptr = *(marray + i) + j;
            if (potential_min_ptr == NULL) {
                continue;
            }
            
            int64_t *checked_potential_min_ptr = int64_ptr_min(potential_min_ptr, &min);
            if (checked_potential_min_ptr != NULL) {
                min = *checked_potential_min_ptr;
                min_ptr = checked_potential_min_ptr;
            }
        }
    }

    return min_ptr;
}

void marray_normalize( int64_t** marray, size_t sizes[], size_t rows, int64_t m ) {
    if (!marray || !sizes || !rows || !m) {
        return;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < *(sizes + i); j++) {
            if (*(marray + i) == NULL) {
                continue;
            }
            
            int64_t *var_ptr = *(marray + i) + j;
            if (var_ptr != NULL) {
                *var_ptr = *var_ptr - m;
            }
        }
    }
}

// remove '_'
void _perform() {
    size_t rows = 0;
    size_t *sizes = 0;
    
    int64_t **double_arr_ptr = marray_read(&rows, &sizes);
    if (!double_arr_ptr || !sizes || !rows) {
        return;
    }
    
    int64_t* min_ptr = marray_int_min(double_arr_ptr, sizes, rows);
    if (min_ptr == NULL || !(*min_ptr)) {
        return;
    }
    
    marray_normalize(double_arr_ptr, sizes, rows, *min_ptr);
    
    marray_print(double_arr_ptr, sizes, rows);
    
    marray_free(double_arr_ptr, rows);
    free(sizes);
}
// <--end 6-->

int main() {
    // <--q1-->
    // -1
    // ошибка
    // 1024
    // 0 
    // <--end q1-->

    // <--q2-->
    // ошибка
    // 0
    // -1
    // 1024 
    // <--end q2-->

    perform();
    _perform();
    return 0;
}