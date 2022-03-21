/* CS261- HW1 - Program4.c*/
/* Name: Kevin Pfeil
 * Date: 1/13/2020
 * Solution Description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student{
    char initials[2];
    int score;
};

void swap(struct student *xp, struct student *yp) { 
    struct student temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void sort(struct student* students, int n) {
    int i, j, min_idx; 
    /*standard selection sort algorithm*/
    for (i = 0; i < n-1; i++) { 
        min_idx = i; 
        for (j = i+1; j < n; j++) {
            if (students[j].initials[0] < students[min_idx].initials[0]) {
                min_idx = j;
            }
        }
  
        swap(&students[min_idx], &students[i]); 
    }
    /*this loop is for checking the second initials*/
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (students[i].initials[0] == students[j].initials[0]) {
                if (students[i].initials[1] < students[j].initials[1]) {
                    swap(&students[i], &students[j]);
                }
            }
        }
    }
}

int main() {
    int n, i;
    srand(time(NULL));

    printf("Enter the number of random students you would like to generate:\n");
    scanf("%d", &n);
    /*checking case if theres no students to sort*/
    if (n <= 0) {
        printf("There are no students to sort! The program will end.\n");
        return 0;
    }

    struct student *students;
    students = malloc(n * sizeof(struct student));

    for (i = 0; i < n; i++) {
        students[i].score = rand() % 100;
        char c1 = rand() % 26 + 'A';
        char c2 = rand() % 26 + 'A';
        students[i].initials[0] = c1;
        students[i].initials[1] = c2;
    }

    printf("The array of students before sorting:\n");
    for (i = 0; i < n; i++) {
        printf("%d. %c%c %d\n", (i + 1), students[i].initials[0], students[i].initials[1], students[i].score);
    }

    sort(students, n);

    printf("The array of students after sorting:\n");
    for (i = 0; i < n; i++) {
        printf("%d. %c%c %d\n", (i + 1), students[i].initials[0], students[i].initials[1], students[i].score);
    }

    free(students);
    
    return 0;
}