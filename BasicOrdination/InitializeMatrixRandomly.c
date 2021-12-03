/******************************************************************************

  This code show how initialize an unidimensional array with random values.
  Created by: isokmio@gmail.com
  Created at: 29/11/2021

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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
}

/**
 *  Find and return the value of higest element in the array
 */
int higest(int *array, int size){
    int higher = -1;
    for(int i=0; i<size; i++){
        higher = (array[i] > higher)? array[i]: higher;
    }
    return higher;
}

/**
 *  Find and return the value of lowest element in the array
 */
int lowest(int *array, int size){
    int lower = INT_MAX;
    for(int i=0; i<size; i++){
        lower = (array[i] < lower)? array[i]: lower;
    }
    return lower;
}

int main()
{
    int notes[SIZE];
    randomInit(notes);
    printArray(notes);
    int higestValue = higest(notes, SIZE);
    int lowestValue = lowest(notes, SIZE);

    printf("The highest value in the notes are: %i.", higestValue);
    printf("The lowest value in the notes are: %i.", lowestValue);
    printf("The range of this set is: %i", higestValue - lowestValue);
    return 0;
}
