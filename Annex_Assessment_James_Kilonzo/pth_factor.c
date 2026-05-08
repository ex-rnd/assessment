// James Kilonzo: pth_factor.c
#include <stdio.h>
#include <math.h>

long pthFactor(long n, long p) {

    long long small_factors[100000];
    long long count = 0;

    for (long d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            small_factors[count] = d;
            count = count + 1; 
        }
    }

    if (p < count) {
        return small_factors[p-1];
    }

    p = p - count;
    long last_index = count - 1;

    if (small_factors[last_index] * small_factors[last_index] == n) {
        last_index = last_index - 1;
    }

    if (p <= last_index +1) {
        return n / small_factors[last_index - (p-1)];
    }

    return 0;

}

int main() {

    // Basic Test 
    printf("n = 10, p = 3 -> %ld (expected 5)\n", pthFactor(10, 3));
    // Perfect Square Test 
    printf("n = 36, p = 9 -> %ld (expected 36)\n", pthFactor(36, 9));
    // Edge Case
    printf("n=1,  p=2  -> %ld (expected 0)\n",  pthFactor(1, 2));
    // Really Big Number 
    printf("n=1000000000000000, p=1 -> %ld (expected 1)\n", pthFactor(1000000000000000L, 1));

    return 0;

}









