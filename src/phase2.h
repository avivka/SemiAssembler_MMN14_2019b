/* Includes				*/

#include	"utils/FileReader.h"
#include	"utils/FileWriter.h"
#include	"utils/TextUtils.h"
#include	"utils/Error.h"
#include 	"utils/List.h"
#include	"modules/DataSegment.h"
#include	"modules/CodeSegement.h"

/* Defines				*/

#ifndef 	ASSEMBLER_PHASE2_H
#define 	ASSEMBLER_PHASE2_H

/* Extern Data Members	*/

extern int currentLine;

/* Function Declaration	*/

void		doPhase2			(char*);
void 		handleNextLine		(char*);
void 		createEnteriesFile	(char*);
void 		createExternalsFile	(char*);
void 		createObjectFile	(char*, int, int);
#endif
