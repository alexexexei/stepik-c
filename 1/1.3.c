#include<stdio.h>

int print( int i ) { 
   printf("Hello!"); 
   return !i;
}

int is_single_digit(int n) {
    if ((n < 0) || (n > 9)) { 
        return 0;
    }  
    return 1;
}

int is_double_digit(int n) {
    if ((n < 10) || (n > 99)) { 
        return 0;
    } 
    return 1;
}

int is_sorted3(int a, int b, int c) { 
    if ((a > b) && (b > c)) {
        return -1;
    }
    if ((a < b) && (b < c)) {
        return 1;
    }
    return 0;
}

int max3(int a, int b, int c) {   
    if ((a >= b) && (a >= c)) {
        return a;
    }
    if ((b >= a) && (b >= c)) {
        return b;
    }
    return c;
}

void fizzbuzz(int number) {
    if (number <= 0) {
        printf("no");
        return;
    }
    if ((number % 3 == 0) && (number % 5 == 0)) {
        printf("fizzbuzz");
        return;
    }
    if (number % 3 == 0) {
        printf("fizz");
        return;
    }
    if (number % 5 == 0) {
        printf("buzz");
        return;
    }
}

int main() {
    int a = 10;
    if (a > 5) { printf("1"); }
    if (a > 8) { printf("2"); }
    if (a > 3) { printf("3"); }

    printf("\n");

    a = 10;
    if (a > 5) { printf("9"); }
    else {
        if (a > 8) { printf("2"); }
        if (a > 3) { printf("3"); }
    }

    printf("\n");

    printf("%d", 990 > 33 * 31);

    printf("\n");

    printf("%i\n", 4 > 3);
    printf("%i\n", 0);
    printf("%i\n", 99 <= 83);
    printf("%i\n", (44 > 99) && (99 > 44));
    printf("%i\n", (44 > 99) || (99 > 44));

    printf("%i\n",(1 > 2) > 3);
    printf("%i\n", (1 < 3) > 0);
    printf("%i\n", 1 && 9);
    printf("%i\n", 0 || 9);
    printf("%i\n", 8 && (5 < 4));

    printf("%i\n", 4 > 3 && print(10));
    printf("%i\n", 4 < 3 && print(42) && print(88));
    printf("%i\n", print(0) && print(9));
    printf("%i", 4 < 3 || print(42) || print(88));

    return 0;
}