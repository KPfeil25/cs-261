/* CS261- HW1 - Program3.c*/
/* Name: Kevin Pfeil
 * Date: 1/13/2020
 * Solution Description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int* numbers, int n) { 
    int i, key, j;  

    for (i = 1; i < n; i++) {  
        key = numbers[i];  
        j = i - 1;  

        while (j >= 0 && numbers[j] > key) {  
            numbers[j + 1] = numbers[j];  
            j = j - 1;  
        }  
        numbers[j + 1] = key;  
    } 
}

int main() {

    int n;

    printf("Enter the number of random integrs you would like:\n");
    scanf("%d", &n);

    if (n == 0) {
        printf("Cannot sort an array of zero numbers, program will end.");
        return 0;
    }

    int *numbers;
    numbers = malloc(n * sizeof(int));

    int i, j;
    for (i = 0; i < n; i++) {
        numbers[i] = rand() % 100;
    }
    printf("Unsorted array of random numbers:\n");
    for (j = 0; j < n; j++) {
        printf("%d\n", numbers[j]);
    }

    sort(numbers, n);
    printf("Sorted array of random numbers:\n");
    for (j = 0; j < n; j++) {
        printf("%d\n", numbers[j]);
    }
    
    free(numbers);

    return 0;
}