#include<stdio.h>
#include <math.h>

int read_int() {
    int res = 0; 
    scanf("%d", &res);
    return res; 
}

int is_square(int a) {
    if (a < 0) {
        return 0;
    }
    if ((a == 0) || (a == 1)) {
        return 1;
    }
    double i = 2;
    while (i < a) {
        if ((i * i) == a) {
            return 1;
        }
        i += 1;
    }
    return 0;
}

int divides(int a, int b) { 
    return a % b == 0; 
}

void print_newline() { 
    printf("\n"); 
}

void divisors(int n) {
    int i = 2;
    
    printf("%d: ", n);
    while (i <= n) {
        if (divides(n, i)) {
            printf("%d ", i);
        }
        i++;
    }
    
    print_newline();
}

void all_divisors(int limit) {
    int i = 1;
    while (i <= limit) {
        divisors(i);
        i++;
    }
}

int is_prime(int a) {
    if (a < 2) {
        return 0;
    }
    
    int end = sqrt(a) + 1;
    int i = 2;
    while (i < end) {
        if (a % i == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}

int main() {
    int insomnia = read_int();
    
    if (insomnia > 10) {
        printf("No");
    } else {
        while (insomnia <= 10) {
            printf("%i ", insomnia);
            insomnia++;
        }
    }

    printf("\n");

    all_divisors(100);

    printf("\n");

    printf("%i\n", is_square(4));
    printf("%i", is_prime(3));
   
    return 0;
}
