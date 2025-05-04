#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRAY_SIZE 10000

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int is_sorted(int *array, size_t size) {
    for (size_t i = 1; i < size; i++) {
        if (array[i-1] > array[i]) {
            return 0;
        }
    }
    return 1;
}

void fill_sorted(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = (int)i;
    }
}

void fill_reverse_sorted(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = (int)(size - i);
    }
}

void fill_random(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = rand();
    }
}

void test_case(const char *description, void (*fill_func)(int *, size_t)) {
    int *array = malloc(ARRAY_SIZE * sizeof(int));
    if (!array) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    fill_func(array, ARRAY_SIZE);

    clock_t start = clock();
    qsort(array, ARRAY_SIZE, sizeof(int), compare_ints);
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%s:\n", description);
    printf("  Time taken: %.6f seconds\n", duration);

    if (is_sorted(array, ARRAY_SIZE)) {
        printf("  Array is sorted correctly!\n");
    } else {
        printf("  Sorting failed!\n");
    }

    printf("\n");

    free(array);
}

int main() {
    srand((unsigned int)time(NULL));

    test_case("Sorted array", fill_sorted);
    test_case("Reverse sorted array", fill_reverse_sorted);
    test_case("Random array", fill_random);

    return 0;
}
