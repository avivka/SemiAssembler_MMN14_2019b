#include 	"Analyzer.h"

STATEMENT_TYPE 	getStatementTypeOfSentence			(char* sentence)
{
	if(isStatementTypeDataStatement(sentence))
		return DATA_STATEMENT_TYPE_DATA;
	
	if(isStatementTypeDataStatementEntry(sentence))
		return  DATA_STATEMENT_TYPE_ENTRY;
	
	if(isStatementTypeDataStatementExtern(sentence))
		return  DATA_STATEMENT_TYPE_EXTERN;
	
	if(isStatementTypeDataStatementString(sentence))
		return  DATA_STATEMENT_TYPE_STRING;
	
	if(isStatementTypeDataStatementDefine(sentence))
		return  DATA_STATEMENT_TYPE_DEFINE;
	
	if(isCommandStatement(sentence))
		return COMMAND_STATEMENT;
	
	return  INVALID_STATEMENT;
}

int 			isDataStatement						(char *sentence)
{
    STATEMENT_TYPE type = getStatementTypeOfSentence(sentence);

    if(	type == DATA_STATEMENT_TYPE_DATA ||
		type == DATA_STATEMENT_TYPE_ENTRY ||
		type == DATA_STATEMENT_TYPE_EXTERN ||
		type == DATA_STATEMENT_TYPE_DEFINE ||
		type == DATA_STATEMENT_TYPE_STRING)
        {
			return  1;
		}

    return 0;
}

int 			validateLabel						(char* label)
{
    int 		i							= 0;
    
    if(strlen(label) <= 30 )
    {
        if((strlen(label) == 2 && label[0] == 'r'))
        {
            if((label[1] >= 1 && label[1] <= NUMBER_SEVEN_ASCII_CODE))
            {
                ERROR_PROGRAM(("Label cant be named as register"));

                return 0;
            }
            
            else if (isalpha(label[1]) || isdigit(label[1]))
            {
                return 1;
			}
            
            else
            {
              ERROR_PROGRAM(("Label Cannot contain signs"));
			}

            return 0;
        }
        
        else if (!((strcmp(label, "mov") == 0) || (strcmp(label, "cmp") == 0) || (strcmp(label, "add") == 0) || (strcmp(label, "sub") == 0) ||
                   (strcmp(label, "lea") == 0) || (strcmp(label, "not") == 0) || (strcmp(label, "clr") == 0) || (strcmp(label, "inc") == 0) ||
                   (strcmp(label, "dec") == 0) || (strcmp(label, "jmp") == 0) || (strcmp(label, "bne") == 0) || (strcmp(label, "red") == 0) ||
                   (strcmp(label, "prn") == 0) || (strcmp(label, "jsr") == 0) || (strcmp(label, "rts") == 0) || (strcmp(label, "stop") == 0 )))
        {
            if (!isalpha(label[0]))
            {
                ERROR_PROGRAM(("Label Cannot start with digits"));
            
                return 0;
            }
            
            for (i = 1; i < (strlen(label)); i++)
            {
                if (!(isalpha(label[i]) || isdigit(label[i])))
                {
                    ERROR_PROGRAM(("Label contains signs"));
                 
                    return 0;
                }
            }
            
            return 1;
        }
        
        else
        {
            ERROR_PROGRAM(("Label cannot be named as an instruction"));
        
            return 0;
        }
        
    }
    
    else
    {
        ERROR_PROGRAM(("Label is too long (more than 30 chars)"));
    
        return 0;
    }
}

char* 			extractLabel						(char* sentence)
{		
    const char 	ch 							= ':';
    char* 		buff						= "";
    int 		i 							= 0;
    
    buff = (char*)malloc(sizeof(char) * MAX_SIZE_OF_LABEL);

	errorIfMallocFailed(buff, "when trying to allocate memory for the label check.");
	
    if(strchr(sentence, ch))
    {
        if((sentence[0] != ' ') && (sentence[0] != '\t'))
        {
            while(sentence[i] && sentence[i] != ':')
            {
                buff[i] = sentence[i];
    
                i++;
            }

            if (sentence[i] == ':' && ((!isspace(sentence[i+1])) && sentence[i+1] != '\n'))
            {
                ERROR_PROGRAM(("label should end with : and then have ' '."));
            }

            buff[i] = '\0';
        }
        
        else
        {
            ERROR_PROGRAM(("the label contains spaces or tabs"));
            free(buff);
            return NULL;
        }
        
        buff[i]='\0';
        
        validateLabel(buff);
        
        return buff;
    }
    
    else
    {
        free(buff);
        return  NULL;
	}
}

char* 			extractIndexOperandLabel			(char* indexOperandValue)
{
	char* 		buff 						= "";
	int 		i 							= 0;
	
	buff = (char*)malloc(sizeof(char) * MAX_SIZE_OF_LABEL);
	errorIfMallocFailed(buff, "when trying to allocate memory for the label check.");
	
	while ((i < strlen(indexOperandValue)) && (indexOperandValue[i] != '['))
	{
		buff[i] = indexOperandValue[i];
	
		i++;		
	}
	
	if(strlen(buff) == 0)
	{
		free (buff);
		
		return  NULL;
	}
	
	buff[i] = '\0';

    return  buff;
	
}

int 			isStatementTypeDataStatement		(char* sentence)
{
    char*		result						= "";
    char* 		string 						= ".data";
    int 		i							= 1;
    
    result = strchr(sentence, '.');
    
    if(strlen(sentence) == 0)
    {
        return 0;
	}

    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t'))
        {
            if(result[i] != string[i])
            {
                return 0;
            }
            
            i++;
        }
        
        return 1;
    }
    
    else
    {
		return 0;
	}
}

int 			isStatementTypeDataStatementString	(char* sentence)
{
    char* 		result						= "";
    char* 		string 						= ".string";
    int 		i							= 1;
 
    result = strchr(sentence, '.');
    
    if(strlen(sentence) == 0)
    {
        return 0;
	}

    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t'))
        {
            if(result[i] != string[i])
            {
                return 0;
            }
            
            i++;
        }
        
        return 1;
    }
    
    else
    {
        return 0;
	}
}

int 			isStatementTypeDataStatementEntry	(char* sentence)
{
    char* 		result						= "";
    char* 		string 						= ".entry";
    int 		i							= 1;
    
    result = strchr(sentence, '.');
    
    if(strlen(sentence) == 0)
    {
        return 0;
	}
    
    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t'))
        {
            if(result[i] != string[i])
            {
                return 0;
            }
            
            i++;
        }
        
        return 1;
    }
    
    else
    {
        return 0;
	}
}

int 			isStatementTypeDataStatementExtern	(char* sentence)
{
    char* 		result							= "";
    char* 		string 							= ".extern";
    int 		i								= 1;
 
    result = strchr(sentence, '.');
 
    if(strlen(sentence) == 0)
    {
        return 0;
	}
    
    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t'))
        {
            if(result[i] != string[i])
            {
                return 0;
            }
            
            i++;
        }
        
        return 1;
    }
    
    else
    {
        return 0;
	}
}

int 			isStatementTypeDataStatementDefine	(char* sentence)
{
    char* 		result							= "";
    char* 		string 							= ".define";
    int 		i								= 1;
    
    result = strchr(sentence, '.');
    
    if(strlen(sentence) == 0)
    {
        return 0;
	}

    if(result)
    {
        while((result[i] != '\n' && result[i] != ' ' && result[i] != '\t'))
        {
            if(result[i] != string[i])
            {
                return 0;
            }
            
            i++;
        }
        
        return 1;
    }
    
    else
    {
        return 0;
	}
}

boolean 		isCommentStatementOrEmptyLine		(char *sentence)
{
    if(sentence[0] == ';' || sentence[0] == '\n')
    {
        return TRUE;
    }
    
    else
    {
        while(sentence && isspace(sentence[0]))
        {
            sentence++;
        }
        
        if(sentence[0] == ';' || sentence[0] == '\0')
        {
            return TRUE;
        }
        
        else
        {
            return FALSE;
		}
    }
}

COMMANDS 		getCommandOfStatement				(char* sentence)
{
    int 		labelLength 								= 0;
    int 		iterationIndex 								= 0;
    char* 		potentialCommandString 						= "";
    char 		commandString[DATA_CASE_CHARS_IN_USE] 		= "";
    char* 		label	 									= "";
    COMMANDS 	command;
    
    removeExtraSpaces(sentence);
    
    sentence =  trimwhitespace(sentence);
    
    label = extractLabel(sentence);


    /** figure label offset */
    if(label == NULL)
    {
        free(label);
        labelLength = 0;
	}
	
    else
    {
        /** length of the label, + 1 for the :, + for the space after the label, guaranteed to be single space due to removeExtraSpaces*/
        labelLength = strlen(label) + 2;
	}
	
    iterationIndex = 0;
    
    potentialCommandString = sentence + labelLength;
    
    while(iterationIndex < (strlen(potentialCommandString)) && iterationIndex < MAX_COMMAND_LENGTH)
    {
        commandString[iterationIndex] = potentialCommandString[iterationIndex];
     
        command = commandStringToEnum(commandString);

        /** if we already found the command return it */
        if(command != UNKNOWN_COMMAND)
        {
            free(label);
            return  command;
        }

        iterationIndex++;
    }
    free(label);
    return  UNKNOWN_COMMAND;
}

int 			isCommandStatement					(char *sentence)
{
    COMMANDS 	command						= getCommandOfStatement(sentence);

    if(command != UNKNOWN_COMMAND)
    {
        return 1;
    }

    return 0;

}

boolean			isnumber 							(char* str)
{
    char *ptr;
    strtol(str, &ptr, 10);
    if(strlen(ptr) != 0)
    {
        /*ERROR_PROGRAM(("expected a number, but got %s", ptr));*/
    
        return FALSE;
    }
	
	return TRUE;
}

boolean			check_if_number						(char num)
{
	if (!(num >= NUMBER_ZERO_ASCII_CODE && num <= NUMBER_NINE_ASCII_CODE))
		{
			return FALSE;
		}
	
	return TRUE;
}
