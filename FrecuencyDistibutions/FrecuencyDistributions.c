#include <stdio.h>
#include <stdlib.h>
#include "arrayinput.h"
#define SIZE 65

typedef struct {
    int lower;
    int upper;
    int quantity;
} Clazz;

/**
 *  Return an array with the frecuency in each interval class
 */
int* getFrequencyArray(int *row, int rowSize, int qIntervals, int lowest, int intervalSize){
    int *frecuencies = malloc(qIntervals*sizeof(int));
    int j=0;
    
    for(int i=1; i<=qIntervals; i++){
        int counter = 0;
        int upperLimit = lowest + i*intervalSize;
        while(j<rowSize && row[j]<upperLimit) {
            counter++;
            j++;
        }
        frecuencies[i] = counter;
    }
    
    return frecuencies;
}


/**
 * Print array
 */
void printClazz(Clazz *clazzes, int size){
    for (int i = 0; i < size; i++) {
        printf("%i-%i:  %i\n", clazzes[i].lower, clazzes[i].upper, clazzes[i].quantity);
    }
}


/**
 * Create an array with all classes
 */
Clazz* createClazz(int qIntervals, int lowest, int intervalSize){
    Clazz* clazz = malloc(qIntervals*sizeof(Clazz));
    int pivot = lowest;
    for(int j=0; j<qIntervals; j++){
        clazz[j].lower = pivot;
        clazz[j].upper = pivot + intervalSize;
        pivot += intervalSize;
        clazz[j].quantity = 0;
    }
    
    return clazz;
}

void countOcurrencies(int *row, int rowSize, Clazz *clazz, int intervals){
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < intervals; j++) {
            if(clazz[j].lower <= row[i] && row[i] <= clazz[j].upper){
                clazz[j].quantity += 1;
            }
        }
    }
}

char *renderString(int size){
    char *cad = malloc(size*sizeof(char));
    int i = 0;
    for (i = 0; i < size; i++) {
        cad[i] = '*';
    }
    cad[i] = '\0';
}

void renderRow(int lowerLabel, int upperLabel, int limit){
    char line[limit+1];
    int j=0;
    for(j=0; j<limit; j++){
        line[j] = '*';
    }
    line[j] = '\0';
    
    printf("%2i-%2i:  %s\n", lowerLabel, upperLabel,  line);
}

/**
 * Display histogram in horizontal direction
 */
void renderHistogram(int *frecuencyArray, int size, int intervalSize, int lowest, int high){
    int lowerLimit = lowest;
    int upperLimit = lowest + intervalSize;
    printf("\n\nHISTOGRAMA\n\n");
    for(int i=0; i<=size; i++){
        renderRow(lowest, lowest + intervalSize, frecuencyArray[i]);
        lowest += intervalSize;
    }
}

/**
 * Calculate the relative frequencies from row
 **/
double* relativeFrequencies(int *array, int size, int totalFrequency){
    double *frequencies = malloc(size*sizeof(double));
    for(int i=0; i<totalFrequency; i++){
        frequencies[i] = (double)array[i]/(double)totalFrequency;
    }
    
    return frequencies;
}


void renderRelatives(double *frequencies, int size, int intervalSize, int lowest){
    int lowerLimit = lowest;
    int upperLimit = lowest + intervalSize;
    
    printf("\n\nRELATIVE FREQUENCIES\n\n");
    double error = 0.0;
    for(int i=0; i<=size; i++){
        printf("%3i-%3i: %4.2f\n", lowerLimit, upperLimit, frequencies[i]*100);
        error += frequencies[i];
        lowerLimit = upperLimit;
        upperLimit += intervalSize;
    }
    printf("\nError: %5.2f\n\n", (1- error)*100);
}

int* acumFrequencies(int *array, int size){
    int *acumArray = (int*)malloc(sizeof(int)*size);
    acumArray[0] = array[0];
    for (int i = 1; i < size; i++) {
        acumArray[i] = acumArray[i-1] + array[i];
    }
    return acumArray;
}

void renderAcumulative(int *array, int size){    
    printf("\n\nACUMULATIVE FREQUENCIES\n\n");
    for(int i=0; i<size; i++){
        printf("%i\n", array[i]);
    }
    printf("\n");
}


/**
 * Acumulate the values for the frequencies calculated 
 **/
double* acumFrequenciesPer(double *array, int size){
    for (int i = 1; i < size; i++) {
        array[i] = array[i-1] + array[i];
    }
    return array;
}

void renderAcumulativePer(double *array, int size){
    printf("\n\nACUMULATIVE FREQUENCIES\n\n");
    for (int i = 0; i < size; i++) {
        printf("%4.2f\n", array[i] * 100);
    }
    printf("\n\n");
}

void tRenderAcumulativePer(double *array, int size){
    double acum = array[0];
    int i = 1;
    printf("%4.2f\n", acum);
    do{
        acum += array[i++];
        printf("%4.2f\n", acum);
    } while(i <= size);
}

int main(){
    int notes[SIZE];
    randomInit(notes, SIZE, 240);
    order(notes, SIZE);
    printf("Ordered notes: \n");
    printArray(notes, SIZE);
    int lowest = oLowest(notes, SIZE);
    int higest = oHigest(notes, SIZE);
    int range = oRange(notes, SIZE);
    int intervalSize = getIntervalWidth(notes, SIZE);
    int intervals = range/intervalSize;
    Clazz *clazzes = createClazz(intervals, lowest, intervalSize);

    printf("The highest value in the notes are: %i.\n", higest);
    printf("The lowest value in the notes are: %i.\n", lowest);
    printf("The range of this set is: %i.\n", range);
    printf("The value found for interval width is: %i.\n", intervalSize);
    printf("The number of intervals are: %i.\n\n", intervals);
    countOcurrencies(notes, SIZE, clazzes, intervals);
    printClazz(clazzes, intervals);
    
    //printArray(frecuencies, intervals);
    //for(int i=0; i<=intervals; i++){
    //    printf("%i ", lowest + i*intervalSize);
    //}
    //renderHistogram(frecuencies, intervals, intervalSize, lowest, 50);
    
    //double *rFrecuencies = relativeFrequencies(frecuencies, intervals, SIZE);
    //renderRelatives(rFrecuencies, intervals, intervalSize, lowest);

    //int *rAcumulative = acumFrequencies(frecuencies, intervals);
    //renderAcumulative(rAcumulative, intervals);

    //double *rAcumulative = acumFrequenciesPer(rFrecuencies, intervals);
    //renderAcumulativePer(rAcumulative, intervals);

    //tRenderAcumulativePer(rFrecuencies, intervals);
    return 0;
}