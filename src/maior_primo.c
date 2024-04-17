#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define TARGET 5000000 // a partir daqui fica muito custoso calcular os primos (demorou 11min27s)
#define THREAD_RANGE 1000 // diminuir o número de threads, no meu pc, não aumenta performance
#define THREAD_NUM (TARGET / THREAD_RANGE)

pthread_mutex_t mutex;
size_t largestPrime = 0;

void* getPrimeInRange(void* startPtr) {
    size_t start = *((int*) startPtr);
    const size_t END = start + THREAD_RANGE;

    if (start < 2) {
        start = 2;
    }

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

            if (start > largestPrime) {
                pthread_mutex_lock(&mutex);

                largestPrime = start;

                pthread_mutex_unlock(&mutex);
            }
        }
    }

    return NULL;
}

typedef struct {
    pthread_t thread;
    size_t startValue;
} PrimeThread;

int main() {
    PrimeThread threads[THREAD_NUM];

    pthread_mutex_init(&mutex, NULL);

    for (size_t i = 0, start = 0; i < THREAD_NUM; i++, start += THREAD_RANGE) {
        threads[i].startValue = start;

        int threadCreationStatus = pthread_create(
            &threads[i].thread,
            NULL,
            getPrimeInRange,
            &threads[i].startValue
        );

        if (threadCreationStatus != 0) {
            printf("Error while creating thread %zu\n", i);

            exit(-1);
        }
    }

    for (size_t i = 0; i < THREAD_NUM; i++) {
        pthread_join(threads[i].thread, NULL);
    }

    printf("Largest prime: %zu\n", largestPrime); // 399971

    pthread_mutex_destroy(&mutex);

    return 0;
}
