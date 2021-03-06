#include "List.h"

void 	list_new		(list *list, int elementSize)
{
    list->logicalLength = 0;
    
    list->elementSize = elementSize;
    
    list->head = list->tail = NULL;
}

void 	list_destroy	(list *list)
{

	
    listNode *current;
    
    while(list->head != NULL)
    {
        current = list->head;
        
        list->head = current->next;

        free(current->data);
        free(current);
    }
}

void 	list_append		(list *list, char *element)
{
    listNode* node = malloc(sizeof(listNode));
    errorIfMallocFailed(node, "While trying to allocate new node.");
    
    node->data = (char *) malloc(sizeof(MAX_LINE_SIZE));
    errorIfMallocFailed(node->data, "While trying to allocate data for a new node.");
    
    node->next = NULL;

    strcpy(node->data, element);

    if(list->logicalLength == 0)
    {
        list->head = list->tail = node;
    }
    
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    list->logicalLength++;
}

int 	list_size		(list *list)
{
    return list->logicalLength;
}
