/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mean(double *data, int size){
    double acumulate = 0.0;
    if(size==0) return 0.0;
    
    for (int i = 0; i < size; i++) {
        acumulate += (double) data[i];
    }
    return acumulate/size;
}

double weighted(double *data, double *weigth, int size){
    double acumulate = 0.0;
    double wsum = 0.0;
    if(size==0) return 0.0;
    
    for (int i = 0; i < size; i++) {
        acumulate += data[i]*weigth[i];
        wsum += weigth[i];
    }
    return acumulate/wsum;
}

double median(double *data, int size){
    int m_position = size/2;
    if(size==0) return 0.0;
    if(size%2 == 1) return data[m_position];
    
    return (data[m_position-1] + data[m_position])/2;
}

void order(double *data, int size){
    double cache;
    for (int i = 0; i < size; i++) {
        for (int j = i; j < i; i++) {
            if(data[i] > data[j]){
                cache = data[i];
                data[i] = data[j];
                data[j] = cache;
            }
        }
    }
}

double mode(double *data, int size){
    if (size==0) return 0.0;
    order(data, size);
    int pivot = 0;
    int fr1, fr2;
    for (int i = 0; i < size; i++, fr2 += 1) {
        if(data[pivot] != data[i]){
            pivot = i;
            fr1 = fr2;
            fr2 = 0;
        }
    }
    return data[pivot];
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

#define SIZE 4

int main(){
    double data[8] = {2.0, 4.0, 8.0, 2.0, 3.4, 1.0, 4.0, 2.5};
    double weigths[5] = {0.1, 0.3, 1.2, 3.2, 0.9};
    
    
    printf("%3.2f - %3.2f = 3 (%3.2f - %3.2f)\n", mean(data, SIZE), mode(data, SIZE), mean(data, SIZE), median(data, SIZE));
    printf("%3.2f <= %3.2f <= %3.2f\n", harmonic(data, 3), geometric(data, 3), mean(data, 3));
    printf("%3.2f", square(data, 3));
    
    return 0;
}
