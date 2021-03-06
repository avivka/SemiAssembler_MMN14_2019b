#include "FromBitToSign.h"

extern int decimalAddress;

/** Do binary movements and send 00 or 01 or 10 or 11 to the "to_4_base" function. Returns 0 if all good else returns -1.*/

int 	from_binary_machine_code_to_fourth_base 	(int short binaryCode, int* decimalAddressCounter, char* filename)
{
	int 	counter 						= 0;
	char 	number 							= '\0';
	char	bmcsign[NUM_OF_ACTIVE_BITS/2]	= "";
	char*	filenamewithextention			= "";
	FILE	*pf								= NULL;
	
	if (binaryCode == -1)
	{
		return -1;
	}
	
	filenamewithextention = concat(filename, ".ob");
	
	if (open_or_create_file(&pf, filenamewithextention) == -1)
	{
		return -1;
	}
	
	if (*decimalAddressCounter < maxNumDecimalAddress)
	{
		fputc('0', pf);																					/** puts 0 before the IC number if it is less then 1000*/
	}
	
	fprintf(pf, "%d", *decimalAddressCounter);
	
	(*decimalAddressCounter)++;

	fputc('\t', pf);
	
	while (counter < (NUM_OF_ACTIVE_BITS / 2))
	{
		
		if (binaryCode % 2 == 1)
		{

			if (number == '\0')
			{
				number = '1';
			}
			
			else
			{
							
				bmcsign[counter] = to_4_base(number, '1');
				
				if (bmcsign[counter] == '0')
				{
					fclose(pf);
					return -1;
				}
				
				number = '\0';
				
				counter++;
			}
		}
		
		else
		{		
			if (number == '\0')
			{
				number = '0';
			}
			
			else
			{
					
				bmcsign[counter] = to_4_base(number, '0');
				
				if (bmcsign[counter] == '0')
				{
					fclose(pf);
					return -1;
				}
				
				number = '\0';

				
				counter++;
			}
		}
		
		binaryCode>>= 1;
	}


	printSignToFile(bmcsign, pf);
	
	fputc('\n', pf);

	fclose(pf);
	
	free(filenamewithextention);
	
	return 0;
}

/** Returns * or # or % or ! to the array. Returns 0 if all good.*/

char	to_4_base									(char firstBit, char secondBit)
{	
	secondBit 	= (secondBit - char_to_ascii) * 2;
	firstBit	= (firstBit - char_to_ascii);

		
	switch(secondBit + firstBit)
	{
		case 0:
				/* return * to the array*/
				return '*';
			
		case 1:
				/* return # to the array*/
				return '#';
		
		case 2:
				/* return % to the array*/
				return '%';
				
		case 3:
				/* return ! to the array*/
				return '!';
		
		default:
				/* write error*/
				ERROR_PROGRAM(("There is a problem with the translation to 4 base \n"));
				return '0';
	}

}

/** Prints the array in the opposite way to the file. Returns 0 if all good, else returns -1.*/

int		printSignToFile								(char *bmcsign, FILE* fp)
{
	int i;
	
	for (i = ((NUM_OF_ACTIVE_BITS / 2) - 1) ; i >= 0 ; i--)
	{
		if(bmcsign[i] != '0')
		{
			
			fputc(bmcsign[i], fp);
		}
		
		else
		{
			return -1;
		}
	}
	
	return 0;
}
