#include<stdio.h>
#include <math.h>

void swap(int* a, int* b) {
    int c;
    c = *a;
    *a = *b;
    *b = *&c;
}

void normalize(int* a) {
    if (*a < 0) {
        return;
    }
    while ((*a % 2 == 0) && (*a > 0)) {
        *a /= 2;
    }
}

void simple(int n, int* a, int* b) {
    *a = 1;
    *b = n;
}

void factorize( int n, int* a, int* b )
{
    if ( n == 1 )
    {
        simple( n, a, b );
        return;
    }
        
    int end = sqrt( n ) + 1;
    int is_simple = 1;
    int min_divider = 0;
    int max_divider = 0;
    for ( int i = 2; i <= end; i++ )
    {
        if ( n % i == 0 )
        {
            is_simple = 0;
            min_divider = i;
            max_divider = n / i;
            break;
        }
    }
        
    if ( is_simple )
    {
        simple( n, a, b );
        return;
    }
    
    *a = min_divider;
    *b = max_divider;
    n = ( *a ) * ( *b );
}

void array_reverse(int* array, int size) {
    int c;
    for (int i = 0; i <= (size - 1) / 2; i++) {
        c = array[size - i - 1];
        array[size - i - 1] = array[i];
        array[i] = c;
    }
}

void array_reverse_ptr(int* array, int* limit) {
    int size = limit - array;
    array_reverse(array, size);
}

void array_fib(int* array, int* limit) {
    int size = limit - array;
    if (size <= 0) {
        return;
    }
    if (size >= 1) {
        array[0] = 1;
    }
    if (size >= 2) {
        array[1] = 1;
    }
    if (size > 2) {
        for (int* current = array + 3 - 1; current < limit; current++) {
            *current = *(current - 1) + *(current - 2);
        }
    } else {
        return;
    }
}

int predicate(int number) {
    return number % 2 == 0;
}

int array_contains(int* array, int* limit, int** position) {
   if ((limit - array) <= 0) return 0;
   for (int* current = array; current < limit; current++) {
       if (predicate(*current)) {
           *position = current;
           return 1;
       }
   }
   return 0;
}

int is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

int string_count(char* str) { 
    if ( str == NULL || *str == 0 ) return 0;
    
    char* current = str;
    int byte_sum = 0;
    while ( *current != 0 ) {
        byte_sum++;
        current++;
    }
        
    return byte_sum;
}

int string_words(char* str)  {
    if ( str == NULL || *str == 0 ) return 0;
    
    char* current = str;
    int word_counter = 0;
    while ( *current != 0 ) {
        if ( !is_whitespace( *current ) && ( is_whitespace( *( current + 1 ) ) || ( *( current + 1 ) == 0 ) ) ) {
            word_counter++;
        }
        current++;
    }
    
    return word_counter;
}

int main() {
    int x = 10;
    int y = 200;

    swap( &x, &y );

    printf("%i %i\n", x, y);

    int c = 100;
    normalize(&c);
    printf("%i\n", c);

    int var1;
    int var2;

    factorize(10, &var1, &var2);
    printf("%i %i\n", var1, var2);

    int myarray[] = { 1, 2, 3, 4, 5 };
    size_t size = sizeof(myarray) / sizeof(*(myarray + 0));

    array_reverse(myarray, size);
    for (int i = 0; i < size; i++)
        printf("%i\n", *(myarray + i));

    array_reverse_ptr(myarray, myarray + size);
    for (int i = 0; i < size; i++)
        printf("%i\n", *(myarray + i));

    int marr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    size_t sz = sizeof(marr) / sizeof(*(marr + 0));
    array_fib(marr, marr + sz);
    for (int i = 0; i < sz; i++)
        printf("%i\n", *(marr + i));

    int *pos = NULL;
    printf("%i\n", array_contains(marr, marr + sz, &pos));

    char* s = "hello  world";
    int s_size = string_count(s);
    int words = string_words(s);
    printf("length: %d words: %d", s_size, words);
    
    return 0;
}