#include <stdio.h>
#include <stdlib.h>
#include "arrayinput.h"
#define SIZE 400

/**
 *  Return an array with the frecuency in each interval class
 */
int* getFrecuencyArray(int *row, int rowSize, int qIntervals, int lowest, int intervalSize){
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
 * Display historgram in horizontal direction
 */
void renderHistogram(int *frecuencyArray, int size, int intervalSize, int lowest, int high){
    int lowerLimit = lowest;
    int upperLimit = lowest + intervalSize;
    
    printf("\nHISTOGRAMA\n\n");
    
    for(int i=0; i<size; i++){
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
    int *frecuencies = getFrecuencyArray(notes, SIZE, intervals, lowest, intervalSize);

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
    return 0;
}