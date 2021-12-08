#include <stdio.h>
#include <stdlib.h>
#include "arrayinput.h"
#define SIZE 70

typedef struct {
    int lower;
    int upper;
    int quantity;
    int acumulate;
    double acumulateRelative;
    double relative;
} Clazz;

typedef struct {
    int total;
    int intervals;
    double relatives;
    Clazz *clazz; 
} DataRow;

void printClazz(DataRow data){
    for (int i = 0; i < data.intervals; i++) {
        printf("%3.2i-%3.2i: %2.1i %2.1i %5.2f %5.2f\n", data.clazz[i].lower, data.clazz[i].upper, data.clazz[i].quantity, data.clazz[i].acumulate, data.clazz[i].relative, data.clazz[i].acumulateRelative);
    }
}

Clazz* createClazz(int qIntervals, int lowest, int intervalSize){
    Clazz* clazz = malloc(qIntervals*sizeof(Clazz));
    int pivot = lowest;
    for(int j=0; j<qIntervals; j++){
        clazz[j].lower = pivot;
        clazz[j].upper = pivot + intervalSize;
        pivot += intervalSize;
        clazz[j].quantity = 0;
        clazz[j].acumulate = 0;
    }
    
    return clazz;
}

void frequencies(int *row, DataRow data){
    for (int i = 0; i < data.total; i++) {
        for (int j = 0; j < data.intervals; j++) {
            if(data.clazz[j].lower <= row[i] && row[i] < data.clazz[j].upper){
                data.clazz[j].quantity += 1;
                break;
            }
        }
    }
}

char* renderLine(int size){
    char *cad = malloc((size + 1)*sizeof(char));
    int i = 0;
    for (i = 0; i < size; i++) {
        cad[i] = '*';
    }
    cad[i] = '\0';
    return cad;
}

void graphHistogram(DataRow data){
    printf("\n\nHISTOGRAM\n\n");
    for (int i = 0; i < data.intervals; i++) {
        printf("%3.2i-%3.2i: %s\n", data.clazz[i].lower, data.clazz[i].upper,  renderLine(data.clazz[i].quantity));
    }
}

void graphAcumulate(DataRow data){
    printf("\n\nACUMULATIVE FREQUENCIES\n\n");
    for (int i = 0; i < data.intervals; i++) {
        printf("%3.2i-%3.2i: %s\n", data.clazz[i].lower, data.clazz[i].upper,  renderLine(data.clazz[i].acumulate));
    }
}

void relative(DataRow data){
    for (int i = 0; i < data.intervals; i++) {
        data.clazz[i].relative = (double)data.clazz[i].quantity/data.total;
    }
}

void acumulate(DataRow data){
    data.clazz[0].acumulate = data.clazz[0].quantity;
    for (int i = 1; i < data.intervals; i++) {
        data.clazz[i].acumulate = data.clazz[i-1].acumulate + data.clazz[i].quantity;
    }
}

void acumulateRelative(DataRow data){
    data.clazz[0].acumulateRelative = data.clazz[0].relative;
    for (int i = 1; i < data.intervals; i++) {
        data.clazz[i].acumulateRelative = data.clazz[i-1].acumulateRelative + data.clazz[i].relative;
    }
}

double calculateError(DataRow data){
    double error = 1.0;
    for (int i = 0; i < data.intervals; i++) {
        error -= data.clazz[i].relative;
    }
    return error;
}


int main(){
    int notes[SIZE];
    DataRow data = {.total=SIZE, .intervals=0, .relatives=0.0};
    randomInit(notes, SIZE, 200);
    order(notes, SIZE);
    printf("ORDERED NOTES: \n");
    printArray(notes, SIZE);
    int lowest = oLowest(notes, SIZE);
    int higest = oHigest(notes, SIZE);
    int range = oRange(notes, SIZE);
    int intervalSize = getIntervalWidth(notes, SIZE);
    
    data.intervals = range/intervalSize;
    data.clazz = createClazz(data.intervals, lowest, intervalSize);

    printf("The highest value in the notes are: %i.\n", higest);
    printf("The lowest value in the notes are: %i.\n", lowest);
    printf("The range of this set is: %i.\n", range);
    printf("The value found for interval width is: %i.\n", intervalSize);
    printf("The number of intervals are: %i.\n\n", data.intervals);
    frequencies(notes, data);
    relative(data);
    acumulate(data);
    acumulateRelative(data);
    printClazz(data);
    printf("Error of relatives are: %f.\n\n", calculateError(data));
    graphHistogram(data);
    graphAcumulate(data);
    
    return 0;
}