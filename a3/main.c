#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {
   const char* filename;
   struct hashMap htable;
   struct hashLink *temp;
   char* temp_key;
   char* temp_word;
   int tablesize = 1000;
   FILE* fileptr;
   int* currentCount;
   int i;

   /* if the number of command line args is 1, take from input.txt. If its two, take the provided text file */

   if (argc == 2) {
       filename = argv[1];
   }
   else {
       filename = "input.txt";
   }

   initMap(&htable, tablesize);
   
   fileptr = fopen(filename, "r");
   assert(fileptr);

    /* run through the file and check if the key already exists. If it does, add one to the count. If it doesnt, call insertMap */

    temp_key = getWord(fileptr);

    while (temp_key) {
        currentCount = atMap(&htable, temp_key);
        if (currentCount) {
            (*currentCount)++;
        }
        else {
            insertMap(&htable, temp_key, 1);
        }
        temp_word = temp_key;
        temp_key = getWord(fileptr);
        free(temp_word);
    }

    /* close the file */

   fclose(fileptr);

   /* print the words and their number of occurences */
    printf("Word: Number of occurences\n");
   for (i = 0; i < htable.tableSize; i++) {
       temp = htable.table[i];

       while (temp != 0) {
           printf("%s: %d\n", temp->key, temp->value);
           temp = temp->next;
       }
   }

   freeMap(&htable);

   return 0;
} 

char* getWord(FILE *file) {
    int length = 0;
    int maxLength = 16;
    char character;

    char* word = (char*)malloc(sizeof(char) * maxLength);
    assert(word != NULL); 

    while ((character = fgetc(file)) != EOF) {
        if ((length + 1) > maxLength) {
            maxLength *= 2;
            word = (char*)realloc(word, maxLength);
        }
        /* checks if the current letter is an uppercase letter, lowercase letter, or a number. What defines a character is up in the instructions */
        if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z') || (character >= '0' && character <= '9') || (character == 39)) {
            word[length] = character;
            length++;
        }
        else if (length > 0) {
            break;
        }
    }

    if (length == 0) {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}
