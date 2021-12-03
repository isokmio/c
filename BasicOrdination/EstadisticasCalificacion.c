
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define SIZE 100


/**
 *  This method should be save into header (.h) file to be reused
 */
void randomInit(int *array)
{
    for(int i=0; i<SIZE; i++){
        array[i] = rand()%100;
    }
}


/**
* This method should be save into heade (.h) file to be reused
*/
void printArray(int *array){
    for(int i=0; i<SIZE; i++){
        printf("%i ", array[i]);
    }
    printf("\n");
}

/**
 *  Find and return the value of higest element in the array
 */
int uHigest(int *array, int size){
    int higher = -1;
    for(int i=0; i<size; i++){
        higher = (array[i] > higher)? array[i]: higher;
    }
    return higher;
}

/**
 *  Find and return the value of lowest element in the array
 */
int uLowest(int *array, int size){
    int lower = INT_MAX;
    for(int i=0; i<size; i++){
        lower = (array[i] < lower)? array[i]: lower;
    }
    return lower;
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
void order(int *array, int size, bool ascendent){
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

int main()
{
    int notes[SIZE];
    randomInit(notes);
    int higestValue = uHigest(notes, SIZE);
    int lowestValue = uLowest(notes, SIZE);

    printf("Unordered notes: \n");
    printArray(notes);
    printf("The highest value in the notes are: %i.\n", higestValue);
    printf("The lowest value in the notes are: %i.\n", lowestValue);
    printf("The range of this set is: %i.\n\n", higestValue - lowestValue);
    
    order(notes, SIZE, true);
    printf("Ordered notes: \n");
    printArray(notes);
    printf("The highest value in the notes are: %i.\n", oHigest(notes, SIZE));
    printf("The lowest value in the notes are: %i.\n", oLowest(notes, SIZE));
    printf("The range of this set is: %i.\n\n", oRange(notes, SIZE));
    return 0;
}
