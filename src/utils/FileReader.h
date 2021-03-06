/* Includes				*/

#include 	<stdio.h>
#include 	<stdlib.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	"../constants.h"
#include 	"TextUtils.h"

/* Defines				*/

#ifndef        ASSEMBLER_FILEREADER_H
#define        ASSEMBLER_FILEREADER_H

/* Function Declaration	*/

int 		check_if_file_exists	 	(char*);
int 		open_or_create_file			(FILE**, char*);
int			deleteFile					(char*, char*);
char* 		rename_file					(char *, char*);

/**
 * Keep getting line by line until the end of file.
 * @param file pointer to file.
 * @param nextLineHandler pointer to fucnction that get the next line.
 */
void 		doWhileFileHaveLines		(FILE*, void (*nextLineHandler)(char*));

#endif
