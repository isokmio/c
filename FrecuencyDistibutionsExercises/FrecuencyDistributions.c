#include <stdio.h>
#include <stdlib.h>
#include "arrayinput.h"
#define SIZE 70

typedef struct{
    int size;
    int entries[30];
} UniqueEntry;

typedef struct {
    int lower;
    int upper;
    int quantity;
    int acumulate;
    double acumulateRelative;
    double relative;
    UniqueEntry unique;
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

void printUnique(DataRow data){
    printf("\n\nUNIQUE\n\n");
    for (int i = 0; i < data.intervals; i++) {
        printf("%3.2i-%3.2i: ", data.clazz[i].lower, data.clazz[i].upper);
        for (int j = 0; j < data.clazz[i].unique.size; j++) {
            printf("%3i ", data.clazz[i].unique.entries[j]);
        }
        printf("\n");
    }
}

void createClazz(DataRow *data, int lowest, int intervalSize){
    data->clazz = malloc(data->intervals*sizeof(Clazz));
    int pivot = lowest;
    for(int j=0; j<data->intervals; j++){
        data->clazz[j].lower = pivot;
        data->clazz[j].upper = pivot + intervalSize;
        pivot += intervalSize;
        data->clazz[j].quantity = 0;
        data->clazz[j].acumulate = 0;
    }
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

void calculateUniqueEntry(int *row, DataRow data){
    for (int i = 0; i < data.total; i++) {
        for (int j = 0; j < data.intervals; j++) {
            if(data.clazz[j].lower <= row[i] && row[i] < data.clazz[j].upper){
                data.clazz[j].unique.entries[data.clazz[j].unique.size] = row[i];
                data.clazz[j].unique.size += 1;
            }
        }
    }
}

int main(){
    // 1. Ordenaciones
    int numbers[10] = {17, 45, 38, 27, 6, 48, 11, 57, 34, 22};
    order(numbers, 10);
    printf("Rango: %i\n", oRange(numbers, 10));
    
    // 2. Notes
    int notes[80] = {
        68, 84, 75, 82, 68, 90, 62, 88, 76, 93, 
        73, 79, 88, 73, 60, 93, 71, 59, 85, 75,
        61, 65, 75, 87, 74, 62, 95, 78, 63, 72,
        66, 78, 82, 75, 94, 77, 69, 74, 68, 60,
        96, 78, 89, 61, 75, 95, 60, 79, 83, 71,
        79, 62, 67, 97, 78, 85, 76, 65, 71, 75,
        65, 80, 73, 57, 88, 78, 62, 76, 53, 74,
        86, 67, 73, 81, 72, 63, 76, 75, 85, 77
    };
    order(notes, 80);
    
    // a.
    printf("Higest: %i\n", oHigest(notes, 80));
    
    // b.
    printf("Lowest: %i\n", oLowest(notes, 80));
    
    // c.
    printf("Rango: %i\n", oRange(notes, 80));
    
    // d.
    printf("5 higest: ");
    int *higests2 = oHigestRange(notes, 80, 5);
    for (int i = 0; i < 5; i++) {
        printf("%i ", higests2[i]);
    }
    printf("\n");
    
    // e.
    printf("5 lowest: ");
    int *lowest2 = oLowestRange(notes, 80, 5);
    for (int i = 0; i < 5; i++) {
        printf("%i ", lowest2[i]);
    }
    printf("\n");
    
    // f.
    printf("10ht higher: %i\n", notes[70]);
    
    // g. countEqualLower
    printf("# students with note >= 75: %i\n", countEqualHigher(notes, 80, 75));
    
    // h.
    printf("# students with note <= 75: %i\n", countEqualLower(notes, 80, 75));
    printf("# students with note = 75: %i\n", countEqual(notes, 80, 75));
    
    // i.
    double studentsBetween = (double)countEqualBetween(notes, 80, 65, 85)/80;
    printf("students between 65 and 85: %3.1f\n", studentsBetween*100);
    
    
    int weigth[25] = {
        138, 164, 150, 132, 144, 125, 149, 157,
        146, 158, 140, 147, 136, 148, 152, 144,
        168, 126, 138, 176, 163, 199, 154, 165,
        146, 173, 142, 147, 135, 153, 140, 135,
        161, 145, 135, 142, 150, 156, 145, 128
    };

    DataRow data;
    order(weigth, 25);
    int *frecuencies = frequencies(weigth, data);

    return 0;
}