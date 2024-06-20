#include<inttypes.h>
#include<stdio.h>
#include<stdlib.h>

struct list {
    int64_t value;
    struct list* next;
};

void print_int64(int64_t i);

void list_foreach( const struct list* l, void (f)(int64_t)) {
    struct list* l2 = (struct list*) l;
    while (l2 != NULL) {
        f(l2->value);
        l2 = l2->next;
    }
}

void list_print( const struct list* l) { 
    struct list* l2 = (struct list*) l;
    while (l2 != NULL) {
        printf("%ld", l2->value);
        printf("%c", ' ');
        l2 = l2->next;
    }
}

void list_map_mut(struct list * const l, int64_t (f) (int64_t))  {
    struct list* l2 = (struct list*) l;
    while (l2) {
        l2->value = f(l2->value);
        l2 = l2->next;
    }
}

static int64_t triple( int64_t x ) { return x * 3; }

void list_triple( struct list * const l ) { 
    struct list* l2 = (struct list*) l;
    while (l2) {
        l2->value = triple(l2->value);
        l2 = l2->next;
    }
}

void print_int64(int64_t i) {
    printf("%" PRId64, i);
}

struct list* node_create( int64_t value ) {
    struct list* l = malloc(sizeof(struct list));
    l->value = value;
    l->next = NULL;
    return l;
}

struct list* list_map( const struct list* l, int64_t (f) (int64_t))  {
    if (!l) {
        return (struct list*) l;
    }
    
    struct list* l2 = (struct list*) l;
    struct list* l_new = node_create(f(l2->value));
    struct list* l_new_copy = (struct list*) l_new;

    if (l2->next) {
        l2 = l2->next;
        while (l2) {
            l_new_copy->next = node_create(f(l2->value));
            l_new_copy = l_new_copy->next;
            l2 = l2->next;
        }
    }

    return l_new;
}

int64_t rint(int64_t i) {
    return i;
}

struct list* list_copy( const struct list* l ) {
    return list_map(l, rint);
}

int64_t l_abs(int64_t i) {
    if (i < 0) {return -i;}
    return i;
}

struct list* list_abs( const struct list* l ) {
    return list_map(l, l_abs);
}

void list_destroy( struct list* list )
{
    if (list == NULL)
    {
        return;
    }

    if (list->next == NULL)
    {
        free(list);
        return;
    }

    struct list* temp = list->next;
    while (temp != NULL)
    {
        free(list);
        list = temp;
        temp = temp->next;
    }
    free(list);
}

static int64_t sum( int64_t x, int64_t y) { return x + y; }

typedef int64_t folding(int64_t, int64_t);

int64_t list_fold( const struct list* l, int64_t init, folding f) {
    if (!l) {
        return init;
    }

    int64_t result = init;
    struct list* l2 = (struct list*) l;
    while (l2) {
        result = f( result, l2->value );
        l2 = l2->next;
    }

    return result;
}

int64_t list_sum( const struct list* l ) {
    return list_fold(l, 0, sum);
}

struct list* list_iterate( int64_t init, size_t sz, int64_t(f)(int64_t)) {
    if (!sz) {
        return NULL;
    }
    
    struct list* l = node_create(init);
    struct list* l_copy = l;
    size_t counter = 1;

    while (counter != sz) {
        l_copy->next = node_create(f(init));
        l_copy = l_copy->next;
        init = f(init);
        counter += 1;
    }

    return l;
}

int main() {
    return 0;
}