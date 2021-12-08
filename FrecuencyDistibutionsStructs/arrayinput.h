
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

/**
 *  This method should be save into header (.h) file to be reused
 */
void randomInit(int *array, int size, int range)
{
    for(int i=0; i<size; i++){
        array[i] = rand()%range;
    }
}


/**
* This method should be save into heade (.h) file to be reused
*/
void printArray(int *array, int size){
    for(int i=0; i<size; i++){
        printf("%i ", array[i]);
    }
    printf("\n");
}

/**
 *  Exchange two value position in the same array
 */
int swap(int *array, int size, int i, int j){
    // Checks constrainst to execute de function
    if((i<0 || i>=size) || (j<0 || j>=size))
        return -1;

    int buffer = array[i];
    array[i] = array[j];
    array[j] = buffer;
    return 1;
}

/**
 * Order an array in the way define by parameter ASC 
 */
void order(int *array, int size){
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            if(array[j] < array[i] ){
                swap(array, size, i, j);
            }
        }
    }
}

/**
 * Get the hige value in the ordered array
 */
int oHigest(int *array, int size){
    return array[size-1];
}


/**
 * Get lowest value in the ordered array
 */
int oLowest(int *array, int size){
    return array[0];
}

/**
 * Get the value of the range in the ordered array
 */
int oRange(int *array, int size){
    return oHigest(array, size) - oLowest(array, size);
}

/**
 * Get the corect value of the width for the interval
 */
int getIntervalWidth(int *array, int size){
    int range = oRange(array, size);
    int limit = sqrt(range);
    int selected = -1;
    for(int i=2; i<=limit; i++){
        if((range%i) == 0){
            selected = i;
        }
    }
    return selected;
}