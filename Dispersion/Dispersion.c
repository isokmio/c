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

double *noMutableOrder(double *data, int size){
    double *array = malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++) {
        array[i] = data[i];
    }
    order(array, size);
    return array;
}

double range(double *data, int size){
    double *ordered = noMutableOrder(data, size);
    return ordered[size-1] - ordered[0];
}

double meanDeviation(double *data, int size){
    double aMean = mean(data, size);
    double acumulate = 0.0;
    for (int i = 0; i < size; i++) {
        acumulate += abs(aMean - data[i]);
    }
    return acumulate/size;
}

double typicalDeviation(double *data, int size){
    double aMean = mean(data, size);
    double acumulate = 0.0;
    for (int i = 0; i < size; i++) {
        acumulate += pow(aMean - data[i], 2);
    }
    return sqrt(acumulate/size);
}

double variance(double *data, int size){
    return pow(typicalDeviation(data, size), 2);
}

double variationCoefficient(double *data, int size){
    return typicalDeviation(data, size)/mean(data, size);
}

#define SIZE 10
int main(){
    double data[SIZE] = {2.0, 2.0, 3.0, 5.0, 5.0, 5.0, 6.0, 6.0, 8.0, 9.0};
    printf("Range: %3.2f\n", range(data, SIZE));
    printf("Mean deviation: %3.2f\n", meanDeviation(data, SIZE));
    printf("Typical deviation: %3.2f\n", typicalDeviation(data, SIZE));
    printf("Variance: %3.2f\n", variance(data, SIZE));
    printf("Coefficient of variation: %3.2f ", variationCoefficient(data, SIZE));
    
    return 0;
}
