/* Arthur Quintanilla
 * Intern_Project - Counter
 *
 *
 *
 *
 *
 */

#include "counter.h"


Counter CreateCounter(unsigned int sec, unsigned int min, unsigned int hour)
{
	//checks if valid input
	if(sec > 59 || min > 59 || hour > 23 ) 
	{
		printf("Invalid initialization values for counter.\n");
		if(sec > 59) printf("Seconds must be between 0 and 59. Given: %d\n", (int) sec);
		if(min > 59) printf("Minutes must be between 0 and 59. Given: %d\n", (int) min);
		if(hour > 23) printf("Hours must be between 0 and 23. Given: %d\n", (int) hour);
		return NULL;
	}

	//allocate space for counter and its fields
	Counter ct = (Counter) malloc(sizeof(struct Counter_));
	ct->sec = malloc(sizeof(unsigned int));
	ct->min = malloc(sizeof(unsigned int));
	ct->hour = malloc(sizeof(unsigned int));
	
	//checks if malloc failed
	if(ct DOES_NOT_EXIST || ct->sec DOES_NOT_EXIST || ct->min DOES_NOT_EXIST || ct->hour DOES_NOT_EXIST)
	{
		if(ct->sec EXISTS) free(ct->sec);
		if(ct->min EXISTS) free(ct->min);
		if(ct->hour EXISTS) free(ct->hour);
		if(ct EXISTS) free(ct);
		printf("Failed to allocate memory for Counter\n");
		return NULL;
	}

	//user input is valid and memory successfully allocated
	ct->code = CODE;
	*((unsigned int *) ct->sec) = sec;
	*((unsigned int *) ct->min) = min;
	*((unsigned int *) ct->hour) = hour; 
	return ct;
}


void DestroyCounter(Counter ct)
{
	//if an invalid pointer was given then there is nothing to destroy
	if(ct DOES_NOT_EXIST || COUNTER_PTR_INVALID)
		printf("Invalid Counter passed to DestroyCounter\n");
	else
	{
		//destroys Counter_ struct and all associated data
		free(ct->sec);
		free(ct->min);
		free(ct->hour);
		free(ct);
	}
}


int IncrementSec(Counter ct)
{
	//If the given Counter is invalid print error message and return 0
	if(CounterInvalid(ct))
	{
		printf("Error in IncrementSec:\n");
		PrintError(ct);
		return 0;
	}
	//else perform incrementation to sec field
	if(*((unsigned int *) ct->sec) == 59)
	{
		*((unsigned int *) ct->sec) = 0;
		//increment min field on overflow of sec field
		return IncrementMin(ct);
	}
	(*((unsigned int *) ct->sec))++;
	//return 1 if successful
	return 1;
}
int IncrementMin(Counter ct)
{
	//If the given Counter is invalid print error message and return 0
	if(CounterInvalid(ct))
	{
		printf("Error in IncrementMin:\n");
		PrintError(ct);
		return 0;
	}
	//else perform incrementation to min field
	if(*((unsigned int *) ct->min) == 59)
	{
		*((unsigned int *) ct->min) = 0;
		//increment hour field on overflow of min field
		return IncrementHour(ct);
	}
	(*((unsigned int *) ct->min))++;
	//return 1 if successful
	return 1;
}

int IncrementHour(Counter ct)
{
	//If the given counter is invalid print error message and return 0
	if(CounterInvalid(ct))
	{
		printf("Error in IncrementHour:\n");
		PrintError(ct);
		return 0;
	}
	//else perform incrementation to hour field
	if(*((unsigned int *) ct->hour) == 23)
		*((unsigned int *) ct->hour) = 0;
	else
		(*((unsigned int *) ct->hour))++;
	//return 1 if successful
	return 1;
}

int DecrementSec(Counter ct)
{
	//If the given counter is invalid print error message and return 0
	if(CounterInvalid(ct))
	{
		printf("Error in DecrementSec:\n");
		PrintError(ct);
		return 0;
	}
	//else perform decrementation to second field
	if(*((unsigned int *) ct->sec) == 0)
	{
		*((unsigned int *) ct->sec) = 59;
		//decrement min field on underflow of sec field
		return DecrementMin(ct);
	}
	(*((unsigned int *) ct->sec))--;
	//return 1 if successful
	return 1;
}

int DecrementMin(Counter ct)
{
	//If the given counter is invalid print error message and return 0
	if(CounterInvalid(ct))
	{
		printf("Error in DecrementMin:\n");
		PrintError(ct);
		return 0;
	}
	//else perform derementation to min field
	if(*((unsigned int *) ct->min) == 0)
	{
		*((unsigned int *) ct->min) = 59;
		//decrement hour field on underflow of min field
		return DecrementHour(ct);
	}
	(*((unsigned int *) ct->min))--;
	//return 1 if successful
	return 1;
}

int DecrementHour(Counter ct)
{
	//If the given counter is invalid print error message and return 0
	if(CounterInvalid(ct))
	{
		printf("Error in DecrementHour:\n");
		PrintError(ct);
		return 0;
	}
	//else perform decrementation of hour field
	if(*((unsigned int *) ct->hour) == 0)
		*((unsigned int *) ct->hour) = 23;
	else
		(*((unsigned int *) ct->hour))--;
	//return 1 if successful
	return 1;
}

int DisplayMilitaryTime(Counter ct)
{
	//If the given counter is invalid print error message and return 0
	if(CounterInvalid(ct))
	{
		printf("Error in DisplayMilitaryTime:\n");
		PrintError(ct);
		return 0;
	}
	//Display counter in military time and return 1
	printf("Counter (Military Time): %02u:%02u:%02u\n", *((unsigned int *) ct->hour), *((unsigned int *) ct->min), *((unsigned int *) ct->sec));
	return 1;
}

int DisplayStandardTime(Counter ct)
{
	//If the given counter is invalid print error message and return 0
	if(CounterInvalid(ct))
	{
		printf("Error in DisplayStandardTime:\n");
		PrintError(ct);
		return 0;
	}
	//Display counter in standard time and return 1
	unsigned int hour = (*((unsigned int *) ct->hour)) % 12;
	printf("Counter (Standard Time): %02u:%02u:%02u", hour == 0 ? 12 : hour, *((unsigned int *) ct->min), *((unsigned int *) ct->sec));
	printf(*((unsigned int *) ct->hour) >= 12 ? "pm\n" : "am\n");
	return 1;
}

int CounterInvalid(Counter ct)
{
	//Re-initialize each element in static int err[4] to 0
	int i = 0;
	for(i; i < 4; i++)
		err[i] = 0;

	//If the Counter ct pointer is invalid set first flag to 0 and jump to return
	if(ct DOES_NOT_EXIST || COUNTER_PTR_INVALID)
		err[0] = 1;
	else
	{
		//else check each field in the Counter_ struct for errors and set flags appropriately
		if(*((unsigned int *) ct->sec) > 59)
			err[1] = 1;
		if(*((unsigned int *) ct->min) > 59)
			err[2] = 1;
		if(*((unsigned int *) ct->hour) > 23)
			err[3] = 1;
	}
	//If any flag was set to 1, return 1 to signal errors found. Otherwise, if all flags remained 0, return 0 to signal no errors
	return err[0] || err[1] || err[2] || err[3];
}

void PrintError(Counter ct)
{
	//Print an error message for each flag set to 1 in static int err[4] or print "No error." if all flags are 0.
	if(err[0])
		printf("\tInvalid counter pointer.\n");
	if(err[1])
		printf("\tGiven counter has invalid value in sec field: %d\n", *((unsigned int *) ct->sec));
	if(err[2])
		printf("\tGiven counter has invalid value in min field: %d\n", *((unsigned int *) ct->min));
	if(err[3])
		printf("\tGiven counter has invalid value in hour field: %d\n", *((unsigned int *) ct->hour));
	if(!(err[0] || err[1] || err[2] || err[3]))
		printf("No error.\n");
}