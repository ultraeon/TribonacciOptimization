#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scalable_numbers.h"

struct number* recursiveSolve(int n) {
    struct number *result;
    if(n == 0 || n == 1) {
        result = malloc(sizeof(struct number));
        result->basePointer = malloc(sizeof(unsigned int));
        result->len = 1;
        return result;
    }
    if(n == 2) {
        result = malloc(sizeof(struct number));
        result->basePointer = malloc(sizeof(unsigned int));
        result->basePointer[0] = 1;
        result->len = 1;
        return result;
    }
    struct number *firstAdd = addN(recursiveSolve(n-2), recursiveSolve(n-3));
    result = addN(firstAdd, recursiveSolve(n-1));
    return result;
}
int main() {
    struct number *result = recursiveSolve(30); // stack overflows at n = 31 lmao
    printN(result);
    return 0;
}