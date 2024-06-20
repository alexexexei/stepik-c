#include<stdio.h>

void greet() {
   printf("Hello, ");
}

void _greet( int n ) {
   printf("Hello ");
   printf("%d", n);
   printf("\n");
}

void b() {
   printf("Boris");
}

void v() {
   printf("Vladimir");
}

void print_int(int arg) {
   printf("%d", arg);
}

void print_int2(int arg1, int arg2) {
   printf("%d", arg1);
   printf("\n");
   printf("%d", arg2);
}

void print_newline() {
    printf("\n");
}

void f(int a, int b) {
    printf("%i", a + b);
}

int avg3(int a, int b, int c) {
    return (int) ((a + b + c) / 3);
}

int main() {
   printf("Never");
   printf("gonna");
   printf(" give you up");

   printf("\n");

   printf("%i", 5*6*7*8 + 17283);

   printf("\n");

   greet();
   b();
   print_newline();
   greet();
   v();
   print_newline();
   greet();
   b();

   printf("\n");

   _greet(10);
   _greet(20);
   _greet(42);

   printf("\n");

   f(3, 5);
   printf("\n%i", avg3(1, 5, 3));

   return 0;
}