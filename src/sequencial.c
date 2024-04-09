#include <stdio.h>
#include <stdbool.h>

int main() {
    for (size_t i = 2; i < 1000000; i++) {
        bool isPrime = true;

        for (size_t j = 2; j < i; j++) {
            if (i % j == 0) {
                isPrime = false;

                break;
            }
        }

        if (isPrime) {
            printf("%zu\n", i);
        }
    }

    return 0;
}
