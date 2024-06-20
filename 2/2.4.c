#include<inttypes.h>
#include<stdbool.h>

struct maybe_int64 {
  bool valid;
  int64_t value;
};

struct maybe_int64 some_int64( int64_t i ) {
  return (struct maybe_int64) { .value = i, .valid = true };
}

const struct maybe_int64 none_int64 = { 0 };

struct list {
    int64_t value;
    struct list* next;
};

struct list* node_create( int64_t value ) {
    struct list* l = malloc(sizeof(struct list));
    l->value = value;
    l->next = NULL;
    return l;
}

void list_add_front( struct list** old, int64_t value ) {
    struct list* new = node_create(value);
    new->next = *old;
    *old = new;
}

size_t list_length(const struct list* l)
{
    if ( (l == NULL) || (l->next == NULL) )
    {
        return 0;
    }

    struct list* next = (struct list*) l->next;
    size_t len = 1;
    while (next->next != NULL)
    {
        next = next->next;
        len += 1;
    }
    
    return len + 1;
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

struct list* list_last( const struct list* list )
{
    if (list == NULL)
    {
        return NULL;
    }

    if (list->next == NULL)
    {
        return (struct list*) list;
    }

    struct list* temp = (struct list*) list->next;
    while (1)
    {
        if (temp->next == NULL)
        {
        return (struct list*) temp;
        }
        temp = temp->next;
    }
}

void list_add_back( struct list** old, int64_t value )
{
    if (old == NULL)
    {
        return;
    }
    
    if (*old == NULL)
    {
        *old = node_create(value);
        return;
    }

    struct list* last = list_last(*old);
    struct list* new = node_create(value);
    last->next = new;
    new->next = NULL;
}

int64_t list_sum( const struct list* list )
{
    if (list == NULL)
    {
        return 0;
    }

    if (list->next == NULL)
    {
        return (int64_t) list->value;
    }

    struct list* temp = (struct list*) list->next;
    int64_t sum = list->value;
    while (temp != NULL)
    {
        sum += temp->value;
        temp = temp->next;
    }
    
    return sum;
}

struct maybe_int64 list_at( const struct list* list, size_t idx )
{
    if ( (list == NULL) || (list_length(list) < idx) || (idx < 0) )
    {
        return none_int64;
    }

    size_t index = -1;
    struct list* temp = (struct list*) list;
    while (1)
    {
        index++;
        if (index == idx)
        {
        return some_int64(temp->value);
        }
        temp = temp->next;
    }
}

struct list* list_reverse( const struct list* list )
{
    if (list == NULL)
    {
        return NULL;
    }

    struct list* new = NULL;
    struct list* temp = (struct list*) list;
    while (temp != NULL)
    {
        list_add_front(&new, temp->value);
        temp = temp->next;
    }

    return new;
}

struct maybe_int64 maybe_read_int64() {
    int64_t val;
    if (scanf("%" SCNd64, &val) > 0)
    {
        return some_int64(val);
    }
    return none_int64;
}

struct list* list_read() {
    struct maybe_int64 temp = maybe_read_int64();
    if (!temp.valid)
    {
        return NULL;
    }

    struct list* list = node_create(temp.value);
    struct list* curr_list = list;
    list->value = temp.value;
    while (1)
    {
        temp = maybe_read_int64();
        if (!temp.valid)
        {
        return list;
        }
        curr_list->next = node_create(temp.value);
        curr_list = curr_list->next;
    }
}

int main() {
    return 0;
}