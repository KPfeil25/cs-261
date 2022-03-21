/* bag2set.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynArray.h"


/* Converts the input bag into a set using dynamic arrays 
	param: 	da -- pointer to a bag 	
	return value: void
        result: after exiting the function da points to a set 		
*/
void bag2set(struct DynArr *da) {
        int i, j;

        for (i = 0; i < da->size; i++) {
                for (j = i + 1; j < da->size;) {
                        if (EQ(da->data[i], da->data[j])) {
                                removeAtDynArr(da, i);
                        }
                        else {
                                j++;
                        }
                }
        }
}



/* An example how to test your bag2set() */
int main(int argc, char* argv[]){

	int i;
        struct DynArr da;  /* bag */
        
        initDynArr(&da, 100);
        da.size = 11;
        da.data[0] = 1.3;
	for (i=1;i<da.size-1;i++){
	    da.data[i] = 1.2;
	}
        da.data[da.size-1] = 1.4;

        printf("Bag:\n\n");
	for (i=0;i<da.size;i++){
          printf("%g\n", da.data[i]);
        }
        
        printf("\n\n\n");
        printf("Set:\n\n");
        bag2set(&da);
	for (i=0;i<da.size;i++){
          printf("%g \n", da.data[i]);
        }
        printf("\n");
        
        freeDynArr(da);

	return 0;	
}

