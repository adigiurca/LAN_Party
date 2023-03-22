
#ifndef LAN_PARTY_FUNCTIONS_H
#define LAN_PARTY_FUNCTIONS_H

#endif //LAN_PARTY_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
}PLAYER;

typedef struct Node {
    PLAYER player_info;
    struct Node *next;
}NODE;

void add_at_beginning(NODE**, PLAYER);

