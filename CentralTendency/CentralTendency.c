/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <float.h>

typedef struct{
    double value;
    int quantity;
} Clazz;

typedef struct{
    double value;
    double weigth;
} Weights;

double mean(double *data, int size){
    double acumulate = 0.0;
    if(size==0) return 0.0;
    
    for (int i = 0; i < size; i++) {
        acumulate += (double) data[i];
    }
    return acumulate/size;
}

double wmean(Weights *data, int size){
    double acumulate = 0.0;
    if(size==0) return 0.0;
    for (int i = 0; i < size; i++) {
        acumulate += data[i].value*data[i].weigth;
    }
    return acumulate;
}

void order(double *data, int size){
    double cache=0.0;
    for (int i = 0; i<size; i++) {
        for (int j = i+1; j<size; j++) {
            if(data[j] < data[i]){
                cache = data[i];
                data[i] = data[j];
                data[j] = cache;
            }
        }
    }
}

double median(double *data, int size){
    int m_position = size/2;
    if(size==0) return 0.0;
    order(data, size);
    if(size%2 == 1) return data[m_position];
    return (data[m_position-1] + data[m_position])/2;
}


double mode(double *data, int size){
    if (size==0) return 0.0;
    Clazz clazz[size];
    int entry = 0;
    
    for (int i = 0; i < size; i++) {
        clazz[i].value = 0.0;
        clazz[i].quantity = 0;
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if(data[i] == data[j]){
                clazz[i].value = data[i];
                clazz[i].quantity += 1;
            }
        }
    }
    
    int pivot = clazz[0].quantity;
    int pos=0;
    for (int i = 0; i < size; i++) {
        if(clazz[i].quantity > pivot){
            pos = i;
        }
    }
    
    if(clazz[pos].quantity==1)
        return 0.0;
    return clazz[pos].value;
}


double geometric(double *data, int size){
    if(size==0) return 0.0;
    double acumulate = 1.0;
    double pivot = 1.0/size;
    for (int i = 0; i < size; i++) {
        acumulate *= data[i];
    }
    return pow(acumulate, pivot);
}

double harmonic(double *data, int size){
    if(size==0) return 0.0;
    double acumulate;
    for (int i = 0; i < size; i++) {
        acumulate += 1.0/data[i];
    }
    
    return size/acumulate;
}

double square(double *data, int size){
    if(size==0) return 0.0;
    double acumulate;
    for (int i = 0; i < size; i++) {
        acumulate += pow(data[i], 2);
    }
    return sqrt(acumulate/size);
}


#define TEST_SIZE 10
#define EPSILON 0.01
void test(){
    double array[10] = {2.0, 2.0, 3.0, 5.0, 5.0, 5.0, 6.0, 6.0, 8.0, 9.0};
    double array2[7] = {3.0, 5.0, 6.0, 6.0, 7.0, 10.0, 12.0};
    assert(mean(array, TEST_SIZE) == 5.1);
    assert(mode(array, TEST_SIZE) == 5.0);
    assert(median(array, TEST_SIZE) == 5.0);
    printf("%f", fabs(square(array2, 7)));
    //assert(fabs(harmonic(array2, 7) - 6.43) < EPSILON);
    //assert(fabs(square(array2, 7) - 7.5)  < EPSILON);
}


#define SIZE 10
int main(){
    test();
    double data[10] = {2.0, 2.0, 3.0, 5.0, 5.0, 5.0, 6.0, 6.0, 8.0, 9.0};
    double weigths[5] = {0.1, 0.3, 1.2, 3.2, 0.9};
    
    printf("%3.2f  = %3.2f\n", mean(data, SIZE) - mode(data, SIZE), 3.0 * (mean(data, SIZE) - median(data, SIZE)));
    printf("%3.2f <= %3.2f <= %3.2f\n", harmonic(data, 3), geometric(data, 3), mean(data, 3));
    printf("%3.2f", square(data, 3));
    
    return 0;
}
