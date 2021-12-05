#include <stdio.h>
#include <stdlib.h>
#include "arrayinput.h"
#define SIZE 400

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
 * Display histogram in horizontal direction
 */
void renderHistogram(int *frecuencyArray, int size, int intervalSize, int lowest, int high){
    int lowerLimit = lowest;
    int upperLimit = lowest + intervalSize;
    
    printf("\nHISTOGRAMA\n\n");
    
    for(int i=0; i<=size; i++){
        char line[high];
        for(int j=0; j<high; j++){
            line[j] = '\0';
            if(j<frecuencyArray[i]){
                line[j] = '*';
            }
        }
        
        printf("%2i-%2i:  %s\n", lowerLimit, upperLimit,  line);
        lowerLimit = upperLimit;
        upperLimit += intervalSize;
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
        printf("%3i-%3i: %4.2f%\n", lowerLimit, upperLimit, frequencies[i]*100);
        error += frequencies[i];
        lowerLimit = upperLimit;
        upperLimit += intervalSize;
    }
    printf("\nError: %5.2f\n", (1- error)*100);
}

/**
 * Acumulate the values for the frequencies calculated 
 **/
double* acumFrequencies(double *array, int size){
    for (int i = 1; i < size; i++) {
        array[i] = array[i-1] + array[i];
    }
    return array;
}

void renderAcumulative(double *array, int size){
    for (int i = 0; i < size; i++) {
        printf("%4.2f\n", array[i]);
    }
}

void tRenderAcumulative(double *array, int size){
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
    int *frecuencies = getFrequencyArray(notes, SIZE, intervals, lowest, intervalSize);

    printf("The highest value in the notes are: %i.\n", higest);
    printf("The lowest value in the notes are: %i.\n", lowest);
    printf("The range of this set is: %i.\n", range);
    printf("The value found for interval width is: %i.\n", intervalSize);
    printf("The number of intervals are: %i.\n\n", intervals);
    
    printArray(frecuencies, intervals);
    for(int i=0; i<=intervals; i++){
        printf("%i ", lowest + i*intervalSize);
    }
    renderHistogram(frecuencies, intervals, intervalSize, lowest, 50);
    
    double *rFrecuencies = relativeFrequencies(frecuencies, intervals, SIZE);
    renderRelatives(rFrecuencies, intervals, intervalSize, lowest);

    double *rAcumulative = acumFrequencies(rFrecuencies, intervals);
    renderAcumulative(rAcumulative, intervals);

    //tRenderAcumulative(rFrecuencies, intervals);
    return 0;
}