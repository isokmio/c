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
    double w;
    int quantity;
} Clazz;

void sort(Clazz *data, int size){
    double cache=0.0, w=0.0;
    int q_cache=0;
    for (int i = 0; i<size; i++) {
        for (int j = i+1; j<size; j++) {
            if(data[i].quantity != -1 && data[j].quantity != -1){
                if(data[j].value < data[i].value){
                    cache = data[i].value;
                    q_cache = data[i].quantity;
                    w = data[i].w;
                    
                    data[i].value = data[j].value;
                    data[i].quantity = data[j].quantity;
                    data[i].w = data[j].w;
                    
                    data[j].value = cache;
                    data[j].quantity = q_cache;
                    data[j].w = data[i].w;
                }
            }
        }
    }
}

double min(double *data, int size){
    int min_position = 0;
    for (int i = 1; i < size; i++) {
        if(data[i]<data[min_position]){
            min_position = i;
        }
    }
    return data[min_position];
}

double max(double *data, int size){
    int max_position = 0;
    for (int i = 1; i < size; i++) {
        if(data[i] > data[max_position]){
            max_position = i;
        }
    }
    return data[max_position];
}

int isIn(double number, Clazz *array, int size){
    for (int i = 0; i < size; i++) {
        if(array[i].value == number){
            return i;
        }
    }
    return -1;
}

double mean(Clazz *clazz, int size){
    double acumulate = 0.0;
    int i = 0;
    while(clazz[i].quantity != -1){
        acumulate += clazz[i].value * clazz[i].quantity;
        i++;
    }
    return acumulate/size;
}

double weightedAverage(Clazz *clazz, int size){
    double acumulate = 0.0;
    int i=0;
    while(clazz[i].quantity != -1){
        acumulate += clazz[i].value * clazz[i].w;
        i++;
    }
    return acumulate/size;
}

double moment(Clazz *clazz, int size, int r, double origen){
    double numerator = 0.0;
    int i=1;
    while(clazz[i].quantity != -1){
        numerator += clazz[i].quantity * pow((clazz[i].value - origen), r);
        i++;
    }
    return numerator/size;
}

void initClazz(Clazz *clazz, int size){
    for (int i = 0; i < size; i++) {
        clazz[i].value = 0.0;
        clazz[i].quantity = -1;
    }
}

Clazz *frecuency(double *data, int size){
    Clazz *clazz = malloc(sizeof(Clazz)*size);
    int position, last_position = 0;
    initClazz(clazz, size);
    for (int i = 0; i < size; i++) {
        position = isIn(data[i], clazz, size);
        if(position != -1){
            clazz[position].quantity += 1;
        }else{
            clazz[last_position].value = data[i];
            clazz[last_position].quantity = 1;
            last_position++;
        }
    }
    return clazz;
}

void printClazz(Clazz *clazz, int size){
    printf("\nPrinting...\n");
    for (int i = 0; i < size; i++) {
        printf("%3.2f %i\n", clazz[i].value, clazz[i].quantity);
    }
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
    
    Clazz *clazz = frecuency(data, SIZE);
    printClazz(clazz, SIZE);
    double d_mean  = mean(clazz, SIZE);
    double d2_moment = moment(clazz, SIZE, 2, d_mean);
    printf("Moment Grouped Data: %5.2f", d2_moment);
    sort(clazz, SIZE);
    printClazz(clazz, SIZE);
    
    return 0;
}
