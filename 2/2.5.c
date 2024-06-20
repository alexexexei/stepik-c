#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

union u {
   int64_t a;
   int32_t as_32[2];
   char raw[64];
};

enum either_type { ET_INT, ET_STRING };

struct either_int_string {
  enum either_type type;
  union {
    char* as_string;
    int64_t as_int;
  };
};

struct either_int_string either_from_string(char* s) {
    return (struct either_int_string) {.type = ET_STRING, .as_string = s};
}
struct either_int_string either_from_int(int64_t i) {
    return (struct either_int_string) {.type = ET_INT, .as_int = i};
}

void either_int_string_destroy(struct either_int_string e) {
    if (e.as_string) {
        free(e.as_string);
        free(&e.type);
    }
}

void print(struct either_int_string e) {
  switch (e.type) {
  case ET_INT: {
       printf("Int %" PRId64, e.as_int);
       break;
  }
  case ET_STRING: {
       printf("String %s", e.as_string);  
       break;
  }
  default: {
      break;
  }
  }
}

struct heap_string {
  char* addr;
};

struct heap_string halloc( const char* s ) {
    size_t size = strlen(s) + 1;
    char* ptr = (char*) malloc(size * sizeof(char));
    strcpy(ptr, s);
    return (struct heap_string) {.addr = ptr};
}

void heap_string_free( struct heap_string h ) {
    free(h.addr);
}

int main () {
   printf("%zu", sizeof( union u ) );
   return 0;
}