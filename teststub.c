/* Arthur Quintanilla
 * Intern_Project - Counter
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "counter.h"

unsigned int ValidateInput(char * input)
{
	//if the user entered blank input for an argument
	if(*input == 0)
	{
		printf("Empty argument given.\n");
		exit(EXIT_FAILURE);
	}
	char ** end = malloc(1);
	//if space was uanble to be allocated for **end
	if(end == NULL) 
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	errno = 0;
	unsigned int a = (unsigned int) strtol(input, end, 10);
	//determine if errno was set by strtol
	if(errno)
	{
		perror("Error during input validtion");
		free(end);
		exit(EXIT_FAILURE);
	}
	//print any found invalid input
	if(**end != '\0')
	{
		printf("Invalid input: %s\n", *end);
		free(end);
		exit(EXIT_FAILURE);
	}
	//free pointer and return the retrieved validated input
	free(end);
	return a;
}

int main(int argc, char ** argv)
{
	//ensure the user entered 3 arguments
	if(argc != 4)
	{
		printf("Invalid number of arguments given. Requires 3: sec, min, hour.\n");
		exit(EXIT_FAILURE);
	}

	//validate all user input
	unsigned int sec = ValidateInput(argv[1]);
	unsigned int min = ValidateInput(argv[2]);
	unsigned int hour = ValidateInput(argv[3]);

	//create a counter pointer for testing
	Counter test = CreateCounter(sec, min, hour);
	if(test == NULL)
	{
		printf("Failed to initialize test counter.\n");
		exit(EXIT_FAILURE);
	}

	//This code segment will make predefined adjustments to the counter "test" that was initialized
	//using user input
	printf("\n\n============TESTING USER INPUT============\n\n");

	printf("Initial test counter values.\n");
	DisplayStandardTime(test);
	DisplayMilitaryTime(test);

	printf("\nTesting IncrementSec. Incrementing second 21600 times (6 hours).\n");
	int i = 0;
	for(i; i < 21600; i++)
		IncrementSec(test);
	printf("Current test counter:\n");
	DisplayStandardTime(test);
	DisplayMilitaryTime(test);

	printf("\nTesting IncrementMin. Incrementing minute 360 times (6 hours).\n");
	for(i = 0; i < 360; i++)
		IncrementMin(test);
	printf("Current test counter:\n");
	DisplayStandardTime(test);
	DisplayMilitaryTime(test);

	printf("\nTesting IncrementHour. Incrementing hour 9 times.\n");
	for(i = 0; i < 9; i++)
		IncrementHour(test);
	printf("Current test counter:\n");
	DisplayStandardTime(test);
	DisplayMilitaryTime(test);

	printf("\nTesting DecrementSec. Decrementing second 21600 times (6 hours).\n");
	for(i = 0; i < 21600; i++)
		DecrementSec(test);
	printf("Current test counter:\n");
	DisplayStandardTime(test);
	DisplayMilitaryTime(test);

	printf("\nTesting DecrementMin. Decrementing 360 minutes (6 hours).\n");
	for(i = 0; i < 360; i++)
		DecrementMin(test);
	DisplayStandardTime(test);
	DisplayMilitaryTime(test);

	printf("\nTesting DecrementHour. Decrementing 9 hours.\n");
	for(i = 0; i < 9; i++)
		DecrementHour(test);
	DisplayStandardTime(test);
	DisplayMilitaryTime(test);


	//This code segment will test errors that will be returned by the Counter library when
	//give bad data
	printf("\n\n============ERROR TESTING============\n\n");

	//tests error when invalid data given to CreateCounter
	Counter initerror = CreateCounter(-1, 30, 900);
	printf("\n");
	char * ptr = NULL;

	//rest of this code segment adjusts the fields of the Counter_ struct directly
	//and displays resulting errors
	*((unsigned int *) test->sec) = 500;
	*((unsigned int *) test->min) = 900;


	DisplayMilitaryTime(test);
	DisplayStandardTime(test);

	*((unsigned int *) test->min) = 30;
	*((unsigned int *) test->hour) = 10000;

	IncrementSec(test);
	IncrementMin(test);

	*((unsigned int *) test->hour) = 12;	
	DisplayMilitaryTime(test);

	ptr = ((char *) test) + 1;
	DisplayMilitaryTime((Counter) ptr);
	DestroyCounter((Counter) ptr);


	//this code segment will use a new Counter "rollover" to test the counter data structure's
	//functionality at rollover times
	printf("\n\n============DEMONSTRATING ROLLOVER TIMES============\n\n");
	
	//test and display rollover results from 23:59:59 to 00:00:01
	Counter rollover = CreateCounter(59, 59, 23);
	if(rollover == NULL)
	{
		printf("Failed to initialize rollover counter.\n");
		exit(EXIT_FAILURE);
	}
	for(i = 0; i < 3; i++)
	{
		DisplayMilitaryTime(rollover);
		DisplayStandardTime(rollover);
		IncrementSec(rollover);		
	}
	DestroyCounter(rollover);
	
	//test and display rollover results from 11:59:59 to 12:00:01
	rollover = CreateCounter(59, 59, 11);
	if(rollover == NULL)
	{
		printf("Failed to initialize rollover counter.\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\n");
	for(i = 0; i < 3; i++)
	{
		DisplayMilitaryTime(rollover);
		DisplayStandardTime(rollover);
		IncrementSec(rollover);		
	}
	DestroyCounter(rollover);
	
	//test and display rollover results from 0:59:59 to 01:00:01
	rollover = CreateCounter(59, 59, 0);
	if(rollover == NULL)
	{
		printf("Failed to initialize rollover counter.\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\n");
	for(i = 0; i < 3; i++)
	{
		DisplayMilitaryTime(rollover);
		DisplayStandardTime(rollover);
		IncrementSec(rollover);		
	}

	//frees allocated memory, prints that execution was successful, and exits
	DestroyCounter(rollover);
	DestroyCounter(test);
	printf("\nTesting Complete.\n");
	printf("Exit Success\n");
	exit(EXIT_SUCCESS);
}