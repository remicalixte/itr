#include <stdint.h>
#include <stdlib.h>

int *write_ptr = (int *)0xFC00000;
int *read_ptr = (int *)0xFC00004;
int *word_count_ptr = (int *)0xFC00008;

int main(int argc, char const *argv[]) {
    for (size_t i = 0; i < 1000; i++) {
        int n = 2 * i + 1;
        *write_ptr = n;
    }

    int size = *word_count_ptr;
    int *tab = malloc(size * sizeof(int));
    for (size_t i = 0; i < size; i++) {
        int n = *read_ptr;
        tab[i] = n;
    }
    free(tab);

    return 0;
}
