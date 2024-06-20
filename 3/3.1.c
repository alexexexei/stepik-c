#include<inttypes.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define STACK_CAPACITY 10

enum opcode {
  BC_PUSH, BC_POP, BC_SWAP, BC_DUP,
  BC_IADD, BC_ISUB, BC_IMUL, BC_IDIV, 
  BC_INEG, BC_IMOD, BC_JMP,
  BC_IPRINT, BC_IREAD, 
  BC_ICMP, BC_JZ, 
  BC_STOP 
};

struct bc_noarg { enum opcode opcode; };
struct bc_arg64 { enum opcode opcode; int64_t arg; };

union ins { 
   enum opcode opcode; 
   struct bc_arg64 as_arg64; 
   struct bc_noarg as_noarg;
};

const union ins program[] = {
  { BC_IREAD },
  { .as_arg64 = { BC_PUSH, .arg = 10 } },
  { BC_ISUB },
  { .as_arg64 = { BC_PUSH, .arg = 2 } },
  { BC_IDIV },
  { BC_IPRINT },
  { BC_STOP }
};

struct maybe_int64 {
  bool valid;
  int64_t value;
};

const struct maybe_int64 none_int64 = { 0 };

struct maybe_int64 some_int64( int64_t i ) {
  return (struct maybe_int64) { .value = i, .valid = true };
}

struct array_int {
    int64_t* data;
    size_t size;
};

struct array_int array_int_create( size_t sz ) {
    return (struct array_int) { .data = malloc( sizeof( int64_t ) * sz ), .size = sz };
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

void array_int_free( struct array_int *a ) { 
    if ( a->size > 0 ) {
        free(a->data); 
        a->size = 0;
    } 
}

struct maybe_int64 array_int_get( struct array_int a, size_t i ) {
  if ( (a.size < i) || (i < 0) ) {
      return (struct maybe_int64) none_int64;
  }
  return (struct maybe_int64) some_int64( *(a.data + i)  );
}

struct stack {
  size_t count;
  struct array_int data;
};

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

struct stack stack_create( size_t size ) {
    return (struct stack) { .count = 0, .data = array_int_create(size) };
}

void stack_destroy( struct stack* s ) {
    array_int_free(&s->data);
    s->count = 0;
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

struct vm_state {
  const union ins *ip;
  struct stack data_stack;
};

struct vm_state state_create(const union ins *ip) {
  return (struct vm_state){.ip = ip,
                           .data_stack = stack_create(STACK_CAPACITY)};
}

void state_destroy(struct vm_state *state) {
   stack_destroy(&(state->data_stack));
}

void print_int64(int64_t i) {
    printf("%" PRId64, i);
}

struct maybe_int64 maybe_read_int64() {
    int64_t val;
    if (scanf("%" SCNd64, &val) > 0)
    {
        return some_int64(val);
    }
    return none_int64;
}

void interpret(struct vm_state *state) {
   union ins* st_ip_copy = (union ins*) state->ip;
   while (st_ip_copy->opcode != BC_STOP) {
       switch (st_ip_copy->opcode){
           case BC_PUSH: { stack_push(&(state->data_stack), st_ip_copy->as_arg64.arg); break;}
           case BC_IPRINT: {
               struct maybe_int64 b = stack_pop(&(state->data_stack));
               if (b.valid) {
                   print_int64(b.value);
               }
               break;}
           case BC_IREAD: {
               struct maybe_int64 a = maybe_read_int64();
               if (a.valid) {
                   stack_push(&(state->data_stack), a.value);
               }
               break;}
           case BC_IADD: { 
               struct maybe_int64 some_1 = stack_pop(&(state->data_stack)); 
               struct maybe_int64 some_2 = stack_pop(&(state->data_stack));
               if (some_1.valid && some_2.valid) {
                   stack_push(&(state->data_stack), some_1.value + some_2.value);
               }
               break;}
           default: {exit(0); break;}
       }
       st_ip_copy = st_ip_copy + 1;
   }
}

void interpret_program(const union ins *program) {
  struct vm_state state = state_create(program);
  interpret(&state);
  state_destroy(&state);
}

void interpret_push(struct vm_state* state) {
  stack_push(&(state->data_stack), state->ip->as_arg64.arg);
}

void interpret_iread(struct vm_state* state ) {
   struct maybe_int64 a = maybe_read_int64();
   if (a.valid) {
      stack_push(&(state->data_stack), a.value);
   }
}

void interpret_iadd(struct vm_state* state ) {
   struct maybe_int64 some_1 = stack_pop(&(state->data_stack)); 
   struct maybe_int64 some_2 = stack_pop(&(state->data_stack));
   if (some_1.valid && some_2.valid) {
      stack_push(&(state->data_stack), some_1.value + some_2.value);
   }
}

void interpret_iprint(struct vm_state* state) {
   struct maybe_int64 b = stack_pop(&(state->data_stack));
   if (b.valid) {
      print_int64(b.value);
   }
}

void interpret_stop(struct vm_state* state ) {
   state->ip = NULL;
}

void (*interpreters[])(struct vm_state* state) = {
  [BC_PUSH] = interpret_push,
  [BC_IPRINT] = interpret_iprint,
  [BC_IREAD] = interpret_iread,
  [BC_IADD] = interpret_iadd,
  [BC_STOP] = interpret_stop
};

void _interpret(struct vm_state* state) {
   if (state->ip == NULL) {
      return;
   }

   while (state->ip->opcode != BC_STOP) {
      interpreters[state->ip->opcode](state);
      state->ip = state->ip + 1;
   }
}

void interpret_swap  ( struct vm_state* state )  {
    struct maybe_int64 a = stack_pop( & state->data_stack );
    struct maybe_int64 a2 = stack_pop( & state->data_stack );
    stack_push( & state->data_stack, a.value );
    stack_push( & state->data_stack, a2.value );
}

void interpret_pop   ( struct vm_state* state )  {
    stack_pop( & state->data_stack );
}

void interpret_dup   ( struct vm_state* state )  {
    struct maybe_int64 a = stack_pop( & state->data_stack );
    stack_push( & state->data_stack, a.value );
    stack_push( & state->data_stack, a.value );
}

void lift_unop( struct stack* s, int64_t (f)(int64_t))
{ 
    struct maybe_int64 a = stack_pop( s );
    int64_t b = f(a.value);
    stack_push(s, b);
}

void lift_binop( struct stack* s, int64_t (f)(int64_t, int64_t))
{
    struct maybe_int64 a = stack_pop( s );
    struct maybe_int64 a2 = stack_pop( s );
    int64_t b = f(a2.value, a.value);
    stack_push(s, b);
}

int64_t i64_add(int64_t a, int64_t b) { return a + b; }
int64_t i64_sub(int64_t a, int64_t b) { return a - b; }
int64_t i64_mul(int64_t a, int64_t b) { return a * b; }
int64_t i64_div(int64_t a, int64_t b) { return a / b; }
int64_t i64_cmp(int64_t a, int64_t b) { if (a > b) return 1; else if (a < b) return -1; return 0; }

int64_t i64_neg(int64_t a) { return -a; }

void _interpret_iadd( struct vm_state* state ) { lift_binop(& state->data_stack, i64_add); }
void interpret_isub( struct vm_state* state ) { lift_binop(& state->data_stack, i64_sub); }
void interpret_imul( struct vm_state* state ) { lift_binop(& state->data_stack, i64_mul); }
void interpret_idiv( struct vm_state* state ) { lift_binop(& state->data_stack, i64_div); }
void interpret_icmp( struct vm_state* state ) { lift_binop(& state->data_stack, i64_cmp); }

void interpret_ineg( struct vm_state* state ) { lift_unop (& state->data_stack, i64_neg);  }

enum ins_arg_type { IAT_NOARG, IAT_I64 };

struct ins_descr {
  const char*       mnemonic;
  enum ins_arg_type argtype;
  bool              affects_ip;

  size_t            stack_min;
  int64_t           stack_delta;
};

const struct ins_descr instructions[] = {
  [BC_PUSH]   = { "push",  IAT_I64  ,   false     },
  [BC_IADD]   = { "iadd",  IAT_NOARG,   false     },
  [BC_ISUB]   = { "isub",  IAT_NOARG,   false     },
  [BC_IMUL]   = { "imul",  IAT_NOARG,   false     },
  [BC_IDIV]   = { "idiv",  IAT_NOARG,   false     },
  [BC_IMOD]   = { "imod",  IAT_NOARG,   false     },
  [BC_INEG]   = { "ineg",  IAT_NOARG,   false     },
  [BC_IPRINT] = { "iprint",IAT_NOARG,   false     },
  [BC_IREAD]  = { "iread", IAT_NOARG,   false     },
  [BC_SWAP]   = { "swap",  IAT_NOARG,   false     },
  [BC_POP]    = { "pop",   IAT_NOARG,   false     },
  [BC_DUP]    = { "dup",   IAT_NOARG,   false     },
  [BC_ICMP]   = { "icmp",  IAT_NOARG,   false     },
  [BC_JMP]    = { "jmp",   IAT_I64  ,   true      },
  [BC_JZ]     = { "jz",    IAT_I64  ,   true      },
  [BC_STOP]   = { "stop",  IAT_NOARG,   true      }
};

// this is cursed
typedef void (*ins_interpreter)(struct vm_state* state);
// ins_interpreter ins_interpreters[] ???
ins_interpreter* const ins_interpreters[] = {
  [BC_PUSH]   = interpret_push,
  [BC_IADD]   = interpret_iadd,
  [BC_ISUB]   = interpret_isub,
  [BC_IMUL]   = interpret_imul,
  [BC_IDIV]   = interpret_idiv,
  [BC_INEG]   = interpret_ineg,
  [BC_IPRINT] = interpret_iprint,
  [BC_IREAD]  = interpret_iread,
  [BC_SWAP]   = interpret_swap,
  [BC_POP]    = interpret_pop,
  [BC_DUP]    = interpret_dup,
  [BC_ICMP]   = interpret_icmp,
  [BC_STOP]   = interpret_stop
};
// ins_interpreter* actions ???
void interpret(struct vm_state* state, ins_interpreter * const  (actions)[]) {
  for (; state->ip ;) {
    const union ins* ins = state->ip;

    const struct ins_descr* ins_descr = instructions + ins->opcode;

    size_t st_m = ins_descr->stack_min;
    int64_t count = (int64_t) state->data_stack.count;
    if (st_m > count) {
        printf("%s", "Stack underflow\n");
        return;
    }
    
    int64_t st_d = ins_descr->stack_delta;
    int64_t st_s = (int64_t) state->data_stack.data.size;
    if (st_d > st_s - count) {
        printf("%s", "Stack overflow\n");
        return;
    }
    
    //(*actions[ins->opcode])(state); ???
    actions[ins->opcode](state);

    if (!ins_descr->affects_ip) { state->ip = state->ip + 1; }
  }
}

int main() {
    int64_t i = 3;
    int64_t x = 0;
    switch (i) {
        case 0:  { x = x + 10; };
        case 1:  { x = x + 10; };
        case 2:  { x = x + 10; };
        case 4:  { x = x + 10; };
        case 5:  { x = x + 10; };
        default: { x = x + 1; };
    }
    printf("%i\n", x);

    i = 4;
    x = 0;
    switch (i) {
        case 0:  { x = x + 1; };
        case 1:  { x = x + 1; };
        case 2:  { x = x + 1; };
        case 4:  { x = x + 1; };
        case 5:  { x = x + 1; };
        default: { x = x + 1; };
    }
    printf("%i", x);

    return 0;
}