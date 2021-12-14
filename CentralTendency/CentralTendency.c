/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int frecuency;
  double number;
} Clazz;

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

int fmean(Clazz *clazzes, int size){
    double acumulate = 0.0;
    double total = 0.0;
    
    for (int i = 0; i < size; i++) {
        acumulate += clazzes[i].frecuency*clazzes[i].number;
        total += clazzes[i].frecuency;
    }
    return acumulate/total;
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


int main(){
    double data[11] = {1.0, 2.0, 4.0, 3.0, 4.0, 4.0, 5.0, 1.0, 5.0, 5.0, 5.0};
    double weigths[5] = {0.1, 0.3, 1.2, 3.2, 0.9};
    
    printf("%3.2f", mode(data, 11));
    
    
    return 0;
}
