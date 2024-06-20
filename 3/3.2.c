#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct {
  int64_t value;
} item;

#define STACK_ITEM_PRI PRId64

struct maybe_item {
  bool valid;
  item value;
};

static const struct maybe_item none_int = {0, {0}};

static struct maybe_item some_int(int64_t value) {
  return (struct maybe_item){true, {value}};
}

struct stack_int;

struct stack_int *stack_int_create();

void stack_int_destroy(struct stack_int *s);

bool stack_int_empty(struct stack_int const *s);
bool stack_int_full(struct stack_int const *s);

bool stack_int_push(struct stack_int* s, item i);

struct maybe_item stack_int_pop(struct stack_int* s);

void stack_int_print(struct stack_int const*);
#endif

struct list {
  item value;
  struct list *next;
};

struct stack_int {
  struct list *items;
};

static struct list *c(item i, struct list *next) {
  struct list *result = malloc(sizeof(struct list));
  *result = (struct list){i, next};
  return result;
}

static struct stack_int stack_int_default() {
  return (struct stack_int){.items = NULL};
}

struct stack_int *stack_int_create() {
  struct stack_int *const result = malloc(sizeof(struct stack_int));
  *result = stack_int_default();
  return result;
}

static void list_free( struct list* l ) {
  while (l) {
    struct list *cur = l;
    l = l->next;
    free(cur);
    }
}

void stack_int_destroy(struct stack_int *s) {
    if (!s || !s->items) { return; }
    list_free(s->items);
    free(s);
}

bool stack_int_empty(struct stack_int const *s) { 
    return (!s || !s->items);
}

bool stack_int_full(struct stack_int const *s) { 
    return false;
}

bool stack_int_push(struct stack_int *s, item i) {
    struct list* new = c(i, s->items);
    if (!new) { return false; }
    
    s->items = new;
    return true;
}

struct maybe_item stack_int_pop(struct stack_int *s) {
  if (stack_int_empty(s)) {
    return none_int;
  }
  
  struct maybe_item a = some_int(s->items->value.value);
  struct list* next = s->items->next;
  free(s->items);
  if (next) { s->items = next; }
  return a;
}

static void stack_int_foreach(struct stack_int const *s, void (f)(item)) {
  for (struct list *l = s->items; l; l = l->next)
    f(l->value);
}

static void print_int64_cr(item i) { printf("%" STACK_ITEM_PRI "\n", i.value); }

void stack_int_print(struct stack_int const *s) {
  stack_int_foreach( s, print_int64_cr );
}

static struct stack_interface {
    struct stack_int_interface {
        struct stack_int* (*create)();
        bool (*empty)(struct stack_int const *s);
        bool (*full)(struct stack_int const *s);
        void (*destroy)(struct stack_int *s);
        bool (*push)(struct stack_int *s, item i);
        struct maybe_item (*pop)(struct stack_int *s);
    } int64;
} const stack = {{stack_int_create, stack_int_empty, stack_int_full,
                  stack_int_destroy, stack_int_push, stack_int_pop}};

static bool divides(int64_t x, int64_t y) { return x % y == 0; }
static void print_int_space(int64_t x) {printf("%" PRId64 " ", x); }
static int64_t read_int() { int64_t x; scanf("%" PRId64, &x); return x; }

void print_divisors(int64_t n) {
  if (n > 0) { 
    for (int64_t i = 1; i <= n; i = i + 1) {
      if (divides(n, i)) print_int_space(i);
    }
    printf("$");
  }
  else printf("No");
}

void print_int( int64_t x ) {
  printf("%" PRId64 , x );
}

int main() {
    int64_t x = 100;
    {
        int64_t x = 300;
        {
            int64_t x = 200;
            {
        
            print_int(x);
            }
        }
    }
    return 0;
}