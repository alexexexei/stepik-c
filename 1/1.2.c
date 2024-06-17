#include<stdio.h>

// <--default funcs-->
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
// <--end default funcs-->

// 2
void print_newline() {
    printf("\n");
}

// 5
void f(int a, int b) {
    printf("%i", a + b);
}

// 6
int avg3(int a, int b, int c) {
    return (int) ((a + b + c) / 3);
}

int main() {
   // <--q1-->
   printf("Never");
   printf("gonna");
   printf(" give you up");
   // <--end q1-->

   printf("\n");

   // 1
   printf("%i", 5*6*7*8 + 17283);

   printf("\n");

   // <--3-->
   greet();
   b();
   print_newline();
   greet();
   v();
   print_newline();
   greet();
   b();
   // <--end 3-->

   printf("\n");

   // <--4 (remove '_')-->
   _greet(10);
   _greet(20);
   _greet(42);
   // <--end 4-->

   return 0;
}