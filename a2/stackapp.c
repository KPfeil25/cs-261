/*	stackapp.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether any occurrence of (, {, or [ are balanced 
   with the corresponding ), }, or ] respecting the LIFO principle
	arguments: s pointer to an input string 	
	pre-condition: s is not null	
	post: return 1 for balanced s or 0 for unbalanced s
*/
int isBalanced(char* s)
{
	/*Use the following variables, do not change their names*/
	char ch;  /*stores the current character from the input string*/
	char ts;  /*stores the top element of the stack*/
	int b=1;  /*Boolean variable b=1 means balanced; b=0 means unbalanced string*/

	DynArr *stack;
	stack=newDynArr(100);/* initialize the stack with capacity = 100 */


	if (s && strlen(s))
		while(1) /*infinite loop that has to be stopped explicitly*/
		{
			ch = nextChar(s); /*get the next character in the string*/
			
                        /*stop the while loop when we reach the end of the string*/
			if(ch==0 || ch=='\0') break;

			if (ch == '(' || ch == '{' || ch == '[') {
				/* adding only the opening expressions to the stack */
				pushDynArr(stack, ch);
			}
			else if (ch == ')' || ch == '}' || ch == ']') {
				if (sizeDynArr(stack) == 0) {
					/* if this loop is entered, that means that the expression is trying to be closed
					before it is opened, so we set b = 0 and break */
					b = 0;
					break;
				}
			}
			if (sizeDynArr(stack) != 0) {
				/* only call topDynArr if the stack is not empty */
				ts = topDynArr(stack);
			}

			if (((ch == ')') && (ts == '(')) || ((ch == '}') && (ts == '{')) || ((ch == ']') && (ts == '['))) {
				/* if the current char matches the respective opening expression on the top of
				the stack, then remove them from the stack. They are balanced. */
				popDynArr(stack);
			}
		}
		
		if (!isEmptyDynArr(stack)) {
			/* one final check just in case the stack is not empty. If it is not empty this means that
			the pairs had not matched and thus it is not balanced */
			b = 0;
		}

		/* de-allocate memory made for the stack */
		freeDynArr(stack);

		return b;
		
    /* Free the memory allocated to the stack, and return b=1 or b=0 */
}

int main(int argc, char* argv[]){

	char* s=argv[1];	
	
	/*char s[]="()+x+r*{{{((--{{[()[]]}}))}}}";*/
	

	int res;

	printf("Assignment 2\n");
	
	if(argc==2)
	{
		res = isBalanced(s);
		
		if (res) {
			printf("The string %s is balanced\n",s);
		}
		else {
			printf("The string %s is not balanced\n",s);
		}
	}
	else
		printf("Please enter a string to be evaluated.\n");

	
	return 0;	
}

