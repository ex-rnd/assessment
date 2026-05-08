// James Kilonzo: pth_factor.c
#include <stdio.h>
#include <math.h>

long pthFactor(long n, long p) {


    // Complexity: Reduce O(N) to O(sqrt[N]) by utilizing factor pairing property
    long small_factors[100000]; // Approximately O(sqrt[N])
    long count = 0;


    // Find the small factors -- first half of the O(sqrt[N])
    for (long d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            small_factors[count] = d;
            count = count + 1; 
        }
    }


    // When p is already in the first half (small factors)
    if (p < count) {
        return small_factors[p-1];
    }


    // Working out the large factors - second half of the O(sqrt[N])

    p = p - count;
    long last_index = count - 1;


    // Edge case when dealing with Perfect Squares - Avoid duplicates
    if (small_factors[last_index] * small_factors[last_index] == n) {
        last_index = last_index - 1;
    }

    // Returning the large factors in order - correctly 

    if (p <= last_index +1) {
        return n / small_factors[last_index - (p-1)];
    }

    return 0;

}

int main() {

    // Basic Test 
    printf("Input: n = 10, p = 3 -> %ld (Expected Output 5)\n", pthFactor(10, 3));

    return 0;

}









