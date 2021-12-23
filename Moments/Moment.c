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

double moment(double *data, int size, int r, double origen){
    double acumulate = 0.0;
    for (int i = 0; i < size; i++) {
        acumulate += pow((data[i] - origen), r);
    }
    return acumulate/size;
}

double slant(double *data, int size){
    double d_mean = mean(data, size);
    double d_median = median(data, size);
    double d_dt = typicalDeviation(data, size);
    return (3*(d_mean-d_median))/d_dt;
}

#define SIZE 80
int main(){
    double data[SIZE] = {
        68.0, 84.0, 75.0, 82.0, 68.0, 90.0, 62.0, 88.0, 76.0, 93.0, 
        73.0, 79.0, 88.0, 73.0, 60.0, 93.0, 71.0, 59.0, 85.0, 75.0,
        61.0, 65.0, 75.0, 87.0, 74.0, 62.0, 95.0, 78.0, 63.0, 72.0,
        66.0, 78.0, 82.0, 75.0, 94.0, 77.0, 69.0, 74.0, 68.0, 60.0,
        96.0, 78.0, 89.0, 61.0, 75.0, 95.0, 60.0, 79.0, 83.0, 71.0,
        79.0, 62.0, 67.0, 97.0, 78.0, 85.0, 76.0, 65.0, 71.0, 75.0,
        65.0, 80.0, 73.0, 57.0, 88.0, 78.0, 62.0, 76.0, 53.0, 74.0,
        86.0, 67.0, 73.0, 81.0, 72.0, 63.0, 76.0, 75.0, 85.0, 77.0
    };
    
    double d_mean = mean(data, SIZE);
    double d_variance = variance(data, SIZE);
    double m4 = moment(data, SIZE, 4, d_mean);
    double s = typicalDeviation(data, SIZE);
    printf("Mean: %3.2f\n", d_mean);
    printf("Variance: %3.2f\n", d_variance);
    printf("Moment(2): %3.2f\n", moment(data, SIZE, 2, d_mean));
    printf("Moment(3): %3.2f\n", moment(data, SIZE, 3, d_mean));
    printf("Moment(4): %3.2f\n", m4);
    printf("Sesgo: %3.2f\n", slant(data, SIZE));
    printf("Curtosis: %3.2f\n", m4/pow(s, 4));
    
    return 0;
}
