#include<stdbool.h>
#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>

int64_t read_int64() {
    int64_t iVal;
    scanf("%" SCNd64, &iVal);
    return iVal;
}

struct maybe_int64 {
  bool valid;
  int64_t value;
};

struct maybe_int64 some_int64( int64_t i ) {
  return (struct maybe_int64) { .value = i, .valid = true };
}

const struct maybe_int64 none_int64 = { 0 };

// <--1-->
void maybe_int64_print( struct maybe_int64 i ) {
    if (!i.valid) {
        printf("%s", "None");
        return;
    }
    printf("Some %ld", i.value);
}

struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    if (!a.valid && !b.valid) {
        return none_int64;
    }
    if (a.valid && !b.valid) {
        return some_int64( a.value );
    }
    if (!a.valid && b.valid) {
        return some_int64( b.value );
    }
    if (a.value > b.value) {
        return some_int64( b.value );
    } else {
        return some_int64( a.value );
    }
}
// <--end 1-->

// <--2-->
size_t read_size() { size_t sz = 0; scanf("%zu", &sz); return sz; }

struct array_int {
    int64_t* data;
    size_t size;
};

void array_int_fill( int64_t* array, size_t sz ) {
  for( size_t i = 0; i < sz; i = i + 1 ) {
    array[i] = read_int64();
  }
}

struct array_int array_int_read() {
  const size_t size = read_size();
  if (size > 0) {
    int64_t* array = malloc( sizeof(int64_t) * size);
    array_int_fill( array, size );
    return (struct array_int) { .data = array, .size = size };
  }
  else return (struct array_int) {0};
}

struct maybe_int64 array_int_get( struct array_int a, size_t i ) {
  if ( (a.size < i) || (i < 0) ) {
      return (struct maybe_int64) none_int64;
  }
  return (struct maybe_int64) some_int64( *(a.data + i)  );
}

bool array_int_set( struct array_int a, size_t i, int64_t value ) {
    if ( (a.size < i) || (i < 0) ) {
      return false;
    }
    *(a.data + i) = value;
    if ( *(a.data + i) == value) {
        return true;
    }
    return false;
}

void array_int_print( struct array_int array ) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    printf("%" PRId64 " " , array_int_get( array, i).value);
  }
}

struct maybe_int64 array_int_min( struct array_int array ) {
    if(array.size <= 0){
        return (struct maybe_int64) none_int64;
    }
    if (array.size == 1){
        return (struct maybe_int64) some_int64( *(array.data + 0) );
    }
    int64_t min = *(array.data + 0);
    for (size_t i = 1; i < array.size; i++){
        int64_t pos_min = *(array.data + i);
        if (pos_min < min) {
            min = pos_min;
        }
    }
    return (struct maybe_int64) some_int64(min);
}

void array_int_free( struct array_int *a ) { 
    if ( a->size > 0 ) {
        free(a->data); 
        a->size = 0;
    } 
}
// <--end 2-->

// <--3-->
void array_int_normalize( struct array_int array, int64_t m ) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    array.data[i] = array.data[i] - m;
  }
}

struct maybe_array_int {
  struct array_int value;
  bool valid;
};

struct maybe_array_int some_array_int(struct array_int array) {
  return (struct maybe_array_int) { array, true };
}
const struct maybe_array_int none_array_int = { {NULL, 0}, false };

struct array_array_int {
  struct array_int* data;
  size_t size;
};

struct maybe_array_int array_array_int_get_row( struct array_array_int a, size_t i ) {
  if ( 0 <= i && i < a.size ) { return some_array_int( a.data[i] ); }
  else { return none_array_int; }
}

bool array_array_int_set_row( struct array_array_int a, size_t i, struct array_int value ) {
  if (0 <= i && i < a.size) {
    a.data[i] = value;
    return true;
  }
  else { return false; }
}

struct maybe_int64 array_array_int_get( struct array_array_int a, size_t i, size_t j ) {
    if ( (a.size < i) || (i < 0) || (j < 0) ) {
        return (struct maybe_int64) none_int64;
    }
    return (struct maybe_int64) array_int_get( *(a.data + i), j );
}

bool array_array_int_set( struct array_array_int a, size_t i, size_t j, int64_t value ) {
    if ( (a.size < i) || (*(a.data + i)).size < j ) {
        return false;
    }
    *( (*(a.data + i)).data + j) = value;
    return true;
}

struct array_array_int array_array_int_read() {
    size_t strs = read_size();
    struct array_array_int arr;
    arr.size = strs;
    arr.data = (struct array_int*) malloc(strs * sizeof(struct array_int));
    for (size_t i = 0; i < strs; i++) {
        *(arr.data + i) = array_int_read();
    }
    return (struct array_array_int) arr;
}

void array_array_int_print( struct array_array_int array) {
    if (array.size <= 0) {
        return;
    }
    for (size_t i = 0; i < array.size; i++){
        array_int_print( *(array.data + i) );
        printf("\n");
    }
}

struct maybe_int64 array_array_int_min( struct array_array_int array ) {
    if (array.size <= 0) {
        return (struct maybe_int64) none_int64;
    }
    struct maybe_int64 s_min = {true, 999999};
    if (!((array.data + 0)->size <= 0)) {
        s_min.value = *( (*(array.data + 0)).data + 0 );
    }
    for (size_t i = 0; i < array.size; i++) {
        s_min = maybe_int64_min(s_min, array_int_min( *(array.data + i) ));
    }
    return (struct maybe_int64) s_min;
}

void array_array_int_normalize( struct array_array_int array, int64_t m) {
  for (size_t i = 0; i < array.size; i = i + 1) {
    const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
    if (cur_row.valid) {
         array_int_normalize( cur_row.value, m );
    }
  }
}

void array_array_int_free( struct array_array_int array ) {
    if (array.size <= 0) {
        return;
    }
    for (size_t i = 0; i < array.size; i++) {
        array_int_free( array.data + i );
    }
    free(array.data);
    array.size = 0;
}
// <--end 3-->

void perform() {
  struct array_array_int array = array_array_int_read();
  struct maybe_int64 m = array_array_int_min( array );
  if (m.valid) {
    array_array_int_normalize( array, m.value );
    array_array_int_print( array );
  }
  array_array_int_free( array );
}

struct array_int array_int_create( size_t sz ) {
    return (struct array_int) { .data = malloc( sizeof( int64_t ) * sz ), .size = sz };
}

void print_int64(int64_t i) {
    printf("%" PRId64, i);
}

// <--4-->
struct stack {
  size_t count;
  struct array_int data;
};

size_t stack_count( const struct stack* s ) {
    return s->count;
}

struct stack stack_create( size_t size ) {
    return (struct stack) { .count = 0, .data = array_int_create(size) };
}

void stack_destroy( struct stack* s ) {
    array_int_free(&s->data);
    s->count = 0;
}

bool stack_is_full( const struct stack * s) {
    if (s->count == s->data.size) {
        return true;
    }
    return false;
}

bool stack_is_empty( const struct stack * s) {
    if (s->count == 0) {
        return true;
    }
    return false;
}

bool stack_push( struct stack* s, int64_t value ) {
    if (stack_is_full(s)) {
        return false;
    }
    if (array_int_set(s->data, s->count, value)) {
        s->count = s->count + 1;
        return true;
    }
    return false;
}

struct maybe_int64 stack_pop( struct stack* s ) {
    if (stack_is_empty(s)) {
        return none_int64;
    }
    if (s->count > 0) {
        s->count = s->count - 1;
        struct maybe_int64 mi64 = array_int_get(s->data, s->count);
        return mi64;
    }
    return none_int64;
}

void stack_print( const struct stack* s ) {
  for (size_t i = 0; i < stack_count( s ); i = i + 1 ) {
    print_int64( array_int_get( s->data, i).value );
    printf(" ");
  }
}
// <--end 4-->

int main() {
    // q1
    //  Поля структуры расположены в памяти последовательно, возможны пропуски между ними

    // q2
    // Можно создать массив из таких структур

    perform();
    return 0;
}