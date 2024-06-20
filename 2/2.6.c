#include<inttypes.h>
#include<string.h>
#include<stdlib.h>

typedef char ftype(const float*, size_t (*func)(struct array, int64_t i));

typedef struct { char* addr; } string_heap ;

typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER};

const char* city_string[] = {
  [C_SARATOV] = "Saratov",
  [C_MOSCOW] = "Moscow",
  [C_PARIS] = "Paris",
  [C_LOS_ANGELES] = "Los Angeles",
  [C_OTHER] = "Other"
};

struct user {
  const uid id;
  const string_heap name;
  enum city city;
};

int user_int64_comparer( const struct user* x, const struct user* y ) {
  if (x->id > y->id) return 1;
  if (x->id < y->id) return -1;
  return 0;
}

int int64_void_comparer(const void* _x, const void* _y ) {
  return user_int64_comparer(_x, _y );
}

void users_sort_uid(struct user users[], size_t sz) {
  if (users == NULL || sz == 0) {
    return;
  }

  qsort(users, sz, sizeof(users[0]), int64_void_comparer);
}

int user_charname_comparer( const struct user* x, const struct user* y ) {
  return strcmp(x->name.addr, y->name.addr);
}

int char_void_comparer(const void* _x, const void* _y) {
  return user_charname_comparer(_x, _y);
}

void users_sort_name(struct user users[], size_t sz) {
  if (users == NULL || sz == 0) {
    return;
  }

  qsort(users, sz, sizeof(users[0]), char_void_comparer);
}

int user_charcity_comparer( const struct user* x, const struct user* y ) {
  return strcmp(city_string[x->city], city_string[y->city]);
}

int enum_city_void_comparer(const void* _x, const void* _y) {
  return user_charcity_comparer(_x, _y);
}

void users_sort_city(struct user users[], size_t sz) {
  if (users == NULL || sz == 0) {
    return;
  }

  qsort(users, sz, sizeof(users[0]), enum_city_void_comparer);
}

enum move_dir { MD_UP, MD_RIGHT, MD_DOWN, MD_LEFT, MD_NONE };

typedef void (*move_callback)(const enum move_dir);

struct list
{
  void (*handler)(enum move_dir);
  struct list* next;
};

struct list* node_create( move_callback mvc )
{
    struct list* l = malloc(sizeof(struct list));
    l->handler = mvc;
    l->next = NULL;
    return l;
}

void list_add_front( struct list** old, move_callback mvc )
{
  struct list* new = node_create(mvc);
  new->next = *old;
  *old = new;
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

struct robot {
  const char* name;
  struct list* handlers;
};

void register_callback(struct robot* robot, move_callback new_cb) {
  if (robot && new_cb) {list_add_front(&(robot->handlers), new_cb);}
}

void unregister_all_callbacks(struct robot* robot) {
  if (robot) {list_destroy(robot->handlers);}
}

void move(struct robot* robot, enum move_dir dir) {
  if (robot && dir) {
    struct list* list = robot->handlers;
    while (list != NULL) {
      list->handler(dir);
      list = list->next;
    }
  }
}

int main() {
    return 0;
}