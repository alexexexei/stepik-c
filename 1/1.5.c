#include<stdio.h>

int a = 10;
int b = 20;
int c = 20;

int read_int() {
    int x;
    scanf("%d", &x);
    return x;
}

void q1(int a, int b) {
    a = b;
    printf("a = %d b = %d", a, b);
}

void q2(int a, int b) {
    b = a;
    a = b;
    printf("a = %d b = %d", a, b);
}

void q3(int a, int b, int c) {
    c = a + b;
    b = a;
    a = b + c;
    printf("a = %d b = %d c = %d", a, b, c);
}

int discriminant(int a, int b, int c) {
    return b*b - 4*a*c;
}

int root_count(int a, int b, int c) {
   int D = discriminant(a, b, c);
   if (D < 0) {
       return 0;
   }
   if (D == 0) {
       return 1;
   }
   return 2;
}

int second_task() {
    int a = read_int();
    int b = read_int();
    int c = read_int();
    
    int result = root_count(a, b, c);
    printf("%d", result);
}

int main() {
    q1(a, b);

    printf("\n");

    q2(a, b);

    printf("\n");

    q3(a, b, c);

    printf("\n");

    int input1 = read_int();
    int input2 = read_int();

    printf("%d", input1 + input2);

    printf("\n");
    
    second_task();

    return 0;
}