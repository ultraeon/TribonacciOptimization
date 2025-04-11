#include <stdio.h>

struct number {
    unsigned int *basePointer;
    unsigned int len;
};

void freeN(struct number *num) {
    free(num->basePointer);
    num->basePointer = NULL;
    free(num);
    num = NULL;
}

void printN(struct number *num) {
    for(int i = num->len-1; i > -1; i--) {
        printf("%u", num->basePointer[i]);
    }
    printf("\n");
}

struct number* addN(struct number *num1, struct number *num2) {
    struct number *res = malloc(sizeof(struct number));
    res->len = (num1->len > num2->len) ? num1->len + 1 : num2->len + 1;
    res->basePointer = malloc(sizeof(unsigned int) * res->len);
    unsigned int add1;
    unsigned int add2;
    unsigned int *curSection;
    unsigned int carry = 0;
    bool carryFlag;
    for(int i = 0; i < res->len; i++) { // lazy way of implementing scalable addition
        curSection = &res->basePointer[i];
        add1 = (i < num1->len) ? num1->basePointer[i] : 0;
        add2 = (i < num2->len) ? num2->basePointer[i] : 0;
        carryFlag = __builtin_uadd_overflow(add1+carry, add2, curSection);
        carry = (carryFlag) ? 1 : 0;
    }
    if(res->basePointer[res->len-1] == 0) {
        res->len -= 1; // lazy memory fix
    }
    return res;
}