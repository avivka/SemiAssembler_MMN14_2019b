#include "TextUtils.h"

int 		isContainsComma			(char *input)
{
    return isContainsChar(input, ',');
}

int 		isContainsChar			(char *input, char charToTest)
{
    int 		i				= 0;
    
    for(i = 0 ; i < strlen(input) ; i++)
    {
        if (input[i] == charToTest)
        {
            return  1;
		}
    }
    
    return  0;
}

int 		isWordEndsWithChar		(char *word, char charToTest)
{
    if (word [strlen(word) - 1] == charToTest)
    {
        return 1;
    }
    
    return  0;
}

char 		getLastChar				(char *word)
{
    return  word[strlen(word) - 1];
}

int 		isWordStartsWithChar	(char *word, char charToTest)
{
    if (word [0] == charToTest)
    {
        return 1;
    }
    
    return  0;
}

char* 		trimwhitespace			(char *str)
{
    char* 		end					= "";

    /** Trim leading space */
    while(isspace((unsigned char)*str))
    {
		str++;
	}

    if(*str == 0)  /** All spaces? */
    {
        return str;
	}

    /** Trim trailing space */
    end = str + strlen(str) - 1;
    
    while(end > str && isspace((unsigned char)*end))
    {
		end--;
	}

    /**  Write new null terminator character */
    end[1] = '\0';

    return str;
}

char* 		substringFromTo			(char* string, int from, int to) 
{
    char* 		newString			= "";
    
    /** get enough memory for the new string, including +1 for the string terminator */
    newString = (char*) malloc(sizeof(char *) * strlen(string));
    errorIfMallocFailed(newString, "While trying to allocate memory for a new string.");
  
    memset(newString, '\0', sizeof(char *) * strlen(string));
    
    strncpy(newString, string + from, to - from);
    
    return newString;
}

void 		removeExtraSpaces		(char* str)
{
    int 		i					= 0;
    int			x					= 0;
    
    for(; str[i]; ++i)
    {
        if(!isspace(str[i]) || (i > 0 && !isspace(str[i-1])))
        {
            str[x++] = str[i];
		}
	}
	
    str[x] = '\0';
}

boolean 	isCharsEqual			(char c, char toCompare)
{
    if(c == toCompare)
    {
        return  TRUE;
	}
	
    return  FALSE;
}

void 		validateStringIsNumber	(char *string)
{
    char* 	ptr						= "";
    
    strtol(string, &ptr, 10);
    
    if (strlen(ptr) != 0)
    {
        ERROR_PROGRAM(("expected a number, but got %s", ptr));
    }
}

char* 		concat					(const char *s1, const char *s2)
{
    char* 	result					= "";
    
    result = malloc(strlen(s1) + strlen(s2) + 1); /** +1 for the null-terminator */
    errorIfMallocFailed(result, "for a new string using concat");
    
    strcpy(result, s1);
    
    strcat(result, s2);
    
    return result;
}

char*		is_extention_exists	    (char* s1, char* s2)
{
    char* 	str 					= "";
    char* 	cutExtention 			= "";

    str = strstr(s1, s2); /** if exists - return the pointer to the second string in the first one*/

    if ((str != NULL) && (strcmp (str, s2) == 0))
    {		
        cutExtention = substringFromTo(s1, 0, strlen(s1) - 3);
    }
    
    else
    {
		/** means that the extention already exists in s1*/

		
		return s1;
	}
	
	return cutExtention;
}
