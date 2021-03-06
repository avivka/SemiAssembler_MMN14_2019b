/* Includes 	*/

#include 	<stdio.h>
#include    "../utils/UtilsBMC.h"
#include    "FromBitToSign.h"
#include    "Analyzer.h"
#include    "Opearnds.h"

/* Prototypes 	*/

int			from_line_to_bmc	(commandLine*, int, char*);				/* The main function of creation binary machine code */
short int	create_basic_bmc	(commandLine*, int*, char*);					/* Creates the first binary machine code from operation */
short int 	from_src_des_opr	(commandLine*, boolean, int*, char*);	/* Use to check if the operand is SRC to DES and by the case call the right function */
short int 	opr_immediate		(char*, int*, char*);			/* In case of Immediate operand create the binary machine code for it */
short int 	opr_direct			(char*, boolean, int*, char*);	/* Creates binary machine code by label, internal or external */
short int 	opr_index			(char*, int*, char*);			/* In case of index operand create the binary machine code for it and for the label */
short int	src_des_storage		(commandLine*, int*, char*);					/* In case the operand is storage type */

