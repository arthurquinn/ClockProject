/* Arthur Quintanilla
 * Intern_Project - Counter
 *
 *
 *
 *
 *
 */

#ifndef COUNTER_H
#define COUNTER_H
#include <stdlib.h>
#include <stdio.h>

/* CODE is used in the unsigned int code field of every Counter_ struct successfully returned by CreateCounter.
 * 		Its purpose is to validate when a user passes a Counter pointer to any of the following functions, that the
 *		pointer passed is valid.
 *
 * EXISTS is used to determine if a pointer exists.
 *
 * DOES_NOT_EXIST is used to determine if an address does not exist.
 *
 * COUNTER_PTR_INVALID is used to determine whether the current pointer points to a valid Counter pointer.
 */
#define CODE 83123412
#define EXISTS != NULL
#define DOES_NOT_EXIST == NULL
#define COUNTER_PTR_INVALID *((unsigned int *) ct) != CODE


/* Counter is defined as a pointer to a Counter_ struct.
 * 
 * Counter_ struct is used to hold information about a counter's current sec, min, and hour.
 *		The code field is used to determine whether a pointer points to a valid Counter_ struct.
 * 		The sec, min, and hour are stored as void pointers to keep the data opaque and discourage user
 *		from accessing these fields directly. When successful, they will always point to data that is 
 *		to be interpreted as an unsigned int type.
 *
 * Notes: Counter_ structs store their hour fields always in military time. However, when the user desires standard
 *		time output, hour will be interpreted as its stanard, rather than military, value.
 */
typedef struct Counter_ * Counter;
struct Counter_
{
	unsigned int code;
	void * sec;
	void * min;
	void * hour;
};

/* static int err[4] is an array used to signal errors found in a Counter_ struct give to the function CounterInvalid
 * 
 * Each position in the array represents an error found and will have its value switched to one when detected
 *		err[0]: This field represents an invalid Counter pointer. An invalid Counter pointer is defined as a NULL pointer or a pointer
 *				that does not point to a valid Counter_ struct
 *		err[1]: This field represents an invalid sec field detected in the Counter_ struct
 *		err[2]: This field represents an invalid min field detected in the Counter_ struct
 *		err[3]: This field represents an invalid hour field detected in the Counter_ struct
 */
static int err[4] = {0, 0, 0, 0};



/* Description: The CreateCounter function creates a pointer to a Counter_ struct given 3 unsigned int arguments sec, min, and hour.
 * 		First, it validates that sec, min, and hour are between (including) 0 and their maximum values 59, 59, and 23 respectively.
 *		Since these values are unsigned, negative values will also be greater than these maximum values.
 *		A pointer to a Counter struct is created and return if the function is successful.
 *
 * Return Value: If CreateCounter received invalid input, or was unable to allocate memory for the Counter_ struct or any of its fields
 *		a corresponding error message is printed and NULL is returned.
 *		On successful creation of the Counter_ struct, a valid pointer to this struct is returned.
 * 
 * Notes: CreateCounter accepts unsigned ints but when these values are stored within the newly created CounterStruct they are stored as 
 *		opaque void * types to discourage the users ability to access these fields directly, as this is not the desired implementation
 */
Counter CreateCounter(unsigned int sec, unsigned int min, unsigned int hour);

/* Description: Destroys all allocated memory associated with the Counter_ struct pointed to by argument Counter ct
 *		First, the three void * sec, void * min, and void * hour fields are freed, then the space allocated for the
 *		Counter_ struct itself is freed.
 *
 * Return Value: None, displays message if invalid pointer was given
 */
void DestroyCounter(Counter ct);


/* Description: Increments the unsigned int sec field of the Counter_ struct pointed to by Counter ct. If the sec field is 59,
 *		this function will call IncrementMin to advance the minute and roll sec back down to 0.
 *
 * Return Value: If an invalid Counter ct pointer was given to IncrementSec, 0 is returned. If a invalid sec field was detected
 *		in the Counter_ struct, an error message is displayed and returns 0. Otherwise, on successful incrementation, 
 *		1 is returned.
 */
int IncrementSec(Counter ct);


/* Description: Increments the unsigned int min field of the Counter_ struct pointed to by Counter ct. If the min field is 59,
 *		this function will call IncrementHour to advance the hour and roll min back down to 0.
 *
 * Return Value: If an invalid Counter ct pointer was given to IncrementMin, 0 is returned. If a invalid min field was detected
 *		in the Counter_ struct, an error message is displayed and returns 0. Otherwise, on successful incrementation, 
 *		1 is returned.
 */
int IncrementMin(Counter ct);


/* Description: Increments the unsigned int hour field of the Counter_ struct pointed to by Counter ct. If the hour field is 23,
 *		this function will simply roll hour back down to 0, as there is no field to keep track of days, the counter will effectively
 *		"reset".
 *
 * Return Value: If an invalid Counter ct pointer was given to IncrementHour, 0 is returned. If a invalid hour field was detected
 *		in the Counter_ struct, an error message is displayed and returns 0. Otherwise, on successful incrementation, 
 *		1 is returned.
 */
int IncrementHour(Counter ct);


/* Description: Decrements the unsigned int sec field of the Counter_ struct pointed to by Counter ct. If the sec field is 0,
 *		this function will call DecrementMin to decrease the min and roll sec back up to 59.
 *
 * Return Value: If an invalid Counter ct pointer was given to DecrementSec, 0 is returned. If an invalid sec field was detected
 *		in the Counter_ struct, an error message is displayed and returns 0. Otherwise, on successful decrementation, 
 *		1 is returned.
 */
int DecrementSec(Counter ct);


/* Description: Decrements the unsigned int min field of the Counter_ struct pointed to by Counter ct. If the min field is 0,
 *		this function will call DecrementHour to decrease the hour and roll min back up to 59.
 *
 * Return Value: If an invalid Counter ct pointer was given to DecrementMin, 0 is returned. If an invalid min field was detected
 *		in the Counter_ struct, an error message is displayed and returns 0. Otherwise, on successful decrementation, 
 *		1 is returned.
 */
int DecrementMin(Counter ct);


/* Description: Decrements the unsigned int hour field of the Counter_ struct pointed to by Counter ct. If the hour field is 0,
 *		this function will simply roll hour back up to 23, as there is no field to keep track of days, the counter will effectively
 *		"reset".
 *
 * Return Value: If an invalid Counter ct pointer was given to DecrementHour, 0 is returned. If an invalid hour field was detected
 *		in the Counter_ struct, an error message is displayed and returns 0. Otherwise, on successful decrementation, 
 *		1 is returned.
 */
int DecrementHour(Counter ct);

/* Description: Displays the current value of the Counter_ struct pointed to by argument Counter ct in standard time.
 *		Output is in the format: "Counter (Standard Time): %02u:%02u:%02u(am or pm)". From left to right, the fields are interpreted 
 *		as hour:min:sec(am or pm). If the current value of hour within the Counter_ struct is between (inclusively) 12 and 23, the 
 *		time of day is said to be pm. If this current value is between (inclusively) 0 and 11, the time of day is said to be am.
 *		Also, when the hour value is 0 (12:xx:xxam) a 12 will be displayed rather than 0 to demonstrate it is 12:xx:xxam rather than
 * 		the military value 0.
 *
 * Return Value: If an invalid pointer is given to this function, 0 will be returned and nothing will be printed, otherwise, on successful
 *		print, 1 is returned.
 */
int DisplayStandardTime(Counter ct);


/* Description: Displays the current value of the Counter_ struct pointed to by argument Counter ct in military time.
 *		Output is in the format: "Counter (Military Time): %02u:%02u:%02u".From left to right, the fields are interpreted as
 *		hour:min:sec. 
 *
 * Return Value: If an invalid pointer is given to this funtion, 0 will be returned and nothing will be printed, otherwise, on successful
 *		print, 1 is returned.
 */
int DisplayMilitaryTime(Counter ct);

/* Description: CounterInvalid determines whether or not Counter ct is a valid pointer to a Counter_ struct and (if it is) will determine
 * 		whether the data stored within is valid as well.
 *		This function will first initialize the static int err[4] array to contain all 0's (to erase previous errors found for other Counter pointers)
 *		When an error is detected it will set its appropriate flag in the static int err[4] array from 0 to 1. These flags can be used
 *		in other functions (such as PrintError) to print any and all errors found for a given Counter pointer.
 *
 * Return Value: If any of the flags in err[4] are set to 1, returns 1 to signal that the counter is invalid. If all of the flags within err[4]
 *		are 0, then 0 is returned to signal the counter is not invalid.
 */
int CounterInvalid(Counter ct);


/* Description: PrintError displays a message for all errors currently flagged by static int err[4]. Refer above to desription of err[4] to
 * 		see what each flag within err represents. If all flags in err are 0, the message "No Error." is printed.
 *
 * Notes: PrintError does NOT detect errors. It is simply a function to print errors already flagged by static int err[4]. In order to detect
 *		errors in a counter the function CounterInvalid must be used. Ideally PrintError will be used immediately following a non-zero return value 
 *		from CounterInvalid to display immediately the errors found for that particular struct, if printing the error messages is necessary.

 */ 
void PrintError(Counter ct);

#endif