#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define TARGET 1000000
#define THREAD_RANGE 1000
#define THREAD_NUM (TARGET / THREAD_RANGE)

// Natural numbers greater than 1 that can only be divided by 1 and itself
void* getPrimeInRange(void* startPtr) {
    // Get range
    size_t start = *((int*) startPtr);
    const size_t END = start + THREAD_RANGE;

    // Assure the first thread (from 0 to 10000) will start from 2
    if (start < 2) {
        start = 2;
    }

    // Check every number in range
    for (; start < END; start++) {
        bool isPrime = true;

        for (size_t i = 2; i < start; i++) {
            if (start % i == 0) {
                isPrime = false;

                break;
            }
        }

        if (isPrime) {
            printf("%zu\n", start);
        }
    }

    // Returns NULL because function returns pointer to void
    return NULL;
}

typedef struct {
    pthread_t thread;
    size_t startValue;
} PrimeThread;

int main() {
    PrimeThread threads[THREAD_NUM];

    // Create threads
    for (size_t i = 0, start = 0; i < THREAD_NUM; i++, start += THREAD_RANGE) {
        threads[i].startValue = start;

        int threadCreationStatus = pthread_create(
            &threads[i].thread,
            NULL,
            getPrimeInRange,
            &threads[i].startValue
        );

        // Check creation error
        if (threadCreationStatus != 0) {
            printf("Error while creating thread %zu\n", i);

            exit(-1);
        }
    }

    // Join threads
    for (size_t i = 0; i < THREAD_NUM; i++) {
        pthread_join(threads[i].thread, NULL);
    }

    return 0;
}
