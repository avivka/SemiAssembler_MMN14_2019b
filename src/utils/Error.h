/* Includes				*/

#include 	<stdio.h>
#include 	<stdlib.h>

/* Defines				*/

#ifndef     ASSEMBLER_GENERALUTILS_H
#define 	ASSEMBLER_GENERALUTILS_H

/* Extern Data Members	*/

extern int currentLine;
extern int errorFlag;

/* Macro				*/

#define ERROR_PROGRAM(printfArgs) printf("\n Error:"); printf printfArgs; printf(" at line %d \n", currentLine); errorFlag = 1;

/* Function Declaration	*/

/**
 * Checks if the given pointer is NULL, if it nulls exits the program with suitable error message.
 * @param pointer - the pointer to check
 * @param cause - a custom cause to add to the error message
 */
void 		errorIfMallocFailed		(void*, char*);

#endif
