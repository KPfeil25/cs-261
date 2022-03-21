/* CS261- HW1 - Program2.c*/
/* Name: Kevin Pfeil
 * Date: 1/13/2020
 * Solution Description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
    char initials[2];
    int score;
};

struct student* allocate() {

    struct student *students;
    students = malloc(10 * sizeof(struct student));
    return students;
}

void generate(struct student* students) {
   srand(time(NULL));
   int i;

   for (i = 0; i < 10; i++) {
        students[i].score = rand() % 100;
        char c1 = rand() % 26 + 'A';
        char c2 = rand() % 26 + 'A';
        students[i].initials[0] = c1;
        students[i].initials[1] = c2;
   }
   return;
}

void output(struct student* students) {
   int i;
   for (i = 0; i < 10; i++) {
       printf("%d. %c%c %d\n", (i + 1), students[i].initials[0], students[i].initials[1], students[i].score);
   }
   return;
}

void summary(struct student* students) {
    int i, j, k = 0;
    int sum, min, max = 0;

    for (i = 0; i < 10; i++) {
        sum += students[i].score;
    }
    
    min = students[0].score;

    for (j = 0; j < 10; j++) {
        if (students[j].score < min) {
            min = students[j].score;
        }
    }

    max = students[0].score;

    for (k = 0; k < 10; k++) {
        if (students[k].score > max) {
            max = students[k].score;
        }
    }

    int average = (sum / 10);
    printf("Max score: %d\nMin score: %d\nAverage: %d\n", max, min, average);
    
    return;
}

void deallocate(struct student* stud) {
    /* deallocate all memory from stud
    */
   free(stud);

   return;
}

int main() {
    struct student* stud = NULL;
    stud = allocate();
    generate(stud);
    output(stud);
    summary(stud);
    deallocate(stud);
    return 0;
}
