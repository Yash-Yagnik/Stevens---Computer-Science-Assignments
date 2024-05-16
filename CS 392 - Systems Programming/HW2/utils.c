/*******************************************************************************
 * Name        : utils.c
 * Author      : Yash Yagnik
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include "utils.h"

int cmpr_int(void* num1, void* num2){
    int* number1 = (int*)num1;
    int* number2 = (int*)num2;

    if (*number1 > *number2) {
        return 1;
    }
    else if (*number2 > *number1){
        return -1;
    }
    else {
        return 0;
    }
}
int cmpr_float(void* num1, void* num2){
    float* number1 = (float*)num1;
    float* number2 = (float*)num2;

     if (*number1 > *number2) {
        return 1;
    }
    else if (*number2 > *number1){
        return -1;
    }
    else {
        return 0;
    }
}

void print_int(void* result){
    int* output = (int*)result;

    printf("%d ", *output);
}
void print_float(void* result){
    float* output = (float*)result;

    printf("%f ", *output);
}
