#include <stdlib.h>
#include <stdio.h>
typedef struct {
    int *array;
    size_t used;
    size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
    a->array = (int *)malloc(initialSize * sizeof(int));
    a->used = 0;
    a->size = initialSize;
}

void insertArray(Array *a, int element) {
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (int *)realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

int * primeMul(Array *a, long int n) {

    int i = 2;

    while (i<=n*n) {
        if(!(n%i)) {
            insertArray(a, i);
            n = n/i;
        } else {
            i = i+1;
        }
    }

    insertArray(a, 0);
    return a->array;


}


int main() {

    Array a;
    long int in = 0;
    int i = 0;
    int *res;

    char c = 0;

    initArray(&a, 5);  // initially 5 elements
    insertArray(&a, 1);

    if (scanf("%ld%c", &in, &c)==0 || in <= 0) {
        printf("[error]\n");
        freeArray(&a);
    } else {

        res = primeMul(&a,in);

        while (res[i]) {
            printf("%d ", res[i]);
            i++;

        }

        freeArray(&a);


    }

    return 0;


}
