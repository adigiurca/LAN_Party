
#include "functions.h"

void add_at_beginning(NODE **head, PLAYER v)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->player_info = v;
    newNode->next = *head;
    *head = newNode;
}
