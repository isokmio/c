/******************************************************************************

  This code show how initialize an unidimensional array with random values.
  Created by: isokmio@gmail.com
  Created at: 29/11/2021

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
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

int main()
{
    int array[SIZE];
    randomInit(array);
    printArray(array);
    return 0;
}
